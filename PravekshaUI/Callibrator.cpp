#include "Callibrator.h"

using namespace cv;
using namespace std;
using namespace gpu;

vector<Point> Calibrator::roiPoints;
vector<Point> Calibrator::oriCorners;
vector<double> Calibrator::dist;
vector<vector <int>> Calibrator::roi;
bool Calibrator::rightClicked;
string VariableStorage::path;

int frameN;
vector<Point> corners;
int clicks=0;
int color=255;
vector<vector <int>> Calibrator::getRoI()
{
	return roi;
}

void Calibrator::setRoI(vector<vector <int>> roi)
{
	this->roi = roi;
}

vector<Point> Calibrator::getOriCorners(){
	return this->oriCorners;
}

vector<double> Calibrator::getDistances(){
	return this->dist;
}

void Calibrator::swap(Point* p1, Point* p2){
	Point temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

vector<Point> Calibrator::sort(vector<Point> oriCorners){
	
	if(oriCorners[0].y > oriCorners[1].y){
		swap(&oriCorners[0], &oriCorners[1]);
	}
	if(oriCorners[2].y > oriCorners[3].y){
		swap(&oriCorners[2], &oriCorners[3]);
	}
	if(oriCorners[0].y > oriCorners[2].y){
		swap(&oriCorners[0], &oriCorners[2]);
	}
	if(oriCorners[1].y > oriCorners[3].y){
		swap(&oriCorners[1], &oriCorners[3]);
	}
	if(oriCorners[1].y > oriCorners[2].y){
		swap(&oriCorners[1], &oriCorners[2]);
	}
	if(oriCorners[0].x > oriCorners[1].x){
		swap(&oriCorners[0], &oriCorners[1]);
	}
	if(oriCorners[3].x > oriCorners[2].x){
		swap(&oriCorners[3], &oriCorners[2]);
	}

	return oriCorners;
}

void Calibrator::setOriCorners(vector<Point> oriCorners)
{
	/*Point p11(1021,223);
	Point p21(1317,252);
	Point p31(1184,508);
	Point p41 (170,417);	

	oriCorners[0]=(p11);
	oriCorners[1]=(p21);
	oriCorners[2]=(p31);
	oriCorners[3]=(p41);*/
	oriCorners = sort(oriCorners);

	double x1 = oriCorners[3].x;
	double y1 = oriCorners[3].y;

	double x2 = oriCorners[2].x;
	double y2 = oriCorners[2].y;
	
	double x3 = oriCorners[0].x;
	double y3 = oriCorners[0].y;

	double x4 = oriCorners[1].x;
	double y4 = oriCorners[1].y;

	double m1,m2,c1,c2;
	int x,y;
	m1 = (y1 - y2)/(x1 - x2);
	if(y3>y4){
		c1 = y4 - m1 * x4;
		m2 = (y3 - y1)/(x3 - x1);
		c2 = y1 - m2*x1;
	}
	else{
		c1 = y3 - m1 * x3;
		m2 = (y4 - y2)/(x4 - x2);		
		c2 = y2 - m2 * x2;
	}

	x = (c2 - c1)/(m1 - m2);
	y = m1 *x + c1;

	Point p(x,y);
	
	if(y3>y4){
		oriCorners[0]=(p);
	}
	else{
		oriCorners[1]=(p);
	}	
	//oriCorners.push_back(Point(x,y));
	Calibrator::oriCorners = oriCorners;

	setDist();
}

vector<vector<int>> Calibrator::getWhitePointCordinates()
{
	return whitePointCordinates;
}

void Calibrator::initiateRoi()
{
	for(int i=0;i< roi.size();i++){
		roi[i][0]=i;
		roi[i][1]=-1;
		roi[i][2]=-1;
	}
}

void Calibrator::setDist(){
	
	dist.resize(1080);
	calculateMappingDistances();

}

void Calibrator::mouseHandler(int event, int x, int y, int flags, void* param){
	switch(event){
	case CV_EVENT_LBUTTONDOWN:	
		if(!rightClicked){
			roiPoints.push_back(Point(x,y));	
		}
		else{
			if(clicks<4){
				oriCorners.push_back(Point(x,y));
				clicks++;
			}
			if(clicks==4){				
				color = 0;
				setOriCorners(oriCorners);
				
			}
		}

		break;


	case CV_EVENT_RBUTTONDOWN:

		roiPoints.push_back(Point(roiPoints[0].x, roiPoints[0].y));

		for(int a=1;a<roiPoints.size();a++){
			int k = 0,t,x,y;
			//cout << "x= " << roiP[a].x << " y= " << roiP[a].y <<endl;

			if(roiPoints[a].y<roiPoints[a-1].y){

				for(int b = roiPoints[a-1].y;b>=roiPoints[a].y;b--){
					x = roiPoints[a].x - roiPoints[a-1].x;
					y = roiPoints[a-1].y-roiPoints[a].y;
					t = (x*k)/y;
					if(roi[b][1]==-1)
						roi[b][1]=roiPoints[a-1].x + t;

					else
						//
						int temp=0;
					if(roi[b][1]>roiPoints[a-1].x + t){						
						roi[b][2] =roi[b][1];
						roi[b][1]=roiPoints[a-1].x + t;
					}
					else{
						roi[b][2]=roiPoints[a-1].x + t;
					}
					k++;
				}
			}

			if(roiPoints[a].y>roiPoints[a-1].y){				
				for(int b = roiPoints[a-1].y;b<=roiPoints[a].y;b++){
					x = (roiPoints[a-1].x - roiPoints[a].x);
					y = (roiPoints[a].y-roiPoints[a-1].y);
					t = (x*k)/y;
					if(roi[b][1]!=-1){	
						if(roi[b][1]>roiPoints[a-1].x - t){						
							roi[b][2] =roi[b][1];
							roi[b][1]=roiPoints[a-1].x - t;
						}
						else{
							roi[b][2]=roiPoints[a-1].x - t;
						}
						//roi[b][2]=roiPoints[a-1].x - t;
					}else
						roi[b][1]=roiPoints[a-1].x - t;

					k++;
				}
			}
			if(roiPoints[a].y==roiPoints[a-1].y){
				if(roiPoints[a].x>roiPoints[a-1].x){
					roi[roiPoints[a].y][1]=roiPoints[a-1].x;
					roi[roiPoints[a].y][2]=roiPoints[a].x;
				}

				if(roiPoints[a].x<roiPoints[a-1].x){
					roi[roiPoints[a].y][1]=roiPoints[a].x;
					roi[roiPoints[a].y][2]=roiPoints[a-1].x;
				}
			}
		}		
		rightClicked = true;
		VariableStorage::rightClickFrameNo = frameN;
		break;
	}
}


void Calibrator::drawLines(Mat *toDraw){
	if(roiPoints.size() >0){
		for	(int i=1;i<roiPoints.size();i++){
			line(*toDraw,roiPoints[i-1], roiPoints[i], Scalar(255,255,255), 4, 4,0);
		}
	}
}

void Calibrator::drawLines(Mat *toDraw, int i){
	line(*toDraw,oriCorners[0], oriCorners[1], Scalar(0,200,200), 4, 4,0);
	line(*toDraw,oriCorners[1], oriCorners[2], Scalar(255,255,255), 4, 4,0);
	line(*toDraw,oriCorners[2], oriCorners[3], Scalar(0,200,200), 4, 4,0);
	line(*toDraw,oriCorners[3], oriCorners[0], Scalar(255,255,255), 4, 4,0);
}

void Calibrator::callibrate()
{
	WhiteLineDetector whiteLineDetect;
	cv::VideoCapture capture(VariableStorage::path);
	vector<Point> oriCorners(4);
	clicks = 0;
	color = 255;
	if (!capture.isOpened())
		return ;

	double rate= capture.get(CV_CAP_PROP_FPS);
	int rows = (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	int cols = (int)capture.get(CV_CAP_PROP_FRAME_WIDTH);
	
	int delay = VariableStorage::delay;
	
	int CIRCLE_THRESHOULD = VariableStorage::CIRCLE_THRESHOULD;
	int CLOSEBY_THRESHOULD = VariableStorage::CLOSEBY_THRESHOULD;
	int THRESHOULD_BLOB_VALUE = VariableStorage::THRESHOULD_BLOB_VALUE;

	vector<vector<int> > blobMatrix(rows, vector<int>(cols));
	frameN = 0;
	this->stop = false;
	this->rightClicked = false;

	cv::Mat frame; // current video frame
	cv::Mat outFrame;

	cv::namedWindow("Original",CV_WINDOW_FREERATIO);
	
	resizeWindow("Original",720,480);
	
	if (!capture.read(frame))
		return;

	cv::cvtColor(frame,outFrame,CV_BGR2GRAY);

	roi.resize(frame.rows, vector<int>(3));
	initiateRoi();	
	//setOriCorners(oriCorners);
	//
	
	//vector<vector<int>> whitePointCordiantes = whiteLineDetect.getWhitePointCordinates();

	delay = 1000/rate;
	VariableStorage::delay = delay;

	while (!stop) {
		frameN++;
		if (!capture.read(frame))
			break;

		cv::cvtColor(frame,outFrame,CV_BGR2GRAY);
		
		//////////////// RoI
		drawLines(&frame);
		
		drawCircles(&frame);

		int mouseParam=5;
		cvSetMouseCallback("Original", Calibrator::mouseHandler,&mouseParam);
		
		if(rightClicked)
		{
			//this->whitePointCordinates = whiteLineDetect.identifyWhitePoints(outFrame, frame, blobMatrix, roi);			
		}

		cv::imshow("Original",frame);		
		
		cv::waitKey(delay);
	}

	capture.release();
	cv::destroyAllWindows();
}

void Calibrator::stopVideo()
{
	this->stop = true;
}

QImage Calibrator::Mat2QImage(const cv::Mat3b &src) {
        QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
        for (int y = 0; y < src.rows; ++y) {
                const cv::Vec3b *srcrow = src[y];
                QRgb *destrow = (QRgb*)dest.scanLine(y);
                for (int x = 0; x < src.cols; ++x) {
                        destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
                }
        }
        return dest;
}

void Calibrator::calculateMappingDistances(){
	Point p1(oriCorners[0].x,1080-oriCorners[0].y);
	Point p2(oriCorners[1].x,1080-oriCorners[1].y);
	Point p3(oriCorners[2].x,1080-oriCorners[2].y);
	Point p4(oriCorners[3].x,1080-oriCorners[3].y);

	double m1 =(p4.y-p3.y)*1.0/(p4.x-p3.x);	
	double m2 =(p4.y-p1.y)*1.0/(p4.x-p1.x);
	double m3 =(p3.y-p2.y)*1.0/(p3.x-p2.x);	

	double p3p4Dist=sqrt(1.0*(p4.y-p3.y)*(p4.y-p3.y)+(p4.x-p3.x)*(p4.x-p3.x));
	for(int y=p1.y;y>0;y--){	
		int x=p1.x;

		double x0=((p1.y-y)+(m1*x-m2*p1.x))/(m1-m2);
		double y0=(m1*m2*(x-p1.x)-m2*y+m1*p1.y)/(m1-m2);
		double x1=(y-p2.y+m3*p2.x-m1*x)/(m3-m1);
		double y1=(m1*m3*(x-p2.x)-m3*y+m1*p2.y)/(m1-m3);	

		double x0y0x1y1Dist=sqrt(1.0*(y0-y1)*(y0-y1)+(x0-x1)*(x0-x1));
		int ty=(1080.5-y0);
		dist[ty]=1.0*dist[ty-1]+p3p4Dist/x0y0x1y1Dist;
		//printf("%d %f  \n",ty,dist[ty]);
		if(y0<p4.y ){
			dist[dist.size()-1]=dist[ty];
		}
	}
	int count=0;
	for(int y=p1.y;y<1080;y++){	
		int x=p1.x;

		double x0=((p1.y-y)+(m1*x-m2*p1.x))/(m1-m2);
		double y0=(m1*m2*(x-p1.x)-m2*y+m1*p1.y)/(m1-m2);
		double x1=(y-p2.y+m3*p2.x-m1*x)/(m3-m1);
		double y1=(m1*m3*(x-p2.x)-m3*y+m1*p2.y)/(m1-m3);	

		double x0y0x1y1Dist=sqrt(1.0*(y0-y1)*(y0-y1)+(x0-x1)*(x0-x1));
		int ty=(1080.5-y0);
		dist[ty]=1.0*dist[ty+1]-p3p4Dist/x0y0x1y1Dist;
		//printf("%d %f  \n",ty,dist[ty]);
		count++;
		/*if(count>10 ){
		break;
		}*/
	}
	for(int t=0;t<1080;t++){
		printf("%d %f\n",t,dist[t]);
		/*if(t%100==0){
		system("pause");
		}*/
	}

}

void Calibrator::drawCircles(Mat *toDraw){
	for(int i=0; i<oriCorners.size();i++){
		circle(*toDraw, Point( oriCorners[i].x, oriCorners[i].y), 10,  Scalar(color,255,255), 5, 8, 0 );
	}
}
