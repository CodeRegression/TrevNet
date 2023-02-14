//--------------------------------------------------
// Unit Tests for Arguments
//
// @author: Wild Boar
//
// @date: 2023-02-13
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNetLib/Network.h>
#include <TrevNetLib/Generator/RandomGenerator.h>
using namespace NVL_AI;

//--------------------------------------------------
// Prototypes
//--------------------------------------------------
int Evaluate(Network& network, int input1, int input2);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify that the unit test can learn the XOR function
 */
TEST(XOR_Test, basic_xor_training_test)
{
	// Create the training data
	Mat data = (Mat_<double>(4, 3) << 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0); auto dataLink = (double *) data.data;

	cout << "Creating network" << endl;
	auto generator = RandomGenerator(); auto network = Network(&generator, vector<int> {2, 10, 1});

	cout << "Starting training" << endl;
	for (auto i = 0; i < 300; i++) 
	{
		auto total = 0.0;
		for (auto row = 0; row < data.rows; row++) 
		{
			auto input = vector<double> { dataLink[row * 3 + 0], dataLink[row * 3 + 1]};
			auto output = vector<double> { dataLink[row * 3 + 2]};
			total += network.Update(input, output, 1e-2);
		}

		cout << "Epoch: " << i << " --- Error: " << (total / 4.0) << endl;
	}

	// Cout Testing Results
	ASSERT_EQ(Evaluate(network, 0, 0), 0);
	ASSERT_EQ(Evaluate(network, 1, 0), 1);
	ASSERT_EQ(Evaluate(network, 0, 1), 1);
	ASSERT_EQ(Evaluate(network, 1, 1), 0);
}

//--------------------------------------------------
// Evaluation Helper 
//--------------------------------------------------

/**
 * @brief Evaluate the XOR operation
 * @param network The network we trained 
 * @param input1 The first input
 * @param input2 The second input
 * @return int The resultant value
 */
int Evaluate(Network& network, int input1, int input2) 
{
	auto inputs = vector<double> { (double)input1, (double)input2};
	auto output = vector<double>();
	network.Evaluate(inputs, output);
	return output[0] < 0.5 ? 0 : 1;
}