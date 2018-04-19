cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BWEM)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENBW_DIR ${PROJECT_SOURCE_DIR}/external/openbw)

include_directories(
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/include
)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPILib)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/OpenBWData)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPICore)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPI)
include_directories(
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/Util/Source
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPI/openbw
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPI/openbw/BWAPI
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPI/Source/BWAPI
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPI/Source
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPICore
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/Shared
)

include_directories(
  ${PROJECT_SOURCE_DIR}/BWEM/include
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/include
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
  ${PROJECT_SOURCE_DIR}/BWEM/src/*.cpp
)
add_library(BWEBlib
  ${bwemSources}
)
target_link_libraries(BWEBlib
  BWAPILIB
)


include_directories(
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPI/Source
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPICore
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/OpenBWData
  ${PROJECT_SOURCE_DIR}/external/openbw
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
  ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

file(GLOB testsources
	#${GOOGLETEST_SOURCES}
  ${PROJECT_SOURCE_DIR}/tests/*.cpp
)
add_library(BWData ALIAS OpenBWData)
add_executable(tests
  ${testsources}
  $<TARGET_OBJECTS:BWAPIObj>
  $<TARGET_OBJECTS:BWAPICore>
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/OpenBWData/BW/BWData.cpp
)

target_link_libraries(tests
  googletest
  BWEBlib
  BWAPILIB
)

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/tests)
file(COPY Tests/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
