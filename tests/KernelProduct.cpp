#include "gtest/gtest.h"
#include "../src/KernelProduct.h"

// test the getter method for the kernel
TEST(KernelProductTest, testGetKernel) {
    std::vector<std::vector<float>> kernel = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    KernelProduct<int> kp(kernel);
    ASSERT_EQ(kp.getKernel(), kernel);
}
