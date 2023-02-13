#--------------------------------------------------------
# Top-Level: TrevNetLib
#
# @author: Wild Boar
#
# @Date Created: 2023-02-13
#--------------------------------------------------------

cmake_minimum_required(VERSION 3.0.0)
project(TrevNetLib VERSION 0.1.0)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

# Setup base directory
set(LIBRARY_BASE $ENV{HOME}/Libraries)

# Setup the includes for the libraries
include_directories("../" "${LIBRARY_BASE}/NVLib")

# Add the NVLib library to the folder
add_library(NVLib STATIC IMPORTED)
set_target_properties(NVLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/NVLib/build/NVLib/libNVLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/NVLib"
)

# Add OpenCV to the solution
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add OpenSSL support to the project as well
find_package(OpenSSL REQUIRED)

add_subdirectory(TrevNetLib)
add_subdirectory(TrevNetTests)