/*
By qinshuo
2015.4.28

Note: The length of the signal must less than 80 points
	  Level of decompose is less than 6  
*/


#ifndef _WAVELET_H_
#define _WAVELET_H_

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	const int db4_len = 8;
	const double db4_Lo_D[] = {-0.010597, 0.032883, 0.030841, -0.187035, -0.027984, 0.630881, 0.714847 ,0.230378};
	const double db4_Hi_D[] = {-0.230378, 0.714847, -0.630881, -0.027984, 0.187035, 0.030841, -0.032883, -0.010597};
	const double db4_Lo_R[] = {0.230378, 0.714847, 0.630881, -0.027984, -0.187035, 0.030841, 0.032883, -0.010597};
	const double db4_Hi_R[] = {-0.010597, -0.032883, 0.030841, 0.187035, -0.027984, -0.630881, 0.714847 ,-0.230378};

	const int db6_len = 12;
	const double db6_Lo_D[] = {-0.00107730108499558,0.004777257511010651,0.0005538422009938016,-0.031582039318031156,0.02752286553001629,0.09750160558707936,-0.12976686756709563,-0.22626469396516913,0.3152503517092432,0.7511339080215775,0.4946238903983854,0.11154074335008017};
	const double db6_Hi_D[] = {-0.11154074335008017,0.4946238903983854,-0.7511339080215775,0.3152503517092432,0.22626469396516913,-0.12976686756709563,-0.09750160558707936,0.02752286553001629,0.031582039318031156,0.0005538422009938016,-0.004777257511010651,-0.00107730108499558};
	const double db6_Lo_R[] = {0.11154074335008017,	0.4946238903983854,	0.7511339080215775,	0.3152503517092432,-0.22626469396516913,-0.12976686756709563,0.09750160558707936,0.02752286553001629,-0.031582039318031156,0.0005538422009938016,0.004777257511010651,-0.00107730108499558};
	const double db6_Hi_R[] = {-0.00107730108499558,-0.004777257511010651,0.0005538422009938016,0.031582039318031156,0.02752286553001629,-0.09750160558707936,-0.12976686756709563,0.22626469396516913,0.3152503517092432,-0.7511339080215775,0.4946238903983854,-0.11154074335008017};

	// Compute coefficients of approximation.
	typedef struct 
	{
		int length;
		double capp[100];
		double cdet[100];
	} WaveCoeff;

	typedef struct
	{
		int length;
		double capp[100];
		double cdet[100];
	} WaveRecon;

	//down sample function
	void DownSample(double* signal,int sig_length,double* result);
	//up sample function
	void UpSample(double* signal,int sig_length,double* result);
	//create wavelet filters
	void CreateDB4(double*,int*);

	//extend array in the front and end
	void WExtend(double* init_signal,int init_len,double* dest_signal,int ext_len,double* fore_ext,double* back_ext);
	//basic convolution function
	void WConvolve(double* signal, int lenSignal, const double* filter, int lenFilter,double* result,double* fore_ext,double* back_ext);
	//discrete wavelet transform
	void DWT(double* signal,int sig_len, const double* Lo_D,int low_len, const double* Hi_D,int hig_len ,WaveCoeff* coeff,		 double* fore_ext,double* back_ext);
	//multi level wavelet transform
	void WaveDecompose(double* signal,int sig_len, const double* Lo_D,int low_len, const double* Hi_D,int hig_len,WaveCoeff* para_comtainer,int de_level);
	
	void IWConvolve(double* signal, int lenSignal, const double* filter, int lenFilter, double* result);
	//discrete wavelet inverse transform for one level
	void IDWT(double* signal,int sig_len, const double* filter,int filter_len,double* result,int result_len);
	//re-construct the wave for a specified level
	void WaveReconstruct(double* signal,int sig_len, const double* Lo_R,int low_len, const double* Hi_R,int hig_len ,WaveCoeff* coeff,WaveRecon* recon,const char mode,int level);
	

#ifdef __cplusplus
}
#endif

#endif


