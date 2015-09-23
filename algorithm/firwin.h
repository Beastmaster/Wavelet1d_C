/*
By    qinshuo.
Site  SIAT. Shenzhen.
Date  2015.3.15

Description:
	FIR filter function
	window function..
*/





#ifndef _FIR_WIN_H_
#define _FIR_WIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif


void firwin(int n, 
			int band, 
			double fln,
			double fhn,
			int wn,
			double* h);

static double window(int type,
					 int n,
					 int i,
					 double beta);

static double kaiser(int i,
					 int n,
					 double beta);

static double bessel(double x);


#ifdef __cplusplus
}
#endif

#endif


