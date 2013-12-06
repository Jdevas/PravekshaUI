#ifndef VEHICLEIDENTIFIER_H
#define VEHICLEIDENTIFIER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;
using namespace gpu;

class VehicleIdentifier
{
	public:
		vector< vector<int> > expandBlobMatrix(cv::Mat &frame, cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<vector <int>> &roi);

	private:
		int THRESHOULD_BLOB_VALUE;
		int CIRCLE_THRESHOULD;
		void recursiveFourNeighbour(Mat &frame, int row, int col, int blobLable, vector< vector<int> > &matrix);
		vector< vector<int> > identifyCentroidAndDrawCircle(cv::Mat &oriFrame, vector< vector<int> > &matrix, vector<int> &blobLablesUsed, vector<vector <int>> roi);
};

#endif