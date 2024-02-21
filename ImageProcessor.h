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

    static bool load(ImageBase& image, const std::string& filename); // Carica un'immagine da un file

    __attribute__((unused)) static bool save(ImageBase& image); // Salva l'immagine con il nome di default
    static bool saveAs(ImageBase& image, const std::string& filename) ; // Salva l'immagine con un nome specifico
    static bool saveImage(ImageBase& image, const std::string& filename, const std::string& magic) ; // Salva l'immagine in formato PPM

    static void applyKernel(ImageBase& image, const std::vector<std::vector<float>>& kernel); // Applica un kernel all'immagine
};


#endif //KERNELPROCESSING_IMAGEPROCESSOR_H