# Set Name of project and language
project(EX04 LANGUAGES CXX)

# Set cmake version
cmake_minimum_required(VERSION 3.0)

# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Create executable using the specified src
add_executable(${PROJECT_NAME}
    main.cpp
    threadLogFile.h
    ex4.cpp
    ex4.h
    threadLogFileSafe.h)

find_package(Threads)

# Define required c++ standard to C++11
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
	$<$<CXX_COMPILER_ID:MSVC>: /Wall>
)

FILE(COPY Files/threadLog.txt DESTINATION ${PROJECT_BINARY_DIR})
FILE(COPY Files/threadLogSafe.txt DESTINATION ${PROJECT_BINARY_DIR})
