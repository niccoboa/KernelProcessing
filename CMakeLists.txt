cmake_minimum_required(VERSION 3.10)
project(KernelProcessing)

set(CMAKE_CXX_STANDARD 11)

file(COPY images DESTINATION ${CMAKE_BINARY_DIR})

# file(CREATE_LINK "${PROJECT_SOURCE_DIR}/images"
#        "${CMAKE_CURRENT_BINARY_DIR}/images" SYMBOLIC)

add_executable(KernelProcessing main.cpp
        ImageBase.h
        Image.h
        Kernels.h
        Channel.h
        ImageProcessor.h
        ImageProcessor.cpp
        )


file(GLOB PGM_FILES "${CMAKE_BINARY_DIR}/images/*.pgm")
file(GLOB PPM_FILES "${CMAKE_BINARY_DIR}/images/*.ppm")

#add_custom_command(
#        TARGET KernelProcessing POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${PGM_FILES}
#        ${PPM_FILES}
#        ${PROJECT_SOURCE_DIR}/images/
#)
