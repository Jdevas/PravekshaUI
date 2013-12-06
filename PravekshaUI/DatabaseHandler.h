#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

#include <windows.h> 
#include <strsafe.h>
#include <sqlite3.h>
#include <fstream>

using namespace cv;
using namespace std;
using namespace gpu;

class DatabaseHandler{
	public:
		DatabaseHandler();
		void initiateDB();
		void insertVehicle(int speed);
		void insertViolation(String violation, int violationId, int violationType);
		vector<vector <int>> retrieveTodayData();

};

#endif