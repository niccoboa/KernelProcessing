#include <iostream>
#include <vector>

#include "Channel.h"
// #include "ImageBase.h"
#include "Image.h"
#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    Image<Channel::GRAY> image;
    ImageProcessor processor;

    processor.load(image, "images/mona_lisa.pgm");

    processor.applyKernel(image, blur5x5);

    processor.saveAs(image, "../images/output");

    return 0;
}


