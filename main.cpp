#include "ImageProcessor.h"
#include "Kernel.h"

int main() {

    Image<Channel::GRAY> image;

    try {
        ImageProcessor::load(image, "monaLisa.pgm");
        ImageProcessor::applyKernel(image, edgeDetect[1]);
        ImageProcessor::saveAs(image, "monaLisa_edge");

    } catch (const std::exception &e) {
        std::cerr << "An error occurred. "<< std::endl;
    }

    return 0;
}