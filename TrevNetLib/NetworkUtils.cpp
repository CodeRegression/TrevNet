//--------------------------------------------------
// Implementation of class NetworkUtils
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#include "NetworkUtils.h"
using namespace NVL_AI;

//--------------------------------------------------
// Forward
//--------------------------------------------------

/**
 * @brief Executes a round of forward propagation between two layers
 * @param bottomLayer The layer that we are propagating FROM
 * @param topLayer The layer that we are propagating TO
 */
void NetworkUtils::ForwardPropagate(Layer* bottomLayer, Layer* topLayer)
{
	for (auto i = 0; i < topLayer->GetNodeCount(); i++) 
	{
		auto edges = vector<Edge *>(); bottomLayer->GetDestinationEdges(i, edges);

		auto total = 0.0;
		for (auto edge : edges) 
		{
			auto nodeValue = bottomLayer->GetNode(edge->GetSource())->GetForwardValue();
			auto update = edge->GetWeight() * nodeValue;
			total += update;
		}

		topLayer->GetNode(i)->SetForwardValue(Relu(total));
	}
}

//--------------------------------------------------
// Backward
//--------------------------------------------------

/**
 * @brief Executes a round of backward propagator between two layers
 * @param topLayer The layer that we are propagating FROM
 * @param bottomLayer The layer that we are propagating TO
 */
void NetworkUtils::BackwardPropagate(Layer * topLayer, Layer * bottomLayer)
{
	for (auto i = 0; i < bottomLayer->GetNodeCount(); i++) 
	{
		auto edges = vector<Edge *>(); bottomLayer->GetSourceEdges(i, edges);
		auto nodeValue = bottomLayer->GetNode(i)->GetForwardValue();
		auto isZero = (abs(nodeValue) < 1e-8);
		if (isZero) { bottomLayer->GetNode(i)->SetBackwardValue(0); continue; }

		// NOTE: This method heavily relies on the LeRU activation function!

		auto total = 0.0;
		for (auto edge : edges) 
		{
			auto nodeDelta = topLayer->GetNode(edge->GetDestination())->GetBackwardValue();
			auto update = edge->GetWeight() * nodeDelta;
			total += update;
		}

		bottomLayer->GetNode(i)->SetBackwardValue(total);
	}
}

//--------------------------------------------------
// Weight Update Logic
//--------------------------------------------------

/**
 * @brief Add the functionality to update the weight of the system
 * @param layer The layer that we are updating
 * @param edgeId The edge that we care about
 * @param factor The weight factor that we plan to update the weights by
 * @return double The update delta
 */
double NetworkUtils::UpdateWeight(vector<Layer *>& network, int layerId, int edgeId, double factor) 
{
	if (network.size() <= (layerId + 1)) throw runtime_error("LayerId is out of range");

	auto edge = network[layerId]->GetEdge(edgeId);

	auto destinationNode = network[layerId + 1]->GetNode(edge->GetDestination());
	auto sourceNode = network[layerId]->GetNode(edge->GetSource());
	
	auto weightDelta = sourceNode->GetForwardValue() * destinationNode->GetBackwardValue();
	auto originalWeight = edge->GetWeight();
	auto update = -1 * factor * weightDelta;
	edge->SetWeight(originalWeight + update);
	return weightDelta;
}

//--------------------------------------------------
// Activation Function
//--------------------------------------------------

/**
 * @brief Implementation of the ReLU activation function
 * @param value The value that we are using
 * @return The value of the activation function
 */
double NetworkUtils::Relu(double value) 
{
	if (value >= 0) return value;
	else return 0;
}

//--------------------------------------------------
// Get Error
//--------------------------------------------------

/**
 * @brief Calculate the error associated with real and fake points
 * @param expected Values that are expected
 * @param actual The values that the system generated
 * @return double The associated error
 */
double NetworkUtils::GetError(double expected, double actual) 
{
	auto difference = (expected - actual);
	return 0.5 * difference * difference;
}