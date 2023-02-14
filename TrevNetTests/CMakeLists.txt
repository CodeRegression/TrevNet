#--------------------------------------------------------
# CMake for generating TrevNetLib Testing Suite
#
# @author: Wild Boar
#
# Date Created: 2023-02-13
#--------------------------------------------------------

# Add Google Test to the test group
find_package(GTest REQUIRED)

# Add include directory
include_directories( "../" )
# Setup the includes
include_directories("../" "${LIBRARY_BASE}/NVLib" ${OpenCV_INCLUDE_DIRS})

# Add the UnitTestLib library to the folder
add_library(UnitTestLib STATIC IMPORTED)
set_target_properties(UnitTestLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/UnitTestLib/build/UnitTestLib/libUnitTestLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/UnitTestLib"
)

# Create the executable
add_executable (TrevNetTests
	Tests/Example_Tests.cpp
	Tests/Layer_Tests.cpp
	Tests/NetworkUtils_Tests.cpp
	Tests/Network_Tests.cpp
)


target_link_libraries(TrevNetTests TrevNetLib NVLib UnitTestLib ${OpenCV_LIBS} OpenSSL::SSL GTest::Main)

# Find the associated unit tests
gtest_discover_tests(TrevNetTests)

# Add File Copy Here!
