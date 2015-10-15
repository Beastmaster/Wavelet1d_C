//#include <firwin.h>
#include "wavelet.h"
//#include <Wavelet.hpp>
#include <string.h>
#include <math.h>
//time counter
#include <sys/time.h>

int main(int argc,char** argv)
{
	int signal_len=40;
	int _step  = 1;// (int) signal_len/10;  //read length
	int _shift = (int) signal_len/2;  //select points from reconstructed data

	double* signal_des  = (double*) malloc(signal_len*sizeof(double));
	double* signal_buf1 = (double*) malloc(signal_len*sizeof(double));   //signal buff, hold wavelet filtered signal
	double* signal_buf2 = (double*) malloc(signal_len*sizeof(double));   //signal buff, hold differentiated result
	double* signal_buf3 = (double*) malloc(signal_len*sizeof(double));   //signal buff, hold squaring result
	double* signal_buf4 = (double*) malloc(signal_len*sizeof(double));   //signal buff, hold integrated function result
	
	memset(signal_des ,0,signal_len*sizeof(double));
	memset(signal_buf1,0,signal_len*sizeof(double));
	memset(signal_buf2,0,signal_len*sizeof(double));
	memset(signal_buf3,0,signal_len*sizeof(double));
	memset(signal_buf4,0,signal_len*sizeof(double));
	
	
	WaveCoeff coeff[10];
	WaveRecon recon[10];
	int de_level=5;
	int filter_name=0;
	double des=0.0;     //selected wavelet filter result
	int peak_flg1=0;    //flag2
	int peak_flg2=0;    //flag2
	double peak = 0.0;  //QRS peak

	char* filename=argv[1];
	const char filename2[]="test2.txt";

	printf("opening file %s",filename);

	FILE *fp_r=fopen("test.txt","r");   //read data
	FILE *fp_w=fopen(filename2,"w");   //write result
	
	struct timeval start;
	unsigned long timer;	

	//begin loop
	if (fp_r==NULL)
	{
		printf("NULL file pionter");
		return 0;
	}
	char buf[15]={0};

	while (fgets(buf,15,fp_r)!=NULL)
	{	
		//time counter
		gettimeofday(&start,NULL);
		timer=start.tv_usec;
		printf("%d\n",timer);	
	
		//move out components ahead
		for(int i=0;i<signal_len-_step;i++)
			signal_des[i]=signal_des[i+_step];

		//put new data to signal
		for (int i=signal_len-_step; i<signal_len;i++)
		{
			signal_des[i]=atof(buf);
			if (fgets(buf,15,fp_r)==NULL)
				continue;			
		}

		//begin filter
		switch(filter_name)
		{
		case 0: //db4
			{
				WaveDecompose(signal_des,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);
				break;
			}
		case 1: //db5
			{
				WaveDecompose(signal_des,signal_len,db5_Lo_D,db5_len,db4_Hi_D,db5_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,db5_Lo_R,db5_len,db4_Hi_R,db5_len,coeff,recon,'a',de_level);
				break;
			}
		case 2: //db6
			{
				WaveDecompose(signal_des,signal_len,db6_Lo_D,db6_len,db6_Hi_D,db6_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,db6_Lo_R,db6_len,db6_Hi_R,db6_len,coeff,recon,'a',de_level);
				break;
			}
		case 3: //sym4
			{
				WaveDecompose(signal_des,signal_len,sym4_Lo_D,sym4_len,sym4_Hi_D,sym4_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,sym4_Lo_R,sym4_len,sym4_Hi_R,sym4_len,coeff,recon,'a',de_level);
				break;
			}
		case 4: //sym5
			{
				WaveDecompose(signal_des,signal_len,sym5_Lo_D,sym5_len,sym5_Hi_D,sym5_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,sym5_Lo_R,sym5_len,sym5_Hi_R,sym5_len,coeff,recon,'a',de_level);
				break;
			}
		case 5: //sym6
			{
				WaveDecompose(signal_des,signal_len,sym6_Lo_D,sym6_len,sym6_Hi_D,sym6_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,sym6_Lo_R,sym6_len,sym6_Hi_R,sym6_len,coeff,recon,'a',de_level);
				break;
			}
		case 6: //coif4
			{
				WaveDecompose(signal_des,signal_len,coif4_Lo_D,coif4_len,coif4_Hi_D,coif4_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,coif4_Lo_R,coif4_len,coif4_Hi_R,coif4_len,coeff,recon,'a',de_level);
				break;
			}
		case 7: //coif5
			{
				WaveDecompose(signal_des,signal_len,coif5_Lo_D,coif5_len,coif5_Hi_D,coif5_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,coif5_Lo_R,coif5_len,coif5_Hi_R,coif5_len,coeff,recon,'a',de_level);
				break;
			}
		default: //db4
			{
				WaveDecompose(signal_des,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);
				WaveReconstruct(signal_des,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);
				break;
			}
		}
		
		des = recon[0].capp[_shift];
		
		for(int i=1;i<signal_len;i++)
			signal_buf1[i] = signal_buf1[i-1];
		signal_buf1[0] = des;
		
		//1.  differentiate function -- derivative
		for(int i=signal_len-1;i>0;i--)
			signal_buf2[i] = signal_buf2[i-1];
		signal_buf2[0] = signal_buf1[0]-signal_buf2[3];
		
		//2.  Squaring funciton 
		//3.  Integrate function
		for(int i=signal_len-1;i>0;i--)
		{
			signal_buf3[i] = signal_buf3[i-1];
			signal_buf4[i] = signal_buf4[i-1];
			signal_buf4[0] += signal_buf3[i-1];
		}
		//signal_buf3[0] = signal_buf2[0]*signal_buf2[0];
		signal_buf3[0] = abs(signal_buf2[0]);
		signal_buf4[0] = signal_buf4[0]+signal_buf3[0];
		
		//4.  Search peak
		if (signal_buf4[0]>=peak)&&(signal_buf4[4]<peak)
			printf("detect a peak \n");
		
			
		//select data in the middle of the signal
		for (int i=_shift;i<_shift+_step;i++)
			fprintf(fp_w,"%f\n",des);// recon[0].capp[i]);
	}

	fclose(fp_r);
	fclose(fp_w);

	return 0;
}













