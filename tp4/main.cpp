#include "../common/image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>


int imageIndices[] = {0, 8 ,35};

float FilterGauss[9] = 
{
    1.0/16.0 , 2.0/16.0, 1.0/16.0,
    2.0/16.0 , 4.0/16.0, 2.0/16.0,
    1.0/16.0, 2.0/16.0, 1.0/16.0
};

float FilterNet[9] = {
    0 , -1 , 0 ,
    -1 , 5 , -1,
    0, -1, 0
};

float FilterBoxBlur[9] = {
    1.0/9.0 , 1.0/9.0, 1.0/9.0,
    1.0/9.0 , 1.0/9.0 , 1.0/9.0,
    1.0/9.0, 1/9.0, 1.0/9.0
};

float CustomFilter1[9] = {
    1 , -1 , 1 ,
    -1 , 5 , -1,
    1, -1, 1
};

float CustomFilter2[9] = 
{
    1.0/4.0 , 2.0/4.0, 1.0/4.0,
    2.0/4.0 , 4.0/4.0, 2.0/4.0,
    1.0/4.0, 2.0/4.0, 1.0/4.0
};

const char* FilterNames[] = {
    "Gauss",
    "Net",
    "BoxBlur",
    "Custom1",
    "Custom2"
};

float* Filters[] = {
    FilterGauss,
    FilterNet,
    FilterBoxBlur,
    CustomFilter1,
    CustomFilter2
};

unsigned char* readBinary(const char* path, int id)
{
    const int imageWidth = 32;
    const int imageHeight = 32;
    const int channels = 3;
    unsigned char *out;
    allocation_tableau(out, unsigned char, imageWidth*imageHeight*channels);

    // Open the binary file for reading
    std::ifstream file(path, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open the binary file." << std::endl;
        return NULL;
    }

    const int imageOffset = id * (1 + imageWidth * imageHeight * channels);
    file.seekg(imageOffset);

    uint8_t label;
    std::vector<uint8_t> pixelData(imageWidth * imageHeight * channels);

    file.read(reinterpret_cast<char*>(&label), sizeof(label));
    file.read(reinterpret_cast<char*>(pixelData.data()), pixelData.size());

    for (int i = 0; i < imageHeight; ++i) {
        for (int j = 0; j < imageWidth; ++j) {
            for (int c = 0; c < channels; ++c) {
                int index = c * imageWidth * imageHeight + i * imageWidth + j;
                out[(i * imageWidth + j) * channels + c] = pixelData[index];
            }
        }
    }
    return out;
}

unsigned char GetPixel(OCTET* img, int x, int y, int w, int c) {
     return img[x * w + y + 3 + c];
}

int ApplyFilter(OCTET* img, int x, int y, int w, float filter[], int channel) {
   float value = 0.0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            value += GetPixel(img, x + i*3, y + j*3, w, channel) * filter[(i+1)*3 + (j+1)];
        }
    }

    if (value < 0.0) value = 0.0;
    if (value > 255.0) value = 255.0;

    return (int)value;
}

unsigned char* convolution(unsigned char* img, float filter[], int width, int height,int filterSize) {
    
    const int newWidth = width - (filterSize - 1);
    const int newHeight = height - (filterSize - 1);
    unsigned char* filteredImage;
    allocation_tableau(filteredImage, unsigned char, newWidth*newHeight*3);
    for(int y = 1; y < height - 1; y++) {
        for(int x = 1; x < width - 1; x++) {
            for(int c = 0; c < 3; c++) {
                filteredImage[((y-1) * newWidth + (x-1)) * 3 + c] = ApplyFilter(img, x, y, width , filter, c);
            }
        }
    }
    return filteredImage;
}

unsigned char* pooling(unsigned char* img, int width, int height) {
    const int newWidth = width / 2;
    const int newHeight = height / 2;
    unsigned char* pooledImage;
    allocation_tableau(pooledImage, unsigned char, newWidth*newHeight*3);

    for(int y = 0; y < newHeight; y++) {
        for(int x = 0; x < newWidth; x++) {
            for(int c = 0; c < 3; c++) {
                unsigned char maxPixel = 0;
                for(int dy = 0; dy < 2; dy++) {
                    for(int dx = 0; dx < 2; dx++) {
                        unsigned char pixel = GetPixel(img, x*2 + dx, y*2 + dy, width, c);
                        maxPixel = std::max(maxPixel, pixel);
                    }
                }
                pooledImage[(y * newWidth + x) * 3 + c] = maxPixel;
            }
        }
    }
    return pooledImage;
}

constexpr size_t HARD_CODED_SIZE = 6*6*3;

unsigned char* flatten(const std::vector<unsigned char*>& vec) {
    size_t totalSize = HARD_CODED_SIZE * vec.size();
    
    unsigned char* result = new unsigned char[totalSize];

    size_t index = 0;
    for (const auto& ptr : vec) {
        std::copy(ptr, ptr + HARD_CODED_SIZE, result + index);
        index += HARD_CODED_SIZE;
    }

    return result;
}



std::map<int, std::vector<unsigned char*>> processedImagesMap;

int main(int argc, char **argv) {
    const int width = 32;
    const int height = 32;

    const int filterSize = 3;

    system("mkdir res");

    // on fait notre feature extraction et on stocke les images résultante pour chaque image dans une map
    for (int imgIndex : imageIndices) {
        unsigned char* ppm = readBinary("./cifar-10-batches-bin/data_batch_1.bin", imgIndex);

        processedImagesMap[imgIndex] = std::vector<unsigned char*>();

        for (int filterIndex = 0; filterIndex < 5; filterIndex++) {
            unsigned char* filteredImage = convolution(ppm, Filters[filterIndex], width, height, filterSize);
            unsigned char* firstPooledImage = pooling(filteredImage, width - (filterSize - 1), height - (filterSize - 1));

            for (int secondFilterIndex = 0; secondFilterIndex < 5; secondFilterIndex++) {
                unsigned char* secondFilteredImage = convolution(firstPooledImage, Filters[secondFilterIndex], (width - (filterSize - 1))/2, (height - (filterSize - 1))/2, filterSize);

                unsigned char* secondPooledImage = pooling(secondFilteredImage, (width - (filterSize - 1))/2 - (filterSize - 1), (height - (filterSize - 1))/2 - (filterSize - 1));
                
                processedImagesMap[imgIndex].push_back(secondPooledImage);

                free(secondFilteredImage);
            }

            free(filteredImage);
            free(firstPooledImage);
        }
        free(ppm);
    }

    int caractVectorSize = 6*6*3*5*5; 


    int width2 = sqrt(caractVectorSize / 3);  
    int height2 = width2; 

    for (auto& pair : processedImagesMap) {
       char filename[100]; 
        sprintf(filename, "res/vector_%d.ppm", pair.first);
        ecrire_image_ppm(filename, flatten(pair.second), width2, height2); 

         for (unsigned char* image : pair.second) {
            free(image);
        }
    }


    return 0;
}