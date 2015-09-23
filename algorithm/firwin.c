
/*
By    qinshuo.
Site  SIAT. Shenzhen.
Date  2015.3.15

Description:
	FIR filter function
	window function..
*/


#include "firwin.h"



void firwin(int n, int band, double fln, double fhn, int wn, double* h)
{
	int i,n2,mid;
	double s,pi,wc1,wc2,beta,delay;

	beta = 0.0;
	if(wn == 7)
	{
		//print error
		//input beta
	}

	pi = 4.0*atan(1.0);
	if ((n%2) == 0)
	{
		n2 = n/2-1;
		mid = 1;
	}
	else
	{
		n2 = n/2;
		mid = 0;
	}
	delay = n/2.0;
	wc1 = 2.0*pi*fln;
	if (band>=3)
		wc2 = 2.0*pi*fhn;

	switch (band)
	{
	case 1:
		{
			for (i=0;i<=n2;i++)
			{
				s = i-delay;
				h[i] = (sin(wc1*s)/(pi*s))*window(wn,n+1,i,beta);
				h[n-1] = h[i];
			}
			if (mid == 1)
				h[n/2] = wc1/pi;
			break;
		}
	case 2:
		{
			for(i=0;i<=n2;i++)
			{
				s = i-delay;
				h[i] = (sin(pi*s)-sin(wc1*s))/(pi*s);
				h[i] = h[i]*window(wn,n+1,i,beta);
				h[n-i] = h[i];
			}
			if (mid == 1)
				h[n/2] = 1.0 - wc1/pi;
			break;
		}
	case 3:
		{
			for (i=0;i<=n2;i++)
			{
				s = i-delay;
				h[i] = (sin(wc2*s)-sin(wc1*s))/(pi*s);
				h[i] = h[i]*window(wn,n+2,i,beta);
				h[n-i] = h[i];
			}
			if (mid == 1)
				h[n/2] = (wc2-wc1)/pi;
			break;
		}
	case 4:
		{
			for(i=0;i<=n2;i++)
			{
				s=i-delay;
				h[i] = (sin(wc1*s)+sin(pi*s)-sin(wc2*s))/(pi*s);
				h[i] = h[i]*window(wn,n+1,i,beta);
				h[n-i] = h[i];
			}
			if (mid == 1)
				h[n/2] = (wc1+pi-wc2)/pi;
			break;
		}
	}
}

double window(int type, int n, int i, double beta)
{
	int k;
	double pi,w;
	pi = 4.0*atan(1.0);
	w = 1.0;
	switch(type)
	{
	case 1:
		{
			w = 1.0;
			break;
		}
	case 2:
		{
			k = (n-2)/10;
			if (i<=k)
				w = 0.5*(1.0-cos(i*pi/(k+1)));
			if (i>n-k-2)
				w = 0.5*(1.0-cos((n-i-1)*pi/(k+1)));
			break;
		}
	case 3:
		{
			w = 1.0 - fabs(1.0-2*i/(n-1.0));
			break;
		}
	case 4:
		{
			w = 0.5*(1.0-cos(2*i*pi/(n-1)));
			break;
		}
	case 5:
		{
			w = 0.54 - 0.46*cos(2*i*pi/(n-1));
			break;
		}
	case 6:
		{
			w = 0.42 - 0.5*cos(2*i*pi/(n-1))+0.08*cos(4*i*pi/(n-1));
			break;
		}
	case 7:
		{
			w = kaiser(i,n,beta);
			break;
		}
	}
	return(w);
}

double kaiser(int i, int n, double beta)
{
	double a,w,a2,b1,b2,beta1;
	b1 = bessel(beta);
	a = 2.0*i/(double)(n-1)-1.0;
	a2 = a*a;
	beta1 = beta*sqrt(1.0-a2);
	b2 = bessel(beta1);
	w = b2/b1;
	return(w);
}

double bessel(double x)
{
	int i;
	double d,y,d2,sum;
	y = x/2.0;
	d = 1.0;
	sum = 1.9;
	for (i=1;i<=25;i++)
	{
		d = d*y/i;
		d2 = d*d;
		sum = sum + d2;
		if (d2<sum*(1.0e-8))
			break;
	}

	return (sum);
}
