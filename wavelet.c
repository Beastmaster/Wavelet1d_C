/*
By qinshuo
2015.4.28

Release function in matlab wavelet toolbox
Some thing change in this release
To accomplish high efficiency, I use fixed array as buff
*/

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


//Function: amended convolution function
//Parameters: signal array, signal length, filter array, filter length, return convolve result array (malloc memory here)
//			  Length of result is : lenSignal+lenFilter-1
//			  Length of fore_ext and back_ext is lenFilter-1
//Note: Take the central part of the convolved result
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
	double ext_signal[BUFF_LEN] = {0};
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
	//if ((fp = fopen("wconvolve_testxx", "w")) == NULL) {
	//	perror("Error opening input file");
	//	exit(-1);
	//}
	//for (i=0;i<100;i++)
	//{
	//	fprintf(fp,"%6f",result[i]);
	//	fprintf(fp,",");
	//}
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
	double z[BUFF_LEN]={0};
	int len_result = sig_len+low_len-1;
	FILE* fp;

	//add length of app and det array
	coeff->length = len_result/2+1;
	//convolve low pass filter
	WConvolve(signal,sig_len,Lo_D,low_len,z,fore_ext,back_ext);
	//down sample here
	for (i=0; i < len_result; i+=2)
	{
		coeff->capp[i/2] = z[i];
	}

	//convolve high pass filter
	WConvolve(signal,sig_len,Hi_D,hig_len,z,fore_ext,back_ext);
	//down sample here
	for (i = 0; i < len_result; i+=2)
	{
		coeff->cdet[i/2] = z[i];
	}

	//test code wite
	//print for test
	//if ((fp = fopen("wconvolve_test", "w")) == NULL) {
	//	perror("Error opening input file");
	//	exit(-1);
	//}
	//for (i=0;i<100;i++)
	//{
	//	fprintf(fp,"%6f",z[i]);
	//	fprintf(fp,",");
	//}
	//fclose(fp);
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
	for (i=1;i<=de_level;i++)
	{
		DWT(para_comtainer[i-1].capp,para_comtainer[i-1].length,Lo_D,low_len,Hi_D,hig_len,&para_comtainer[i],NULL,NULL);
	}

}
//Function: basic convolution function
//Parameters: signal array, signal length, filter array, filter length, return convolve result array (malloc memory here)
//			  Length of result is : lenSignal+lenFilter-1
//Note: 
void IWConvolve(double* signal, 
			   int lenSignal, 
			   const double* filter, 
			   int lenFilter,
			   double* result)
{
	unsigned char i,j=0;

	for (i = 0; i < lenFilter; i++)
	{
		for ( j = 0; j <= i; j++)
			result[i] += signal[j] * filter[i - j];
	}
	for ( i = lenFilter; i < lenSignal; i++)
	{
		for ( j = 0; j <lenFilter; j++)
			result[i] += signal[i - j] * filter[j];
	}
	for ( i = lenSignal; i < lenSignal + lenFilter - 1; i++)
	{
		for ( j = i - lenSignal + 1; j < lenFilter; j++)
			result[i] += signal[i - j] * filter[j];
	}
}


//Function: discrete wavelet reverse transform
//Parameters: signal, low pass reconstruct filter, high pass reconstruct filter
//			 low_len and high_len must match
//			 Length of coeff app and det is half
//			 Length of result is 2*sig_len+filter_len+1
//Note:  Up sample controversial, reference insert 0 in even number position
//       While a book says to insert 0 in odd number position
//		 Here we use the first solution
void IDWT(double* signal,
		  int sig_len, 
		  const double* filter,
		  int filter_len, 
		  double* result,
		  int result_len)
{
	unsigned char i=0;
	double ups_signal[BUFF_LEN] = {0};
	double result_temp[BUFF_LEN]= {0};
	//size of output array is 2*signal_size -1
	int ups_signal_len = 2*sig_len - 1;
	//1. insert null point first
	for (i = 1; i < sig_len; ++i)
	{
		ups_signal[2*i - 1] = 0;
		ups_signal[2*i] = signal[i];
	}
	//2.convolve and exclude some points
	IWConvolve(ups_signal,ups_signal_len,filter,filter_len,result_temp);//length of result_temp = 2*sig_len+filter_len-2
	//length of final result = length(result_temp)-(2*filter_len-2)
	for (i=(ups_signal_len+filter_len-1-result_len)/2;i<(ups_signal_len+filter_len-1-result_len)/2+result_len;i++)
	{
		result[i-(ups_signal_len+filter_len-1-result_len)/2] = result_temp[i];
	}
}


//Function: discrete wavelet reverse transform
//Parameters: signal, low pass decompose filter, high pass decompose
//			 low_len and high_len must match
//			 Length of coeff app and det is half
//Note:   You must decompose first
void WaveReconstruct(double* signal,
					 int sig_len, 
					 const double* Lo_R,
					 int low_len, 
					 const double* Hi_R,
					 int hig_len,
					 WaveCoeff* coeff,
					 WaveRecon* recon,
					 const char mode,
					 int level)
{
	double result1[BUFF_LEN] = {0};
	double result2[BUFF_LEN] = {0};
	unsigned char i=level;
	unsigned char j=0;
	int len_result = 0;

	switch (mode)
	{
	case 'a':
		{
			//reconstruct approximate
			for (i=level;i>0;i--)
			{
				//length of result is upper level signal length
				if (i==1)
				{
					len_result =sig_len;
					recon[i-1].length = len_result;
				}
				else
				{
					len_result = coeff[i-2].length;
					recon[i-1].length = len_result;
				}
				//idwt
				if (i%2 == 0)
				{
					if((int)i==level)
						IDWT(coeff[i-1].capp,coeff[i-1].length,Lo_R,low_len,result2,len_result);
					else
						IDWT(result1,coeff[i-1].length,Lo_R,low_len,result2,len_result);
					//put result into recon
					for (j=0;j<len_result;j++)
					{
						recon[i-1].capp[j] = result2[j];
					}
				}
				else
				{
					if((int)i==level)
						IDWT(coeff[i-1].capp,coeff[i-1].length,Lo_R,low_len,result1,len_result);
					else
						IDWT(result2,coeff[i-1].length,Lo_R,low_len,result1,len_result);
					//put result into recon
					for (j=0;j<len_result;j++)
					{
						recon[i-1].capp[j] = result1[j];
					}
				}
			}
			break;
		}
	case 'd':
		{
			//reconstruct details
			for (i=level;i>0;i--)
			{
				//length of result is upper level signal length
				if (i==1)
				{
					len_result =sig_len;
					recon[i-1].length = len_result;
				}
				else
				{
					len_result = coeff[i-2].length;
					recon[i-1].length = len_result;
				}
				//idwt
				if (i%2 == 0)
				{
					if((int)i==level)
						IDWT(coeff[i-1].cdet,coeff[i-1].length,Hi_R,low_len,result2,len_result);
					else
						IDWT(result1,coeff[i-1].length,Hi_R,low_len,result2,len_result);
					//put result into recon
					for (j=0;j<len_result;j++)
					{
						recon[i-1].cdet[j] = result2[j];
					}
				}
				else
				{
					if((int)i==level)
						IDWT(coeff[i-1].cdet,coeff[i-1].length,Hi_R,low_len,result1,len_result);
					else
						IDWT(result2,coeff[i-1].length,Hi_R,low_len,result1,len_result);
					//put result into recon
					for (j=0;j<len_result;j++)
					{
						recon[i-1].cdet[j] = result1[j];
					}
				}
			}
			break;
		}
	default:
		{
			printf("error para\n");
			break;
		}
	}

}





