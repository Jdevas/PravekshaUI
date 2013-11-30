# include "Praveksha.h"


WrongLaneDetector::WrongLaneDetector(){

}

WrongLaneDetector::WrongLaneDetector(vector<Point> oriCorners,vector<double> dist,vector<vector<double>> mappedData){
	this->oriCorners=oriCorners;
	this->dist = dist;
	this->mappedData = mappedData;
}

void WrongLaneDetector::WrongLaneDetection(cv::Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &mapper){

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


	/*int leftRow1 = whitePointCordiantes[0][0];
	int leftCol1 = whitePointCordiantes[0][1];
	int leftRow2 = whitePointCordiantes[0][(whitePointCordiantes[0].size()-2)];
	int leftCol2 = whitePointCordiantes[0][(whitePointCordiantes[0].size()-1)];
	int rightRow1 = whitePointCordiantes[1][0];
	int rightCol1 = whitePointCordiantes[1][1];
	int rightRow2 = whitePointCordiantes[1][(whitePointCordiantes[0].size()-2)];
	int rightCol2 = whitePointCordiantes[1][(whitePointCordiantes[0].size()-1)];*/

	bool isOvertake = false;

	for(int i=0;i<blobs.size();i++){
		isOvertake = false;		
		if((blobs[i][8]==0)&&(blobs[i][5]>0)){
			if(blobs[i][4]==1){

				if((((blobs[i][10]-rightCenterLine)<30)&&((blobs[i][10]-rightCenterLine)<0))&&(blobs[i][11]>height)){

					for(int j=0;j<blobs.size();j++){
						if(i==j||(blobs[j][4]==-1))
							continue;
						if(((blobs[i][11]-blobs[j][11])<height/2)&&((blobs[i][11]-blobs[j][11])>-height/2)){
							isOvertake = true;
							j = blobs.size();
						}
					}
					if((!isOvertake)&&(blobs[i][11]>height/2)){
						for(int j=0;j<mappedData.size();j++){
							if((mappedData[i][3]==-1))
								continue;
							if(((blobs[i][11]-mappedData[j][1])<height/2)&&((blobs[i][11]-mappedData[j][1])>-height/2)){
								isOvertake = true;
							}
						}
					}
					if(!isOvertake){
						cout<< "Wrong Down"<<endl;
						system("Pause");
					}

				}

				//if(((rightCol1-blobs[i][2])*(rightRow2-blobs[i][1])-(rightCol2-blobs[i][2])*(rightRow1-blobs[i][1]))<0){
				//	//cout<< "Wrong" <<endl;
				//}else{
				//	//cout<< "Correct" <<endl;
				//}
			}
			if(blobs[i][4]==-1){
				/*cout<<"AAAAA"<<leftCenterLine<<endl;
				cout<<"BBBBB"<<blobs[i][10]<<endl;*/

				if(((leftCenterLine-blobs[i][10])<30)&&((leftCenterLine-blobs[i][10])<0)&&(blobs[i][11]<height)){
					for(int j=0;j<blobs.size();j++){
						if(i==j||(blobs[i][4]==1))
							continue;
						if(((blobs[i][11]-blobs[j][11])<height/2)&&((blobs[i][11]-blobs[j][11])>-height/2)){
							isOvertake = true;
							j = blobs.size();
						}
					}
					if((!isOvertake)&&(blobs[i][11]<height/2)){
						for(int j=0;j<mappedData.size();j++){
							if((mappedData[i][3]==1))
								continue;
							if(((blobs[i][11]-mappedData[j][1])<height/2)&&((blobs[i][11]-mappedData[j][1])>-height/2)){
								isOvertake = true;
							}
						}
					}
					if(!isOvertake){
						cout<<"WWWWW "<< blobs[i][5]<<endl;
						
						cout<< "Wrong Up"<<endl;
						system("Pause");
					}
				}
			}
		}
	}

}