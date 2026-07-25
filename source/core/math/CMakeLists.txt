cmake_minimum_required(VERSION 3.5.0)

project(myMath VERSION 0.0.1)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RESOURCE_FILES
mymath.cpp 
ProcessGenerationNoice.cpp
simplex.cpp
)


add_library(Math SHARED ${RESOURCE_FILES})
set_target_properties(Math PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
target_include_directories(Math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})