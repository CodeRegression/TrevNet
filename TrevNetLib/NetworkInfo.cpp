//--------------------------------------------------
// Implementation of class NetworkInfo
//
// @author: Wild Boar
//
// @date: 2023-02-18
//--------------------------------------------------

#include "NetworkInfo.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param initString An initializer string for neural networks
 */
NetworkInfo::NetworkInfo(const string& initString)
{
	auto levels = vector<string>(); NVLib::StringUtils::Split(initString, '|', levels);

	for (auto& levelString : levels) 
	{
		auto edges = vector<Edge *>();
		auto nodeCount = ProcessLayer(levelString, edges);
		_edges[_layerCounts.size()] = edges;
		_layerCounts.push_back(nodeCount);
	}
}

//--------------------------------------------------
// Build
//--------------------------------------------------

/**
 * @brief Constructs a network from the loaded data
 * @param layers The layers string that we are loading
 */
void NetworkInfo::BuildNetwork(vector<Layer *>& layers)
{
	for (auto layer : layers) delete layer; layers.clear();

	for (auto count : _layerCounts) 
	{
		auto layerId = layers.size();
		auto nextLayer = new Layer(count);
		auto& edges = _edges[layerId];
		for (auto edge : edges) nextLayer->AddEdge(edge);
		layers.push_back(nextLayer);
	}
}

//--------------------------------------------------
// Processing logic
//--------------------------------------------------

/**
 * @brief Process a layer string
 * @param layerString The associated layer string
 * @param edges The list of edges that we are dealing with
 * @return int The number of nodes found
 */
int NetworkInfo::ProcessLayer(const string& layerString, vector<Edge *>& edges) 
{
	// Declare working variables
	auto nodeCount = -1;

	// Split the layer string into parts
	auto parts = vector<string>(); NVLib::StringUtils::Split(layerString, ',', parts);

	// Handle the special case - final node just contains the node count
	auto hasNoEdge = parts.size() == 1 && parts[0].find(':') == parts[0].npos;
	if (hasNoEdge) 
	{
		auto count = NVLib::StringUtils::String2Int(parts[0]);
		return count;
	}

	// Create the edges and update the node code
	for (auto& part : parts) 
	{
		auto edge = CreateEdge(part);
		edges.push_back(edge);
		if (edge->GetSource() > nodeCount) nodeCount = edge->GetSource();
	}

	// Return the node count
	return nodeCount + 1;
}

/**
 * @brief Create an edge from an edge string
 * @param edgeString The edge string that we are building the edge from
 * @return Edge* The edge that we are working with
 */
Edge * NetworkInfo::CreateEdge(const string& edgeString) 
{
	auto parts = vector<string>(); NVLib::StringUtils::Split(edgeString, ':', parts);

	if (parts.size() != 3) throw runtime_error("Format of the init string does not appear to be correct");
	
	auto sourceId = NVLib::StringUtils::String2Int(parts[0]);
	auto destinationId = NVLib::StringUtils::String2Int(parts[1]);
	auto weight = NVLib::StringUtils::String2Double(parts[2]);

	return new Edge(sourceId, destinationId, weight);
}

//--------------------------------------------------
// Getters
//--------------------------------------------------

/**
 * @brief Retrieve the edges for a given layer
 * @param layerId The layer identifier of the layer that we want the edges for
 * @return vector<Edge*>& The resultant edges
 */
vector<Edge*> & NetworkInfo::GetEdges(int layerId) 
{
	return _edges[layerId];
}