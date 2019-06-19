cmake_minimum_required(VERSION 3.14)

project(Hemingway)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

include_directories(
  include
  vendor
)

add_subdirectory(src)

add_subdirectory(test)
