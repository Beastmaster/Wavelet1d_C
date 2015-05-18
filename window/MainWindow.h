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
#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QString>

//print screen
#include <QPixmap>
#include <QDateTime>
#include <QTextStream>

#include <QTimer>
#include <time.h>

//include serial port head files
#include "win_qextserialport.h"

//wavelet functions
#include "wavelet.h"

//qwt need head files
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

class QwtPlotView;

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
		void set_Filter(int);
		void set_Level(int);
		void receive_Data();
		void info_Panel_Scroll();
		void pass_Dot(double);
		void get_refresh_Timeout(int);
		void check_port_Status();
		void test_timer_func();
		void change_X_Scope(int);
		void change_Y_pos_Scope(int);
		void change_Y_neg_Scope(int);
		void check_save_Data(bool checked);
		void save_Dot(double);
		void snip_Screen();
		
	signals:
		void get_data_Done(double);


protected:

	//--------------for signal process--------------//
	int long_length;
	double signal_init[30];
	int signal_len;
	int de_level;
	int filter_name;
	WaveCoeff coeff[10];
	WaveRecon recon[10];

private:
	Ui::MainWindow	*ui;
	PortSettings myComSetting;
	Win_QextSerialPort* myCom;
	QByteArray com_temp;
	QString comName;
	QTimer* check_port_Timer; //check serial port status 500ms
	QTimer* test_timer;
	int     test_timer_cnt;
	QTextStream* data_text;
	QFile data_file;

	//private functions
	void Para_Init();

	//parameters to refresh plot view
	int refresh_timeout;  //unit is millisecond (mS)
    int point_cnt;        //number of points in view
	QwtPlotView* plot_view;   //plot view


};



class QwtPlotView:QThread
{
	Q_OBJECT

	typedef struct 
	{
		int length;
		double* x_val;
		double* y_val;
	} point_coordinate;
public:
	QwtPlotView(QwtPlot* plot_view);
	~QwtPlotView();

	void replot(QPolygonF* new_points);
	void setInterval(int);
	void pass_Dot(double);
	void change_Y_Scope(int,int);
	void change_X_Scope(int);

	public slots:
		void run();

private:
	QTimer* timer_plot;

	QwtPlot* plot_view;
	
	//plot parameters
	QwtPlotCurve *curve;
	QwtPlotGrid *grid;
	QwtSymbol *symbol;
	int num_points_dis;
	double dot_temp;
	int point_cnt;

	point_coordinate point_coor;
};









#endif







