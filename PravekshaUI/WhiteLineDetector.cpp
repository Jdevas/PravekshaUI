#include "WhiteLineDetector.h"

using namespace cv;
using namespace std;
using namespace gpu;


/*
this fuction returns the output of this class which is the coordinates of white points
*/
vector<vector<int>> WhiteLineDetector::getWhitePointCordinates()
{
	return whitePointCordiantes;
}


/*
main function of the white line detecting process
this identify white points and group them into blobs using other following functions
*/
vector<vector<int>> WhiteLineDetector::identifyWhitePoints(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> roi)
{
	THRESHOULD_BLOB_VALUE = VariableStorage::THRESHOULD_BLOB_VALUE;
	CIRCLE_THRESHOULD = VariableStorage::CIRCLE_THRESHOULD;

	vector< vector<int> > whitePointBlobs;
	vector<vector<double>> colinearPoints;
	vector<vector<double>> disticntBlobNoSet;
	vector<vector<double>> middleWhitePoints;
	Mat whitePoints = frame.clone();
	uchar* pC;
	uchar* pW;
	int count = 0;
	int r=0;
	int g=0;
	int b=0;
	vector<int> points(2);

	for(int row=0;row<frame.rows;row++){					
		pC = frame.ptr(row);
		pW = whitePoints.ptr(row);
		for(int col=roi[row][1]; col<roi[row][2];col++){
			count = 0;

			b = oriFrame.at<cv::Vec3b>(row,col)[0];
			g = oriFrame.at<cv::Vec3b>(row,col)[1];
			r = oriFrame.at<cv::Vec3b>(row,col)[2];

			if((r>200)&&(g>200)&&(b>200)){

				oriFrame.at<cv::Vec3b>(row,col)[0] = 0;
				oriFrame.at<cv::Vec3b>(row,col)[1] = 0;
				oriFrame.at<cv::Vec3b>(row,col)[2] = 0;

				pW[col] = 0;

			}else{
				pW[col] = 255;
			}


		}
	}


	whitePointBlobs = whitePointesExpandBlobMatrix(whitePoints, frame, matrix, roi);

	colinearPoints = calculateMidleWhiteLines(whitePoints, whitePointBlobs);
	disticntBlobNoSet = mergeWhiteLines(colinearPoints);
	middleWhitePoints = removeLongLines(disticntBlobNoSet, whitePointBlobs);
	whitePointCordiantes = getWhiteLineCordinates(middleWhitePoints, whitePointBlobs);

	return whitePointCordiantes;
}

vector< vector<int> > WhiteLineDetector::whitePointesExpandBlobMatrix(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> roi){
	uchar* pF; 
	uchar* pO;
	uchar* pOP;

	int blobLable = 1;
	int blobTemp = blobLable;
	vector<int> blobLablesUsed;
	bool blobTaken = false;
	bool blobChanged = false;
	int nextRowValMat;
	int nextColValMat;

	//set matrix 0
	for(int row = 0; row < frame.rows; row++) {
		for(int col = 0; col < frame.cols; col++) {	
			matrix[row][col] = 0;
		}
	}

	for(int row=0; row <frame.rows; row++){
		pF = frame.ptr(row);
		pO = oriFrame.ptr(row);

		if(row > 0){
			pOP = frame.ptr(row-1);
		}	

		for(int col=roi[row][1]; col < roi[row][2]; col++){
			if(pF[col] == 0 && matrix[row][col] == 0){  //if it is foreground

				blobChanged = false;
				blobTemp = blobLable;			


				matrix[row][col] = blobLable;

				//expand using recursion
				whitePointesRecursiveFourNeighbour(frame, row, col, blobLable, matrix);

				blobLable = blobTemp;

				blobLablesUsed.push_back(blobLable);
				blobLable++;
			}			
		}
	}

	return whiteBlobsCentroidAndDrawCircle(oriFrame,frame, matrix, blobLablesUsed, roi);
}

/*
recursive function to group white points to blobs using four neighbour connectivity
*/
void WhiteLineDetector::whitePointesRecursiveFourNeighbour(Mat &frame, int row, int col, int blobLable, vector< vector<int> > &matrix){
	uchar* pF;

	pF = frame.ptr(row);

	if(pF[col] > THRESHOULD_BLOB_VALUE)
		return;

	uchar* pFN;
	uchar* pFP;

	if(row < (frame.rows-1)){
		pFN = frame.ptr(row+1);
	}

	if(row > 0){
		pFP = frame.ptr(row-1);
	}

	if( col < frame.cols-1 && pF[col+1] ==0 && matrix[row][col+1] != blobLable){ // next column
		matrix[row][col+1] = blobLable;
		whitePointesRecursiveFourNeighbour(frame, row, col+1, blobLable, matrix);
	}if( row < frame.rows-1 && pFN[col] ==0 && matrix[row+1][col] != blobLable){ // below row
		matrix[row+1][col] = blobLable;
		whitePointesRecursiveFourNeighbour(frame, row+1, col, blobLable, matrix);
	}if( col > 1 && pF[col-1] ==0 && matrix[row][col-1] != blobLable){ // previous col
		matrix[row][col-1] = blobLable;
		whitePointesRecursiveFourNeighbour(frame, row, col-1, blobLable, matrix);
	}
}

/*
calculate area and centroid of the white point blobs. blobs will be considered as as cirlces
*/
vector< vector<int> > WhiteLineDetector::whiteBlobsCentroidAndDrawCircle(cv::Mat &oriFrame,cv::Mat &whiteFrame, vector< vector<int> > &matrix, vector<int> &blobLablesUsed, vector<vector <int>> roi){

	int tempCount = 0;

	vector< vector<int> > blobs(blobLablesUsed.size(), vector<int>(7));
	int rowCentroidValue = 0;
	int colCentroidValue = 0;
	int elementCount = 0;

	for(int i=0; i < matrix.size(); i++){
		for(int j=roi[i][1]; j<roi[i][2];j++){
			if(matrix[i][j] > 0)
				tempCount++;
		}
		if(tempCount > 0){
			for(int j=roi[i][1]; j<roi[i][2];j++){
				if(matrix[i][j] > 0){
					for(int k=0; k < blobLablesUsed.size(); k++){
						if(matrix[i][j] == blobLablesUsed[k]){
							blobs[k][0] = blobLablesUsed[k];
							blobs[k][1] += i;
							blobs[k][2] += j;
							blobs[k][3]++;
						}
					}
				}
			}
		}
	}	

	int radius = 0;
	int thresh = 100;

	int MAX_CIRCLE_THRESHOLD = 0;

	for(int k=0; k < blobs.size(); k++){

		rowCentroidValue = blobs[k][1] / blobs[k][3];
		colCentroidValue = blobs[k][2] / blobs[k][3];
		blobs[k][1] = rowCentroidValue;
		blobs[k][2] = colCentroidValue;


		if(blobs[k][1]<0.2*oriFrame.rows){
			CIRCLE_THRESHOULD = 0.2*thresh;
			MAX_CIRCLE_THRESHOLD = thresh;
		}
		else if(blobs[k][1]<0.4*oriFrame.rows){
			CIRCLE_THRESHOULD = 0.4*thresh;
			MAX_CIRCLE_THRESHOLD = 3*thresh;
		}
		else if(blobs[k][1]<0.6*oriFrame.rows){
			CIRCLE_THRESHOULD = 0.6*thresh;
			MAX_CIRCLE_THRESHOLD = 1000000;
		}
		else if(blobs[k][1]<0.8*oriFrame.rows){
			CIRCLE_THRESHOULD = 0.8*thresh;
			MAX_CIRCLE_THRESHOLD =1000000;
		}
		else if(blobs[k][1]<oriFrame.rows)
			CIRCLE_THRESHOULD = thresh;

		if((blobs[k][1]>0.3*oriFrame.rows)&&(blobs[k][3] > CIRCLE_THRESHOULD)&&(blobs[k][3] < MAX_CIRCLE_THRESHOLD)){
			
			blobs[k][6] = 1;
			radius = sqrt(blobs[k][3] / 2.00);
		}
	}



	return blobs;
}


/*
calculate gradient between two given points. 
Input points should be give by row and col
*/
double WhiteLineDetector::getGradient(int row1, int col1, int row2, int col2){
	double rowDiff = row1-row2;
	double colDiff = col1-col2;

	if(colDiff==0)
		return 1000000;
	else{
		return (rowDiff/colDiff);
	}
}

/*
this will check whether three given points are colinear. point coordinates should be given in rows and cols
*/
bool WhiteLineDetector::isColinear(int firstBlobNo, int secondBlobNo, int thridBlobNo, int row, int col, int row1, int col1, int row2, int col2){
	double COLINEAR_THRESHOLD = 0.05;

	double gradient1 = getGradient(row, col, row1, col1);
	double gradient2 = getGradient(row, col, row2, col2);
	double diff = gradient1-gradient2;

	if((-COLINEAR_THRESHOLD<diff) && (diff<COLINEAR_THRESHOLD)){
		return true;
	}else 
		return false;
}

/*
calculate average gradient between three given points.
fist calulte gradient between first two points and then calculate average between second and third points
finally get the average between ablove two values
*/
double WhiteLineDetector::averageGradient(int firstBlobNo, int secondBlobNo, int thridBlobNo, int row, int col, int row1, int col1, int row2, int col2){
	double gradient1 = getGradient(row, col, row1, col1);
	double gradient2 = getGradient(row, col, row2, col2);
	double average = (gradient1+gradient2)/2;
	return average;
}


vector<vector <int>> WhiteLineDetector::removeSmallBlobs(vector<vector <int>> &blobs){
	vector<vector <int>> blobsToReturn = blobs;
	for(int i=0;i<blobsToReturn.size();i++){

		if(blobsToReturn[i][6]==0){

			blobsToReturn.erase(blobsToReturn.begin()+i);
			i=i-1;
		}
	}

	return blobsToReturn;
}


vector<vector <double>> WhiteLineDetector::removeExtraPoints(vector<vector <double>> &whitePoints){
	vector<vector <double>> whitePointsBefore = whitePoints;
	for(int i=0;i<whitePointsBefore.size();i++){

		if(whitePointsBefore[i][0]==0){

			whitePointsBefore.erase(whitePointsBefore.begin()+i);
			i=i-1;
		}
	}

	return whitePointsBefore;
}

//calculate middle white lines and store in sorted order
vector<vector <double>> WhiteLineDetector::calculateMidleWhiteLines(cv::Mat &whiteFrame, vector<vector<int>> &oriBlobs){
	vector<vector<int>> whiteBlobs = removeSmallBlobs(oriBlobs);

	int noOfCombinations = (whiteBlobs.size()*(whiteBlobs.size()-1)*(whiteBlobs.size()-2))/6;

	vector<vector<double>> colinearBlobNo(noOfCombinations, vector<double>(10));
	bool isCol = false;
	double avgGradient = 0;
	int count = 0;
	if(whiteBlobs.size()>3){
		for(int i=0;i<whiteBlobs.size()-2;i++){
			vector<double> blobNo(4);

			if(whiteBlobs[i][6]!=1)
				continue;

			for(int j=i+1;j<whiteBlobs.size()-1;j++){
				if(whiteBlobs[j][6]!=1)
					continue;			
				isCol = false;
				for(int k=j+1; k<whiteBlobs.size();k++){
					if(whiteBlobs[k][6]!=1)
						continue;
					isCol = isColinear(whiteBlobs[i][0],whiteBlobs[j][0],whiteBlobs[k][0],whiteBlobs[i][1], whiteBlobs[i][2], whiteBlobs[j][1], whiteBlobs[j][2], whiteBlobs[k][1], whiteBlobs[k][2]);
					if(isCol){


						colinearBlobNo[count][0] = whiteBlobs[i][0];
						colinearBlobNo[count][1] = whiteBlobs[j][0];
						colinearBlobNo[count][2] = whiteBlobs[k][0];


						avgGradient = averageGradient(i,j,k,whiteBlobs[i][1], whiteBlobs[i][2], whiteBlobs[j][1], whiteBlobs[j][2], whiteBlobs[k][1], whiteBlobs[k][2]);

						colinearBlobNo[count][3] = avgGradient;
						colinearBlobNo[count][4] = whiteBlobs[i][1];
						colinearBlobNo[count][5] = whiteBlobs[i][2];
						colinearBlobNo[count][6] = whiteBlobs[j][1];
						colinearBlobNo[count][7] = whiteBlobs[j][2];
						colinearBlobNo[count][8] = whiteBlobs[k][1];
						colinearBlobNo[count][9] = whiteBlobs[k][2];

						count ++;					
					}

				}

			}

		}
	}
	return removeExtraPoints(colinearBlobNo);


}

vector<vector<double>> WhiteLineDetector::mergeWhiteLines(vector<vector <double>> &colinearBlobNo){
	double avereageGradientThreshold = 0.01;		///to remove unwanted lines    
	double gradientThreshold = 0.001;				///to grouped same line points   
	int noOfelements = colinearBlobNo.size();
	vector<vector<double>> sortedColinearPoints(noOfelements, vector<double>(10));
	vector<vector<double>> (noOfelements, vector<double>(10));
	vector<vector<double>> mergedColinearPoints(noOfelements, vector<double>(9));
	vector<double> averageGradientList(noOfelements);

	///sort average gradients
	for(int i=0;i<colinearBlobNo.size();i++){
		averageGradientList[i] = colinearBlobNo[i][3];
	}	
	sort(averageGradientList.begin(),averageGradientList.end());

	///inserted according to sorted order of gradients to sortedColinearPoints
	for(int i=0; i<averageGradientList.size();i++){
		for(int j=0; j<colinearBlobNo.size();j++){
			if(colinearBlobNo[j][3]==averageGradientList[i]){
				sortedColinearPoints[i] = colinearBlobNo[j];
			}
		}
	}

	//remove unwanted colinear points
	bool isCol = false;
	double averageDiff = 0;
	for(int i=0;i<sortedColinearPoints.size();i++){
		isCol  = false;
		for(int j=0;j<averageGradientList.size();j++){

			averageDiff = sortedColinearPoints[i][3] - averageGradientList[j];
			if(averageDiff==0)
				continue;
			if((averageDiff<avereageGradientThreshold)&&(averageDiff>-avereageGradientThreshold)){
				isCol = true;
			}
		}

		//if((!isCol)||((sortedColinearPoints[i][3]>-0.3)&&(sortedColinearPoints[i][3]<0.3))){
		if(((sortedColinearPoints[i][3]>-0.3))){
			sortedColinearPoints.erase(sortedColinearPoints.begin() +i);			
			i = i-1;

		}
	}

	///group colinear blob nos together
	vector<vector<double>> groupedPoints;
	vector<double> tempPoints;
	bool isCommon = false;
	for(int i=0; i<sortedColinearPoints.size();i++){
		isCommon = false;
		for(int j=i+1; j<sortedColinearPoints.size();j++){
			//vector<double> tempPoints;
			for(int k=0;k<3;k++){
				for(int l=0;l<3;l++){
					if(sortedColinearPoints[i][k]==sortedColinearPoints[j][l]){
						tempPoints.push_back(sortedColinearPoints[i][0]);
						tempPoints.push_back(sortedColinearPoints[i][1]);
						tempPoints.push_back(sortedColinearPoints[i][2]);
						tempPoints.push_back(sortedColinearPoints[j][0]);
						tempPoints.push_back(sortedColinearPoints[j][1]);
						tempPoints.push_back(sortedColinearPoints[j][2]);
						isCommon = true;
						l=4;
						k=4;
					}
				}
			}			
		}
		if(!isCommon){
			if(tempPoints.size()==0){
				tempPoints.push_back(sortedColinearPoints[i][0]);
				tempPoints.push_back(sortedColinearPoints[i][1]);
				tempPoints.push_back(sortedColinearPoints[i][2]);
			}

			sort(tempPoints.begin(),tempPoints.end());

			double last = 0;
			double current = 0;
			int count = 0;
			int tempPointsSize = tempPoints.size();
			vector<double> distinctWhiteBlobNo;

			for(int m=0;m<tempPointsSize;m++){
				current = tempPoints.back();
				tempPoints.pop_back();
				if(last == current)
					continue;
				else{
					distinctWhiteBlobNo.push_back(current);
					last = current;
				}
			}

			groupedPoints.push_back(distinctWhiteBlobNo);
		}
	}

	return groupedPoints;

}

vector<vector<double>> WhiteLineDetector::removeLongLines(vector<vector<double>> &groupedPoints, vector<vector<int>> &oriWhitePoints){

	int WhiteLineMaxThreshold = 1500;
	vector<vector<double>> oriGroupedPoints = groupedPoints;

	vector<vector<double>> returnVec;
	int groupedPointsSize = groupedPoints.size();
	bool external = false;
	for(int i=0;i<groupedPointsSize;i++){
		vector<double> tempPoints = groupedPoints.back();	
		groupedPoints.pop_back();
		external = false;
		int tempSize = tempPoints.size();
		int blobNo = 0;

		for(int j=0; j<tempSize; j++){
			blobNo = tempPoints.at(j);
			if(oriWhitePoints[blobNo-1][3]>WhiteLineMaxThreshold){
				external = true;
				j = tempSize;
			}
		}
		if(!external){
			returnVec.push_back(tempPoints);
		}

	}	


	return returnVec;
}

vector<vector<int>> WhiteLineDetector::getWhiteLineCordinates(vector<vector<double>> &whiteLineBlobNo, vector<vector<int>> &oriWhitePoints){
	vector<vector<double>> oriWhiteLineBlobNo = whiteLineBlobNo;

	int minSize = 10000;

	for(int i=0;i<whiteLineBlobNo.size();i++){

		if(minSize>whiteLineBlobNo.at(i).size())
			minSize = whiteLineBlobNo.at(i).size();
	}

	vector<vector<int>> whitePointCordinates(whiteLineBlobNo.size(),vector<int>(2*minSize));      //this is set of coordinate of white points. in each element vector even numbers for row values and odd numbers for column values 
	int count = 0;
	int blobNo = 0;
	for(int i=0;i<whiteLineBlobNo.size();i++){
		vector<int> cordinates(2*minSize);
		count = 0;
		for(int j=0;j< minSize;j++){
			blobNo = whiteLineBlobNo.at(i).at(j);
			cordinates[count] = oriWhitePoints[blobNo-1][1];
			cordinates[count+1] = oriWhitePoints[blobNo-1][2];

			count = count+2;;
		}

		whitePointCordinates[i] = cordinates;
	}

	return whitePointCordinates;
}