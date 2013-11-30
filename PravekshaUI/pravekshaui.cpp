#include "pravekshaui.h"

PravekshaUI::PravekshaUI(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);	
	QObject::connect(ui.lstLog, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onListItemClicked(const QModelIndex &)));
	cal = Calibrator();
	listModel = new QStringListModel(this);
}

PravekshaUI::~PravekshaUI()
{

}

void PravekshaUI::on_btnStartCallibration_clicked()
{
	if(VariableStorage::path==""){
	VariableStorage::path="F:/20july2013_time_7am_9am/Export_2013-07-24_114637/0 - 2013-07-20 12-00-00-033.asf";
	}
	cal.callibrate();
	//ui.btnStopCallibration->setEnabled(true);
}

void PravekshaUI::on_btnStopCallibration_clicked()
{
	cal.stopVideo();
	praveksha.setCalibrator(cal);
	praveksha.pravekshaHandler();
}

void PravekshaUI::on_btnBrowse_clicked() {

QFileDialog dialog(this);
dialog.setNameFilter(tr("Videos (*.asf *.mp4 *.avi *.wmv *.3gp)"));
dialog.setViewMode(QFileDialog::Detail);
QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video"),
"D:/Academic/FYP/Video",
tr("Videos (*.asf *.mp4 *.avi *.wmv *.3gp)"));
VariableStorage::path = fileName.toStdString();
ui.txtPath->setText(fileName);
}


void PravekshaUI::updateLogList(double speed){
	//ui.lineEdit->setText(QString::number(speed));	
   
	listModel->insertRow(listModel->rowCount());
	QModelIndex index = listModel->index(listModel->rowCount()-1);
	listModel->setData(index, QString::number(speed));
	ui.lstLog->setModel(listModel);
}

void PravekshaUI::onListItemClicked(const QModelIndex index)
{
	//ui.lblImage->setText(index.data().toString());
	ui.lblImage->setText(QString::number(index.row()));
	std::stringstream s;
	s << "F:/20july2013_time_7am_9am/Logs/Praveksha_2013-11-27/"<<index.row()+1<< ".jpg";	
	QString st = QString::fromStdString(s.str());
	ui.lblImage->setPixmap(st);
}