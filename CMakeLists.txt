cmake_minimum_required(VERSION 3.23)
project(radicalfield LANGUAGES CXX)

add_library(radicalfield INTERFACE)

target_compile_features(radicalfield INTERFACE cxx_std_20)
target_sources(radicalfield INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        include/radicalfield/QuadraticElement2.hpp
        include/radicalfield/QuadraticElement235.hpp
)
