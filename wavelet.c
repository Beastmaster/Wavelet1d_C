#include "wavelet.h"



//Function: basic convolution function
//Parameters: signal array, signal length, filter array, filter length, return convolve result array (malloc memory here)
//			  Length of result is : lenSignal+lenFilter-1
void WConvolve(double* signal, int lenSignal, const double* filter, int lenFilter,double* result)
{
	int i=0;
	int j=0;
	//if (result != NULL)
	//{
	//	free(result);
	//}
	//result =(double*) malloc((lenSignal+lenFilter-1)*sizeof(double));

	//1. extend array first
	int nLenExt = lenFilter;
	//length of temp array = sig_len + low_len + hig_len - 2
	int ext_len = lenSignal+nLenExt+nLenExt-2; //extended array length
	double* ext_signal = (double*) malloc(ext_len*sizeof(double));
	WExtend(signal,lenSignal,ext_signal,nLenExt,NULL,NULL);

	//2. convolve
	//3. present valid component only (exclude extended component)
	//for (i= 0; i < lenFilter; i++)
	//{
	//	for (j = 0; j <= i; j++)
	//		result[i] += ext_signal[j] * filter[i - j];
	//}
	for (i = lenFilter; i < ext_len; i++)
	{
		for (j = 0; j <lenFilter; j++)
			result[i-lenFilter] += ext_signal[i - j] * filter[j];
	}
	//for (i = ext_len; i < ext_len + lenFilter - 1; i++)
	//{
	//	for (j = i - ext_len + 1; j < lenFilter; j++)
	//		result[i] += ext_signal[i - j] * filter[j];
	//}

}



//Function:
//Parameter: sig_length must be even number
//			Length of result : sig_length/2
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
//Note:		ext_len = length of filter para -1
void WExtend(double* init_signal,int init_len,double* dest_signal,int ext_len,double* fore_ext,double* back_ext)
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

//Function: discrete wavelet transform
//Parameters: signal, low pass decompose filter, high pass decompose
//			 low_len and high_len must match
//			 Length of coeff app and det is half of convolved length (sig_len+ext_len-1)/2
void DWT(double* signal,int sig_len, const double* Lo_D,int low_len, const double* Hi_D,int hig_len ,WaveCoeff* coeff)
{   
	int i = 0;
	double z[100];
	int len_result = sig_len+low_len-1;
	
	//convolve low pass filter
	WConvolve(signal,sig_len,Lo_D,low_len,z);

	for (i=1; i < len_result; i+=2)
	{
		coeff->app[(i-1)/2] = z[i];
	}

	//convolve high pass filter
	WConvolve(signal,sig_len,Hi_D,hig_len,z);

	for (i = 1; i < len_result; i+=2)
	{
		coeff->det[(i-1)/2] = z[i];
	}
}

//Function: discrete wavelet reverse transform
//Parameters: signal, low pass decompose filter, high pass decompose
//			 low_len and high_len must match
//			 Length of coeff app and det is half
void IDWT(double* signal,int sig_len, const double* Lo_R,int low_len, const double* Hi_R,int hig_len ,WaveCoeff* coeff)
{

}


//Function: Main funciton for wavelet decompose
//Parameters: de_level -> decompose level
void WaveDecompose(double* signal,int sig_len, const double* filter,int filter_len,WaveCoeff* para_comtainer,int de_level)
{



}


