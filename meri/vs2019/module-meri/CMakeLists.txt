# CMAKE verison
cmake_minimum_required(VERSION 3.15)

# Project name
set(objname meri)
project(${objname})


### Source File
set(srcpath ../../module/meri/)
set(source_files_ex ../../core/mousemessage.h
					../../core/mousemessage.cpp
                    ../../core/datamessage.h
					../../core/datamessage.cpp
					../../core/keyboardmessage.h
					../../core/keyboardmessage.cpp
					../../core/config/config.h
					../../core/config/config.cpp
					)
FILE(GLOB source_files ${srcpath}*.h ${srcpath}*.cpp )
set(source ${source_files} ${source_files_ex})

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
add_library(${objname} SHARED ${source})
set_property(TARGET ${objname} PROPERTY CXX_STANDARD 17)

### dependencies
 #add_dependencies(${objname})