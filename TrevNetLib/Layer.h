//--------------------------------------------------
// A layer within the neural network
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#pragma once

#include <iomanip>
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

		void AddEdge(Edge * edge);

		void GetSourceEdges(int nodeId, EdgeSet& edges);
		void GetDestinationEdges(int nodeId, EdgeSet& edges);
		void GetString(ostream& value);

		inline vector<Node *>& GetNodes() { return _nodes; }
		inline EdgeSet& GetEdges() { return _edges; }
		inline unordered_map<int, EdgeSet>& GetSourceLookup() { return _sourceLookup; }
		inline unordered_map<int, EdgeSet>& GetDestinationLookup() { return _destinationLookup; }
		inline int GetNodeCount() { return _nodes.size(); }
		inline int GetEdgeCount() { return _edges.size(); }
		inline Node * GetNode(int index) { return _nodes[index]; }
		inline Edge * GetEdge(int index) { return _edges[index]; }
	private:
		void UpdateLookup(unordered_map<int, EdgeSet> & lookup, int nodeId, Edge * edge);
		void GetEdgeSet(unordered_map<int, EdgeSet> & lookup, int nodeId, EdgeSet& edges);
	};
}
