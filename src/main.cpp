#include "ImageProcessor.h"
#include "Kernel.h"

int main() {

    Image<Channel::RGB> image;

    try {
        ImageProcessor::load(image, "../media/input/lena.ppm");
        ImageProcessor::applyKernel(image, edgeDetect[1]);
        ImageProcessor::saveAs(image, "../media/output/", "lena_edge-detect1");

    } catch (const std::exception &e) {
        std::cerr << "An error occurred." << std::endl;
    }

    return 0;
}