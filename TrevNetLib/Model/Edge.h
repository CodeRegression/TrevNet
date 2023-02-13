//--------------------------------------------------
// Describes the link between two nodes in a neural network
//
// @author: Wild Boar
//
// @date: 2023-02-13
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

namespace NVL_AI
{
	class Edge
	{
		private:
			int _source;
			int _destination;
			double _weight;
		public:
			Edge(int source, int destination, double weight);

			inline int& GetSource() { return _source; }
			inline int& GetDestination() { return _destination; }
			inline double& GetWeight() { return _weight; }

			inline void SetWeight(double value) { _weight = value; }
	};
}
