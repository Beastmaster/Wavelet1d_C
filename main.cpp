
#include "wavelet.h"


int main(char**, int)
{
	//double signal_init[]={0,    0.2079,    0.4067,    0.5878,    0.7431,    0.8660,
	//					0.9511 ,   0.9945,    0.9945,    0.9511,    0.8660,    0.7431,
	//					0.5878,    0.4067,    0.2079,    0.0000,   -0.2079,   -0.4067,
	//					-0.5878,   -0.7431,   -0.8660,   -0.9511,   -0.9945,   -0.9945,
	//					-0.9511,   -0.8660,   -0.7431,   -0.5878,   -0.4067,   -0.2079};
	//
	double signal_init[] = {0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0.0322, 0.0622,0.0900,0.1156,
		0.1389,0.1600,0.1789,0.1956,
		0.2100,0.2222,0.2322,0.2400,
		0.2456,0.2489,0.2500,0.2489,
		0.2456,0.2400,0.2322,0.2222,
		0.2100,0.1956,0.1789,0.1600,
		0.1389,0.1156,0.0900,0.0622,
		0.0322,0,0,0
	};
	
	int signal_len=45;

	int i,j=0;
	FILE* fp;

	int de_level=5;
	WaveCoeff coeff[10] = {0};
	WaveRecon recon[10] = {0};


	DWT(signal_init,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,&coeff[0],NULL,NULL);


	
	WaveDecompose(signal_init,signal_len,db4_Lo_D,db4_len,db4_Hi_D,db4_len,coeff,de_level);


	WaveReconstruct(signal_init,signal_len,db4_Lo_R,db4_len,db4_Hi_R,db4_len,coeff,recon,'a',de_level);

	//print for test
	if ((fp = fopen("result", "w")) == NULL) {
		perror("Error opening input file");
		exit(-1);
	}
	//print signal
	fprintf(fp,"signal: \n");
	for (i=0;i<signal_len;i++)
	{	
		fprintf(fp,"%6f",signal_init[i]);
		fprintf(fp,",");
	}

	//print result
	fprintf(fp,"\n decompose parameters\n");
	for (i=0;i<de_level;i++)
	{
		fprintf(fp,"level %d: ",i+1);
		for(j=0;j<coeff[i].length;j++)
		{
			fprintf(fp,"%6f",coeff[i].capp[j]);
			fprintf(fp,",");
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n reconstruct parameters\n");
	for (i=0;i<de_level;i++)
	{
		fprintf(fp,"level %d: ",i+1);
		for(j=0;j<recon[i].length;j++)
		{
			fprintf(fp,"%6f",recon[i].capp[j]);
			fprintf(fp,",");
		}
		fprintf(fp,"\n");
	}
	fclose(fp);


	return 0;
}
