#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    // 1) Set Channels
    Image<Channel::GRAY> image;

    // 2) Load Image
    ImageProcessor::load(image, "images/lennanew.pgm");

    // 3) Apply kernel
    ImageProcessor::applyKernel(image, sharpen[1]);

    // 4) Save Image
    ImageProcessor::saveAs(image, "images/lena_sharpened");

    return 0;
}