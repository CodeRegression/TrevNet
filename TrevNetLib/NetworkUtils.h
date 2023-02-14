//--------------------------------------------------
// A set of utilities for performing the neural network calculations
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include "Layer.h"

namespace NVL_AI
{
	class NetworkUtils
	{
	public:
		static void ForwardPropagate(Layer* bottomLayer, Layer* topLayer);
		static void BackwardPropagate(Layer * topLayer, Layer * bottomLayer);
		static double UpdateWeight(vector<Layer *>& network, int layerId, int edgeId, double factor);
		static double Relu(double value);
		static double GetError(double expected, double actual);
	};
}
