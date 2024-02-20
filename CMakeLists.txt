cmake_minimum_required(VERSION 3.10)
project(KernelProcessing)

set(CMAKE_CXX_STANDARD 11)

file(COPY images DESTINATION ${CMAKE_BINARY_DIR})

add_executable(KernelProcessing main.cpp
        Image.h
        Channel.h
        ImageProcessor.h
        ImageBase.h
        ImageProcessor.cpp
        Kernels.h)