#include "../common/image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

unsigned char GetPixel(unsigned char* img, int x, int y, int w, int h, int c) {
    return img[(y * w + x) * 3 + c];
}

int ApplyFilter(unsigned char* img, int x, int y, int w, int h, float filter[], int channel) {
    float value = 0.0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            value += GetPixel(img, x + j, y + i, w, h, channel) * filter[(i+1)*3 + (j+1)];
        }
    }

    //fonction d'activation
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
                filteredImage[((y-1) * newWidth + (x-1)) * 3 + c] = ApplyFilter(img, x, y, width, height, filter, c);
            }
        }
    }
    return filteredImage;
}

int main(int argc, char **argv) {
    char cNomImg[250];
    if (argc != 2) {
        printf("Usage: name.ppm \n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImg);

    const int width = 32;
    const int height = 32;

    unsigned char* ppm = readBinary("./cifar-10-batches-bin/data_batch_1.bin",0);

    const int filterSize = 3;
  //  unsigned char* filteredImage = convolution(ppm, FilterNet, width, height,filterSize);

  //  ecrire_image_ppm(cNomImg, filteredImage,  width - (filterSize - 1), height - (filterSize - 1)); 

    ecrire_image_ppm(cNomImg, ppm,  width , height); 

    free(ppm);
   // free(filteredImage);

    return 0;
}
