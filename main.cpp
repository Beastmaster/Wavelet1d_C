#include "MainWindow.h"
#include <QApplication>

#include "wavelet.h"
#include <string>
#include <fstream>
#include <iostream>

int main(int argc,char ** argv)
{
	QApplication ui_main(argc,argv);

	MainWindow* new_win = new MainWindow;
	new_win->show();

	ui_main.exec();

/*
	int long_length = 100;
	double signal_init[500] = {0};
	int signal_len=30;
	int i=0;
	int j=0;
	FILE* fp;
	FILE* fp2;
	char read_buff[20] = {0};

	int de_level=5;
	WaveCoeff coeff[10] = {0};
	WaveRecon recon[10] = {0};

	std::fstream in("new.txt");
	std::string str;
	while(std::getline(in,str))//(i<500)//((fgets(read_buff,20,fp2))!=NULL)
	{
		//fgets(read_buff,10,fp2);
		//shift data
		for (j=0;j<signal_len-1;j++)
		{
			signal_init[j] = signal_init[j+1];
		}
		std::cout<<str<<std::endl;
		printf("\n%d \n",i++);

		signal_init[j] = std::stod(str);//double (atof(str));

		//do transform
		WaveDecompose(signal_init,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
		WaveReconstruct(signal_init,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);

		//print signal
		fprintf(fp,"%6f",recon[0].capp[signal_len-1]);
		fprintf(fp,",");
	}
	printf("done");*/

	return 0;
}
