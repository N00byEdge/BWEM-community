cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BWEM)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OPENBW_DIR ${PROJECT_SOURCE_DIR}/external/openbw)
set(BWEM_DIR ${PROJECT_SOURCE_DIR}/BWEM)
set(BWAPI_DIR ${PROJECT_SOURCE_DIR}/external/openbw-bwapi)

include_directories(
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/Util/Source
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPI/openbw
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPI/openbw/BWAPI
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPI/Source/BWAPI
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPI/Source
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/BWAPICore
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/Shared
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/include
)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPILIB)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/OpenBWData)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPICore)
add_subdirectory(${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPI)

add_subdirectory(${PROJECT_SOURCE_DIR}/BWEM)
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests)
