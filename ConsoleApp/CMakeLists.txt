# CMakeList.txt : CMake project for ITU-R-P528-4, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)
project(ConsoleApp)

set(CMAKE_CXX_STANDARD 11)

# Add source to this project's executable.
add_executable(${PROJECT_NAME}
    main.cpp)

target_link_libraries(${PROJECT_NAME} ITU-R-P528-4)

target_include_directories(${PROJECT_NAME} PRIVATE ../include)