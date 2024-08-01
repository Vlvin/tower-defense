cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_definitions(-DNDEBUG)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

project(TowerFork)

set(SRC ${PROJECT_SOURCE_DIR}/src)

set(BUILD ${CMAKE_CURRENT_BINARY_DIR})

set(LIBS ${PROJECT_SOURCE_DIR}/libs)

set(INCLUDE
  ${SRC}/headers
  ${LIBS}/raylib-master/src
)

set(LIB_NAMES
  raylib
)

set(SOURCES 
  ${SRC}/Node.cpp
  ${SRC}/SceneManager.cpp
  ${SRC}/Scene.cpp
  ${SRC}/Button.cpp
  ${SRC}/Map.cpp
  ${SRC}/ColorTools.cpp
  ${SRC}/Creep.cpp
  ${SRC}/Bullet.cpp
  ${SRC}/PathNode.cpp
  ${SRC}/Tourel.cpp

)


add_subdirectory(${LIBS}/raylib-master)



# # building tests
# add_executable(tests ${SRC}/test.cpp ${SOURCES})
# target_include_directories(tests PUBLIC ${INCLUDE})
# target_link_libraries(tests ${LIB_NAMES})

# # run tests
# add_custom_command(
#     # OUTPUT "${BUILD}/autolog.txt"
#     TARGET tests
#     POST_BUILD
#     COMMAND "${BUILD}/tests" ARGS -s 0 10 -s 0 11 -e 39 10 -e 39 11
#     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#     COMMENT "Running tests: output in ${BUILD}/log.txt"
#     VERBATIM
# )
# add_custom_target(run_tests 
#     ALL 
#     DEPENDS tests
# )


message("DEBUG", "${CMAKE_CURRENT_BINARY_DIR}")
# building main
add_executable(main ${SRC}/main.cpp ${SOURCES})
# add_dependencies(main run_tests)
target_include_directories(main PUBLIC ${INCLUDE})
target_link_libraries(main ${LIB_NAMES})

