#include "Praveksha.h"
#include "pravekshaui.h"

string date;
double VariableStorage::distance;
String VariableStorage::loggerPath;

PravekshaUI::PravekshaUI(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	stringstream namess;
	namess<< (now->tm_year + 1900) <<'-' <<(now->tm_mon + 1) << '-' <<  now->tm_mday;
	date =namess.str();

	ui.setupUi(this);	
	QObject::connect(ui.tabWidget , SIGNAL(currentChanged(int)), this,SLOT(currentChangedSlot(int)));
	QObject::connect(ui.lstLog, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onListItemClicked(const QModelIndex &)));
	cal = Calibrator();
	listModel = new QStringListModel(this);
}

PravekshaUI::~PravekshaUI()
{

}

void PravekshaUI::on_btnStartCallibration_clicked()
{
	vector<Point> p;
	Calibrator::oriCorners = p;
	Calibrator::roiPoints = p;
	ui.btnStartCallibration->setEnabled(false);	
	ui.btnStopCallibration->setEnabled(true);
	if(VariableStorage::path==""){
		VariableStorage::path="F:/20july2013_time_7am_9am/Export_2013-07-24_114637/0 - 2013-07-20 12-00-00-033.asf";
	}
	cal.callibrate();
}

void PravekshaUI::on_btnStopCallibration_clicked()
{
	ui.btnStartCallibration->setEnabled(true);
	ui.btnStopCallibration->setEnabled(false);
	cal.stopVideo();
	praveksha.setCalibrator(cal);
	praveksha.pravekshaHandler();
}

void PravekshaUI::on_btnBrowse_clicked() {

QFileDialog dialog(this);
dialog.setNameFilter(tr("Videos (*.asf *.mp4 *.avi *.wmv *.3gp)"));
dialog.setViewMode(QFileDialog::Detail);
QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video"),"D:/Academic/FYP/Video",tr("Videos (*.asf *.mp4 *.avi *.wmv *.3gp)"));
VariableStorage::path = fileName.toStdString();
ui.txtPath->setText(fileName);

}

void PravekshaUI::on_btnSetLoggerPath_clicked(){		
	
	VariableStorage::loggerPath = ui.txtLoggerPath->text().toStdString();
	//ui.lblTest->setText(QString::fromStdString(VariableStorage::loggerPath));
}

void PravekshaUI::on_btnSetDistance_clicked(){
	VariableStorage::distance = ui.txtDistance->text().toDouble();
}

void PravekshaUI::updateLogList(String violation){
	//ui.lineEdit->setText(QString::number(speed));	
   
	listModel->insertRow(listModel->rowCount());
	QModelIndex index = listModel->index(listModel->rowCount()-1);
	listModel->setData(index, QString::fromStdString(violation));
	ui.lstLog->setModel(listModel);
}

void PravekshaUI::onListItemClicked(const QModelIndex index)
{
	
	//ui.lblImage->setText(QString::number(index.row()));
	std::stringstream s;
	QStringList ss = index.data().toString().split("_");
	QString sss;
	if(ss.last().startsWith("B")){
		sss = ss.first() + "_2";
	}else{
		sss = ss.first();
	}
	s << VariableStorage::loggerPath << "Praveksha_" << date << "/"<< sss.toStdString() << ".jpg";	
	QString st = QString::fromStdString(s.str());
	//ui.lblImage->setText(ss.last());
	ui.lblImage->setPixmap(st);
}

void PravekshaUI::on_btnStat_clicked()
{
	PravekshaUI::updateStat();
}

void PravekshaUI::currentChangedSlot(int id)
{
	if(id == 1){
		PravekshaUI::updateStat();
	}

}

void PravekshaUI::updateStat(){
	int maxY = 0;
		DatabaseHandler dbHandler;
		vector< vector<int> > vehicles = dbHandler.retrieveTodayData();

		customPlot = new QCustomPlot(ui.widgetGraph);
		
		QVector<double> x(vehicles.size()-1), y(vehicles.size()-1); 

		for (int i=0; i<vehicles.size()-1; i++)
		{
			x[i] = vehicles[i+1][0]; 
			y[i] = vehicles[i+1][1]; 
		}

		for (int i=0; i<y.size(); i++)
		{
			if(i==0)
				maxY = y[i];

			if(y[i] > maxY)
				maxY = y[i];
		}

		myBars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
		customPlot->addPlottable(myBars);
		// now we can modify properties of myBars:
		myBars->setData(x, y);

		customPlot->xAxis->setLabel("Rule Violation");
		customPlot->yAxis->setLabel("Number of Vehicles");
		// set axes ranges, so we see all data:
		customPlot->xAxis->setAutoTickCount(2);
		customPlot->resize(ui.widgetGraph->width(),ui.widgetGraph->height());
		customPlot->rescaleAxes(true);
		customPlot->replot();
		
		ui.txtTotVehicles->display(vehicles[0][0]);
		ui.txtWrongLane->display(vehicles[1][1]);
		ui.txtHighSpeed->display(vehicles[2][1]);
		//ui.txtBoth->display(vehicles[3][1]);

		
}