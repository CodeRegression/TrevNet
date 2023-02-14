//--------------------------------------------------
// Unit Tests for class NetworkUtils
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNetLib/NetworkUtils.h>
#include <TrevNetLib/Generator/SeriesGenerator.h>
using namespace NVL_AI;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void SetupNetwork(vector<Layer *>& network, const vector<int>& counts, NumberGenerator * generator);
void SetInputs(vector<Layer *>& network, const vector<double>& inputs);
void ForwardPropagate(vector<Layer *>& network, const vector<double>& inputs);
void ConnectLayer(Layer * layer, Layer * next, NumberGenerator* generator);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that forward propagation is working effectively
 */
TEST(NetworkUtils_Test, forward_propagate)
{
	// Setup
	auto generator = SeriesGenerator(vector<double> { 0.3, 0.1, 0.8, 0.8, 0.5, 0.2, 0.4, 0.6 });
	auto network = vector<Layer *>(); SetupNetwork(network, vector<int> {3, 2, 1}, &generator);

	// Execute
	ForwardPropagate(network, vector<double> {-3, 2, 4} );

	// Confirm
	ASSERT_EQ(network[0]->GetNode(0)->GetForwardValue(), -3);
	ASSERT_EQ(network[0]->GetNode(1)->GetForwardValue(), 2);
	ASSERT_EQ(network[0]->GetNode(2)->GetForwardValue(), 4);

	ASSERT_EQ(network[1]->GetNode(0)->GetForwardValue(), 2.5);
	ASSERT_EQ(network[1]->GetNode(1)->GetForwardValue(), 0);

	ASSERT_EQ(network[2]->GetNode(0)->GetForwardValue(), 1);

	// Teardown
	for (auto& layer : network) delete layer;
}

/**
 * @brief Confirm that backward propagation is working effectively
 */
TEST(NetworkUtils_Test, backward_propagate)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

//--------------------------------------------------
// Helper Methods
//--------------------------------------------------

/**
 * @brief Initialize the test network
 * @param network The network that we are initializing 
 * @param counts The counts associated with the network
 * @param generator The number generator associated with the network
 */
void SetupNetwork(vector<Layer *>& network, const vector<int>& counts, NumberGenerator* generator) 
{
	// Housekeeping
	if (counts.size() == 0) return; network.clear();

	// Create the first layer
	network.push_back(new Layer(counts[0])); auto previous = network[0];

	// Add subsequent layers and edges
	for (auto i = 1; i < counts.size(); i++) 
	{
		auto current = new Layer(counts[i]); network.push_back(current);
		ConnectLayer(previous, current, generator);
		previous = current;
	}
}

/**
 * @brief Set the given inputs of the network
 * @param network The network that we are initializing
 * @param inputs The inputs that we want the network to have
 */
void SetInputs(vector<Layer *>& network, const vector<double>& inputs) 
{
	if (network[0]->GetNodeCount() != inputs.size()) throw runtime_error("There is a mismatch in node counts");
	for (auto i = 0; i < inputs.size(); i++) network[0]->GetNodes()[i]->SetForwardValue(inputs[i]);
}

/**
 * @brief Perform forward propagation within the network
 * @param network The network that we are perform forward propagation for
 * @param inputs The set of inputs that we want
 */
void ForwardPropagate(vector<Layer *>& network, const vector<double>& inputs) 
{
	if (network.size() <= 1) throw runtime_error("The network needs atleast 2 layers to forward propagate");

	SetInputs(network, inputs);

	for (auto i = 1; i < network.size(); i++) 
	{
		NetworkUtils::ForwardPropagate(network[i-1], network[i]);
	}
}

/**
 * @brief A helper for "fully connecting" layers
 * @param layer The layer that we are adding edges to
 * @param next The next layer that we are adding those edges to
 * @param generator The generator we are using for the weights
 */
void ConnectLayer(Layer * layer, Layer * next, NumberGenerator * generator) 
{
	for (auto i = 0; i < next->GetNodeCount(); i++) 
	{
		for (auto j = 0; j < layer->GetNodeCount(); j++) 
		{
			auto weight = generator->GetNext(0, 1, 3);
			auto edge = new Edge(j, i, weight);
			layer->AddEdge(edge);
		}
	}
}
