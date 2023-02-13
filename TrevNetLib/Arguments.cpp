//--------------------------------------------------
// Implementation code for Arguments
//
// @author: Wild Boar
//
// @date: 2023-02-13
//--------------------------------------------------

#include "Arguments.h"
using namespace NVL_Tools;

//--------------------------------------------------
// Constructors
//--------------------------------------------------

/**
 * Main
 * @param argc The number of input arguments to the system
 * @param argv The incomming values
 */
Arguments::Arguments(int argc, char ** argv)
{
	if (argc != 2) throw runtime_error("Usage: TrevNet <param>");
    _param = argv[1];
}
