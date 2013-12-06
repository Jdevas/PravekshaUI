#ifndef WRONGLANEDETECTOR_H
#define WRONGLANEDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

#include <Praveksha.h>
#include "Logger.h"

using namespace cv;
using namespace std;
using namespace gpu;

class WrongLaneDetector
{
	public:
		WrongLaneDetector();
		WrongLaneDetector(vector<Point> oriCorners,vector<double> dist);
		VehicleDataStruct WrongLaneDetection(cv::Mat oriFrame, VehicleDataStruct &vehicleData, vector<Point> oriCorners, vector<double> dist, Logger &logHandler);
		//void setLogger(Logger* logger);

	private:
		vector<Point> oriCorners;
		vector<double> dist;
		//Logger* logHandler;		
		//vector<vector<double>> mappedData;

};


#endif