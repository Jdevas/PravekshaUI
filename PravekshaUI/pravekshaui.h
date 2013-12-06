#ifndef PRAVEKSHAUI_H
#define PRAVEKSHAUI_H

#include <QtGui/QMainWindow>
#include "ui_pravekshaui.h"
#include "PravekshaHandler.h"
#include "qcustomplot.h"
#include "DatabaseHandler.h"


class PravekshaUI : public QMainWindow
{
	Q_OBJECT

public:
	PravekshaUI(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PravekshaUI();	
	PravekshaHandler praveksha;

private:
	Ui::PravekshaUIClass ui;
	Calibrator cal;
	QStringList *stringList;
	QStringListModel* listModel;
	QCustomPlot *customPlot;
	QCPBars *myBars; 

public slots:
		void on_btnStartCallibration_clicked();
		void on_btnStopCallibration_clicked();
		void on_btnBrowse_clicked();			
		void on_btnSetLoggerPath_clicked();
		void on_btnSetDistance_clicked();
		void onListItemClicked(const QModelIndex index);
		void on_btnStat_clicked();

private slots:
        void updateLogList(String violation);
		void currentChangedSlot(int id);
		void updateStat();
};

#endif // PRAVEKSHAUI_H
