cmake_minimum_required(VERSION 3.23)
project(cowboys_vs_ninjas)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES
        Demo.cpp
        Test.cpp
        TestCounter.cpp
        sources/*.cpp
        )

add_executable(cowboys_vs_ninjas ${SOURCE_FILES})

