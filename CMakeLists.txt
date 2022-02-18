cmake_minimum_required(VERSION 3.10)
project(fsm-demo)

# Custom executable name.
set(EXECUTABLE_NAME fsm-demo)

# Use g++-8 and C++17 for arm64 compatibility.
set(CMAKE_CXX_COMPILER /usr/bin/g++-8)
set(CMAKE_CXX_STANDARD 17)

# Options for different build type.
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_options(
            # Complete debugger support.
            -O0
    )
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    add_compile_options(
            # Maximum speed.
            -O3
            -flto
            # Disable this flag when error occurs.
            -march=native
    )
endif ()

# Ceres-Solver.
find_package(Ceres 2 REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

# Linux GNU Library.
if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    include_directories(/usr/include/x86_64-linux-gnu)
elseif (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    include_directories(/usr/include/aarch64-linux-gnu)
endif ()

# Project sources.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules)

# All sources in modules will be compiled.
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/modules/*/*.c*)

add_executable(${EXECUTABLE_NAME} main.cpp ${SRC})

target_link_libraries(${EXECUTABLE_NAME}
        ${CMAKE_THREAD_LIBS_INIT}
        ${CERES_LIBRARIES}
        stdc++fs  # In C++17, this standard library should be manually linked.
        gflags
        )
