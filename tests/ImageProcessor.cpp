#include "gtest/gtest.h"
#include "../src/ImageProcessor.h"
#include "../src/Kernel.h"

// exception is thrown when the file is not found
TEST(ImageProcessor, load_exception) {
    Image<Channel::GRAY> image;
    ASSERT_THROW(ImageProcessor::load(image, "nonexistent.pgm"), std::runtime_error);
}

// Test if the loaded and the saved images have the correct attributes (width, height, channels)
TEST(ImageProcessor, saveAs_attributes) {
    Image<Channel::GRAY> image;
    ImageProcessor::load(image, "../../media/input/monaLisa.pgm");
    ASSERT_EQ(image.getWidth(), 250);
    ASSERT_EQ(image.getHeight(), 360);
    ASSERT_EQ(image.getChannels(), Channel::GRAY);
    ASSERT_EQ(image.getMaxValue(), 255);
    ImageProcessor::saveAs(image, "../../media/output/monaLisa_test");
    Image<Channel::GRAY> savedImage;
    ImageProcessor::load(savedImage, "../../media/output/monaLisa_test.pgm");
    ASSERT_EQ(savedImage.getWidth(), 250);
    ASSERT_EQ(savedImage.getHeight(), 360);
    ASSERT_EQ(savedImage.getChannels(), Channel::GRAY);
}

// test channels of PPM image
TEST(ImageProcessor, channels_ppm) {
    Image<Channel::RGB> image;
    ImageProcessor::load(image, "../../media/input/lena.ppm");
    ASSERT_EQ(image.getChannels(), Channel::RGB);
}


// Test with empty kernel, it raises an exception
TEST(ImageProcessor, applyKernel_emptyKernel) {
    Image<Channel::GRAY> image;
    ImageProcessor::load(image, "../../media/input/monaLisa.pgm");
    std::vector<std::vector<float>> kernel;
    ASSERT_THROW(ImageProcessor::applyKernel(image, kernel), std::runtime_error);
}

// Test all the kernels (kernel mashup)
TEST(ImageProcessor, applyKernel_kernels) {
    Image<Channel::GRAY> image;
    ImageProcessor::load(image, "../../media/input/monaLisa.pgm");
    std::vector<std::vector<float>> kernel;
    ImageProcessor::applyKernel(image, identity);
    ImageProcessor::applyKernel(image, blur[0]);
    ImageProcessor::applyKernel(image, blur[1]);
    ImageProcessor::applyKernel(image, customSquaredBlur(3));
    ImageProcessor::applyKernel(image, edgeDetect[0]);
    ImageProcessor::applyKernel(image, edgeDetect[1]);
    ImageProcessor::applyKernel(image, sharpen[0]);
    ImageProcessor::applyKernel(image, sharpen[1]);
    ImageProcessor::applyKernel(image, sobel[0]);
    ImageProcessor::applyKernel(image, sobel[1]);

    ImageProcessor::saveAs(image, "../../media/output/monaLisa_mashup");
}

// test identity kernel
TEST(ImageProcessor, applyKernel_identity) {
    Image<Channel::GRAY> image;
    ImageProcessor::load(image, "../../media/input/monaLisa.pgm");
    ImageProcessor::applyKernel(image, identity);
    ImageProcessor::saveAs(image, "../../media/output/monaLisa_identity");
}

// test blur kernel function
TEST(ImageProcessor, applyKernel_blur) {
    Image<Channel::GRAY> image;
    ImageProcessor::load(image, "../../media/input/monaLisa.pgm");
    ImageProcessor::applyKernel(image, customSquaredBlur(7)); // 7x7 blur
    ImageProcessor::saveAs(image, "../../media/output/monaLisa_blurfunction");
}

// test edge detection kernel for ppm image
TEST(ImageProcessor, applyKernel_edgeDetect) {
    Image<Channel::RGB> image;
    ImageProcessor::load(image, "../../media/input/lena.ppm");
    ImageProcessor::applyKernel(image, edgeDetect[1]);
    ImageProcessor::saveAs(image, "../../media/output/lena_edgePPM");
}