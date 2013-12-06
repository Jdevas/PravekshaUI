#include "Praveksha.h"
#include "Logger.h"

using namespace cv;
using namespace std;
using namespace gpu;


//typedef struct ViolationData
//{
//  String violation;
//  int violationId;
//} ;

Logger::Logger(){

	setLogPath(" ");
	dbHandler = new DatabaseHandler;
	dbHandler->initiateDB();
	wrongLaneViolationId = 0;
	overSpeedViolationId = 0;
	bothViolationId = 0;
}

void Logger::setLogPath(String path)
{
	if(VariableStorage::loggerPath==""){
		VariableStorage::loggerPath = "F:/20july2013_time_7am_9am/Logs/";
	}
	//logFolderPath = VariableStorage::loggerPath;
	violationId = 0;
}

int Logger::writeFile(String violation, Mat* frame, int inViolationID, int writeType, int violationType, int speed){

	inViolationID;

	if(writeType==4){
		dbHandler->insertVehicle(speed);

		return 0;
	}

	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	stringstream namess;
	namess<< (now->tm_year + 1900) <<'-' <<(now->tm_mon + 1) << '-' <<  now->tm_mday;
	string date =namess.str();	

	stringstream times;
	times <<(now-> tm_hour)<<":"<<(now-> tm_min)<<":"<<(now-> tm_sec);

	string logFileName =  "Praveksha_"+date;	
	stringstream id ;

	if(violationType==1){
		id<<inViolationID;
		violation = "Wrong Lane";		
	}
	else if(violationType==2){
		id<<inViolationID;				
		violation = "Over Speed";
	}else if (violationType==3){
		id<<inViolationID;
		id<<"_2";
		violation = "Wrong Lane and Over Speed";
	}
	String folderName=VariableStorage::loggerPath+logFileName;
	String logFileFullPath = VariableStorage::loggerPath+logFileName+".csv";
	String screenShotFullPath=folderName+"\\"+id.str()+".jpg";

	ofstream fi;
	fi.open("debug.txt");
	fi << logFileFullPath;
	ofstream myfile;
	myfile.open (logFileFullPath,ios::app);
	mkdir(folderName.c_str());

	if(writeType==1){		//only Image

		

		imwrite(screenShotFullPath,*frame);		
		//dbHandler->insertViolation(violation, violationId);
	}
	if(writeType==2){		//only Log
		wrongLaneViolationId++;
		stringstream s;
		s << inViolationID << "_WL" << wrongLaneViolationId << " : Wrong lane violated " << "at " << times.str();
		emit violationDetected(s.str());

		stringstream timess ;
		timess << inViolationID<<","<<times.str()<<","<<violation<<","<<screenShotFullPath<<endl;
		String log= timess.str();		
		myfile << log;		
		dbHandler->insertViolation(violation, inViolationID, violationType);		
	}
	if(writeType==3){	//both image & Log	
		stringstream s;

		if(violationType == 2){	
			overSpeedViolationId++;
			s << inViolationID << "_OS" << overSpeedViolationId << " : Over Speed at " << speed << " kmph " << "at " << times.str();	
			emit violationDetected(s.str());
		}
		if(violationType == 3){
			bothViolationId++;
			s << inViolationID << "_BV" << bothViolationId << " : Wrong Lane violated at Over Speed of " << speed << " kmph " << "at " << times.str();	
			emit violationDetected(s.str());
		}

	

		stringstream timess ;
		timess << inViolationID<<","<<times.str()<<","<<violation<<","<<screenShotFullPath<<endl;
		String log= timess.str();
		imwrite(screenShotFullPath,*frame);
		myfile << log;
		dbHandler->insertViolation(violation, inViolationID, violationType);
	}
	myfile.close();

	return inViolationID;
}

int Logger::getIncrementedViolationId(){
	this->violationId++;
	return violationId;
}

