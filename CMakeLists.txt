cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BWEM)

enable_language(CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/bwapi/CMake/BWAPI)

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(BWAPI_LIB_NAME "BWAPI-Staticd")
    SET(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
ELSE()
    SET(BWAPI_LIB_NAME "BWAPI-Static")
    SET(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
ENDIF()


include_directories(
  ${PROJECT_SOURCE_DIR}/external/bwapi/bwapi/include
)

set(GOOGLETEST_ROOT
  external/googletest/googletest CACHE STRING "Google Test source root"
)

set(GOOGLETEST_SOURCES
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
)

include_directories(
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

add_library(googletest
  ${GOOGLETEST_SOURCES}
)


file(GLOB bwemSources
  ${PROJECT_SOURCE_DIR}/src/*.cpp
)
add_library(BWEBlib
  ${bwemSources}
)
target_link_libraries(BWEBlib
  ${BWAPI_LIB_NAME}
)


file(GLOB testsources
	#${GOOGLETEST_SOURCES}
  ${PROJECT_SOURCE_DIR}/tests/*.cpp
)


add_executable(tests
  ${testsources}
)
include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/external/bwapi/bwapi/include
)

target_link_libraries(tests
  googletest
  BWEBlib
  ${BWAPI_LIB_NAME}
)

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/tests)
