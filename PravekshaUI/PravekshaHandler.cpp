#include "PravekshaHandler.h"

using namespace cv;
using namespace std;
using namespace gpu;

int VariableStorage::frameNo;
int VariableStorage::rightClickFrameNo;
int VariableStorage::delay;

void PravekshaHandler::setCalibrator(Calibrator cal)
{
	
	this->callibrator = cal;
}

PravekshaHandler::PravekshaHandler()
{
	VariableStorage::frameNo = 0;
	VariableStorage::delay = 0;

	morph_elem = 0;
	morph_size = 20;
	morph_operator = 0;
	WEIGHT = 0.1;

	VehicleIdentifier vehicleidentifier;
	VehicleTracker vehiTracker;

}

PravekshaHandler::PravekshaHandler(Logger *logger)
{
	VariableStorage::frameNo = 0;
	VariableStorage::delay = 0;

	morph_elem = 0;
	morph_size = 20;
	morph_operator = 0;
	WEIGHT = 0.1;

	//WhiteLineDetector whiteLineDetector;
	VehicleIdentifier vehicleidentifier;
	VehicleTracker vehiTracker;
	//sp = spd;
	this->logHandler = logger;
	//Calibrator callibrator = cal;
}

void PravekshaHandler::pravekshaHandler()
{
	//cv::VideoCapture capture("E:/Export_2013-07-24_121107/0 - 2013-07-20 12-00-00-033.asf");
	cv::VideoCapture capture(VariableStorage::path);

	if (!capture.isOpened())
		return ;

	double rate= capture.get(CV_CAP_PROP_FPS);
	int rows = (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	int cols = (int)capture.get(CV_CAP_PROP_FRAME_WIDTH);
	vector<vector<int> > blobMatrix(rows, vector<int>(cols));
	
	VehicleDataStruct vehicleData;
	
	vector< vector<int> > mapper; // map vehicles in two consecutive frames
	vector< vector<int> > blobs;
	vector<vector<double>> mappedData;
	vector< vector<int> > previousBlobs;

	int delay = VariableStorage::delay;
	int BACKGROUND_SUBSTRACTION_THRESHOULD = VariableStorage::BACKGROUND_SUBSTRACTION_THRESHOULD;
	int CIRCLE_THRESHOULD = VariableStorage::CIRCLE_THRESHOULD;
	int CLOSEBY_THRESHOULD = VariableStorage::CLOSEBY_THRESHOULD;
	int THRESHOULD_BLOB_VALUE = VariableStorage::THRESHOULD_BLOB_VALUE;

	bool stop(false);

	cv::Mat frame; // current video frame
	cv::Mat meanFrame;
	cv::Mat inputFrame;
	cv::Mat outFrame;
	cv::Mat copyFrame;
	cv::Mat oriMeanFrame;

	cv::namedWindow("Background",CV_WINDOW_FREERATIO);
	cv::namedWindow("Original",CV_WINDOW_FREERATIO);
	cv::namedWindow("After",CV_WINDOW_FREERATIO);
	
	resizeWindow("Background",330,210);
	
	int size = 335;
	int hor = 100;

	cvMoveWindow("Original", 0, 0);
	cvMoveWindow("Background",0, hor);
	
	if (!capture.read(frame))
		return;

	cv::cvtColor(frame,frame,CV_BGR2GRAY);

	roi = callibrator.getRoI();
	
	vector<vector<int>> whitePointCordiantes = callibrator.getWhitePointCordinates();
	//ruleHandler = RuleHandler(vehicleData,frame, blobs, previousBlobs, mapper, whitePointCordiantes, sp, mappedData);
	ruleHandler = RuleHandler(vehicleData,frame, whitePointCordiantes, logHandler );
	
	/*databaseHandler.initiateDB();*/
	meanFrame=frame.clone();	
	oriMeanFrame = meanFrame.clone();
	

	delay = 1000/rate;
	VariableStorage::delay = delay;
	int frameN=0;
	while (!stop) {
		frameN++;

		if(frameN==VariableStorage::rightClickFrameNo)
			continue;

		if (!capture.read(frame))
			break;

		/*if(frameN<3435)
			continue;*/
		if(frameN==1266)
			int ggg=0;

		VariableStorage::frameNo++;
		copyFrame = frame*2/3;
		cv::cvtColor(frame,frame,CV_BGR2GRAY);
		frame.copyTo(outFrame);

		
		/*if(VariableStorage::frameNo < 200)
			continue;*/
		for(int row = 0; row < frame.rows; ++row) {
			uchar* pF = frame.ptr(row);
			uchar* pM = meanFrame.ptr(row);
			uchar* pO = outFrame.ptr(row);
			uchar* pC = copyFrame.ptr(row);
	
			for(int col = 0; col < roi[row][1]; ++col) {				              
				pO[col] = 255; 
 			}
			for(int col = roi[row][1]; col < roi[row][2]; ++col) {				              
				pC[col*3]=pC[col*3]*3/2;
				pC[col*3+1]=pC[col*3+1]*3/2;
				pC[col*3+2]=pC[col*3+2]*3/2;

				if((pF[col]-pM[col])>BACKGROUND_SUBSTRACTION_THRESHOULD || (pM[col]-pF[col]>BACKGROUND_SUBSTRACTION_THRESHOULD)){   
					pO[col] = 0;//pF[col];  
				}  
				else{  
					pO[col] = 255; 
					pM[col] =  (1-WEIGHT)*pM[col]+WEIGHT*pF[col];
				}  
			}	
			
			for(int col = roi[row][2]; col < frame.cols; ++col) {				              
				pO[col] = 255; 		
			}
		}
		
		
		inputFrame = outFrame.clone();

		// Since MORPH_X : 2,3,4,5 and 6
		int operation = morph_operator + 2;
		morph_size = 20;
		Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

		/// Apply the specified morphology operation
		morphologyEx( inputFrame, outFrame, operation, element );

		operation = 3;
		morph_size = 5;
		element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
		inputFrame = outFrame.clone();
		morphologyEx( inputFrame, outFrame, operation, element );
		cv::imshow("After",outFrame);

		//for(int row = 0; row < frame.rows; ++row) {
		//		uchar* pO = outFrame.ptr(row);
		//		uchar *pF = frame.ptr(row);
		//		uchar* pM = meanFrame.ptr(row);			
		//		for(int col = roi[row][1]; col < roi[row][2]; ++col) {
		//			if((pO[col]==255)){   
		//				pM[col] =  (1-WEIGHT)*pM[col]+WEIGHT*pF[col];
		//			}  	

		//		}		
		//	}


		if(VariableStorage::frameNo==1){
			blobs = vehicleidentifier.expandBlobMatrix(outFrame,frame,blobMatrix, callibrator.getRoI());
			vehicleData.blobs = blobs;
		}
		else{
			vehicleData.previousBlobs = vehicleData.blobs;
			blobs = vehicleidentifier.expandBlobMatrix(outFrame,frame,blobMatrix, callibrator.getRoI());

			if(blobs.size() > 0 && blobs[0][0] == 1001){
				meanFrame = oriMeanFrame;
				continue;
			}

			mapper = vehiTracker.vehicleTracker(blobs, vehicleData.previousBlobs, rows);
			
			vehicleData.blobs = blobs;
			vehicleData.mapper = mapper;

			ruleHandler.setFrame(copyFrame);
			ruleHandler.setVehicleData(vehicleData);
			
			vehicleData = ruleHandler.detectRules(callibrator.getOriCorners(), callibrator.getDistances());
			
		}
		//resizeWindow("Original",720,480);
		this->callibrator.drawLines(&copyFrame, 1);
		cv::imshow("Original",copyFrame);
		cv::imshow("Background",meanFrame);
		
		//
		
		cout << VariableStorage::frameNo << endl;
		// introduce a delay
		// or press key to stop

		cv::waitKey(delay);
		//if (cv::waitKey(delay)>=0)
		//stop= true;

	}

	// Close the video file
	capture.release();
}