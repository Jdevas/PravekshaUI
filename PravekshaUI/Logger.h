#ifndef LOGGER_H
#define LOGGER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

#include <QObject>
#include < QtGUI >

#include <DatabaseHandler.h>

#include <fstream>
#include <direct.h>

using namespace cv;
using namespace std;
using namespace gpu;

class Logger : public QObject
{
    Q_OBJECT

	public:
		Logger();
		int writeFile(String violation, Mat* frame, int inViolationID, int writeType, int violationType, int speed);
		void setLogPath(String path);
		int getIncrementedViolationId();		
		
	signals:		
		void violationDetected(String violation);

	private:
		//Logger* logHandler;		
		Q_DISABLE_COPY(Logger);
		//String logFolderPath;
		int violationId;
		int wrongLaneViolationId;
		int overSpeedViolationId;
		int bothViolationId;
		DatabaseHandler* dbHandler;
};


#endif