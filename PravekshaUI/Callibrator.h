#ifndef CALLIBRATOR_H
#define CALLIBRATOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "Praveksha.h"
#include "WhiteLineDetector.h"

#include < QtGUI >

using namespace cv;
using namespace std;
using namespace gpu;

class Calibrator
{
	public:
		void drawLines(Mat *toDraw);
		void drawLines(Mat *toDraw, int i);
		void drawCircles(Mat *toDraw);
		void initiateRoi();
		vector<vector <int>> getRoI();
		vector<Point> getOriCorners();
		vector<double> getDistances();
		void setRoI(vector<vector <int>>);
		static void setOriCorners(vector<Point>);
		static void mouseHandler(int event, int x, int y, int flags, void* param);
		void callibrate();
		void stopVideo();
		static void calculateMappingDistances();
		vector<vector<int>> getWhitePointCordinates();
		QImage Calibrator::Mat2QImage(const cv::Mat3b &src);		
		static vector<Point> roiPoints;		
		static vector<Point> oriCorners;
		static void setDist();
		static vector<Point> sort(vector<Point> oriCorners);
		static void swap(Point *p1, Point *p2);

	private:
		String path;
		bool stop;
		static bool rightClicked;
		static vector<vector <int>> roi;		
		static vector<double> dist;
		vector<vector<int>> whitePointCordinates;
};

#endif