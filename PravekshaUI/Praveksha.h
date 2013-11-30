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
#include <sqlite3.h>

#include <QObject>
#include < QtGUI >

using namespace cv;
using namespace std;
using namespace gpu;

//extern vector<vector <int>> roi;

//extern long violationId;
//extern String logFolderPath;
//
//extern int frameNo;
//extern int delay;
//
//extern int THRESHOULD_BLOB_VALUE;
//extern int CIRCLE_THRESHOULD;
//extern int CLOSEBY_THRESHOULD;
//extern int BACKGROUND_SUBSTRACTION_THRESHOULD;


struct VehicleDataStruct {
		vector< vector<int> > blobs;
		vector<vector<double>> mappedData;
		vector< vector<int> > previousBlobs;
		vector< vector<int> > mapper;
	};

static class VariableStorage
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

};

class Calibrator
{
	public:
		void drawLines(Mat *toDraw);
		void initiateRoi();
		vector<vector <int>> getRoI();
		vector<Point> getOriCorners();
		vector<double> getDistances();
		void setRoI(vector<vector <int>>);
		void setOriCorners(vector<Point>);
		static void mouseHandler(int event, int x, int y, int flags, void* param);
		void callibrate();
		void stopVideo();
		void calculateMappingDistances();
		vector<vector<int>> getWhitePointCordinates();
		QImage Calibrator::Mat2QImage(const cv::Mat3b &src);		
		static vector<Point> roiPoints;
		void setDist();

	private:
		String path;
		bool stop;
		static bool rightClicked;
		static vector<vector <int>> roi;		
		static vector<Point> oriCorners;		
		static vector<double> dist;
		vector<vector<int>> whitePointCordinates;
};

class WhiteLineDetector
{
	private:
		int THRESHOULD_BLOB_VALUE;
		int CIRCLE_THRESHOULD;
		vector<vector<int>> whitePointCordiantes;
		vector< vector<int> > whitePointesExpandBlobMatrix(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> roi);
		void whitePointesRecursiveFourNeighbour(Mat &frame, int row, int col, int blobLable, vector< vector<int> > &matrix);
		vector< vector<int> > whiteBlobsCentroidAndDrawCircle(cv::Mat &oriFrame,cv::Mat &whiteFrame, vector< vector<int> > &matrix, vector<int> &blobLablesUsed, vector<vector <int>> roi);
		double getGradient(int row1, int col1, int row2, int col2);
		bool isColinear(int firstBlobNo, int secondBlobNo, int thridBlobNo, int row, int col, int row1, int col1, int row2, int col2);
		double averageGradient(int firstBlobNo, int secondBlobNo, int thridBlobNo, int row, int col, int row1, int col1, int row2, int col2);
		vector<vector <int>> removeSmallBlobs(vector<vector <int>> &blobs);
		vector<vector <double>> removeExtraPoints(vector<vector <double>> &whitePoints);
		vector<vector <double>> calculateMidleWhiteLines(cv::Mat &whiteFrame, vector<vector<int>> &oriBlobs);
		vector<vector<double>> mergeWhiteLines(vector<vector <double>> &colinearBlobNo);
		vector<vector<double>> removeLongLines(vector<vector<double>> &groupedPoints, vector<vector<int>> &oriWhitePoints);
		vector<vector<int>> getWhiteLineCordinates(vector<vector<double>> &whiteLineBlobNo, vector<vector<int>> &oriWhitePoints);

	public:
		vector<vector<int>> getWhitePointCordinates();
		vector<vector<int>> identifyWhitePoints(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> roi);
};

class Logger
{
	public:
		Logger();
		void writeFile(String violation, Mat* frame);
		void setLogPath(String path);

	private:
		String logFolderPath;
		long violationId;

};

class WrongLaneDetector
{
	public:
		WrongLaneDetector();
		WrongLaneDetector(vector<Point> oriCorners,vector<double> dist,vector<vector<double>> mappedData);
		void WrongLaneDetection(cv::Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &mapper);

	private:
		vector<Point> oriCorners;
		vector<double> dist;
		vector<vector<double>> mappedData;

};

class Mapper
{
	public:
		Mapper(vector<Point> oriCorners);
		Mapper(vector<Point> oriCorners,vector<double> dist);
		VehicleDataStruct transform1(vector<vector<int>> &blobs, VehicleDataStruct &vehicleData , Mat &frame,vector<Point> oriCorners, vector<double> dist);
		Point transformPoint(int x, int yt,int row, int col, Mat &frame, vector<Point> oriCorners, vector<double> dist);

	private:
		vector<Point> oriCorners;	
		vector<double> dist;
};

class SpeedDetector : public QObject
{
    Q_OBJECT

	public:
		//explicit SpeedDetector(QObject *parent = 0);
		//SpeedDetector();
		SpeedDetector(vector<Point> oriCorners);
		SpeedDetector::SpeedDetector(QObject *parent = 0):QObject(parent){}
		vector<vector<int>> speedDetection(cv::Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &blobsPrevious, vector<vector<int>> &mapper, vector<vector<int>> whitePointCordiantes, vector<Point> oriCorners);
		void setLogger(Logger* logger);	
		

	signals:
		void violationDetected(double speed);

	private:
		Logger* logHandler;		
		Q_DISABLE_COPY(SpeedDetector);
		vector<Point> oriCorners;

};


class RuleHandler
{
	public:
		RuleHandler();
		//RuleHandler(VehicleDataStruct vehicleData, Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &blobsPrevious, vector<vector<int>> &mapper, vector<vector<int>> whitePointCordiantes, SpeedDetector *sp, vector<vector<double>> mappedData);
		RuleHandler::RuleHandler(VehicleDataStruct &vehicleData, Mat oriFrame, vector<vector<int>> whitePoints, SpeedDetector *sp);
		void setSpeedRule(SpeedDetector *s);
		//vector<vector<int>> detectRules(vector<Point> oriCorners, vector<double> dist);
		VehicleDataStruct RuleHandler::detectRules(vector<Point> oriCorners, vector<double> dist);
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

		Logger* logHandler;
};

class VehicleIdentifier
{
	public:
		vector< vector<int> > expandBlobMatrix(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> &roi);

	private:
		int THRESHOULD_BLOB_VALUE;
		int CIRCLE_THRESHOULD;
		void recursiveFourNeighbour(Mat &frame, int row, int col, int blobLable, vector< vector<int> > &matrix);
		vector< vector<int> > identifyCentroidAndDrawCircle(cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<int> &blobLablesUsed, vector<vector <int>> roi);
};

class VehicleTracker
{
	public:
		vector< vector<int> > vehicleTracker(vector< vector<int> > &blobs, vector< vector<int> > &previousBlobs, int rows);
};

class DatabaseHandler{
	public:
		void initiateDB();
		void insertVehicle(int speed);
		void insertViolation(String violation, int violationId);
};

class PravekshaHandler
{
	public:
		PravekshaHandler(SpeedDetector *spd);
		PravekshaHandler();
		void pravekshaHandler();
		void setCalibrator(Calibrator cal);
		
		
	private:
		vector<vector <int>> roi;

		String path;		
		int morph_elem;
		int morph_size;
		int morph_operator;
		//int const max_operator = 4;
		//int const max_elem = 2;
		static int const max_kernel_size = 21;

		double WEIGHT;
		
		WhiteLineDetector whiteLineDetector;
		VehicleIdentifier vehicleidentifier;
		VehicleTracker vehiTracker;
		Calibrator callibrator;
		RuleHandler ruleHandler;
		SpeedDetector* sp;

};



#endif