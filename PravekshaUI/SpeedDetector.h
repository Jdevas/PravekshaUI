#ifndef SPEEDDETECTOR_H
#define SPEEDDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

#include <QObject>
#include < QtGUI >

#include "Praveksha.h"
#include "Logger.h"

using namespace cv;
using namespace std;
using namespace gpu;


class SpeedDetector //: public QObject
{
    //Q_OBJECT

	public:
		//explicit SpeedDetector(QObject *parent = 0);
		//SpeedDetector();
		SpeedDetector();
		SpeedDetector(vector<Point> oriCorners);
//		SpeedDetector::SpeedDetector(QObject *parent = 0):QObject(parent){}
		//vector<vector<int>> speedDetection(cv::Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &blobsPrevious, vector<vector<int>> &mapper, vector<vector<int>> whitePointCordiantes, vector<Point> oriCorners);
		vector<vector<int>> speedDetection(cv::Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &blobsPrevious, vector<vector<int>> &mapper, vector<vector<int>> whitePointCordiantes, vector<Point> oriCorners, Logger &logHandler);
		//void setLogger(Logger* logger);	
		

	//signals:
		//void speedViolationDetected(String violatoion);

	private:
		//Logger* logHandler;		
		//Q_DISABLE_COPY(SpeedDetector);
		vector<Point> oriCorners;

};


#endif