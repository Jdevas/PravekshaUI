#include "Praveksha.h"

using namespace cv;
using namespace std;
using namespace gpu;


SpeedDetector::SpeedDetector(vector<Point> oriCorners){
	this->oriCorners = oriCorners;
}

void SpeedDetector::setLogger(Logger* logger)
{
	SpeedDetector::logHandler = logger;
}

vector<vector<int>> SpeedDetector::speedDetection(cv::Mat oriFrame, vector<vector<int>> &blobs, vector<vector<int>> &blobsPrevious, vector<vector<int>> &mapper, vector<vector<int>> whitePointCordiantes, vector<Point> oriCorners)
{

	int frameNo = VariableStorage::frameNo;
	int delay = VariableStorage::delay;
	int BACKGROUND_SUBSTRACTION_THRESHOULD = VariableStorage::BACKGROUND_SUBSTRACTION_THRESHOULD;
	int CIRCLE_THRESHOULD = VariableStorage::CIRCLE_THRESHOULD;
	int CLOSEBY_THRESHOULD = VariableStorage::CLOSEBY_THRESHOULD;
	int THRESHOULD_BLOB_VALUE = VariableStorage::THRESHOULD_BLOB_VALUE;		
	
	if(frameNo==10){
		int jk=0;
	}

	Point p1(oriCorners[0].x,1080-oriCorners[0].y);
	Point p2(oriCorners[1].x,1080-oriCorners[1].y);
	Point p3(oriCorners[2].x,1080-oriCorners[2].y);
	Point p4(oriCorners[3].x,1080-oriCorners[3].y);

	/*double m1 =(p4.y-p3.y)*1.0/(p4.x-p3.x);	
	double m2 =(p4.y-p1.y)*1.0/(p4.x-p1.x);
	double m3 =(p3.y-p2.y)*1.0/(p3.x-p2.x);	


	double x0=((p1.y-(p1.y+p4.y)*1.0/2)*1.0+(m1*(p1.x+p4.x)*1.0/2-m2*p1.x))/(m1-m2);
	double y0=(m1*m2*((p1.x+p4.x)*1.0/2-p1.x)-m2*(p1.y+p4.y)*1.0/2+m1*p1.y)/(m1-m2);


	double x1=(1.0*(p1.y+p4.y)*1.0/2-1.0*p2.y+m3*p2.x-m1*(p1.x+p4.x)*1.0/2)/(m3-m1);
	double y1=(m1*m3*(1.0*(p1.x+p4.x)*1.0/2-p2.x)-m3*(p1.y+p4.y)*1.0/2+m1*p2.y)/(m1-m3);

	y0=1080-y0;
	y1=1080-y1;*/

	int ax1 = 890;
	int ay1 = 270;
	int ax2 = 1320;
	int ay2 = 280;

	int bx1 = 360;
	int by1 = 400;
	int bx2 = 1200;
	int by2 = 470;

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

	if(frameNo >= 120)
		int h=0;

	/*Point l1(GX1,GY1);
	Point l2(GX2,GY2);

	line(oriFrame,l1, l2, Scalar(255,255,255), 1, 4,0);*/

	for(int i=0; i<blobs.size(); i++){
		speed = 0;
		finalSpeed = 0;
		tempSpeed = 0;
		vector<int> positionValues(noOfCheckingLines);
		int positionValue = 0;

		if(blobs[i][3]<CIRCLE_THRESHOULD)
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
						k=blobsPrevious.size();
					}
				}				
				j=mapper.size();
			}
		}		

		if(blobs[i][5]==-1)
			continue;

		positionValues[0] = ((oriCorners[0].x - blobs[i][2])*(oriCorners[1].y- blobs[i][1]) - (oriCorners[1].x - blobs[i][2])*(oriCorners[0].y - blobs[i][1]));
		//positionValues[1] = ((x0 - blobs[i][2])*(y1- blobs[i][1]) - (x1 - blobs[i][2])*(y0 - blobs[i][1]));
		//positionValues[2] = ((oriCorners[3].x - blobs[i][2])*(oriCorners[2].y- blobs[i][1]) - (oriCorners[2].x - blobs[i][2])*(oriCorners[3].y - blobs[i][1]));
		//positionValues[1] = ((GX1 - blobs[i][2])*(GY2- blobs[i][1]) - (GX2 - blobs[i][2])*(GY1 - blobs[i][1]));
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
							//	cout<<speed<<endl;
							blobs[i][9] = blobs[i][9]/(blobs[i][8]);
							blobs[i][8] = -1;
							blobs[i][5] = -1;
						}

						/*speedVec[i][0] = blobs[i][0];
						speedVec[i][1] = speed;
						*/
						//cout<< "In frame No - "<< frameNo<<endl;
						//cout<< "Frame Diff - "<< frameDiff<<endl;
					}
				}
			}

		}


		if(blobs[i][8] == -1){
			finalSpeed = blobs[i][9];			
		}

		radius = sqrt(blobs[i][3] / 2.00);

		int t=0;

		if(blobs[i][1] < 0.5*oriFrame.rows){
			circle( oriFrame, Point( blobs[i][2], blobs[i][1]), radius,  CV_RGB(255,255,255), 2, 8, 0 );
		}else if((0.7*oriFrame.rows> blobs[i][1])&&(blobs[i][3]>40*CIRCLE_THRESHOULD)){
			circle( oriFrame, Point( blobs[i][2], blobs[i][1]), radius,  CV_RGB(255,255,255), 2, 8, 0 );

		}
		else if((blobs[i][3]>100*CIRCLE_THRESHOULD)){
			circle( oriFrame, Point( blobs[i][2], blobs[i][1]), radius,  CV_RGB(255,255,255), 2, 8, 0 );

		}
		/*else if((0.9*oriFrame.rows> blobs[i][1])&&(blobs[i][3]>80*CIRCLE_THRESHOULD)){
		circle( oriFrame, Point( blobs[i][2], blobs[i][1]), radius,  Scalar(255), 2, 8, 0 );

		}else if((blobs[i][3]>100*CIRCLE_THRESHOULD)){
		circle( oriFrame, Point( blobs[i][2], blobs[i][1]), radius,  Scalar(255), 2, 8, 0 );

		}*/



		if((300>finalSpeed)&&(finalSpeed>0)){			
			ss << finalSpeed;
			s = ss.str();
			//cout<<finalSpeed<<endl;
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
				if(blobs[i][7]!=1){
					logHandler -> writeFile("Over speed ",&oriFrame);
					emit violationDetected(finalSpeed);
					blobs[i][7] = 1;
				}
			}else {
				cv::putText(oriFrame, s, pt, fontface, scale*(radius/20), CV_RGB(0,0,0), thickness, 8);
			}

			s="";
			ss.flush();
		}
	}

	//return speedVec;

	return blobs;
}