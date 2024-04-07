cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED YES)

project(TechDemo::MapLoader)

set(SRC ${PROJECT_SOURCE_DIR}/src)

set(LIBS ${PROJECT_SOURCE_DIR}/libs)

set(INCLUDE
    ${SRC}/headers
    ${LIBS}/raylib-master/src
)

set(LIB_NAMES
    raylib
)
set(DPLATFORM_DESKTOP Wayland)
set(SOURCES 
    ${SRC}/main.cpp
    ${SRC}/Window.cpp
    ${SRC}/File.cpp
    ${SRC}/Map.cpp
    ${SRC}/PathFinder.cpp
)

add_subdirectory(${LIBS}/raylib-master)

add_executable(main ${SOURCES})

target_include_directories(main PUBLIC ${INCLUDE})

target_link_libraries(main ${LIB_NAMES})

