#include "ImageProcessor.h"
#include "Kernel.h"

int main() {

    Image<Channel::RGB> image;
    std::string outPath = "../media/output/"; // set the output path

    try {
        ImageProcessor::load(image, "../media/input/lena.ppm");
        ImageProcessor::applyKernel(image, edgeDetect[0]);
        ImageProcessor::saveAs(image, outPath + "lena_edge-detect");

    } catch (const std::exception &e) {
        std::cerr << "An error occurred." << std::endl;
    }

    return 0;
}