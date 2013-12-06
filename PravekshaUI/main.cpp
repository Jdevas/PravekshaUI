#include "pravekshaui.h"
#include <QtGui/QApplication>
#include "qcustomplot.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Logger logger; 
	VariableStorage::distance=0;
	PravekshaUI w;
	w.praveksha = PravekshaHandler(&logger);

	QObject::connect(&logger, SIGNAL(violationDetected(String)),&w,SLOT(updateLogList(String)));      //connect logger with qt interface
	
	w.move(675,100);
	w.show();
	return a.exec();
}