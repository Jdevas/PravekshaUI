#include "RuleHandler.h"

using namespace cv;
using namespace std;
using namespace gpu;

RuleHandler::RuleHandler(){

}

RuleHandler::RuleHandler(VehicleDataStruct &vehicleData, Mat oriFrame, vector<vector<int>> whitePoints, Logger *logger)
{
	vehicleData = vehicleData;
	frame = oriFrame;
	whitePointCordiantes = whitePoints;
	//setSpeedRule(sp);
	logHandler = logger;
	speedRule = new SpeedDetector;
	transformer = new Mapper;
	wrongLaneDetector = new WrongLaneDetector;
	

}

//void RuleHandler::setSpeedRule(SpeedDetector *sp){
//	speedRule = sp;
//	//logHandler = new Logger;
//}

void RuleHandler::setFrame(cv::Mat fr){
	this->frame = fr;
}

void RuleHandler::setVehicleData(VehicleDataStruct vehicleData){
	this->vehicleData = vehicleData;
}

VehicleDataStruct RuleHandler::detectRules(vector<Point> oriCorners, vector<double> dist){
	//speedRule -> setLogger(logHandler);
	//wrongLaneDetector ->setLogger(logHandler);
	
	
	
	if(VariableStorage::frameNo==90)
		int jhhh=0;
	this->vehicles = speedRule -> speedDetection(frame, vehicleData.blobs, vehicleData.previousBlobs, vehicleData.mapper, this->whitePointCordiantes, oriCorners, *logHandler);	
	this->vehicleData =  transformer->transform1(vehicles, vehicleData,frame,oriCorners, dist, *logHandler );	
	this->vehicleData = wrongLaneDetector->WrongLaneDetection(frame, vehicleData, oriCorners, dist, *logHandler);
	
	
	return this->vehicleData;
}
