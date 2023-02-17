//--------------------------------------------------
// Unit Tests for class Network
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNetLib/Network.h>
#include <TrevNetLib/Generator/SeriesGenerator.h>
#include <TrevNetLib/Generator/RandomGenerator.h>
using namespace NVL_AI;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Make sure that the network has the expected structure
 */
TEST(Network_Test, confirm_network)
{
	// Setup
	auto generator = RandomGenerator();

	// Execute
	auto network = Network(&generator, vector<int> { 3, 2, 1 });

	// Confirm
	ASSERT_EQ(network.GetLayers().size(), 3);
	ASSERT_EQ(network.GetLayers()[0]->GetNodeCount(), 3);
	ASSERT_EQ(network.GetLayers()[0]->GetEdgeCount(), 6);
	ASSERT_EQ(network.GetLayers()[1]->GetNodeCount(), 2);
	ASSERT_EQ(network.GetLayers()[1]->GetEdgeCount(), 2);
	ASSERT_EQ(network.GetLayers()[2]->GetNodeCount(), 1);
	ASSERT_EQ(network.GetLayers()[2]->GetEdgeCount(), 0);
}

/**
 * @brief Confirm that the network is able to evaluate expressions
 */
TEST(Network_Test, evaluate)
{
	// Setup
	auto generator = SeriesGenerator(vector<double> { 0.3, 0.1, 0.8, 0.8, 0.5, 0.2, 0.4, 0.6 });
	auto network = Network(&generator, vector<int> {3, 2, 1} );

	// Execute
	auto output = vector<double>(); network.Evaluate(vector<double> { -3, 2, 4}, output);

	// Confirm
	ASSERT_EQ(output.size(), 1);
	ASSERT_EQ(output[0], 1);
}

/**
 * @brief Confirm that the network is capable of performing an update
 */
TEST(Network_Test, update)
{
	// Setup
	auto generator = SeriesGenerator(vector<double> { 0.3, 0.1, 0.8, 0.8, 0.5, 0.2, 0.4, 0.6 });
	auto network = Network(&generator, vector<int> {3, 2, 1} );
	auto inputs = vector<double> { -3, 2, 4}; auto expected = vector<double> { 0.8 };

	// Execute
	auto output_1 = vector<double>(); network.Evaluate(inputs, output_1);
	network.Update(inputs, expected, 1e-1);
	auto output_2 = vector<double>(); network.Evaluate(inputs, output_2);

	// Confirm
	ASSERT_GT(NetworkUtils::GetError(expected[0], output_1[0]), NetworkUtils::GetError(expected[0], output_2[0]));
}

/**
 * @brief Confirms that the same input produces the same output 
 */
TEST(Network_Test, init_string_inverse_test) 
{
	FAIL() << "Not Implemented";
}

/**
 * @brief Confirms that the network behaves in the predicated way when given weights
 */
TEST(Network_Test, load_test) 
{
	FAIL() << "Not Implemented";
}