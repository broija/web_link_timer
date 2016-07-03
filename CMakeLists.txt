#broija 2016/07/01
#CMakeLists.txt for web_link_timer 1.0.0

cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME web_link_timer)
project(${PROJECT_NAME})

#_-_-_-_-_-_COMPILER_-_-_-_-_-_
SET(CMAKE_C_COMPILER "/usr/bin/clang")
SET(CMAKE_CXX_COMPILER "/usr/bin/clang")
#-_-_-_-_-_-

#_-_-_-_-_-_FLAGS_-_-_-_-_-_
#set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS} -g -Wall -pedantic -lstdc++")
#set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Wextra -fexceptions -mthreads -pedantic -O2 -frtti") 
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Wextra -fexceptions -pedantic -O2 -frtti")

#-_-_-_-_-_-

#_-_-_-_-_-_SOME DIRECTORIES_-_-_-_-_-_
set(PROJECT_DIR /home/broija/prog/cpp/${PROJECT_NAME})
#set(MINGW_DIR D:/Programs/Qt/Qt5.1.0/Tools/mingw48_32/i686-w64-mingw32)
#set(MINGW_LIB_DIR ${MINGW_DIR}/lib)
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

#Defining and removing "main" files from lib sources
#set(MAIN_FILE main.cpp)
#get_filename_component(_file_to_remove ${MAIN_FILE} ABSOLUTE)

#list(REMOVE_ITEM LIB_SOURCE_FILES ${_file_to_remove})
#-_-_-_-_-_-

#_-_-_-_-_-_BUILD OUTPUTS_-_-_-_-_-_
add_executable(${TARGET_APP} ${SOURCE_FILES})
#-_-_-_-_-_-

#_-_-_-_-_-_DEFINITIONS_-_-_-_-_-_
target_compile_definitions(${TARGET_APP} PUBLIC -DWVT_CYGWIN)

#set(WINDLL_NAME \"lib${TARGET_LIB_TESSERACT}.dll\")
#add_definitions( -D_tagBLOB_DEFINED -DUSE_STD_NAMESPACE -DWINDLLNAME=${WINDLL_NAME})
#-_-_-_-_-_-

#_-_-_-_-_-_LINKING_-_-_-_-_-_
set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})

#find_library(LEPTONICA_LIB NAMES lept lept-3 liblept liblept-3 PATHS ${LEPTONICA_DIR}/bin)
#find_library(WS2_32_LIB NAMES libws2_32.a PATHS ${MINGW_LIB_DIR} NO_DEFAULT_PATH NO_SYSTEM_ENVIRONMENT_PATH)

#find_library(LIBSTDCPP NAMES libstdc++ PATHS ${LIBSTDCPP_DIR})
set(LIBSTDCPP ${LIBSTDCPP_DIR}/libstdc++.a)

target_link_libraries(${TARGET_APP} ${LIBSTDCPP})
#target_link_libraries(${TARGET_LIB_TESSERACT} ${LEPTONICA_LIB} ${WS2_32_LIB})
#target_link_libraries(${TARGET_APP_SVPAINT} ${TARGET_LIB_TESSERACT})
#target_link_libraries(${TARGET_APP_TESSERACT} ${TARGET_LIB_TESSERACT})
#-_-_-_-_-_-
