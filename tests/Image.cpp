#include "gtest/gtest.h"
#include "../src/Image.h"

// test getter and setter methods for image attributes
TEST(ImageTest, testGetters) {
    Image<Channel::RGB> image;
    image.setWidth(10);
    image.setHeight(20);
    ASSERT_EQ(image.getWidth(), 10);
    ASSERT_EQ(image.getHeight(), 20);
}

// test data getter and setter methods
TEST(ImageTest, testData) {
    Image<Channel::RGB> image;
    std::vector<std::vector<unsigned char>> data = {{1, 2, 3}, {4, 5, 6}};
    image.setData(data);
    ASSERT_EQ(image.getData(), data);
}

// test pixel getter and setter methods
TEST(ImageTest, testPixel) {
    Image<Channel::RGB> image;
    std::vector<std::vector<unsigned char>> data = {{1, 2, 3}, {4, 5, 6}};
    image.setData(data);
    ASSERT_EQ(image.getPixel(0, 0, 0), 1);
    ASSERT_EQ(image.getPixel(0, 0, 1), 2);
    ASSERT_EQ(image.getPixel(0, 0, 2), 3);
    ASSERT_EQ(image.getPixel(0, 1, 0), 4);
    ASSERT_EQ(image.getPixel(0, 1, 1), 5);
    ASSERT_EQ(image.getPixel(0, 1, 2), 6);
    image.setPixel(0, 0, 0);
    image.setPixel(0, 0, 1);
    image.setPixel(0, 0, 2);
    image.setPixel(1, 0, 0);
    image.setPixel(1, 0, 1);
    image.setPixel(1, 0, 2);
    ASSERT_EQ(image.getPixel(0, 0, 0), 10);
    ASSERT_EQ(image.getPixel(0, 0, 1), 20);
    ASSERT_EQ(image.getPixel(0, 0, 2), 30);
    ASSERT_EQ(image.getPixel(0, 1, 0), 40);
    ASSERT_EQ(image.getPixel(0, 1, 1), 50);
    ASSERT_EQ(image.getPixel(0, 1, 2), 60);
}

// test clone method
TEST(ImageTest, testClone) {
    Image<Channel::RGB> image;
    std::vector<std::vector<unsigned char>> data = {{1, 2, 3}, {4, 5, 6}};
    image.setData(data);
    ImageBase* clonedImage = image.clone();
    ASSERT_EQ(clonedImage->getData(), data);
    delete clonedImage;
}

// test operator method
TEST(ImageTest, testOperator) {
    Image<Channel::RGB> image;
    std::vector<std::vector<unsigned char>> data = {{1, 2, 3}, {4, 5, 6}};
    image.setData(data);
    ASSERT_EQ(image(0, 0), 1);
    ASSERT_EQ(image(0, 1), 4);
}

