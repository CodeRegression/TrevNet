//--------------------------------------------------
// A base class for a "source" of numbers
//
// @author: Wild Boar
//
// @date: 2023-02-05
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

namespace NVL_AI
{
	class NumberGenerator
	{
	public:
		NumberGenerator() {}
		virtual double GetNext(int min, int max, int resolution) = 0;
	};
}