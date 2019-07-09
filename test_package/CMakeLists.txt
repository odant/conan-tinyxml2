# Tests for tinyxml2 Conan package
# Dmitriy Vetutnev, Odant 2019


project(PackageTest CXX)
cmake_minimum_required(VERSION 3.0)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

enable_testing()


# CONAN_PKG::tinyxml2 imported target

add_executable(test_parse_CONAN_PKG test_parse.cpp)
target_link_libraries(test_parse_CONAN_PKG CONAN_PKG::tinyxml2)
set_target_properties(test_parse_CONAN_PKG
    PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH True
)
add_test(
    NAME test_parse_CONAN_PKG
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND test_parse_CONAN_PKG
)


# tinyxml2::tinyxml2 imported target

find_package(tinyxml2 REQUIRED)

add_executable(test_parse test_parse.cpp)
target_link_libraries(test_parse tinyxml2::tinyxml2)
set_target_properties(test_parse
    PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH True
)
add_test(
    NAME test_pasre
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND test_parse
)

add_executable(test_create test_create.cpp)
target_link_libraries(test_create tinyxml2::tinyxml2)
set_target_properties(test_create
    PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH True
)
add_test(
    NAME test_create
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND test_create
)
