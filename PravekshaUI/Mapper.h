#ifndef MAPPER_H
#define MAPPER_H

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

class Mapper
{
	public:
		Mapper();
		Mapper(vector<Point> oriCorners);
		Mapper(vector<Point> oriCorners,vector<double> dist);
		VehicleDataStruct transform1(vector<vector<int>> &blobs, VehicleDataStruct &vehicleData , Mat &frame,vector<Point> oriCorners, vector<double> dist, Logger &logHandler);
		Point transformPoint(int x, int yt,int row, int col, Mat &frame, vector<Point> oriCorners, vector<double> dist);
		
	private:
		vector<Point> oriCorners;	
		vector<double> dist;
};


#endif