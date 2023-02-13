//--------------------------------------------------
// The definition of a node within the system
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
	class Node
	{
	private:
		double _forwardValue;
		double _backwardValue;
	public:
		Node();

		inline double& GetForwardValue() { return _forwardValue; }
		inline double& GetBackwardValue() { return _backwardValue; }

		inline void SetForwardValue(double value) { _forwardValue = value; }
		inline void SetBackwardValue(double value) { _backwardValue = value; }
	};
}
