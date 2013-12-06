#ifndef PRAVEKSHAHANDLER_H
#define PRAVEKSHAHANDLER_H

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

#include <windows.h> 
#include <strsafe.h> 
#include <stdio.h>

#include <Callibrator.h>
#include <WhiteLineDetector.h>
#include <VehicleIdentifier.h>
#include <VehicleTracker.h>
#include <SpeedDetector.h>
#include <RuleHandler.h>

using namespace cv;
using namespace std;
using namespace gpu;

class PravekshaHandler
{
	public:
		PravekshaHandler(Logger *logger);
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
		//DatabaseHandler databaseHandler;
		//SpeedDetector* sp;
		Logger* logHandler; 


};


#endif