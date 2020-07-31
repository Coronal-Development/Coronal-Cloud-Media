# CMAKE verison
cmake_minimum_required(VERSION 3.15)

# Project name
set(objname meri-test)
project(${objname})


### Source File
set(srcpath ../../module/meri-test/)
FILE(GLOB source_files ${srcpath}*.h ${srcpath}*.cpp )
set(source ${source_files} )

## addtion include directory
set(add_include_dir ../../3rdparty/)

## addtion library directory
set(add_lib_dir ${build_output_directory} ../../3rdparty/lib/)

## addtion library
set(add_lib jsoncpp.lib)

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

add_executable(${objname}  ${source})
set_property(TARGET ${objname} PROPERTY CXX_STANDARD 17)
set_target_properties(
    ${objname}  PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${build_output_directory})
### dependencies
 #add_dependencies(${objname})