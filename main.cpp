#include <iostream>
#include <vector>
#include <fstream>

#include "Channel.h"
#include "Image.h"
#include "ImageProcessor.h"

int main() {

    
    ImageProcessor<Channel::RGB> processor;


    if (!processor.load("images/buck.ppm")) {
        std::cerr << "Errore durante il caricamento dell'immagine" << std::endl;
        return 1;
    }
    // std::vector<std::vector<float>> kernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    std::vector<std::vector<float>> kernelBlur = {
            {1.0f / 9, 1.0f / 9, 1.0f / 9},
            {1.0f / 9, 1.0f / 9, 1.0f / 9},
            {1.0f / 9, 1.0f / 9, 1.0f / 9}
    };

    std::vector<std::vector<float>> kernel = {
            {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
            {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
            {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
            {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
            {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25}
    };


    processor.applyKernel(kernel);

    // Salvataggio dell'immagine risultante
    if (!processor.saveAs("../images/output")) {
        std::cerr << "Errore durante il salvataggio dell'immagine" << std::endl;
        return 1;
    }

    std::cout << "Immagine salvata correttamente" << std::endl;

    return 0;
}


