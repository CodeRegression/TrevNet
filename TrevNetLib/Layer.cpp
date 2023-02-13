//--------------------------------------------------
// Implementation of class Layer
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#include "Layer.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param nodeCount The number of nodes that should be in the layer
 */
Layer::Layer(int nodeCount)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Main Terminator
 */
Layer::~Layer()
{
	for (auto node : _nodes) delete node;
	for (auto edge : _edges) delete edge;
}

//--------------------------------------------------
// Add Edge
//--------------------------------------------------

/**
 * @brief Adds an edge to the system
 * @param sourceIndex The index of the source node we are referencing
 * @param destinationIndex The index of the destination we are referencing
 * @param weight The initial weight of the node
 */
void Layer::AddEdge(int sourceIndex, int destinationIndex, double weight)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Retrieval
//--------------------------------------------------

/**
 * @brief Get all the edges related to the source
 * @param nodeId The identifier of the node that we want the edges for
 * @param edges The edges that are associated with this node
 */
void Layer::GetSourceEdges(int nodeId, EdgeSet& edges)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Get all the edges related to a destination
 * @param GetDestinationEdges Get all the edges related to the given destination
 * @param edges The edges that are associated with the given node
 */
void Layer::GetDestinationEdges(int GetDestinationEdges, EdgeSet& edges)
{
	throw runtime_error("Not implemented");
}