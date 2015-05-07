/*
Author: Qinshuo
Date:   2015.5.7
Site:   SIAT, Shenzhen

Description:
1. serial port basic function
2. display real time plot
*/
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QApplication>

#include <QTimer>


//include serial port head files
#include "win_qextserialport.h"

//wavelet functions
#include "wavelet.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	public slots:

		void find_Port();
		void open_Port();
		void close_Port();
		void send_Data();
		void sel_portName(QString);
		void set_BaudRate(int);
		void set_dataBits(int);
		void set_Parity(int);
		void set_stopBits(int);
		void receive_Data();
		void info_Panel_Scroll();
		void print_Dot(double);
		void get_refresh_Timeout(int);
		void test_func();
		
	signals:
		void get_data_Done(double);


protected:
	//parameters that used by wavelet
	double signal_init[30];
	int signal_len;
	int de_level;
	WaveCoeff coeff[10];
	WaveRecon recon[10];

private:
	Ui::MainWindow	*ui;
	PortSettings myComSetting;
	Win_QextSerialPort* myCom;
	QString comName;
	QTimer* new_Timer;

	//private functions
	void Para_Init();

	//parameters to refresh plot view
	int refresh_timeout;  //unit is millisecond (mS)

};
#endif







