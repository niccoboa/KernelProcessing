#include "ImageProcessor.h"
#include "Kernel.h"

int main() {

    Image<Channel::GRAY> image;
    std::string outPath = "../media/output/";

    try {
        ImageProcessor::load(image, "../media/input/monaLisa.pgm");
        ImageProcessor::applyKernel(image, edgeDetect[1]);
        ImageProcessor::saveAs(image, outPath + "monaLisa_edgeDetected");

    } catch (const std::exception &e) {
        std::cerr << "An error occurred." << std::endl;
    }

    return 0;
}