cmake_minimum_required(VERSION 3.10)
project(KernelProcessing)

set(CMAKE_CXX_STANDARD 11)

file(COPY images DESTINATION ${CMAKE_BINARY_DIR})

add_executable(KernelProcessing main.cpp
        ImageBase.h
        Image.h
        Kernels.h
        Channel.h
        ImageProcessor.h
        ImageProcessor.cpp)