#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <iostream>

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
	connect(this->new_Timer,SIGNAL(timeout()),this,SLOT(test_func()));
	//com port receive data signal has already connected in open_port()
	//connect signal to enable atuo-scroll in info panel
	connect(this->ui->info_Panel,SIGNAL(cursorPositionChanged()),this,SLOT(info_Panel_Scroll()));
	//connect user defined function
	connect(this,SIGNAL(get_data_Done(double)),this,SLOT(print_Dot(double)));
}

MainWindow::~MainWindow()
{
	if (myCom!=NULL)
	{
		delete myCom;
	}
}

void MainWindow::test_func()
{
	std::cout<<"ttt"<<std::endl;
}


void MainWindow::Para_Init()
{
	refresh_timeout = 1000;
	new_Timer = new QTimer(this);
	new_Timer->start(refresh_timeout);
	this->ui->refresh_Time->setRange(0,2000);
	this->ui->refresh_Time->setValue(1000);

	comName = "com1";
	myComSetting.BaudRate = BAUD9600;
	myComSetting.DataBits = DATA_8;
	myComSetting.Parity   = PAR_NONE;
	myComSetting.FlowControl = FLOW_OFF;
	myComSetting.StopBits = STOP_1;
	myComSetting.Timeout_Millisec = 500;

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
}


void MainWindow::receive_Data()
{
	QByteArray temp = myCom->readAll();
	this->ui->info_Panel->insertPlainText(temp);
	double tem_double = temp.toDouble();

	//shift data
	for (int j=0;j<signal_len-1;j++)
	{
		signal_init[j] = signal_init[j+1];
	}

	signal_init[signal_len-1] = tem_double;

	//do transform
	WaveDecompose  (signal_init,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
	WaveReconstruct(signal_init,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);

	tem_double = recon[0].capp[signal_len-1];

	emit get_data_Done(tem_double);
}



void MainWindow::print_Dot(double in_data)
{

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
	this->refresh_timeout = in;
	new_Timer->start(this->refresh_timeout);
}


