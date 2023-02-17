//--------------------------------------------------
// A helper class for the loading and decoding of initStrings
//
// @author: Wild Boar
//
// @date: 2023-02-18
//--------------------------------------------------

#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

#include "Model/Edge.h"
#include "Layer.h"

namespace NVL_AI
{
	class NetworkInfo
	{
	private:
		vector<int> _layerCounts;
		unordered_map<int, vector<Edge *>> _edges;

	public:
		NetworkInfo(const string& initString);

		void BuildNetwork(vector<Layer *>& layer);

		inline vector<int>& GetLayerCounts() { return _layerCounts; }
		inline unordered_map<int, vector<Edge *>>& GetEdges() { return _edges; }
	};
}
