#include "pravekshaui.h"
#include <QtGui/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SpeedDetector spd;

	PravekshaUI w;
	w.praveksha = PravekshaHandler(&spd);

	QObject::connect(&spd, SIGNAL(violationDetected(double)),&w,SLOT(updateLogList(double)));
	//QObject::connect(&w, SIGNAL(itemClicked(QListWidgetItem*)), &w, SLOT(onListItemClicked(QListWidgetItem*)));
	w.show();
	return a.exec();
}
