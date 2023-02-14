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
	throw runtime_error("Not implemented");
}

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