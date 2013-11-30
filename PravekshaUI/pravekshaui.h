#ifndef PRAVEKSHAUI_H
#define PRAVEKSHAUI_H

#include <QtGui/QMainWindow>
#include "ui_pravekshaui.h"
#include "Praveksha.h"

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

public slots:
		void on_btnStartCallibration_clicked();
		void on_btnStopCallibration_clicked();
		void on_btnBrowse_clicked();	
		void onListItemClicked(const QModelIndex index);

private slots:
        void updateLogList(double speed);
};

#endif // PRAVEKSHAUI_H
