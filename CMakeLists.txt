cmake_minimum_required(VERSION 4.0.2)

project("asteroids")

set(TARGET_NAME "app")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

file(GLOB SRC_FILES "src/*.cpp")
add_executable(${TARGET_NAME} ${SRC_FILES})

target_include_directories(${TARGET_NAME} PUBLIC "include")
target_link_libraries(${TARGET_NAME} SDL3 SDL3_image)
target_compile_options(${TARGET_NAME} PRIVATE -Wall)
