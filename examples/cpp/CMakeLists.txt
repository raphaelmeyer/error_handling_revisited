cmake_minimum_required(VERSION 3.14)

project(cpp_examples)

add_library(settings INTERFACE)
target_compile_options(settings INTERFACE "-Wall" "-Werror" "-std=c++20")

function(add_example NAME)
  set(SOURCE "${NAME}.cc")
  add_executable(${NAME} ${SOURCE})
  target_link_libraries(${NAME} PRIVATE settings)
endfunction(add_example)

add_example(example01)
add_example(example02)
add_example(example03)
add_example(example04)
add_example(example05)
add_example(example06)
add_example(example07)
add_example(example08)
add_example(example09)
add_example(example10)
