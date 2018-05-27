
include_directories(
  ${BWEM_DIR}/include
  ${BWAPI_DIR}/bwapi/include
)

file(GLOB bwemSources
    ${BWEM_DIR}/src/*.cpp
)
add_library(BWEBlib
  ${bwemSources}
)

if(MSVC)
	target_compile_options(BWEBlib PUBLIC "/permissive-")
endif()

target_link_libraries(BWEBlib
  BWAPILIB
)