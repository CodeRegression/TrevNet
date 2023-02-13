//--------------------------------------------------
// Implementation of class Edge
//
// @author: Wild Boar
//
// @date: 2023-02-13
//--------------------------------------------------

#include "Edge.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param source Initialize variable <source>
 * @param destination Initialize variable <destination>
 * @param weight Initialize variable <weight>
 */
Edge::Edge(int source, int destination, double weight)
{
	_source = source;
	_destination = destination;
	_weight = weight;
}