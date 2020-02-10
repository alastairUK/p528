# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project ("ITU-R-P528-4")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 11)

enable_testing()

# Include sub-projects.
add_subdirectory ("Tests")
add_subdirectory ("ConsoleApp")

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later.

set(Headers
    include/LOSTable.h
    include/p528.h)

set(Sources
    src/AbsorptionParameters.cpp
    src/CalculateEffectiveRayLength.cpp
    src/CombineDistributions.cpp
    src/FindKForYpiAt99Percent.cpp
    src/GetPathLoss.cpp
    src/InverseComplementaryCumulativeDistributionFunction.cpp
    src/LOSTable.cpp
    src/LineOfSight.cpp
    src/LinearInterpolation.cpp
    src/LongTermVariability.cpp
    src/Main.cpp
    src/MainEx.cpp
    src/NakagamiRice.cpp
    src/RayOptics.cpp
    src/RayTrace.cpp
    src/ReflectionCoefficients.cpp
    src/SmoothEarthDiffraction.cpp
    src/TerminalGeometry.cpp
    src/TranshorizonAbsorptionLoss.cpp
    src/TranshorizonSearch.cpp
    src/Troposcatter.cpp
    src/ValidateInputs.cpp
    src/data.cpp)

# Add source to this project's executable.
add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})