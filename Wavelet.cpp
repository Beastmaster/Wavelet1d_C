//////////////////////////////////////////////////////////////////////////
// Wavelet.cpp 小波分解与重构的C/C++语言实现
//

// DB4小波滤波器组
// Lo_D 分解低通滤波器
// Hi_D 分解高通滤波器
// Lo_R 重构低通滤波器
// Hi_R 重构高通滤波器
// 
// Lo_R[0]= 0.2303778133088964;
// Lo_R[1]= 0.7148465705529154;
// Lo_R[2]= 0.6308807679398597;
// Lo_R[3]=-0.0279837694168599;
// Lo_R[4]=-0.1870348117190931;
// Lo_R[5]= 0.0308413818355607;
// Lo_R[6]= 0.0328830116668852;
// Lo_R[7]=-0.0105974017850890;

//#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include "Wavelet.hpp"
using namespace std;
using namespace Wavelet;

// 一维小波多层分解
C_L Wavelet::WaveDec(const vector<double>& signal,  const int nMaxLevel, const char* strWaveName)
{
	const WaveFilter& filters = WFilters(strWaveName, 'd'); // 选择分解滤波器
	int len = signal.size();
	C_L cl;
	cl.L.push_back(len);
	WaveCoeff waveCoeff;
	waveCoeff.app = signal;
	vector<double>::iterator itC;
	vector<int>::iterator itL;

	for (int i = 0; i < nMaxLevel; ++i)
	{
		waveCoeff = DWT(waveCoeff.app, filters.Low, filters.High);
		itC = cl.C.begin();
		cl.C.insert(itC, waveCoeff.det.begin(), waveCoeff.det.end());
		itL = cl.L.begin();
		cl.L.insert(itL, waveCoeff.det.size());
	}
	itC = cl.C.begin();
	cl.C.insert(itC, waveCoeff.app.begin(), waveCoeff.app.end());
	itL = cl.L.begin();
	cl.L.insert(itL, waveCoeff.app.size());
	return cl;
}

// 重构系数
vector<double> Wavelet::WRCoef(const char a_or_d, const vector<double>& C, const vector<int>& L,
							   const char* strWaveName, const int nLevel)
{
	vector<double> Coef;
	const WaveFilter& filter = WFilters(strWaveName, 'r'); // 选择小波重构滤波器
	int nMax = L.size() - 2;
	int nMin;
	char type = tolower(a_or_d);
	if ('a' == type) // a表示重构近似系数
		nMin = 0;
	else if ('d' == type) // d表示重构细节系数
		nMin = 1;
	else 
	{
		cerr << "bad parameter: a_or_d: "<< a_or_d << "\n";
		exit(1);
	}
	if (nLevel < nMin || nLevel > nMax)
	{
		cerr << "bad parameter for level\n";
		exit(1);
	}
	vector<double> F1;
	switch (type)
	{
		case 'a':
			Coef = AppCoef(C, L, strWaveName, nLevel);
			if (0 == nLevel)
				return Coef;
			F1 = filter.Low;
			break;
		case 'd':
			Coef = DetCoef(C, L, nLevel);
			F1 = filter.High;
			break;
		default:
			;
	}
	int iMin = L.size() - nLevel;
	Coef = UpsConv1(Coef, F1, L[iMin], "sym");
	for (int k = 1; k < nLevel; ++k)
	{
		Coef = UpsConv1(Coef, filter.Low, L[iMin + k], "sym");
	}
	return Coef;
}

// 上采样卷积
vector<double> Wavelet::UpsConv1(const vector<double>& signal, const vector<double>& filter,
								 const int nLen,  const char* strMode)
{
	//implement dyadup(y,0)
	vector<double> y(2 * signal.size() - 1);
	y[0] = signal[0];

	// 2 插值
	for (int i = 1; i < signal.size(); ++i)
	{
		y[2*i - 1] = 0;
		y[2*i] = signal[i];
	}
	y = Conv(y, filter);

	//extract the central portion
	vector<double>::iterator it = y.begin();
	return vector<double>(it + (y.size() - nLen) / 2, it + (y.size() + nLen) / 2);
}

// 卷积
vector<double> Wavelet::Conv(const vector<double>& vecSignal, const vector<double>& vecFilter)
{
	vector<double> signal(vecSignal);
	vector<double> filter(vecFilter);
	if (signal.size() < filter.size())
		signal.swap(filter);   
	int lenSignal = signal.size();
	int lenFilter = filter.size();
	vector<double> result(lenSignal + lenFilter - 1);

	for (int i = 0; i < lenFilter; i++)
	{
		for (int j = 0; j <= i; j++)
			result[i] += signal[j] * filter[i - j];
	}
	for (int i = lenFilter; i < lenSignal; i++)
	{
		for (int j = 0; j <lenFilter; j++)
			result[i] += signal[i - j] * filter[j];
	}
	for (int i = lenSignal; i < lenSignal + lenFilter - 1; i++)
	{
		for (int j = i - lenSignal + 1; j < lenFilter; j++)
			result[i] += signal[i - j] * filter[j];
	}
	return result;
}

// 重构细节系数
vector<double> Wavelet::DetCoef(const vector<double>& C, const vector<int>& L, const int nLevel )
{
	if (nLevel < 1 || nLevel > L.size() - 2)
	{
		cerr << "bad level parameter\n";
		exit(1);
	}

	int nlast = 0, nfirst = 0;
	vector<int>::const_reverse_iterator it = L.rbegin();
	++it;
	for (int i = 1; i < nLevel; ++i)
	{
		nlast += *it;
		++it;
	}
	nfirst = nlast + *it;
	return vector<double>(C.end() - nfirst, C.end() - nlast);
}

// 离散小波变换
WaveCoeff Wavelet::DWT(const vector<double>& signal, const vector<double>& Lo_D, const vector<double>& Hi_D)
{
	int nLenExt = Lo_D.size() - 1;
	vector<double> y;
	y = WExtend(signal, nLenExt, "sym");
	vector<double> z;
	z = WConv1(y, Lo_D, "valid");
	WaveCoeff coeff;
	for (int i = 1; i < z.size(); i += 2)
	{
		coeff.app.push_back(z[i]);
	}
	z = WConv1(y, Hi_D, "valid");
	for (int i = 1; i < z.size(); i += 2)
	{
		coeff.det.push_back(z[i]);
	}
	return coeff;
}

// 确定小波类型，返回滤波器
const WaveFilter& Wavelet::WFilters(const char* strWaveName, const char d_or_r)
{
	char type = tolower(d_or_r);
	if (!strcmp(strWaveName, "sym4"))
	{
		switch(type)
		{
		case 'd':
			return Wavelet::sym4_d;
			break;
		case 'r':
			return Wavelet::sym4_r;
			break;
		default:
			cerr << "bad parameter for d_or_r\n";
			exit(1);
		}
	}
	else if (!strcmp(strWaveName, "db4"))
	{
		switch(type)
		{
		case 'd':
			return Wavelet::db4_d;
			break;
		case 'r':
			return Wavelet::db4_r;
			break;
		default:
			cerr << "bad parameter for d_or_r\n";
			exit(1);
		}
	}
	else 
	{
		cerr << "not implement \n";
		exit(1);
	}
}

// 近似系数
vector<double> Wavelet::AppCoef(const vector<double>& C, const vector<int>& L, const char* strWaveName, const int nLevel)
{
	int nMaxLevel = L.size() - 2;
	if (nLevel < 0 || nLevel > nMaxLevel)
	{
		cerr << "bad parameter for level\n";
		exit(1);
	}
	const WaveFilter& filters = WFilters(strWaveName, 'r');
	vector<double> app(C.begin(), C.begin() + L[0]); //app for the last level
	vector<double> det;
	for (int i = 0; i < nMaxLevel - nLevel; ++i)
	{
		det = DetCoef(C, L, nMaxLevel - i);
		app = IDWT(app, det, filters.Low, filters.High, L[i + 2]);
	}
	return app;
}

// 逆小波变换
vector<double> Wavelet::IDWT(const vector<double>& app,
							 const vector<double>& det,
							 const vector<double>& Lo_R,
							 const vector<double>& Hi_R,
							 const int nLenCentral)
{
	vector<double> app1, app2;
	app1 = UpsConv1(app, Lo_R, nLenCentral, "sym");
	app2 = UpsConv1(det, Hi_R, nLenCentral, "sym");
	for (int i = 0; i < nLenCentral; ++i)
	{
		app1[i] += app2[i];
	}
	return app1;
}

// 向量对称扩展
vector<double> Wavelet::WExtend(const vector<double>& signal, const int nLenExt, const char* mode)
{
	int signalLen = signal.size();
	vector<double> result(signalLen + 2 * nLenExt);
	for (int i = 0, idx = nLenExt; idx < signalLen + nLenExt; ++i, ++idx)
	{
		result[idx] = signal[i];
	}
	for (int idx = nLenExt - 1, bFlag = 1, signalIdx = 0; idx >= 0; --idx)
	{
		result[idx] = signal[signalIdx];
		if (bFlag && ++signalIdx == signalLen)
		{
			bFlag = 0;
			signalIdx = signalLen - 1;
		}
		else if (!bFlag && --signalIdx == -1) 
		{
			bFlag = 1;
			signalIdx = 0;
		}
	}
	for (int idx = nLenExt + signalLen, bFlag = 0, signalIdx = signalLen - 1; idx < 2 * nLenExt + signalLen; ++idx)
	{
		result[idx] = signal[signalIdx];
		if (bFlag && ++signalIdx == signalLen)
		{
			bFlag = 0;
			signalIdx = signalLen - 1;
		}
		else if (!bFlag && --signalIdx == -1) 
		{
			bFlag = 1;
			signalIdx = 0;
		}
	}
	return result;
}

// Returns only those parts of the convolution that are computed without the zero-padded edges.
vector<double> Wavelet::WConv1(const vector<double>& signal, const vector<double>& filter, const char* shape)
{
	vector<double> y;
	y = Conv(signal, filter);
	int nLenExt = filter.size() - 1;
	return vector<double>(y.begin() + nLenExt, y.end() - nLenExt);
}
