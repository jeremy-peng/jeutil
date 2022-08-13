cmake_policy(SET CMP0048 NEW)

project(jeutil
    VERSION "0.0.1"
    DESCRIPTION "A simple libs"
)

cmake_minimum_required(VERSION 3.12)


set(CMAKE_CXX_STANDARD 14)

set(SRC src/threadpool.cpp)


add_library(${PROJECT_NAME} SHARED ${SRC})
target_link_libraries(${PROJECT_NAME} pthread)
set_target_properties("${PROJECT_NAME}"
PROPERTIES
    VERSION "${PROJECT_VERSION}")


option(BUILD_TEST_BINS "Build test binaries" on)
if (${BUILD_TEST_BINS})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(test)
endif()


option(BUILD_UNITTEST "Build unittest" off)  # OFF is the default  

if (${BUILD_UNITTEST})
    add_subdirectory(unittest)
endif()


