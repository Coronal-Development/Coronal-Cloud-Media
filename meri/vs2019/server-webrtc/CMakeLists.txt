# CMAKE verison
cmake_minimum_required(VERSION 3.15)

# Project name
set(objname server-webrtc)
project(${objname})


### Source File
set(search_path ../../module/server-webrtc/)
set(search_path_ex ../../core/webrtc/)
FILE(GLOB search_files ${search_path}*.h ${search_path}*.cpp )
FILE(GLOB search_files_ex ${search_path_ex}*.h ${search_path_ex}*.cpp )
set(source_files_ex ../../core/coronalserver.h ../../core/coronalserver.cpp ../../core/signalingserver.h ../../core/signalingserver.cpp)
set(source ${search_files} ${search_files_ex} ${source_files_ex})

## addtion include directory
set(add_include_dir ../../3rdparty/OWT/include ../../3rdparty/SocketIO/include)

## addtion library directory
set(add_lib_dir ../../3rdparty/OWT/lib/x64 ../../3rdparty/SocketIO/lib/x64 ../../3rdparty/Boost/lib/x64)

## addtion library
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(add_lib owt-debug.lib sioclient-debug.lib libboost_system-vc141-mt-sgd-x64-1_67.lib libboost_random-vc141-mt-sgd-x64-1_67.lib libboost_date_time-vc141-mt-sgd-x64-1_67.lib)
else()
	set(add_lib owt-release.lib sioclient-release.lib libboost_system-vc141-mt-s-x64-1_67.lib libboost_random-vc141-mt-s-x64-1_67.lib libboost_date_time-vc141-mt-s-x64-1_67.lib)
endif()
set(add_lib ${add_lib} secur32.lib dmoguids.lib msdmo.lib wmcodecdspuuid.lib strmiids.lib d3d9.lib d3d11.lib dxgi.lib winmm.lib ${build_output_directory}/controller-sdl.lib)

## Preprocessor Definitions
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(preprocessor_macroa -D__STDC_LIMIT_MACROS -DWEBRTC_WIN -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
else()
	set(preprocessor_macroa -D__STDC_LIMIT_MACROS -DWEBRTC_WIN -D_WINSOCK_DEPRECATED_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
endif()




### Set Statically link the runtime libraries
add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
    )

### Configruation object
include_directories(${base_add_include} ${add_include_dir})
link_directories(${base_link_directory} ${add_lib_dir})
link_libraries(${exbase_lib} ${add_lib})
add_definitions(${base_preprocessor} ${preprocessor_macroa})

### Set build output directory
SET(LIBRARY_OUTPUT_PATH ${build_output_directory}/mod)

### generate dynamic library
add_library(${objname} SHARED ${source})

### dependencies
add_dependencies(${objname} controller-sdl)
