#include <iostream>
#include <vector>

#include "Channel.h"
// #include "ImageBase.h"
#include "Image.h"
#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    Image<Channel::GRAY> image;

    ImageProcessor::load(image, "images/monaLisa.pgm");
    ImageProcessor::applyKernel(image, sharpen3x3);
    ImageProcessor::saveAs(image, "images/monaLisa_sharpened");

    return 0;
}


