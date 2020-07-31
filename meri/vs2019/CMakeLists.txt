# CMAKE verison
cmake_minimum_required(VERSION 3.0.0)

# Project name
project(meri)

### Created The Build Output Directory
set(build_output_directory ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "Build Output directory")
message("Build Output Directory : ${CMAKE_BINARY_DIR}")
file(MAKE_DIRECTORY ${build_output_directory})
file(MAKE_DIRECTORY ${build_output_directory}/mod)
file(MAKE_DIRECTORY ${build_output_directory}/config/common)
message("Created The Build Output Directory Done(${build_output_directory}).")


### Copy configruation files
FILE(GLOB config_files ../config/*.* )
FILE(GLOB config_common_files ../config/common/*.* )
file(COPY ${config_files} DESTINATION ${build_output_directory}/config/)
file(COPY ${config_common_files} DESTINATION ${build_output_directory}/config/common/)
message("Copy configruation files to config directory Done(${build_output_directory}).")


### Baisc Configuration


### Preprocessor Define


### sets Character Set to Unicode or Multi Byte
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_MBCS")

add_subdirectory(module-meri)
add_subdirectory(module-test)
add_subdirectory(module-media-services)
#add_subdirectory(server-webrtc)

