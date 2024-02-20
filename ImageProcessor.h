//
// Created by niccoboa on 19/02/2024.
//

#ifndef KERNELPROCESSING_IMAGEPROCESSOR_H
#define KERNELPROCESSING_IMAGEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Image.h"
#include "Channel.h"

//template<Channel C>
class ImageProcessor {

public:

    // Metodi per leggere/scrivere immagini e applicare il kernel

    bool load(ImageBase& image, const std::string& filename); // Carica un'immagine da un file

    bool save(ImageBase& image) const; // Salva l'immagine
    bool saveAs(ImageBase& image, const std::string& filename) const; // Salva l'immagine con un nome specifico
    bool savePGM(ImageBase& image, const std::string& filename) const; // Salva l'immagine in formato PGM
    bool savePPM(ImageBase& image, const std::string& filename) const; // Salva l'immagine in formato PPM

    void applyKernel(ImageBase& image, const std::vector<std::vector<float>>& kernel); // Applica un kernel all'immagine
};


/*bool ImageProcessor::load(ImageBase& image, const std::string &filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Impossibile aprire il file " << filename << std::endl;
        return false;
    }

    Channel c = image.getChannels();

    std::cout << "File " << filename << " aperto correttamente" << std::endl;
    std::string magicNumber;
    int width, height, maxValue;
    inputFile >> magicNumber >> width >> height >> maxValue;
    if (magicNumber != "P2" && magicNumber != "P3") {
        std::cerr << "Il file non è in formato PGM o PPM" << std::endl;
        return false;
    }

    std::vector<std::vector<int>> pixelData(height, std::vector<int>(width * static_cast<int>(c)));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width * static_cast<int>(c); ++x) {
            inputFile >> pixelData[y][x];
        }
    }

    inputFile.close();
    // Impostare i dati dell'immagine
    // image = Image<C>(width, height);

    //Image<C>& concreteImage = dynamic_cast<Image<C>&>(image);
    image.setWidth(width);
    image.setHeight(height);

    std::cout << "Larghezza: " << width << " Altezza: " << height << std::endl;

    /*for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int ch = 0; ch < static_cast<int>(c); ++ch) {
                image.setPixel(x, y, ch, pixelData[y][x * static_cast<int>(c) + ch]);
            }
        }
    }*/
/*
    image.setData(pixelData);
    std::cout << "Ok" << std::endl;
    return true;

}*/

#endif //KERNELPROCESSING_IMAGEPROCESSOR_H