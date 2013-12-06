#include "VehicleTracker.h"
#include "Praveksha.h"

using namespace cv;
using namespace std;
using namespace gpu;

vector< vector<int> > VehicleTracker::vehicleTracker(vector< vector<int> > &blobs, vector< vector<int> > &previousBlobs, int rows)
{
	int CIRCLE_THRESHOULD = VariableStorage::CIRCLE_THRESHOULD;

	vector< vector<int> > mapper(previousBlobs.size(), vector<int>(3));

	if(previousBlobs.size() == 0)
		return mapper;

	int CENTROID_THRESHOULD = 10;
	int AREA_THRESHOULD = 10;
	int centroidDist;
	double centroidSqr; 
	int x=0, y=0, pX=0, pY=0, xDist=0, yDist = 0;

	for(int i=0; i<previousBlobs.size(); i++){
		if(previousBlobs[i][3] <= CIRCLE_THRESHOULD)
			continue;

		mapper[i][0] = previousBlobs[i][0];
		pX = previousBlobs[i][1];
		pY = previousBlobs[i][2];

		for(int j=0; j<blobs.size(); j++){
			if(blobs[j][3] <= CIRCLE_THRESHOULD)
				continue;
			x = blobs[j][1];
			y = blobs[j][2];

			xDist = x - pX;
			yDist = y - pY;

			centroidSqr = xDist*xDist*0.8 + yDist*yDist*0.2;
			centroidDist = sqrt(centroidSqr);

			if(x > (3*rows/4))
				CENTROID_THRESHOULD = 120;
			else if(x > (rows/2))
				CENTROID_THRESHOULD = 80;
			else if(x > (rows/4))
				CENTROID_THRESHOULD = 40;
			else
				CENTROID_THRESHOULD = 20;

			if(centroidDist < CENTROID_THRESHOULD){

				if((x > pX) && (blobs[j][3]>previousBlobs[i][3])) 
					blobs[j][4] = 1; //going down
				else if((x < pX) && (blobs[j][3]<previousBlobs[i][3])) 
					blobs[j][4] = -1; //going up
				else if(x > pX)
					blobs[j][4] = 1; //going down
				else if(x < pX)
					blobs[j][4] = -1; //going up
				else if(x==pX){
					blobs[j][4] = previousBlobs[i][4];
				}


				//if(x > pX)
				//	blobs[j][4] = 1; //going down
				//else if(x < pX)
				//	blobs[j][4] = -1; //going up
				//else if(previousBlobs[i][3] > blobs[j][3])
				//	blobs[j][4] = -1;
				//else if(previousBlobs[i][3] < blobs[j][3])
				//	blobs[j][4] = 1;

				if(previousBlobs[i][4] == blobs[j][4]){
					mapper[i][1] = blobs[j][0]; //map 2 vehicles
					mapper[i][2] = blobs[j][4];
				}
				/*else if(i==j){
				if((((x-pX)<=CENTROID_THRESHOULD)&&((x-pX)>=-CENTROID_THRESHOULD))){
				mapper[i][1] = blobs[j][0]; 
				blobs[j][4] = previousBlobs[i][4];
				mapper[i][2] = blobs[j][4];
				}
				}*/
			}
		}
	}
	//int temp1,temp2;
	//for(int i = 0; i < mapper.size(); i++){
	//	temp1 = mapper[i][0];
	//	temp2 = mapper[i][1];
	//	//cout << "map: " << temp1 << " - " << temp2 << endl;

	//	if(temp1 > 0 && temp2 > 0){
	//		for(int j = 0; j<previousBlobs.size(); j++){
	//			if(previousBlobs[j][0] == temp1)
	//				pX = previousBlobs[j][1];
	//		}

	//		for(int j = 0; j<blobs.size(); j++){
	//			if(blobs[j][0] == temp2)
	//				x = blobs[j][1];
	//		}

	//		//cout << "x dist: " << pX << " - " << x << endl;
	//	}
	//}




	return mapper;
	return mapper;
}