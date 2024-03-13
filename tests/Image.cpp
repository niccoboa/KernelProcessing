#include "gtest/gtest.h"
#include "../src/Image.h"

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


// test clone method
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