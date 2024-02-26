cmake_minimum_required(VERSION 3.10)
project(KernelProcessing)

set(CMAKE_CXX_STANDARD 11)

file(COPY media/input DESTINATION ${CMAKE_BINARY_DIR}) # copy images to build directory


add_executable(KernelProcessing main.cpp
        ImageBase.h
        Image.h
        Kernel.h
        Channel.h
        ImageProcessor.h
        ImageProcessor.cpp
        )


file(GLOB PGM_FILES "${CMAKE_BINARY_DIR}/media/*.pgm") # get all .pgm files
file(GLOB PPM_FILES "${CMAKE_BINARY_DIR}/images/*.ppm") # get all .ppm files
