#include "gtest/gtest.h"
#include "../src/KernelProduct.h"

// test that the sum of the blur kernel is 1
TEST(Kernel, sumBlur) {
    float sum = 0;
    for (auto &row : blur[0]) {
        for (auto &value : row) {
            sum += value;
        }
    }
    ASSERT_EQ(sum, 1);
}

// test that the sum of the edgeDetect kernel is 0
TEST(Kernel, sumEdgeDetect) {
    float sum = 0;
    for (auto &row : edgeDetect[0]) {
        for (auto &value : row) {
            sum += value;
        }
    }
    ASSERT_EQ(sum, 0);
}

