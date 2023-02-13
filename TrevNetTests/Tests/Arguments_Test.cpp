//--------------------------------------------------
// Unit Tests for Arguments
//
// @author: Wild Boar
//
// @date: 2023-02-13
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNetLib/Arguments.h>
using namespace NVL_Tools;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that the arguments are initialized correct
 */
TEST(Arguments_Test, ConfirmProjectLoad)
{
	// Setup
	char * param[] = { (char *)"app_path", (char*) "param" };

	// Execute
	auto arguments = Arguments(2, param);

	// Confirm
	ASSERT_EQ(arguments.GetParam(), "param");
}
