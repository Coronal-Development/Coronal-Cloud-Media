# CMAKE verison
cmake_minimum_required(VERSION 3.15)

# Project name
set(objname controller-sdl)
project(${objname})


### Source File
set(srcpath ../../module/controller/)
set(source_files_ex ../../core/controller.h ../../core/controller.cpp)
FILE(GLOB source_files ${srcpath}*.h ${srcpath}*.cpp )
set(source ${source_files} ${source_files_ex})
message("[${objname}][source]: ${source}")

## addtion include directory
set(add_include_dir ../../3rdparty/)

## addtion library directory
#set(add_lib_dir )

## addtion library
# set(add_lib ws2_32.lib SDL2.lib)

## Preprocessor Definitions
	set(preprocessor_macroa -DMERI_EXPORTS)
#endif()


### Configruation object
include_directories(${add_include_dir})
link_directories(${add_lib_dir})
link_libraries(${add_lib})
add_definitions(${preprocessor_macroa})

### Set build output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${build_output_directory})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${build_output_directory})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${build_output_directory})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${build_output_directory})

### generate dynamic library
add_library(${objname} SHARED ${source})

### dependencies
# add_dependencies(${objname} libga)