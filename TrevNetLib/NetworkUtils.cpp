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
	throw runtime_error("Not implemented");
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
