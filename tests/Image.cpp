#include "gtest/gtest.h"
#include "../src/Image.h"

// Tests for Image class (Load, Save, Getters, Setters)

// test getter and setter methods for image attributes
TEST(ImageTest, testGetters) {
    Image<int> image(3);
    image.setWidth(10);
    image.setHeight(20);
    image.setMaxValue(255);

    ASSERT_EQ(image.getWidth(), 10);
    ASSERT_EQ(image.getHeight(), 20);
    ASSERT_EQ(image.getMaxValue(), 255);
    ASSERT_EQ(image.getChannels(), 3);
}


// test clone method (used in applyKernel method)
TEST(ImageTest, testClone) {
    Image<int> image(3);
    image.setWidth(10);
    image.setHeight(20);
    image.setMaxValue(255);
    Image<int> newImage(image);
    ASSERT_EQ(newImage.getWidth(), 10);
    ASSERT_EQ(newImage.getHeight(), 20);
    ASSERT_EQ(newImage.getMaxValue(), 255);
    ASSERT_EQ(newImage.getChannels(), 3);
}

// test load method
TEST(ImageTest, testLoad) {
    Image<int> image(3);
    image.load("media/input/lena.ppm");
    ASSERT_EQ(image.getWidth(), 256);
    ASSERT_EQ(image.getHeight(), 256);
    ASSERT_EQ(image.getMaxValue(), 255);
    ASSERT_EQ(image.getChannels(), 3);
}

// test saveImage method
TEST(ImageTest, testSaveImage) {
    Image<int> image(3);
    image.load("media/input/lena.ppm");
    image.saveImage("media/output/lena-test");
    Image<int> newImage(3);
    newImage.load("media/output/lena-test.ppm");
    ASSERT_EQ(newImage.getWidth(), 256);
    ASSERT_EQ(newImage.getHeight(), 256);
    ASSERT_EQ(newImage.getMaxValue(), 255);
    ASSERT_EQ(newImage.getChannels(), 3);
}

// test getPixel method
TEST(ImageTest, testGetPixel) {
    Image<int> image(1);
    image.load("media/input/dragon.pgm");
    ASSERT_EQ(image.getPixel(0, 0, 0), 255);

}

// test setPixel method
TEST(ImageTest, testSetPixel) {
    Image<int> image(1);
    image.load("media/input/dragon.pgm");
    image.setPixel(0, 0, 0);
    ASSERT_EQ(image.getPixel(0, 0, 0), 0);
}

