# Set Name of project and language
project(EX03 LANGUAGES CXX)

# Set cmake version
cmake_minimum_required(VERSION 3.0)

# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5PrintSupport CONFIG REQUIRED)

# Create executable using the specified src
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ui/widget.cpp
    src/ui/widget.h
    src/ui/widget.ui
    src/ui/qcustomplot-source/qcustomplot.cpp
    src/ui/qcustomplot-source/qcustomplot.h
    )

set(APP_INCLUDE_DIRS src src/ui src/ui/qcustomplot-source)
INCLUDE_DIRECTORIES(${APP_INCLUDE_DIRS})

# Define required c++ standard to C++11
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
	$<$<CXX_COMPILER_ID:MSVC>: /Wall>
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::PrintSupport)
