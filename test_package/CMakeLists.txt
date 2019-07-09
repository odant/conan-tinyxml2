# Tests for tinyxml2 Conan package
# Dmitriy Vetutnev, Odant 2019


project(PackageTest CXX)
cmake_minimum_required(VERSION 3.0)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

enable_testing()


# CONAN_PKG::tinyxml2 imported target

add_executable(test_load_CONAN_PKG test_load.cpp)
target_link_libraries(test_load_CONAN_PKG CONAN_PKG::tinyxml2)
set_target_properties(test_load_CONAN_PKG
    PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH True
)
add_test(
    NAME test_load_CONAN_PKG
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND test_load_CONAN_PKG
)


# tinyxml2::tinyxml2 imported target

find_package(tinyxml2 REQUIRED)

add_executable(test_load test_load.cpp)
target_link_libraries(test_load tinyxml2::tinyxml2)
set_target_properties(test_load
    PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH True
)
add_test(
    NAME test_load
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND test_load
)
