#include "SpeedDetector.h"

using namespace cv;
using namespace std;
using namespace gpu;


SpeedDetector::SpeedDetector(){}

SpeedDetector::SpeedDetector(vector<Point> oriCorners){
	this->oriCorners = oriCorners;
}

vector<vector<int>> SpeedDetector::speedDetection(cv::Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &blobsPrevious, vector<vector<int>> &mapper, vector<vector<int>> whitePointCordiantes, vector<Point> oriCorners, Logger &logHandler)
{

	int frameNo = VariableStorage::frameNo;
	int delay = VariableStorage::delay;
	int BACKGROUND_SUBSTRACTION_THRESHOULD = VariableStorage::BACKGROUND_SUBSTRACTION_THRESHOULD;
	int CIRCLE_THRESHOULD = VariableStorage::CIRCLE_THRESHOULD;
	int CLOSEBY_THRESHOULD = VariableStorage::CLOSEBY_THRESHOULD;
	int THRESHOULD_BLOB_VALUE = VariableStorage::THRESHOULD_BLOB_VALUE;		
	
	Point p1(oriCorners[0].x,1080-oriCorners[0].y);
	Point p2(oriCorners[1].x,1080-oriCorners[1].y);
	Point p3(oriCorners[2].x,1080-oriCorners[2].y);
	Point p4(oriCorners[3].x,1080-oriCorners[3].y);

	double distaceSpeedP = 0.05;
	//////////////end of hard code variables////////////

	int noOfCheckingLines = 2;
	vector <vector<int>> speedVec(blobs.size(), vector<int>(2));
	int frameDiff = 0;
	double speed = 0;
	int finalSpeed = 0;
	int tempSpeed = 0;
	long timeMili = 0;

	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.5;
	int thickness = 3;
	int baseline = 0;
	int radius = 0;
	string s;
	stringstream ss;

	for(int i=0; i<blobs.size(); i++){
		speed = 0;
		finalSpeed = 0;
		tempSpeed = 0;
		vector<int> positionValues(noOfCheckingLines);
		int positionValue = 0;

		if(blobs[i][3]<=CIRCLE_THRESHOULD)
			continue;
		/*if(blobs[i][5]==-1)
		continue;*/
		for(int j=0;j<mapper.size();j++){
			if(mapper[j][1]==blobs[i][0]){
				for(int k =0; k<blobsPrevious.size(); k++){
					if(blobsPrevious[k][3]<CIRCLE_THRESHOULD)
						continue;
					/*if(blobsPrevious[j][5]==-1)
					continue;*/
					if(mapper[j][0]==blobsPrevious[k][0]){
						blobs[i][5] = blobsPrevious[k][5];
						blobs[i][6] = blobsPrevious[k][6];
						blobs[i][7] = blobsPrevious[k][7];
						blobs[i][8] = blobsPrevious[k][8];

						blobs[i][9] = blobsPrevious[k][9];
						blobs[i][10] = blobsPrevious[k][10];

						blobs[i][11] = blobsPrevious[k][11];//xmapping						
						blobs[i][12] = blobsPrevious[k][12];//ymapping
						blobs[i][13] = blobsPrevious[k][13];//speed*100
						blobs[i][14] = blobsPrevious[k][14];//isMapped
						blobs[i][15] = blobsPrevious[k][15];
						blobs[i][16] = blobsPrevious[k][16];
						k=blobsPrevious.size();
					}
				}				
				j=mapper.size();
			}
		}		

		if(blobs[i][5]==-1){			
			continue;
		}

		positionValues[0] = ((oriCorners[0].x - blobs[i][2])*(oriCorners[1].y- blobs[i][1]) - (oriCorners[1].x - blobs[i][2])*(oriCorners[0].y - blobs[i][1]));		
		positionValues[1] = ((oriCorners[3].x - blobs[i][2])*(oriCorners[2].y- blobs[i][1]) - (oriCorners[2].x - blobs[i][2])*(oriCorners[3].y - blobs[i][1]));

		for(int n=0;n<positionValues.size();n++){

			if(blobs[i][4] == 1){							// is going down
				if((positionValues[n] >=0 ) && (blobs[i][5]==0) ){



					blobs[i][5] = frameNo;	
					blobs[i][6] = n;

					cout<< "Down In frame No - "<< frameNo<<endl;
				}
				if((positionValues[n] >= 0 ) && (blobs[i][5]!=0) && (blobs[i][5]!=-1) &&(blobs[i][6] == n-1) ){

					frameDiff = frameNo - blobs[i][5];
					if(frameDiff<10)
					{
						blobs[i][8] = -2;
					}else{
						//cout<<frameDiff<<endl;
						//system("Pause");

						blobs[i][12] = frameDiff;
						cout<< "Down Out frame No - "<< frameNo<<endl;

						timeMili = frameDiff*delay;
						speed = (distaceSpeedP/(timeMili))*3600000;

						//cout<<speed<<endl;

						tempSpeed = speed;

						//blobs[i][5] = frameNo;
						blobs[i][6] = n;
						blobs[i][8] = blobs[i][8]+1;
						blobs[i][9] = blobs[i][9]+tempSpeed;

						if(n==positionValues.size()-1){
							//cout<<speed<<endl;
							blobs[i][9] = blobs[i][9]/(blobs[i][8]);
							blobs[i][8] = -1;
							blobs[i][5] = -1;
						}
					}
				}

			}else if(blobs[i][4] == -1){
				if((positionValues[n] <= 0 ) && (blobs[i][5]==0)  ){

					blobs[i][5] = frameNo;	
					blobs[i][6] = n;
					cout<< "Up In frame No - "<< frameNo<<endl;
				}
				if((positionValues[n] <= 0 )&& (blobs[i][5]!=0) && (blobs[i][5]!=-1) &&(blobs[i][6] == n+1) ){

					frameDiff = frameNo - blobs[i][5];
					if(frameDiff<10)
					{
						blobs[i][8] = -2;
					}else{
						//cout<<frameDiff<<endl;
						//system("Pause");
						blobs[i][12] = frameDiff;

						timeMili = frameDiff*delay;
						speed = (distaceSpeedP/(timeMili))*3600000;
						//cout<<speed<<endl;

						cout<< "Up Out frame No - "<< frameNo<<endl;

						tempSpeed = speed;

						//blobs[i][5] = frameNo;
						blobs[i][6] = n;
						blobs[i][8] = blobs[i][8]+1;
						blobs[i][9] = blobs[i][9]+tempSpeed;

						if(n==0){							
							blobs[i][9] = blobs[i][9]/(blobs[i][8]);
							blobs[i][8] = -1;
							blobs[i][5] = -1;
						}						
					}
				}
			}

		}


		if(blobs[i][8] == -1){
			finalSpeed = blobs[i][9];			
		}

		radius = sqrt(blobs[i][3] / 2.00);

		int t=0;

		circle( oriFrame, Point( blobs[i][2], blobs[i][1]), radius,  CV_RGB(255,255,255), 2, 8, 0 );

		if((300>finalSpeed)&&(finalSpeed>0)){			
			ss << finalSpeed;
			s = ss.str();

			if(finalSpeed<100)
				s = s.substr(s.length()-2,2);
			else
				s = s.substr(s.length()-3,3);

			cv::Size text = cv::getTextSize(s, fontface, scale*(radius/20), thickness, &baseline);
			cv::Point pt(blobs[i][2], blobs[i][1] - radius);

			cv::rectangle(
				oriFrame, 
				pt + cv::Point(0, baseline), 
				pt + cv::Point(text.width, -text.height), 
				CV_RGB(255,255,255), CV_FILLED
				);

			if(finalSpeed>100){
				cv::putText(oriFrame, s, pt, fontface, scale*(radius/20), CV_RGB(255,0,0), thickness, 8);
				
					if(blobs[i][7]==0){
						
						blobs[i][15] = logHandler.getIncrementedViolationId();
						blobs[i][7] = logHandler.writeFile("Over speed ",&oriFrame, blobs[i][15], 3, 2, finalSpeed);
						blobs[i][7] = -1;

						if(blobs[i][16]==1)
							blobs[i][16] = 3;
						else
							blobs[i][16] = 2;
						
					}else if(blobs[i][7]>0){
						
						if(blobs[i][16]==1){
							blobs[i][16] = 3;
							blobs[i][7] = logHandler.writeFile("Over Speed and Wrong Lane",&oriFrame, blobs[i][15],3, blobs[i][16], finalSpeed);
						}
						else{
							blobs[i][15] = logHandler.getIncrementedViolationId();
							blobs[i][16] = 2;
							blobs[i][7] = logHandler.writeFile("Over Speed",&oriFrame, blobs[i][15],3, blobs[i][16], finalSpeed);
						}
						blobs[i][7] = -1;						
					}
					
				
			}else {
				cv::putText(oriFrame, s, pt, fontface, scale*(radius/20), CV_RGB(0,0,0), thickness, 8);
			}

			s="";
			ss.flush();
		}
	}

	return blobs;
}

