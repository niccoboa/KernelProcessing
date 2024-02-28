#include "gtest/gtest.h"
#include "../src/ImageBase.h"
#include "../src/Image.h"

// test that I can create an image object with inherited methods
TEST(ImageBaseTest, testImageBase) {
    Image<Channel::RGB> image;
    image.setWidth(10);
    image.setHeight(20);
    ASSERT_EQ(image.getWidth(), 10);
    ASSERT_EQ(image.getHeight(), 20);
    ASSERT_EQ(image.getChannels(), Channel::RGB);
}

