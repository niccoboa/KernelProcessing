#include "gtest/gtest.h"
#include "../src/ImageProcessor.h"
#include "../src/Kernel.h"

// Test if the loaded image has the correct attributes (width, height, channels)
TEST(ImageProcessor, load_attributes) {
    Image<Channel::GRAY> image;
    ImageProcessor::load(image, "../../media/input/monaLisa.pgm");
    ASSERT_EQ(image.getWidth(), 250);
    ASSERT_EQ(image.getHeight(), 360);
    ASSERT_EQ(image.getChannels(), Channel::GRAY);
}

// exception is thrown when the file is not found
TEST(ImageProcessor, load_exception) {
    Image<Channel::GRAY> image;
    ASSERT_THROW(ImageProcessor::load(image, "nonexistent.pgm"), std::runtime_error);
}

// Test if the saved image has the correct attributes (width, height, channels)
TEST(ImageProcessor, saveAs_attributes) {
    Image<Channel::GRAY> image;
    ImageProcessor::load(image, "../../media/input/monaLisa.pgm");
    ImageProcessor::saveAs(image, "../../media/output/monaLisa_test");
    Image<Channel::GRAY> savedImage;
    ImageProcessor::load(savedImage, "../../media/output/monaLisa_test.pgm");
    ASSERT_EQ(savedImage.getWidth(), 250);
    ASSERT_EQ(savedImage.getHeight(), 360);
    ASSERT_EQ(savedImage.getChannels(), Channel::GRAY);
}