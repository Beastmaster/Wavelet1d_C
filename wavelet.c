#include "wavelet.h"




//Function:
//Parameter: sig_length must be even number
//			Length of result : sig_length/2
//Note: This function is not used here, because we down-sample result in DWT
void DownSample(double* signal,int sig_length,double* result)
{
	//if (result!=NULL)
	//{
	//	free(result);
	//}
	//result = (double*) malloc(sig_length/2*(sizeof(double)));
	unsigned char i=0;
	for (i=0;i<sig_length/2;i++)
	{
		result[i] = signal[2*i];
	}

}


//Function:
//Parameter: sig_length must be even number
//			length of result: sig_length*2
//Note: This function is not used here, because we up-sample result in IDWT
void UpSample(double* signal,int sig_length,double* result)
{
	//if (result!=NULL)
	//{
	//	free(result);
	//}
	//result = (double*) malloc(sig_length*2*(sizeof(double)));
	
	//even: x
	unsigned char i=0;
	for (i=0;i<sig_length*2;i++)
	{
		result[2*i] = signal[i];
		result[2*i+1] = 0.00;
	}

}

//Function: Create db4 decompose filter parameters
void CreateDB4_Decompose_low(double* filter,int* length)
{
	
}


//Function: extend a series by ext_len from the begin and at end
//			Length of array must match:
//			init_len = length of init_signal
//			length of dest_signal = init_len + ext_len*2
//			fore_ext(length) = back_ext(length) = ext_len
//Parameters: initial signal array, extended signal array, extend length by half
//			array at the end is additional array to extend
//Note:		ext_len = length of filter -1
void WExtend(double* init_signal,
			 int init_len,
			 double* dest_signal,
			 int ext_len,
			 double* fore_ext,  //ext_len = len_filter-1
			 double* back_ext)  //ext_len = len_filter-1
{
	unsigned char i=0;

	if (init_signal==NULL || dest_signal==NULL)
	{
		return;
	}

	if (fore_ext == NULL || back_ext == NULL)
	{
		//if extend array is null, extent by zero or other methods
		//you can refer to matlab: wextend function for details
		//1. extend by 0
		for (i=0;i<ext_len;i++)
		{
			dest_signal[i] = 0;
		}
		for (i=ext_len;i<ext_len+init_len;i++)
		{
			dest_signal[i] = init_signal[i-ext_len];
		}
		for (i=ext_len+init_len;i<ext_len+init_len+ext_len;i++)
		{
			dest_signal[i] = 0;
		}
	}
	else
	{
		for (i=0;i<ext_len;i++)
		{
			dest_signal[i] = fore_ext[i];
		}
		for (i=ext_len;i<ext_len+init_len;i++)
		{
			dest_signal[i] = init_signal[i-ext_len];
		}
		for (i=ext_len+init_len;i<ext_len+init_len+ext_len;i++)
		{
			dest_signal[i] = back_ext[i-ext_len+init_len];
		}
	}

}


//Function: basic convolution function
//Parameters: signal array, signal length, filter array, filter length, return convolve result array (malloc memory here)
//			  Length of result is : lenSignal+lenFilter-1
//			  Length of fore_ext and back_ext is lenFilter-1
void WConvolve(double* signal, 
			   int lenSignal, 
			   const double* filter, 
			   int lenFilter,
			   double* result,
			   double* fore_ext,	//extend array in the front
			   double* back_ext)	//extend array in the end
{
	FILE* fp;
	unsigned char i=0;
	unsigned char j=0;
	//if (result != NULL)
	//{
	//	free(result);
	//}
	//result =(double*) malloc((lenSignal+lenFilter-1)*sizeof(double));

	//1. extend array first
	int nLenExt = lenFilter;
	//length of temp array = sig_len + low_len + hig_len - 2
	int ext_len = lenSignal+nLenExt+nLenExt-2; //extended array length
	//double* ext_signal = (double*) malloc(ext_len*sizeof(double));
	double ext_signal[100] = {0};
	WExtend(signal,lenSignal,ext_signal,nLenExt,fore_ext,back_ext);

	//2. convolve
	//3. present valid component only (exclude extended component)
	//for (i= 0; i < lenFilter; i++)
	//{
	//	result[i]=0;
	//	for (j = 0; j <= i; j++)
	//		result[i] += ext_signal[j] * filter[i - j];
	//}
	for (i = lenFilter; i <= ext_len; i++)
	{
		result[i-lenFilter]=0;
		for (j = 0; j <lenFilter; j++)
		{
			result[i-lenFilter] += ext_signal[i - j] * filter[j];
		}
	}
	//for (i = ext_len; i < ext_len + lenFilter - 1; i++)
	//{
	//	for (j = i - ext_len + 1; j < lenFilter; j++)
	//		result[i] += ext_signal[i - j] * filter[j];
	//}
	//test code wite
	//print for test
	if ((fp = fopen("wconvolve_testxx", "w")) == NULL) {
		perror("Error opening input file");
		exit(-1);
	}
	for (i=0;i<100;i++)
	{
		fprintf(fp,"%6f",result[i]);
		fprintf(fp,",");
	}
}



//Function: discrete wavelet transform
//Parameters: signal, low pass decompose filter, high pass decompose
//			 low_len and high_len must match
//			 Length of coeff app and det is half of convolved length (sig_len+ext_len-1)/2
void DWT(double* signal,
		 int sig_len, 
		 const double* Lo_D,
		 int low_len, 
		 const double* Hi_D,
		 int hig_len,
		 WaveCoeff* coeff,
		 double* fore_ext,	//extend array in the front
		 double* back_ext)	//extend array in the end
{   
	unsigned char i = 0;
	double z[100]={0};
	int len_result = sig_len+low_len-1;
	FILE* fp;

	//convolve low pass filter
	WConvolve(signal,sig_len,Lo_D,low_len,z,fore_ext,back_ext);
	//down sample here
	for (i=1; i < len_result; i+=2)
	{
		coeff->app[(i-1)/2] = z[i];
	}

	//convolve high pass filter
	WConvolve(signal,sig_len,Hi_D,hig_len,z,fore_ext,back_ext);
	//down sample here
	for (i = 1; i < len_result; i+=2)
	{
		coeff->det[(i-1)/2] = z[i];
	}

	//test code wite
	//print for test
	if ((fp = fopen("wconvolve_test", "w")) == NULL) {
		perror("Error opening input file");
		exit(-1);
	}
	for (i=0;i<100;i++)
	{
		fprintf(fp,"%6f",z[i]);
		fprintf(fp,",");
	}
	fclose(fp);
}



//Function: Main funciton for wavelet decompose
//Parameters: de_level -> decompose level
void WaveDecompose(double* signal,
				   int sig_len, 
				   const double* Lo_D,
				   int low_len, 
				   const double* Hi_D,
				   int hig_len,
				   WaveCoeff* para_comtainer,
				   int de_level)
{
	unsigned char i=0;

	//calculate validation of 
	if (de_level<1)
	{
		return;
	}
	//for (i=0;i<de_level;i++)
	//{
	//	if (len_temp<2)
	//	{
	//		//error: level exceeded

	//		printf("error: exceeded  %d level",i);
	//		return;
	//	}
	//	len_temp = (len_temp+hig_len-1)/2;
	//}

	//decompose the first level
	DWT(signal,sig_len,Lo_D,low_len,Hi_D,hig_len,&para_comtainer[0],NULL,NULL);
	//decompose other levels
	for (i=1;i<de_level;i++)
	{
		DWT(para_comtainer[i-1].app,sig_len,Lo_D,low_len,Hi_D,hig_len,&para_comtainer[i],NULL,NULL);
		sig_len = (sig_len+hig_len-1)/2;
	}

}

//Function: discrete wavelet reverse transform
//Parameters: signal, low pass decompose filter, high pass decompose
//			 low_len and high_len must match
//			 Length of coeff app and det is half
void IDWT(double* signal,int sig_len, 
		  const double* Lo_R,
		  int low_len, 
		  const double* Hi_R,
		  int hig_len,
		  WaveCoeff* coeff,
		  double* result)
{
	unsigned char i=0;

	//1. insert null point first



}


//Function: discrete wavelet reverse transform
//Parameters: signal, low pass decompose filter, high pass decompose
//			 low_len and high_len must match
//			 Length of coeff app and det is half
void WaveReconstruct(double* signal,int sig_len, const double* Lo_R,int low_len, const double* Hi_R,int hig_len ,WaveCoeff* coeff,int level)
{

}
