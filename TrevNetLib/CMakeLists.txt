#--------------------------------------------------------
# CMake for generating the TrevNetLib
#
# @author: Wild Boar
#
# Date Created: 2023-02-13
#--------------------------------------------------------

# Setup includes directories
include_directories("../" ${OpenCV_INCLUDE_DIRS})

# Create Library
add_library (TrevNetLib STATIC
	Generator/RandomGenerator.cpp
	Generator/SeriesGenerator.cpp
	Model/Edge.cpp
	Model/Node.cpp
	Layer.cpp
	NetworkUtils.cpp
)

