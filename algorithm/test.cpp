//#include <firwin.h>
#include "wavelet.h"
//#include <Wavelet.hpp>
#include <string.h>

//time counter
#include <sys/time.h>

int main(int argc,char** argv)
{
	int signal_len=512;
	int _step  = 1;// (int) signal_len/10;  //read length
	int _shift = (int) signal_len/3;  //select points from reconstructed data

	double* signal_des  = (double*) malloc(signal_len*sizeof(double)) ;
	memset(signal_des,0,signal_len*sizeof(double));

	WaveCoeff coeff[10];
	WaveRecon recon[10];
	int de_level=5;
	int filter_name=0;

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


		//select data in the middle of the signal
		for (int i=_shift;i<_shift+_step;i++)
			fprintf(fp_w,"%f\n", recon[0].capp[i]);
	}

	fclose(fp_r);
	fclose(fp_w);

	return 0;
}



