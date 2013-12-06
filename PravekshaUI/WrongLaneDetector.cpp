#include "WrongLaneDetector.h"


WrongLaneDetector::WrongLaneDetector(){

}

WrongLaneDetector::WrongLaneDetector(vector<Point> oriCorners,vector<double> dist){
	this->oriCorners=oriCorners;
	this->dist = dist;
	//this->mappedData = mappedData;
}

//void WrongLaneDetector::setLogger(Logger* logger)
//{
//	WrongLaneDetector::logHandler = logger;
//}


VehicleDataStruct WrongLaneDetector::WrongLaneDetection(cv::Mat oriFrame, VehicleDataStruct &vehicleData, vector<Point> oriCorners, vector<double> dist, Logger &logHandler){

	int width=0.5+ sqrt(1.0*(oriCorners[3].y-oriCorners[2].y)*(oriCorners[3].y-oriCorners[2].y)+(oriCorners[3].x-oriCorners[2].x)*(oriCorners[3].x-oriCorners[2].x));
	int height= 0.5+dist[dist.size()-1];//sqrt(1.0*(oriCorners[2].y-oriCorners[0].y)*(oriCorners[2].y-oriCorners[0].y)+(oriCorners[2].x-oriCorners[0].x)*(oriCorners[2].x-oriCorners[0].x));

	int leftLine=0;
	int leftCenterLine=width/4;
	int centerLine=width/2;
	int rightCenterLine=3*width/4;
	int rightLine=width;

	int topLine=0;
	int realMappingStart=height/2;
	int realMappingEnd=3*height/2;
	int bottomLine=2*height;

	double radiousRatio;
	int radius = 0;
	int CIRCLE_THRESHOULD = VariableStorage::CIRCLE_THRESHOULD;
	/*int leftRow1 = whitePointCordiantes[0][0];
	int leftCol1 = whitePointCordiantes[0][1];
	int leftRow2 = whitePointCordiantes[0][(whitePointCordiantes[0].size()-2)];
	int leftCol2 = whitePointCordiantes[0][(whitePointCordiantes[0].size()-1)];
	int rightRow1 = whitePointCordiantes[1][0];
	int rightCol1 = whitePointCordiantes[1][1];
	int rightRow2 = whitePointCordiantes[1][(whitePointCordiantes[0].size()-2)];
	int rightCol2 = whitePointCordiantes[1][(whitePointCordiantes[0].size()-1)];*/

	bool isOvertake = false;

	try{
	for(int i=0;i<vehicleData.blobs.size();i++){
		if(vehicleData.blobs[i][3]<=CIRCLE_THRESHOULD){
			continue;
		}
		if(vehicleData.blobs[i][14]==-1){
			radius = sqrt(vehicleData.blobs[i][3] / 2.00);
			circle( oriFrame, Point( vehicleData.blobs[i][2], vehicleData.blobs[i][1]), radius,  CV_RGB(255,0,0), 2, 8, 0 );
			
			continue;
		}


		isOvertake = false;		
		if((vehicleData.blobs[i][8]==0)&&(vehicleData.blobs[i][5]>0)){
			if(vehicleData.blobs[i][4]==1){

				if((((vehicleData.blobs[i][10]-rightCenterLine)<30))&&(vehicleData.blobs[i][11]>height)){

					for(int j=0;j<vehicleData.blobs.size();j++){
						if(vehicleData.blobs[j][3]<= CIRCLE_THRESHOULD){
							continue;
						}
						if(i==j||(vehicleData.blobs[j][4]==-1))
							continue;
						if((rightCenterLine-vehicleData.blobs[j][10])>0)
							continue;
						if(((vehicleData.blobs[i][11]-vehicleData.blobs[j][11])<2*height/3)&&((vehicleData.blobs[i][11]-vehicleData.blobs[j][11])>-2*height/3)){
							isOvertake = true;
							j = vehicleData.blobs.size();
						}
					}
					if((!isOvertake)&&(vehicleData.blobs[i][11]>height/2)){
						for(int j=0;j<vehicleData.mappedData.size();j++){
							if((vehicleData.mappedData[j][3]==-1))
								continue;
							if((rightCenterLine-vehicleData.mappedData[j][0])>0)
								continue;
							if(((vehicleData.blobs[i][11]-vehicleData.mappedData[j][1])<2*height/3)&&((vehicleData.blobs[i][11]-vehicleData.mappedData[j][1])>-2*height/3)){
								isOvertake = true;
							}
						}
					}
					if(!isOvertake){
						vehicleData.blobs[i][14]++;

					}

				}

				//if(((rightCol1-blobs[i][2])*(rightRow2-blobs[i][1])-(rightCol2-blobs[i][2])*(rightRow1-blobs[i][1]))<0){
				//	//cout<< "Wrong" <<endl;
				//}else{
				//	//cout<< "Correct" <<endl;
				//}
			}
			if(vehicleData.blobs[i][4]==-1){
				/*cout<<"AAAAA"<<leftCenterLine<<endl;
				cout<<"BBBBB"<<blobs[i][10]<<endl;*/

				if(((leftCenterLine-vehicleData.blobs[i][10])<30)&&(vehicleData.blobs[i][11]<height)){
					for(int j=0;j<vehicleData.blobs.size();j++){
						if(vehicleData.blobs[j][3]<= CIRCLE_THRESHOULD){
							continue;
						}
						if(i==j||(vehicleData.blobs[i][4]==1))
							continue;
						if((leftCenterLine-vehicleData.blobs[j][10])<0)
							continue;
						if(((vehicleData.blobs[i][11]-vehicleData.blobs[j][11])<2*height/3)&&((vehicleData.blobs[i][11]-vehicleData.blobs[j][11])>-2*height/3)){
							isOvertake = true;
							j = vehicleData.blobs.size();
						}
					}
					if((!isOvertake)&&(vehicleData.blobs[i][11]<height/2)){
						for(int j=0;j<vehicleData.mappedData.size();j++){
							if((vehicleData.mappedData[j][3]==1))
								continue;
							if((leftCenterLine-vehicleData.mappedData[j][0])<0)
								continue;
							if(((vehicleData.blobs[i][11]-vehicleData.mappedData[j][1])<2*height/3)&&((vehicleData.blobs[i][11]-vehicleData.mappedData[j][1])>-2*height/3)){
								isOvertake = true;
							}
						}
					}
					if(!isOvertake){
						vehicleData.blobs[i][14]++;

					}
				}
			}

			if(vehicleData.blobs[i][14]>3){

				vehicleData.blobs[i][14] = -1;
				radius = sqrt(vehicleData.blobs[i][3] / 2.00);

				circle( oriFrame, Point( vehicleData.blobs[i][2], vehicleData.blobs[i][1]), radius,  CV_RGB(255,0,0), 2, 8, 0 );

				//if(vehicleData.blobs[i][7]!=0){
					vehicleData.blobs[i][15] = logHandler.getIncrementedViolationId();
					vehicleData.blobs[i][16] = 1;
					vehicleData.blobs[i][7] = logHandler.writeFile("Wrong Lane",&oriFrame, vehicleData.blobs[i][15], 1, vehicleData.blobs[i][16],0);
				/*}else{
					vehicleData.blobs[i][15] = logHandler.getIncrementedViolationId();
					vehicleData.blobs[i][16] = 1;
					vehicleData.blobs[i][7] = logHandler.writeFile("Wrong Lane ",&oriFrame,0, 1, 1);
				}*/
				
			}

		}
	}
	}catch(std::exception& ex){
		VariableStorage::frameNo;
		int lll=0;
		}

	return vehicleData;
}