#include "gtest/gtest.h"
#include "../src/KernelProduct.h"
#include "../src/BlurCreator.h"
#include "../src/Image.h"


TEST(ApplyKernel, createKernel) {
    ApplyKernel<int> factory; // Concrete Creator
    std::unique_ptr<KernelProduct<int>> kernel = factory.createKernel(7); // Concrete Product
    std::vector<std::vector<float>> expectedKernel(7, std::vector<float>(7, 1.0f / 49.0f));
    EXPECT_EQ(kernel->getKernel(), expectedKernel);
}

// test applyKernel method (it does not modify the original image resolution and max value)
TEST(ApplyKernel, applyKernel) {
    Image<int> image(3); // create image with c channels
    image.load("media/input/lena.ppm"); // load image

    ApplyKernel<int> factory; // Concrete Creator
    std::unique_ptr<KernelProduct<int>> kernel = factory.createKernel(7); // Concrete Product
    kernel->applyKernel(image); // apply kernel to image

    image.saveImage("media/output/lena-blur"); // save image

    Image<int> newImage(3);
    newImage.load("media/output/lena-blur.ppm");
    EXPECT_EQ(newImage.getWidth(), 512);
    EXPECT_EQ(newImage.getHeight(), 512);
    EXPECT_EQ(newImage.getMaxValue(), 255);
    EXPECT_EQ(newImage.getChannels(), 3);
    EXPECT_EQ(newImage.getPixel(0, 0, 0), 226);
}