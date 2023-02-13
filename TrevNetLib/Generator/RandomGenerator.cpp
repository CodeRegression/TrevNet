//--------------------------------------------------
// Implementation of class RandomGenerator
//
// @author: Wild Boar
//
// @date: 2023-02-05
//--------------------------------------------------

#include "RandomGenerator.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Default Constructor
 */
RandomGenerator::RandomGenerator()
{
	// Extra initialization can go here
}

//--------------------------------------------------
// Number Retrieval
//--------------------------------------------------

/**
 * @brief Retrieve the next number in the list
 * @param min The minimum number in the range
 * @param max The maximum number in the range
 * @param resolution Determines the number of decimal placed
 * @return double Returns a double
 */
double RandomGenerator::GetNext(int min, int max, int resolution)
{
	auto scale = (int) pow(10, resolution);
	auto value = (double)NVLib::RandomUtils::GetInteger(min * scale, max * scale);
	value = value / (double) scale;
	return value;
}
