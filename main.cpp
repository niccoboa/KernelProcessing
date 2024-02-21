#include <iostream>
#include <vector>

#include "Channel.h"
// #include "ImageBase.h"
#include "Image.h"
#include "ImageProcessor.h"
#include "Kernels.h"

int main() {

    Image<Channel::RGB> image;

    ImageProcessor::load(image, "images/under.ppm");
    ImageProcessor::applyKernel(image, edgeDetect3x3);
    ImageProcessor::saveAs(image, "images/under_edge_detect3x3mezzi");

    return 0;
}


