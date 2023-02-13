//--------------------------------------------------
// A class for loading and retrieving a series of numbers (in a loop)
//
// @author: Wild Boar
//
// @date: 2023-02-05
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include "NumberGenerator.h"

namespace NVL_AI
{
	class SeriesGenerator : public NumberGenerator
	{
	private:
		vector<double> _series;
		int _index;
	public:
		SeriesGenerator(const vector<double>& series);
		virtual double GetNext(int min, int max, int resolution) override;
		inline int& GetIndex() { return _index; }
	};
}
