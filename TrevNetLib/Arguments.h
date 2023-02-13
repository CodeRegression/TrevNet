//--------------------------------------------------
// A container for commandline parameters
//
// @author: Wild Boar
//
// @date: 2023-02-13
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

namespace NVL_Tools
{
	class Arguments
	{
	private:
		string _param;
	public:
		Arguments(int argc, char ** argv);

		inline string& GetParam() { return _param; }
	};
}
