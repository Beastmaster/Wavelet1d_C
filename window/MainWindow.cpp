#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <math.h>

const double test_data[] = 
{
	0.242829
	,0.623746
	,0.437564
	,0.0586238
	,0.0838475
	,0.507896
	,0.776643
	,0.587504
	,0.322593
	,0.496892
	,1.0053
	,1.1651
	,0.618749
	,-0.145541
	,-0.341168
	,0.143415
	,0.635302
	,0.540987
	,0.0865776
	,-0.0632829
	,0.283049
	,0.632739
	,0.540891
	,0.233634
	,0.263
	,0.705935
	,0.973702
	,0.584181
	,-0.16679
	,-0.509014
	,-0.159113
	,0.357462
	,0.38421
	,-0.0202079
	,-0.23941
	,0.0431232
	,0.432933
	,0.41934
	,0.0982847
	,0.0324241
	,0.448395
	,0.852458
	,0.644285
	,-0.0736648
	,-0.55856
	,-0.344253
	,0.207231
	,0.380501
	,0.03622
	,-0.277992
	,-0.0985545
	,0.334901
	,0.462458
	,0.196146
	,0.0377927
	,0.356896
	,0.82618
	,0.791441
	,0.148108
	,-0.457299
	,-0.40552
	,0.143542
	,0.47444
	,0.242269
	,-0.135351
	,-0.0940565
	,0.304855
	,0.5113
	,0.281558
	,0.0304617
	,0.23643
	,0.737447
	,0.855498
	,0.296672
	,-0.408154
	,-0.516127
	,0.00566627
	,0.462868
	,0.327943
	,-0.107093
	,-0.190538
	,0.195229
	,0.523662
	,0.398094
	,0.114859
	,0.228113
	,0.744964
	,1.01482
	,0.576128
	,-0.200534
	,-0.504576
	,-0.0865454
	,0.468508
	,0.492782
	,0.0814177
	,-0.123706
	,0.175687
	,0.562858
	,0.540388
	,0.235284
	,0.207028
	,0.643106
	,1.02137
	,0.771575
	,0.0499811
	,-0.388172
	,-0.124457
	,0.431561
	,0.574904
	,0.219444
	,-0.0665276
	,0.141305
	,0.559197
	,0.64007
	,0.348168
	,0.202588
	,0.53047
	,0.955251
	,0.842977
	,0.159629
	,-0.411861
	,-0.300617
	,0.262155
	,0.551409
	,0.285177
	,-0.0743217
	,0.00753595
	,0.411171
	,0.583312
	,0.335196
	,0.114303
	,0.360394
	,0.84831
	,0.902594
	,0.295528
	,-0.395916
	,-0.466982
	,0.051721
	,0.463623
	,0.308202
	,-0.0864242
	,-0.117411
	,0.256697
	,0.509794
	,0.321323
	,0.0433372
	,0.207495
	,0.761654
	,1.05999
	,0.672844
	,-0.0519113
	,-0.386629
	,-0.0814322
	,0.385625
	,0.44681
	,0.122756
	,-0.10481
	,0.0315048
	,0.288928
	,0.317719
	,0.133865
	,0.0340591
	,0.152498
	,0.303159
	,0.275786
	,0.122558
	,0.0509975
	,0.121913
	,0.184574
	,0.10197
	,-0.0753222
	,-0.207159
	,-0.258042
	,-0.313234
	,-0.428306
	,-0.546188
	,-0.583761
	,-0.539243
	,-0.464864
	,-0.360144
	,-0.148168
	,0.232529
	,0.745627
	,1.28185
	,1.74537
	,2.09898
	,2.34411
	,2.48678
	,2.52889
	,2.47467
	,2.33285
	,2.11467
	,1.83378
	,1.50789
	,1.16599
	,0.859087
	,0.648091
	,0.55399
	,0.520604
	,0.444648
};

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Para_Init();

	connect(this->ui->port_name_Comb,SIGNAL(currentIndexChanged(const QString)),this,SLOT(sel_portName(QString)));
	connect(this->ui->baud_rate_Comb,SIGNAL(currentIndexChanged(int)),			this,SLOT(set_BaudRate(int)));
	connect(this->ui->stop_bits_Comb,SIGNAL(currentIndexChanged(int)),			this,SLOT(set_stopBits(int)));
	connect(this->ui->data_bits_Comb,SIGNAL(currentIndexChanged(int)),			this,SLOT(set_dataBits(int)));
	connect(this->ui->parity_Comb,   SIGNAL(currentIndexChanged(int)),			this,SLOT(set_Parity(int)));
	connect(this->ui->open_port_Btn, SIGNAL(clicked()),							this,SLOT(open_Port()));
	connect(this->ui->close_port_Btn,SIGNAL(clicked()),							this,SLOT(close_Port()));
	connect(this->ui->send_Btn,SIGNAL(clicked()),							this,SLOT(send_Data()));
	connect(this->ui->refresh_Time,  SIGNAL(valueChanged(int)),				this,SLOT(get_refresh_Timeout(int)));

	//connect timer function
	connect(this->check_port_Timer,SIGNAL(timeout()),this,SLOT(check_port_Status()));
	connect(this->test_timer,      SIGNAL(timeout()),this,SLOT(test_timer_func()));
	//com port receive data signal has already connected in open_port()
	//connect signal to enable atuo-scroll in info panel
	connect(this->ui->info_Panel,SIGNAL(cursorPositionChanged()),this,SLOT(info_Panel_Scroll()));
	//connect user defined function
	connect(this,SIGNAL(get_data_Done(double)),this,SLOT(pass_Dot(double)));
	//connect sliderbar
	connect(this->ui->num_points_Slider,SIGNAL(valueChanged(int)),this,SLOT(change_X_Scope(int)));
	connect(this->ui->y_pos_Scope,SIGNAL(valueChanged(int)),this,SLOT(change_Y_pos_Scope(int)));
	connect(this->ui->y_neg_Scope,SIGNAL(valueChanged(int)),this,SLOT(change_Y_neg_Scope(int)));
}

MainWindow::~MainWindow()
{
	//stop timer first
	check_port_Timer->stop();
	delete check_port_Timer;

	if (myCom!=NULL)
	{
		delete myCom;
	}

	delete plot_view;
}



void MainWindow::Para_Init()
{
	point_cnt = 100;
	plot_view = new QwtPlotView(this->ui->qwtPlot);

	check_port_Timer = new QTimer(this);
	test_timer = new QTimer(this);
	test_timer->start(2);
	test_timer_cnt = 0;

	//start timer here
	check_port_Timer->start(500);
	this->ui->refresh_Time->setRange(0,1000);
	this->ui->refresh_Time->setValue(10);

	comName = "com1";
	myComSetting.BaudRate = BAUD9600;
	myComSetting.DataBits = DATA_8;
	myComSetting.Parity   = PAR_NONE;
	myComSetting.FlowControl = FLOW_OFF;
	myComSetting.StopBits = STOP_1;
	myComSetting.Timeout_Millisec = 27;

	myCom = NULL;//new Win_QextSerialPort(comName,myComSetting,QextSerialBase::EventDriven);

	//parameters used in wavelet transform
	//zero out all of these containers
	for (int i=0;i<30;i++)
	{
		signal_init[i]=0;
	}
	signal_len=30;
	de_level=5;
	for (int i=0;i<10;i++)
	{
		coeff[i].length=0 ;
		recon[i].length=0 ;
		for (int j=0;j<100;j++)
		{
			coeff[i].capp[j]=0;
			coeff[i].cdet[j]=0;
			recon[i].capp[j]=0;
			recon[i].cdet[j]=0;
		}
	}

	//setup slider bar
	this->ui->num_points_Slider->setMinimum(100);
	this->ui->num_points_Slider->setMaximum(2000);
	this->ui->num_points_Slider->setTickInterval(100);

	//setup y scope bar
	this->ui->y_pos_Scope->setMinimum(0);
	this->ui->y_pos_Scope->setMaximum(200);
	this->ui->y_pos_Scope->setSliderPosition(2);
	this->ui->y_neg_Scope->setMinimum(-200);
	this->ui->y_neg_Scope->setMaximum(0);
	this->ui->y_neg_Scope->setSliderPosition(-2);

	//--------------init signal process parameters------------//
	long_length = 100;
	signal_init[30];
	memset(signal_init,0,30*sizeof(double));
	signal_len = 30;
	de_level = 5;
	memset(coeff,0,10*sizeof(WaveCoeff));
	memset(recon,0,10*sizeof(WaveCoeff));
}

//receive data and do wavelet decompose and reconstruct 
//emit a signal and pass data to plot in chart view
void MainWindow::receive_Data()
{
	if (myCom->bytesAvailable()>=1)
	{

	QByteArray temp = myCom->readAll();
	QString tem_qstr = QString(temp);
	double tem_num = tem_qstr.toDouble();
	this->ui->info_Panel->insertPlainText(QString::number(tem_num));
	this->ui->info_Panel->insertPlainText("\n");

	//this line emit a signal to trigger pass_Dot
	emit get_data_Done(tem_num/300);
	}
}


//trigger by receive_data 
//pass data to buff
void MainWindow::pass_Dot(double in_data)
{
	long start = clock();
	//process data first
	for (int j=0;j<signal_len-1;j++)
	{
		signal_init[j] = signal_init[j+1];
	}

	signal_init[signal_len-1] = in_data;

	//do transform
	WaveDecompose(signal_init,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
	WaveReconstruct(signal_init,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);
	
	//std::cout<<end-start<<std::endl;
	if (this->ui->en_filter_Btn->isChecked())
	{
		this->plot_view->pass_Dot(recon[0].capp[signal_len-1]);
	}
	else
	{
		this->plot_view->pass_Dot(in_data);
	}
	long end = clock();
	//std::cout<<in_data<<std::endl;
}

void MainWindow::send_Data()
{
	if (myCom == NULL)
		return;
	else
	{
		if (!myCom->isOpen())
		{
			QMessageBox::warning(NULL,"warning","Com Port no open",QMessageBox::Yes);
			return;
		}
	}

	QString temp = this->ui->send_Panel->toPlainText();

	//send data
	myCom->write(temp.toAscii());

	//clear data in send panel
	this->ui->send_Panel->clear();
}


void MainWindow::find_Port()
{
	//myCom->close();
}


void MainWindow::open_Port()
{
	//create new com port
	if (myCom != NULL)
	{
		disconnect(myCom,SIGNAL(readyRead()),this,SLOT(receive_Data()));
		delete myCom;
	}
	myCom = new Win_QextSerialPort(comName,myComSetting,QextSerialBase::EventDriven);

	//open it
	if (!myCom->open(QIODevice::ReadWrite))
	{
		QMessageBox::warning(NULL,"Warning","Cannot Open Port",QMessageBox::Yes);
		return;
	}

	//
	connect(myCom,SIGNAL(readyRead()),this,SLOT(receive_Data()));
}

void MainWindow::close_Port()
{
	if (myCom == NULL)
	{
		return;
	}
	if (myCom->isOpen())
	{
		myCom->close();
	}
}

void MainWindow::sel_portName(QString str)
{
	std::cout<<str.toStdString()<<std::endl;
	comName = str;
}

void MainWindow::set_BaudRate(int index)
{
	switch (index)
	{
	case 0:
		{
			myComSetting.BaudRate = BAUD9600;
			break;
		}
	case 1:
		{
			myComSetting.BaudRate = BAUD19200;
			break;
		}
	case 2:
		{
			myComSetting.BaudRate = BAUD115200;
			break;
		}
	case 3:
		{
			myComSetting.BaudRate = BAUD300;
			break;
		}
	case 4:
		{
			myComSetting.BaudRate = BAUD600;
			break;
		}
	case 5:
		{
			myComSetting.BaudRate = BAUD1200;
			break;
		}
	case 6:
		{
			myComSetting.BaudRate = BAUD2400;
			break;
		}
	case 7:
		{
			myComSetting.BaudRate = BAUD4800;
			break;
		}
	default:
		break;
	}
}

void MainWindow::set_Parity(int index)
{
	switch (index)
	{
	case 0:
		{
			myComSetting.Parity = PAR_NONE;
			break;
		}
	case 1:
		{
			myComSetting.Parity = PAR_ODD;
			break;
		}
	case 2:
		{
			myComSetting.Parity = PAR_EVEN;
			break;
		}
	case 3:
		{
			myComSetting.Parity = PAR_MARK;
			break;
		}
	case 4:
		{
			myComSetting.Parity = PAR_SPACE;
			break;
		}
	default:
		break;
	}
}

void MainWindow::set_dataBits(int index)
{
	switch (index)
	{
	case 0:
		{
			myComSetting.DataBits = DATA_8;
			break;
		}
	case 1:
		{
			myComSetting.DataBits = DATA_7;
			break;
		}
	case 2:
		{
			myComSetting.DataBits = DATA_6;
			break;
		}
	case 3:
		{
			myComSetting.DataBits = DATA_5;
			break;
		}
	default:
		break;
	}
}

void MainWindow::set_stopBits(int index)
{
	switch (index)
	{
	case 0:
		{
			myComSetting.StopBits = STOP_1;
			break;
		}
	case 1:
		{
			myComSetting.StopBits = STOP_2;
			break;
		}
	case 2:
		{
			myComSetting.StopBits = STOP_1_5;
			break;
		}
	default:
		break;
	}
}

//information scroll in info panel
void MainWindow::info_Panel_Scroll()
{
	QTextCursor text_cursor =  ui->info_Panel->textCursor();
	text_cursor.movePosition(QTextCursor::End);
	ui->info_Panel->setTextCursor(text_cursor);
}

void MainWindow::get_refresh_Timeout(int in)
{
	plot_view->setInterval(in);
}

void MainWindow::check_port_Status()
{
	if (myCom == NULL)
	{
		this->ui->is_Open_Btn->setChecked(Qt::Unchecked);
	}
	else
	{
		if (myCom->isOpen())
		{
			this->ui->is_Open_Btn->setChecked(Qt::Checked);
		}
		else
		{
			this->ui->is_Open_Btn->setChecked(Qt::Unchecked);
		}
	}
	return;
}

void MainWindow::change_X_Scope(int num)
{
	plot_view->change_X_Scope(num);
}

void MainWindow::change_Y_pos_Scope(int pos)
{
	plot_view->change_Y_Scope(pos,this->ui->y_neg_Scope->value());
}

void MainWindow::change_Y_neg_Scope(int neg)
{
	plot_view->change_Y_Scope(this->ui->y_pos_Scope->value(),neg);
}

void MainWindow::test_timer_func()
{
	if (test_timer_cnt>199)
	{
		test_timer_cnt = 0;
	}
	//double pi = 3.1415926;
	double data_buff = test_data[test_timer_cnt];
	test_timer_cnt++;

	emit get_data_Done(data_buff);

}


QwtPlotView::QwtPlotView(QwtPlot* plot)
{
	this->plot_view = plot;
	//plot init process
	this->plot_view->setTitle( "ECG Signal" );
	this->plot_view->setCanvasBackground( Qt::white );
	this->plot_view->setAxisScale( QwtPlot::yLeft, -2.0, 2.0 );
	this->plot_view->setAxisScale( QwtPlot::xBottom, 0.0, 100.0 );
	this->plot_view->insertLegend( new QwtLegend() );

	grid = new QwtPlotGrid();
	grid->attach( this->plot_view);

	curve = new QwtPlotCurve();
	//curve->setTitle( "Some Points" );
	curve->setPen( Qt::blue, 4 ),
		curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

	symbol = new QwtSymbol( QwtSymbol::Ellipse,
		QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
	//curve->setSymbol( symbol );

	curve->attach( this->plot_view);

	num_points_dis = 100;
	//init points here
	point_coor.length = num_points_dis;
	point_coor.x_val = new double[point_coor.length];
	point_coor.y_val = new double[point_coor.length];
	for (int i=0;i<point_coor.length;i++)
	{
		point_coor.x_val[i]=i;
		point_coor.y_val[i]=0;
	}
	dot_temp = 0.0;
	point_cnt = 0;

	curve->setRawSamples(point_coor.x_val,point_coor.y_val,point_coor.length);

	timer_plot = new QTimer;
	timer_plot->start(5);
	//connect 
	connect(timer_plot,SIGNAL(timeout()),this,SLOT(run()));
}

QwtPlotView::~QwtPlotView()
{
	//disconnect
	this->exit();
	disconnect(timer_plot,SIGNAL(timeout()),this,SLOT(run()));
	//stop timer
	timer_plot->stop();
	delete timer_plot;

	delete curve;
	delete grid;
	delete symbol;

	delete point_coor.x_val;
	delete point_coor.y_val;
}

void QwtPlotView::replot(QPolygonF* new_points)
{
	curve->setSamples( *new_points );
	this->plot_view->replot();
}

//inter refresh frequency
void QwtPlotView::setInterval(int inter)
{
	timer_plot->start(inter);
}

void QwtPlotView::run()
{
	if (point_cnt>this->num_points_dis-1)
	{
		point_cnt = 0;
	}
	point_coor.y_val[point_cnt] = dot_temp;
	point_cnt++;

	this->plot_view->replot();
}

void QwtPlotView::pass_Dot(double d)
{
	dot_temp = d;
}

void QwtPlotView::change_Y_Scope(int pos,int neg)
{
	this->plot_view->setAxisScale( QwtPlot::yLeft,neg ,pos  );
}

void QwtPlotView::change_X_Scope(int xx)
{
	this->num_points_dis = xx;
	point_coor.length = num_points_dis;
	//delete data first
	delete point_coor.x_val;
	delete point_coor.y_val;

	//re-new array
	point_coor.x_val = new double[point_coor.length];
	point_coor.y_val = new double[point_coor.length];
	for (int i=0;i<point_coor.length;i++)
	{
		point_coor.x_val[i]=i;
		point_coor.y_val[i]=0;
	}

	this->plot_view->setAxisScale( QwtPlot::xBottom, 0.0, point_coor.length );
	curve->setRawSamples(point_coor.x_val,point_coor.y_val,point_coor.length);
}


