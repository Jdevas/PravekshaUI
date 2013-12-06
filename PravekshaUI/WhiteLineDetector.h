#ifndef WHITELINEDETECTOR_H
#define WHITELINEDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "Praveksha.h"

using namespace cv;
using namespace std;
using namespace gpu;

class WhiteLineDetector
{
	private:
		int THRESHOULD_BLOB_VALUE;
		int CIRCLE_THRESHOULD;
		vector<vector<int>> whitePointCordiantes;
		vector< vector<int> > whitePointesExpandBlobMatrix(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> roi);
		void whitePointesRecursiveFourNeighbour(Mat &frame, int row, int col, int blobLable, vector< vector<int> > &matrix);
		vector< vector<int> > whiteBlobsCentroidAndDrawCircle(cv::Mat &oriFrame,cv::Mat &whiteFrame, vector< vector<int> > &matrix, vector<int> &blobLablesUsed, vector<vector <int>> roi);
		double getGradient(int row1, int col1, int row2, int col2);
		bool isColinear(int firstBlobNo, int secondBlobNo, int thridBlobNo, int row, int col, int row1, int col1, int row2, int col2);
		double averageGradient(int firstBlobNo, int secondBlobNo, int thridBlobNo, int row, int col, int row1, int col1, int row2, int col2);
		vector<vector <int>> removeSmallBlobs(vector<vector <int>> &blobs);
		vector<vector <double>> removeExtraPoints(vector<vector <double>> &whitePoints);
		vector<vector <double>> calculateMidleWhiteLines(cv::Mat &whiteFrame, vector<vector<int>> &oriBlobs);
		vector<vector<double>> mergeWhiteLines(vector<vector <double>> &colinearBlobNo);
		vector<vector<double>> removeLongLines(vector<vector<double>> &groupedPoints, vector<vector<int>> &oriWhitePoints);
		vector<vector<int>> getWhiteLineCordinates(vector<vector<double>> &whiteLineBlobNo, vector<vector<int>> &oriWhitePoints);

	public:
		vector<vector<int>> getWhitePointCordinates();
		vector<vector<int>> identifyWhitePoints(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> roi);
};

#endif