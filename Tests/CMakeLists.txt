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

file(GLOB testsources
	#${GOOGLETEST_SOURCES}
  ${PROJECT_SOURCE_DIR}/Tests/*.cpp
)

include_directories(
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPI/Source
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/BWAPICore
  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/OpenBWData
  ${PROJECT_SOURCE_DIR}/external/openbw
)

add_library(BWData ALIAS OpenBWData)

include_directories(
  ${PROJECT_SOURCE_DIR}/BWEM/include
#  ${PROJECT_SOURCE_DIR}/external/openbw-bwapi/bwapi/include
)

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
  dl
)

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/tests)
file(COPY ${PROJECT_SOURCE_DIR}/Tests/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
