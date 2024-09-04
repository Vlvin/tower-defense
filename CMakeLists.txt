cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TowerFork)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(googletest)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR


set(CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_definitions(-DNDEBUG)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set(SRC ${PROJECT_SOURCE_DIR}/src)

set(TEST_SOURCES ${PROJECT_SOURCE_DIR}/tests)

set(HEADERS ${PROJECT_SOURCE_DIR}/include)

set(BUILD ${CMAKE_CURRENT_BINARY_DIR})

set(LIBS ${PROJECT_SOURCE_DIR}/libs)

set(INCLUDE
  ${HEADERS}
  ${LIBS}/raylib-master/src
  ${googletest_SOURCE_DIR}/GTest::
)

set(LIB_NAMES
  raylib
)

set(SOURCES 
  ${SRC}/SceneManager.cpp
  ${SRC}/InputHandler.cpp
  ${SRC}/CameraObject.cpp
  ${SRC}/Game.cpp
  ${SRC}/Node.cpp
  ${SRC}/Scene.cpp
  ${SRC}/Button.cpp
  ${SRC}/Map.cpp
  ${SRC}/ColorTools.cpp
  ${SRC}/Creep.cpp
  ${SRC}/Bullet.cpp
  ${SRC}/PathNode.cpp
  ${SRC}/Tourel.cpp
  ${SRC}/Tiler.cpp
  ${SRC}/Player.cpp
  ${SRC}/PlayerHUD.cpp

)

set(TESTS 
  ${TEST_SOURCES}/CameraObjectTest.cpp
)


add_subdirectory(${LIBS}/raylib-master)
# add_subdirectory(${LIBS}/googletest)

# # building tests
# add_executable(tests ${TESTS} ${SOURCES})
# target_include_directories(tests PUBLIC ${INCLUDE})
# target_link_libraries(tests ${LIB_NAMES} GTest::gtest_main)

# run tests
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


# enable_testing()

# include(GoogleTest) 
# gtest_discover_tests(tests)


# building main
add_executable(main ${SRC}/main.cpp ${SOURCES})
target_include_directories(main PUBLIC ${INCLUDE})
target_link_libraries(main ${LIB_NAMES})

# copy exec

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${BUILD}/main
                ${CMAKE_CURRENT_SOURCE_DIR}/TowerDefense
        COMMENT "Running tests: output in ${BUILD}/log.txt")
add_custom_target(copy_exec 
  ALL 
  DEPENDS main
)



