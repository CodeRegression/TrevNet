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
	for (auto i = 0; i < nodeCount; i++) _nodes.push_back(new Node());
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
 * @param edge The edge that we are adding
 */
void Layer::AddEdge(Edge * edge)
{
	UpdateLookup(_sourceLookup, edge->GetSource(), edge);
	UpdateLookup(_destinationLookup, edge->GetDestination(), edge);
	_edges.push_back(edge);
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
	GetEdgeSet(_sourceLookup, nodeId, edges);
}

/**
 * @brief Get all the edges related to a destination
 * @param nodeId Get all the edges related to the given destination
 * @param edges The edges that are associated with the given node
 */
void Layer::GetDestinationEdges(int nodeId, EdgeSet& edges)
{
	GetEdgeSet(_destinationLookup, nodeId, edges);
}

//--------------------------------------------------
// Helpers
//--------------------------------------------------

/**
 * @brief Update the given lookup method
 * @param lookup The lookup that we are updating
 * @param nodeId The nodeId of the value being updated
 * @param edge The edge that is being added
 */
void Layer::UpdateLookup(unordered_map<int, EdgeSet> & lookup, int nodeId, Edge * edge) 
{
	lookup[nodeId].push_back(edge);
}

/**
 * @brief Retrieve the given set of edges
 * @param lookup The lookup that we are updating
 * @param nodeId The nodeId of the value that is being updated
 * @param edges The edge that is being loaded
 */
void Layer::GetEdgeSet(unordered_map<int, EdgeSet> & lookup, int nodeId, EdgeSet& edges) 
{
	edges.clear();
	if (lookup.find(nodeId) == lookup.end()) return;
	auto& edgeSet = lookup[nodeId];
	for (auto edge : edgeSet) edges.push_back(edge); 
}