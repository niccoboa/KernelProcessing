#include <iostream>
#include <vector>

#include "Channel.h"
// #include "ImageBase.h"
#include "Image.h"
#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    Image<Channel::RGB> image;
    ImageProcessor processor;

    processor.load(image, "images/buck.ppm");

    processor.applyKernel(image, blur5x5);

    // Salvataggio dell'immagine risultante
    if (!processor.saveAs(image, "../images/output")) {
        std::cerr << "Errore durante il salvataggio dell'immagine" << std::endl;
        return 1;
    }

    std::cout << "Immagine salvata correttamente" << std::endl;

    return 0;
}


