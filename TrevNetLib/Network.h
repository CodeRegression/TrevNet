//--------------------------------------------------
// The main wrapper for the network functionality
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include "NetworkUtils.h"
#include "Generator/NumberGenerator.h"
#include "NetworkInfo.h"

namespace NVL_AI
{
	class Network
	{
	private:
		vector<Layer *> _layers;
	public:
		Network(const string& initString);
		Network(NumberGenerator * generator, const vector<int>& structure);
		~Network();

		void Evaluate(const vector<double>& inputs, vector<double>& outputs);
		double Update(const vector<double>& inputs, const vector<double>& expectedOutputs, double learnRate);

		void GetModelString(ostream& buffer);

		inline vector<Layer *>& GetLayers() { return _layers; }
	private:
		void ConnectLayer(Layer * layer, Layer * next, NumberGenerator * generator);
		void BackPropagate(vector<Layer *>& network, const vector<double>& inputs, const vector<double>& expected);
	};
}
