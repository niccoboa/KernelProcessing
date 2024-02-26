#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    Image<Channel::GRAY> image;                                          // 1) Set channles

    ImageProcessor::load(image, "images/lena.pgm");         // 2) Load image
    ImageProcessor::applyKernel(image, edgeDetect3x3[3]);              //  3) Apply kernel
    ImageProcessor::saveAs(image, "images/lena_new");      // 4) Save image

    return 0;
}