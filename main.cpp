#include "Channel.h"
#include "Image.h"
#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    Image<Channel::GRAY> image;                                            // 1) Set channles

    ImageProcessor::load(image, "images/monaLisa.pgm");         // 2) Load image
    ImageProcessor::applyKernel(image, blur5x5);                 //  3) Apply kernel
    ImageProcessor::saveAs(image, "images/monalisa_blurred");   // 4) Save image

    return 0;
}


