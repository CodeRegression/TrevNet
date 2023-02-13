//--------------------------------------------------
// A class for loading and retrieving random numbers
//
// @author: Wild Boar
//
// @date: 2023-02-05
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/RandomUtils.h>
#include "NumberGenerator.h"

namespace NVL_AI
{
	class RandomGenerator : public NumberGenerator
	{
	public:
		RandomGenerator();
		virtual double GetNext(int min, int max, int resolution) override;
	};
}
