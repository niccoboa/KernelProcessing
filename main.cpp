#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    Image<Channel::RGB> image;                                            // 1) Set channles

    ImageProcessor::load(image, "images/under.ppm");         // 2) Load image
    ImageProcessor::applyKernel(image, blur[1]);                 //  3) Apply kernel
    ImageProcessor::saveAs(image, "images/under_blur");   // 4) Save image

    return 0;
}