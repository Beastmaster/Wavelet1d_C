
#include "wavelet.h"


int main(char**, int)
{
	double signal_init[]={0,    0.2079,    0.4067,    0.5878,    0.7431,    0.8660,
						0.9511 ,   0.9945,    0.9945,    0.9511,    0.8660,    0.7431,
						0.5878,    0.4067,    0.2079,    0.0000,   -0.2079,   -0.4067,
						-0.5878,   -0.7431,   -0.8660,   -0.9511,   -0.9945,   -0.9945,
						-0.9511,   -0.8660,   -0.7431,   -0.5878,   -0.4067,   -0.2079};
	int signal_len=30;

	int i=0;
	FILE* fp;

	WaveCoeff coeff;

	DWT(signal_init,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,&coeff);

	//print for test
	if ((fp = fopen("result", "w")) == NULL) {
		perror("Error opening input file");
		exit(-1);
	}
	for (i=0;i<100;i++)
	{
		fprintf(fp,"%6f",coeff.app[i]);
		fprintf(fp,",");
	}
	fprintf(fp,"\n");
	for (i=0;i<100;i++)
	{
		fprintf(fp,"%6f",coeff.det[i]);
		fprintf(fp,",");
	}
	

	return 0;
}
