cmake_minimum_required(VERSION 3.11)
project(roda)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(roda-test
  ${MOLPHENE_SRC_FILES}
  "${PROJECT_SOURCE_DIR}/test/main.cpp"
)

target_compile_options(roda-test PRIVATE "-Wall" "-stdlib=libc++")

target_include_directories(roda-test
PRIVATE
  "${PROJECT_SOURCE_DIR}/third_party/Catch2/single_include"
  "${PROJECT_SOURCE_DIR}/include"
)
