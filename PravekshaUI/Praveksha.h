#ifndef PRAVEKSHA_H
#define PRAVEKSHA_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <sstream>

using namespace cv;
using namespace std;
using namespace gpu;


struct VehicleDataStruct {
	vector< vector<int> > blobs;
	vector<vector<double>> mappedData;
	vector< vector<int> > previousBlobs;
	vector< vector<int> > mapper;
};

class VariableStorage
{
public:
	static int const THRESHOULD_BLOB_VALUE = 220;
	static int const CIRCLE_THRESHOULD = 600;
	static int const CLOSEBY_THRESHOULD = 200;
	static int const BACKGROUND_SUBSTRACTION_THRESHOULD = 50;
	static int delay;
	static int frameNo;
	static int rightClickFrameNo;
	static String path;	
	static String loggerPath;
	static double distance;

};

#endif