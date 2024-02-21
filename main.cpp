#include "Channel.h"
#include "Image.h"
#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    Image<Channel::RGB> image;

    ImageProcessor::load(image, "images/newton.ppm");
    ImageProcessor::applyKernel(image, edgeDetect3x3);
    ImageProcessor::saveAs(image, "images/newton_edge");

    return 0;
}


