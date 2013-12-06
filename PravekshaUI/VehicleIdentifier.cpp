#include "VehicleIdentifier.h"
#include "Praveksha.h"

using namespace cv;
using namespace std;
using namespace gpu;

vector< vector<int> > VehicleIdentifier::expandBlobMatrix(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> &roi)
{
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

	THRESHOULD_BLOB_VALUE = VariableStorage::THRESHOULD_BLOB_VALUE;
	CIRCLE_THRESHOULD = VariableStorage::CIRCLE_THRESHOULD;

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
			if(pF[col] < THRESHOULD_BLOB_VALUE && matrix[row][col] == 0){  //if it is foreground

				blobChanged = false;
				blobTemp = blobLable;

				if(matrix[row][col] == 0){	  //if pixel is identified as a blob and corresponding matrix element was not updated yet
					matrix[row][col] = blobLable;

				}else{
					//get the current blob number
					blobTemp = blobLable;
					blobLable = matrix[row][col];
				}

				//expand using recursion
				recursiveFourNeighbour(frame, row, col, blobLable, matrix);

				blobLable = blobTemp;

				blobLablesUsed.push_back(blobLable);
				blobLable++;
			}
		}
	}

	return identifyCentroidAndDrawCircle(oriFrame, matrix, blobLablesUsed, roi);
}

void VehicleIdentifier::recursiveFourNeighbour(Mat &frame, int row, int col, int blobLable, vector< vector<int> > &matrix)
{
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

	if( col < frame.cols-1 && pF[col+1] < THRESHOULD_BLOB_VALUE && matrix[row][col+1] == 0){ // next column
		matrix[row][col+1] = blobLable;
		recursiveFourNeighbour(frame, row, col+1, blobLable, matrix);
	}if( row < frame.rows-1 && pFN[col] < THRESHOULD_BLOB_VALUE && matrix[row+1][col] == 0){ // below row
		matrix[row+1][col] = blobLable;
		recursiveFourNeighbour(frame, row+1, col, blobLable, matrix);
	}if( col > 1 && pF[col-1] < THRESHOULD_BLOB_VALUE && matrix[row][col-1] == 0){ // previous col
		matrix[row][col-1] = blobLable;
		recursiveFourNeighbour(frame, row, col-1, blobLable, matrix);
	}
}

vector< vector<int> > VehicleIdentifier::identifyCentroidAndDrawCircle(cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<int> &blobLablesUsed, vector<vector <int>> roi)
{

	//////////////////// identify centroids and draw circles

	int tempCount = 0;

	vector< vector<int> > blobs(blobLablesUsed.size(), vector<int>(17));
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

	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.5;
	int thickness = 3;
	int baseline = 0;
	int radius = 0;
	string s;
	stringstream ss;
	int temp = 0;

	for(int k=0; k < blobs.size(); k++){
		if(blobs[k][3] > CIRCLE_THRESHOULD){
			rowCentroidValue = blobs[k][1] / blobs[k][3];
			colCentroidValue = blobs[k][2] / blobs[k][3];
			blobs[k][1] = rowCentroidValue;
			blobs[k][2] = colCentroidValue;

			radius = sqrt(blobs[k][3] / 2.00);

		}
	}

	return blobs;
}