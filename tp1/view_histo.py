import matplotlib.pyplot as plt

def plot_histogram_from_file(filename, label=None):
    # Lecture des données
    x = []
    y = []
    with open(filename, 'r') as f:
        for line in f:
            values = line.split()
            x.append(int(values[0]))
            y.append(int(values[1]))

    # Tracer l'histogramme
    plt.bar(x, y, width=1, align='center', label=label, alpha=0.5)

def main():
    plot_histogram_from_file('histo.dat', "Image originale")
    plot_histogram_from_file('histo1.dat', "Image chiffrée")
    
    plt.title("Histogrammes de l'image originale et chiffrée")
    plt.xlabel("Valeur des pixels")
    plt.ylabel("Nombre de pixels")
    plt.legend(loc='upper right')
    plt.show()

if __name__ == '__main__':
    main()
