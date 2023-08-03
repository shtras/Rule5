cmake_minimum_required(VERSION 3.15)

project(rule5)

add_library(mfc_compiler_flags INTERFACE)
target_compile_features(mfc_compiler_flags INTERFACE cxx_std_20)

add_executable(rule5 main.cpp)
target_link_libraries(rule5 PRIVATE mfc_compiler_flags)
