cmake_minimum_required(VERSION 3.5)

project(SudokuSolverQt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(SudokuSolverQt
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  sudoku.h
  sudoku.cpp
  OCR.h
  OCR.cpp
)

target_link_libraries(SudokuSolverQt PRIVATE Qt5::Widgets ${OpenCV_LIBS})
