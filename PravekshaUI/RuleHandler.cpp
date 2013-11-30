#include "Praveksha.h"

using namespace cv;
using namespace std;
using namespace gpu;

RuleHandler::RuleHandler(){

}

RuleHandler::RuleHandler(VehicleDataStruct &vehicleData, Mat oriFrame, vector<vector<int>> whitePoints, SpeedDetector *sp)
{
	vehicleData = vehicleData;
	frame = oriFrame;
	whitePointCordiantes = whitePoints;
	setSpeedRule(sp);
	
}

void RuleHandler::setSpeedRule(SpeedDetector *sp){
	speedRule = sp;
	logHandler = new Logger;
}

void RuleHandler::setFrame(cv::Mat fr){
	this->frame = fr;
}

void RuleHandler::setVehicleData(VehicleDataStruct vehicleData){
	this->vehicleData = vehicleData;
}

VehicleDataStruct RuleHandler::detectRules(vector<Point> oriCorners, vector<double> dist)
{
	speedRule -> setLogger(logHandler);
	this->vehicles = speedRule -> speedDetection(frame, vehicleData.blobs, vehicleData.previousBlobs, vehicleData.mapper, this->whitePointCordiantes, oriCorners);	
	this->vehicleData =  transformer->transform1(vehicles, vehicleData,frame,oriCorners, dist );	
	
	return this->vehicleData;
}
