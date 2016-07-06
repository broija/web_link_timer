#broija 2016/07/01
#CMakeLists.txt for web_link_timer 1.0.0

cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME web_link_timer)
project(${PROJECT_NAME})

set(CMAKE_VERBOSE_MAKEFILE on)

set(CLANG 0)

#_-_-_-_-_-_COMPILER_-_-_-_-_-_
if(${CLANG})
  SET(CMAKE_C_COMPILER "/usr/bin/clang")
  SET(CMAKE_CXX_COMPILER "/usr/bin/clang")
else()
  SET(CMAKE_C_COMPILER "/usr/bin/g++")
  SET(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif()
#-_-_-_-_-_-

#_-_-_-_-_-_FLAGS_-_-_-_-_-_
#set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS} -g -Wall -pedantic -lstdc++")
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Wextra -fexceptions -pedantic -O2 -frtti")

#-_-_-_-_-_-

#_-_-_-_-_-_SOME DIRECTORIES_-_-_-_-_-_
set(PROJECT_DIR /home/broija/prog/cpp/${PROJECT_NAME})
set(LIBSTDCPP_DIR /usr/lib/gcc/x86_64-pc-cygwin/5.4.0/)

#-_-_-_-_-_-

#_-_-_-_-_-_VERSION#_-_-_-_-_-_
set(LIB_VERSION_MAJOR 1)
set(LIB_VERSION_MINOR 0)
set(LIB_VERSION_PATCH 0)

set(VERSION_STRING ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH})

#-_-_-_-_-_-

#_-_-_-_-_-_TARGETS_-_-_-_-_-_
set(TARGET_APP ${PROJECT_NAME})
#-_-_-_-_-_-

#_-_-_-_-_-_DIRECTORIES AND FILES_-_-_-_-_-_
set(CMAKE_BINARY_DIR ../${PROJECT_NAME})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#----Headers----
file(GLOB_RECURSE HEADER_FILES "*.h")

set(LIB_INCLUDE_DIRS "")

foreach (_header_file ${HEADER_FILES})
    get_filename_component(_dir ${_header_file} PATH)
    list (APPEND LIB_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES LIB_INCLUDE_DIRS)

include_directories(${LIB_INCLUDE_DIRS} ${LEPTONICA_DIR}/src)

#----Sources----
set(LIB_SOURCE_DIRS "")
set(LIB_SOURCE_FILES "")

file(GLOB SOURCE_FILES "./*.cpp")

#-_-_-_-_-_-

#_-_-_-_-_-_BUILD OUTPUTS_-_-_-_-_-_
add_executable(${TARGET_APP} ${SOURCE_FILES})
#-_-_-_-_-_-

#_-_-_-_-_-_DEFINITIONS_-_-_-_-_-_
if(${CLANG})
  target_compile_definitions(${TARGET_APP} PUBLIC -DWVT_CYGWIN -DWVT_LOGGER_NO_MUTEX)
else()
  target_compile_definitions(${TARGET_APP} PUBLIC -DWVT_CYGWIN)
endif()

#-_-_-_-_-_-

#_-_-_-_-_-_LINKING_-_-_-_-_-_
set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})

set(LIBSTDCPP ${LIBSTDCPP_DIR}/libstdc++.a)

target_link_libraries(${TARGET_APP} ${LIBSTDCPP})

#-_-_-_-_-_-
