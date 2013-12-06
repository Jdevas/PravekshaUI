#ifndef VEHICLETRACKER_H
#define VEHICLETRACKER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;
using namespace gpu;

class VehicleTracker
{
	public:
		vector< vector<int> > vehicleTracker(vector< vector<int> > &blobs, vector< vector<int> > &previousBlobs, int rows);
};

#endif