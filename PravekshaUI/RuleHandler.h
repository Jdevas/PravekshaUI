#ifndef RULEHANDLER_H
#define RULEHANDLER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

#include <Praveksha.h>
#include <SpeedDetector.h>
#include <Logger.h>
#include <Mapper.h>
#include <WrongLaneDetector.h>

using namespace cv;
using namespace std;
using namespace gpu;

class RuleHandler
{
	public:
		RuleHandler();
		//RuleHandler(VehicleDataStruct vehicleData, Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &blobsPrevious, vector<vector<int>> &mapper, vector<vector<int>> whitePointCordiantes, SpeedDetector *sp, vector<vector<double>> mappedData);
		RuleHandler(VehicleDataStruct &vehicleData, Mat oriFrame, vector<vector<int>> whitePoints, Logger *logger);
		void setSpeedRule(SpeedDetector *s);
		//vector<vector<int>> detectRules(vector<Point> oriCorners, vector<double> dist);
		VehicleDataStruct detectRules(vector<Point> oriCorners, vector<double> dist);
		//vector<vector<double>> homograraphicTransform(vector<Point> oriCorners, vector<double> dist, vector<vector<double>> mappedData);
		void setFrame(cv::Mat fr);
		void setVehicleData(VehicleDataStruct vehicleData);
		/*void setBlob(vector< vector<int> > bl);
		void setPreviouseBlob(vector< vector<int> > prbl);
		void setMapper(vector< vector<int> > mpr);	
		void setMappedData(vector< vector<double> > mappedD);	*/

	private:
		Mat frame;
		VehicleDataStruct vehicleData;
		vector<vector<int>> vehicles;
		vector<vector<int>> vehiclesPrevious;
		vector<vector<int>> vehicleMapper;
		vector<vector<double>> mappedData;
		vector<vector<int>> whitePointCordiantes;
		SpeedDetector* speedRule;
		Mapper* transformer;
		WrongLaneDetector* wrongLaneDetector;

		Logger* logHandler;
};


#endif