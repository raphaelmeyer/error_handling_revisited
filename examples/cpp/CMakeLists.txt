cmake_minimum_required(VERSION 3.14)

add_executable(example1 example1.cc)

target_compile_features(example1 PRIVATE cxx_std_17)

