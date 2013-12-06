# include "Mapper.h"

Mapper::Mapper(){

}

Mapper::Mapper(vector<Point> oriCorners, vector<double> dist){
	this->oriCorners = oriCorners;
	this->dist = dist;
}

VehicleDataStruct Mapper::transform1(vector<vector<int>> &blobs, VehicleDataStruct &vehicleData , Mat &frame,vector<Point> oriCorners, vector<double> dist, Logger &logHandler){
	
	vector<vector<double>> mappedData = vehicleData.mappedData;

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

	int relativeValue1 = 0;
	int relativeValue2 = 0;

	cv::Mat t = cv::Mat::zeros(bottomLine, rightLine, CV_8UC3);

	int devision = 0;

	for(int i=0; i<2*height; i++){
		devision = i/100;
		if(devision%2 !=0){
			rectangle( t, Point(leftCenterLine,i), Point(leftCenterLine,i), Scalar(255,255,255),4, 8,0 );
			rectangle( t, Point(rightCenterLine,i), Point(rightCenterLine,i), Scalar(255,255,255),4, 8,0 );
		}
	}

	line(t,Point(centerLine,topLine), Point(centerLine,bottomLine), Scalar(128,128,128), 32, 8,0);
	line(t,Point(leftLine,realMappingStart),Point(rightLine,realMappingStart), Scalar(0,200,200), 2, 4,0);
	line(t,Point(leftLine,realMappingEnd),Point(rightLine,realMappingEnd), Scalar(0,200,200), 2, 4,0);

	for(int mi=0;mi<mappedData.size();mi++){
		if(mappedData[mi][3]==1)
			mappedData[mi][1]+=mappedData[mi][2];
		else
			mappedData[mi][1]-=mappedData[mi][2];		
		int mx=mappedData[mi][0];
		int my=0.5+mappedData[mi][1];
		//printf("mx=%d my=%d\n",mx,my);
		if(my>bottomLine || my<topLine){
			mappedData.erase(mappedData.begin()+mi);
			cout<<"erased"<<endl;
			//system("Pause");
		}
		Point pm(mx,my);
		circle( t, pm, 5,  CV_RGB(255,0,0), 2, 8, 0 );	
	}

	Point mapped;
	for(int i=0;i<blobs.size();i++){		
		if(blobs[i][3]<=VariableStorage::CIRCLE_THRESHOULD)
			continue;
		Point p= transformPoint(blobs[i][2],blobs[i][1],height,width, frame, oriCorners, dist);
		mapped=Point(p.x,p.y+realMappingStart);
		if(mapped.y<realMappingEnd && mapped.y>realMappingStart){
			circle( t, mapped, 5,  Scalar(255), 2, 8, 0 );		
		}

		blobs[i][10] = mapped.x;
		blobs[i][11]=mapped.y;

		if((blobs[i][13]==0)&&(blobs[i][8]==-1)){

			relativeValue1 = ((oriCorners[0].x - blobs[i][2])*(oriCorners[1].y- blobs[i][1]) - (oriCorners[1].x - blobs[i][2])*(oriCorners[0].y - blobs[i][1]));
			relativeValue2 = ((oriCorners[3].x - blobs[i][2])*(oriCorners[2].y- blobs[i][1]) - (oriCorners[2].x - blobs[i][2])*(oriCorners[3].y - blobs[i][1]));

			if((relativeValue1>=0)&&(relativeValue2>=0)&&(mapped.y>realMappingEnd)&&(blobs[i][4]==1)){

				blobs[i][13]=1;
				vector<double> v;
				v.push_back(mapped.x);
				v.push_back(mapped.y);				
				v.push_back(height/(blobs[i][12]*1.0));
				v.push_back(1);
				mappedData.push_back(v);
				circle( t, Point(mapped.x, mapped.y), 5,  CV_RGB(255,0,0), 2, 8, 0 );	

				if(blobs[i][16]==1){
					vehicleData.blobs[i][7] = logHandler.writeFile("Wrong Lane ",&frame,blobs[i][15], 2, vehicleData.blobs[i][16], vehicleData.blobs[i][9]);					
				}
				logHandler.writeFile("Vehicle Added",&frame,blobs[i][15], 4, -1, vehicleData.blobs[i][9]);					

				printf("addedDown\n");
			}
			if((relativeValue1<=0)&&(relativeValue2<=0)&&(mapped.y<realMappingStart)&&(blobs[i][4]==-1)){
				blobs[i][13]=-1;
				vector<double> v;
				v.push_back(mapped.x);
				v.push_back(mapped.y);				
				v.push_back(height/(blobs[i][12]*1.0));				
				v.push_back(-1);
				mappedData.push_back(v);
				circle( t, Point(mapped.x, mapped.y), 5,  CV_RGB(255,0,0), 2, 8, 0 );	

				if(blobs[i][16]==1){
					vehicleData.blobs[i][7] = logHandler.writeFile("Wrong Lane ",&frame,blobs[i][15], 2, vehicleData.blobs[i][16], vehicleData.blobs[i][9]);
				}
				logHandler.writeFile("Vehicle Added",&frame,blobs[i][15], 4, -1, vehicleData.blobs[i][9]);					
				printf("addedUp\n");
			}
		}
	}	

	cout<<VariableStorage::frameNo<<endl;
	namedWindow("mapping",CV_WINDOW_FREERATIO);
	imshow("mapping",t);

	vehicleData.blobs = blobs;
	vehicleData.mappedData = mappedData;

	return vehicleData;

}

Point Mapper::transformPoint(int x, int yt,int row, int col, Mat &frame, vector<Point> oriCorners, vector<double> dist){
	/*printf("oriX=%d, oriY=%d, ",x,yt);*/
	int y=1080-yt;
	//int row=200;
	//int col=300;

	//Vector<Point> oriCorners(4);

	/*Point p1(626,1080-346);
	Point p2(1250,1080-380);
	Point p3(1152,1080-562);
	Point p4 (122,1080-506);*/

	Point p1(oriCorners[0].x,1080-oriCorners[0].y);
	Point p2(oriCorners[1].x,1080-oriCorners[1].y);
	Point p3(oriCorners[2].x,1080-oriCorners[2].y);
	Point p4(oriCorners[3].x,1080-oriCorners[3].y);

	/*circle( m, Point(p1.x,1080-p1.y), 5,  Scalar(255), 2, 8, 0 );
	circle( m, Point(p2.x,1080-p2.y), 5,  Scalar(255), 2, 8, 0 );
	circle( m, Point(p3.x,1080-p3.y), 5,  Scalar(255), 2, 8, 0 );
	circle( m, Point(p4.x,1080-p4.y), 5,  Scalar(255), 2, 8, 0 );	*/


	double m1 =(p4.y-p3.y)*1.0/(p4.x-p3.x);	
	double m2 =(p4.y-p1.y)*1.0/(p4.x-p1.x);
	double m3 =(p3.y-p2.y)*1.0/(p3.x-p2.x);	


	double x0=((p1.y-y)+(m1*x-m2*p1.x))/(m1-m2);
	double y0=(m1*m2*(x-p1.x)-m2*y+m1*p1.y)/(m1-m2);

	Point q (x0,1080-y0);
	/*printf("q.x=%d, q.y=%d ",q.x,q.y);*/
	circle( frame, q, 5,  CV_RGB(255,0,0), 2, 8, 0 );

	double x1=(y-p2.y+m3*p2.x-m1*x)/(m3-m1);
	double y1=(m1*m3*(x-p2.x)-m3*y+m1*p2.y)/(m1-m3);
	Point w (x1,1080-y1);
	circle( frame, w, 5,  CV_RGB(255,0,0), 2, 8, 0 );

	line(frame,w, q, Scalar(255,255,255), 1, 4,0);

	double l=((y0-y)*1.0/(y-y1));
	double k=((p1.y-y0)*1.0/(y0-p4.y));

	double xm=l*col/(1+l);
	double ym=k*row/(1+k);

	int ymi=y0;
	double yq=dist[1080-ymi]*row/dist[1080-p4.y];
	//printf("xxxxxx  %d   %.2f   %.2f    %d    %.2f\n",ymi,yq,dist[1080-p1.y+ymi],row,dist[1080-p4.y]);

	int px=xm;
	int py=yq;

	//circle( t, Point(px,ymi), 5,  CV_RGB(255,255,0), 2, 8, 0 );

	Point p(px,py);
	//printf("tr poi  %d   %d\n",p.x,p.y);
	return p;

}