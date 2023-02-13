//--------------------------------------------------
// A layer within the neural network
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

#include "Model/Node.h"
#include "Model/Edge.h"

namespace NVL_AI
{
	typedef vector<Edge *> EdgeSet;

	class Layer
	{
	private:
		vector<Node *> _nodes;
		EdgeSet _edges;
		unordered_map<int, EdgeSet> _sourceLookup;
		unordered_map<int, EdgeSet> _destinationLookup;
	public:
		Layer(int nodeCount);
		~Layer();

		void AddEdge(int sourceIndex, int destinationIndex, double weight);

		void GetSourceEdges(int nodeId, EdgeSet& edges);
		void GetDestinationEdges(int nodeId, EdgeSet& edges);

		inline vector<Node *>& GetNodes() { return _nodes; }
		inline EdgeSet& GetEdges() { return _edges; }
		inline unordered_map<int, EdgeSet>& GetSourceLookup() { return _sourceLookup; }
		inline unordered_map<int, EdgeSet>& GetDestinationLookup() { return _destinationLookup; }
	private:
		void UpdateLookup(unordered_map<int, EdgeSet> & lookup, int nodeId, Edge * edge);
		void GetEdgeSet(unordered_map<int, EdgeSet> & lookup, int nodeId, EdgeSet& edges);
	};
}
