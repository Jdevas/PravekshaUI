#include "Praveksha.h"

#include <fstream>
#include <direct.h>

using namespace cv;
using namespace std;
using namespace gpu;

Logger::Logger(){
	setLogPath(" ");
}

void Logger::setLogPath(String path)
{
	logFolderPath = "F:\\20july2013_time_7am_9am\\Logs\\";
	violationId = 0;
}

void Logger::writeFile(String violation, Mat* frame){
	this->violationId = violationId+1;
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	stringstream namess;
	namess<< (now->tm_year + 1900) <<'-' <<(now->tm_mon + 1) << '-' <<  now->tm_mday;;
	string date =namess.str();
	string logFileName =  "Praveksha_"+date;	
	stringstream id ;
	id<<violationId;
	String folderName=logFolderPath+logFileName;
	String logFileFullPath = logFolderPath+logFileName+".csv";
	String screenShotFullPath=logFolderPath+logFileName+"\\"+id.str()+".jpg";

	ofstream fi;
	fi.open("debug.txt");
	fi << logFileFullPath;

	stringstream timess ;
	timess << violationId<<","<<(now-> tm_hour)<<":"<<(now-> tm_min)<<":"<<(now-> tm_sec)<<","<<violation<<","<<screenShotFullPath<<endl;
	String log= timess.str() ;

	ofstream myfile;
	myfile.open (logFileFullPath,ios::app);
	mkdir(folderName.c_str());
	imwrite(screenShotFullPath,*frame);
	myfile << log;
	myfile.close();
}