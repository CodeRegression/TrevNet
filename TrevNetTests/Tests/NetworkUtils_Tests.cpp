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
void ApproxDerivative(vector<Layer *>& network, const vector<double>& inputs, int layerId, int edgeId, const vector<double>& expected, vector<double>& derivatives);
void BackPropagate(vector<Layer *>& network, const vector<double>& inputs, const vector<double>& expected);

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
	// Setup
	auto generator = SeriesGenerator(vector<double> { 0.3, 0.1, 0.8, 0.8, 0.5, 0.2, 0.4, 0.6 });
	auto network = vector<Layer *>(); SetupNetwork(network, vector<int> {3, 2, 1}, &generator);
	auto expected = vector<double> { 0.8 }; auto inputs = vector<double> { -3, 2, 4};

	// Execute
	auto w_1 = vector<double>(); ApproxDerivative(network, inputs, 0, 0, expected, w_1);
	auto w_2 = vector<double>(); ApproxDerivative(network, inputs, 0, 1, expected, w_2);
	auto w_3 = vector<double>(); ApproxDerivative(network, inputs, 0, 2, expected, w_3);

	auto w_4 = vector<double>(); ApproxDerivative(network, inputs, 0, 3, expected, w_4);
	auto w_5 = vector<double>(); ApproxDerivative(network, inputs, 0, 4, expected, w_5);
	auto w_6 = vector<double>(); ApproxDerivative(network, inputs, 0, 5, expected, w_6);

	auto w_7 = vector<double>(); ApproxDerivative(network, inputs, 1, 0, expected, w_7);
	auto w_8 = vector<double>(); ApproxDerivative(network, inputs, 1, 1, expected, w_8);

	ForwardPropagate(network, inputs); BackPropagate(network, inputs, expected);

	auto t_1 = NetworkUtils::UpdateWeight(network, 0, 0, 1);
	auto t_2 = NetworkUtils::UpdateWeight(network, 0, 1, 1);
	auto t_3 = NetworkUtils::UpdateWeight(network, 0, 2, 1);

	auto t_4 = NetworkUtils::UpdateWeight(network, 0, 3, 1);
	auto t_5 = NetworkUtils::UpdateWeight(network, 0, 4, 1);
	auto t_6 = NetworkUtils::UpdateWeight(network, 0, 5, 1);

	auto t_7 = NetworkUtils::UpdateWeight(network, 1, 0, 1);
	auto t_8 = NetworkUtils::UpdateWeight(network, 1, 1, 1);
	
	// Confirm
	ASSERT_NEAR(w_1[0], t_1, 1e-4);
	ASSERT_NEAR(w_2[0], t_2, 1e-4);
	ASSERT_NEAR(w_3[0], t_3, 1e-4);

	ASSERT_NEAR(w_4[0], t_4, 1e-4);
	ASSERT_NEAR(w_5[0], t_5, 1e-4);
	ASSERT_NEAR(w_6[0], t_6, 1e-4);

	ASSERT_NEAR(w_7[0], t_7, 1e-4);
	ASSERT_NEAR(w_8[0], t_8, 1e-4);

	// Teardown
	for (auto& layer : network) delete layer;
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

/**
 * @brief Estimate an approximate derivative for a weight
 * @param network The network
 * @param inputs The set of input points
 * @param layerId The layer identifier
 * @param edgeId The edge identifier
 * @param expected The expected outputs
 * @param derivatives The output derivatives
 */
void ApproxDerivative(vector<Layer *>& network, const vector<double>& inputs, int layerId, int edgeId, const vector<double>& expected, vector<double>& derivatives) 
{
	// Retrieve general variables
	auto lastLayer = network.size() - 1; 
	
	// Perform some minor validation
	if (expected.size() != network[lastLayer]->GetNodeCount()) throw runtime_error("Expected count is wrong");

	// Retrieve the initial weight
	auto weight = network[layerId]->GetEdge(edgeId)->GetWeight();

	// Calculate the initial value
	ForwardPropagate(network, inputs);
	auto errors_1 = vector<double>(); 
	for (auto i = 0; i < network[lastLayer]->GetNodeCount(); i++) 
	{
		auto actualValue = network[lastLayer]->GetNode(i)->GetForwardValue();
		auto expectedValue = expected[i];
		auto error = NetworkUtils::GetError(expectedValue, actualValue);
		errors_1.push_back(error);
	}

	// Calculate the update
	auto delta = 1e-8; network[layerId]->GetEdge(edgeId)->SetWeight(weight + delta);
	ForwardPropagate(network, inputs);
	auto errors_2 = vector<double>(); 
	for (auto i = 0; i < network[lastLayer]->GetNodeCount(); i++) 
	{
		auto actualValue = network[lastLayer]->GetNode(i)->GetForwardValue();
		auto expectedValue = expected[i];
		auto error = NetworkUtils::GetError(expectedValue, actualValue);
		errors_2.push_back(error);
	}

	// Roll back the weight change (to prevent unexpected "side-effects")
	network[layerId]->GetEdge(edgeId)->SetWeight(weight);

	// Determine the derivatives
	derivatives.clear();
	for (auto i = 0; i < network[lastLayer]->GetNodeCount(); i++) 
	{
		auto gradient = (errors_2[i] - errors_1[i]) / delta;
		derivatives.push_back(gradient);
	}
}

/**
 * @brief Add the logic for back propagation
 * @param network The network
 * @param inputs The inputs
 * @param expected The expected values
 */
void BackPropagate(vector<Layer *>& network, const vector<double>& inputs, const vector<double>& expected) 
{
	// Retrieve general variables
	auto lastLayer = network.size() - 1; 
	
	// Perform some minor validation
	if (expected.size() != network[lastLayer]->GetNodeCount()) throw runtime_error("Expected count is wrong");;

	// Setup the inputs
	SetInputs(network, inputs);

	// Set the initial errors
	for (auto i = 0; i < network[lastLayer]->GetNodeCount(); i++) 
	{
		auto actualValue = network[lastLayer]->GetNode(i)->GetForwardValue();
		auto expectedValue = expected[i];
		auto errorDelta = actualValue - expectedValue;
		auto activationDelta = actualValue > 0 ? 1 : 0;
		network[lastLayer]->GetNode(i)->SetBackwardValue(errorDelta * activationDelta); 
	}

	// Calculate the backprop deltas
	for (auto i = lastLayer; i > 0; i--) 
	{
		NetworkUtils::BackwardPropagate(network[i], network[i-1]);
	}
}