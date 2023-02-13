//--------------------------------------------------
// Implementation of class SeriesGenerator
//
// @author: Wild Boar
//
// @date: 2023-02-05
//--------------------------------------------------

#include "SeriesGenerator.h"
using namespace NVL_AI;

//--------------------------------------------------
// Main Constructor
//--------------------------------------------------

/**
 * @brief Main Constructor
 * @param series The series that we are retrieving
 */
SeriesGenerator::SeriesGenerator(const vector<double>& series) : _series(series), _index(0)
{
	if (_series.size() == 0) throw runtime_error("The series generate requires at least one element in the list");
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
double SeriesGenerator::GetNext(int min, int max, int resolution)
{
	if (_index >= _series.size()) _index = 0;
	auto value = _series[_index++];
	if (value < min || value > max) throw runtime_error("Series value is out of range");
	return value;
}
