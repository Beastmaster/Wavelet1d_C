//////////////////////////////////////////////////////////////////////////
// Wavelet.h 小波分解与重构的C/C++语言实现
//
// #ifndef _WAVELET_H_H_
// #define _WAVELET_H_H_
// 
// #endif

/************************************************************************/
/* wavelet.h
* Author: Collin
* Date: 2008/12/01
*/
/************************************************************************/
#ifndef WAVELET_H_H_
#define WAVELET_H_H_
#include <vector>

namespace Wavelet
{
	using std::vector;
	struct C_L
	{
		vector<double> C;
		vector<int> L;
	};

	// 小波滤波器Low低通，High高通
	struct WaveFilter
	{
		vector<double> Low;
		vector<double> High;
	};

	// 小波分解重构信息，app近似，det细节
	struct WaveCoeff
	{
		vector<double> app;
		vector<double> det;
	};

	// sym4小波滤波器
	const double sym4_Lo_D[] = {-0.0758, -0.0296, 0.4976, 0.8037, 0.2979, -0.0992, -0.0126, 0.0322};
	const double sym4_Hi_D[] = {-0.0322, -0.0126, 0.0992, 0.2979, -0.8037, 0.4976, 0.0296, -0.0758};
	const double sym4_Lo_R[] = {0.0322, -0.0126, -0.0992, 0.2979, 0.8037, 0.4976, -0.0296, -0.0758};
	const double sym4_Hi_R[] = {-0.0758, 0.0296, 0.4976, -0.8037, 0.2979, 0.0992, -0.0126, -0.0322};
	const static WaveFilter sym4_d = {vector<double>(sym4_Lo_D, sym4_Lo_D + 8), vector<double>(sym4_Hi_D, sym4_Hi_D + 8)};
	const static WaveFilter sym4_r = {vector<double>(sym4_Lo_R, sym4_Lo_R + 8), vector<double>(sym4_Hi_R, sym4_Hi_R + 8)};

	// db4小波滤波器
	const double db4_Lo_D[] = {-0.010597, 0.032883, 0.030841, -0.187035, -0.027984, 0.630881, 0.714847 ,0.230378};
	const double db4_Hi_D[] = {-0.230378, 0.714847, -0.630881, -0.027984, 0.187035, 0.030841, -0.032883, -0.010597};
	const double db4_Lo_R[] = {0.230378, 0.714847, 0.630881, -0.027984, -0.187035, 0.030841, 0.032883, -0.010597};
	const double db4_Hi_R[] = {-0.010597, -0.032883, 0.030841, 0.187035, -0.027984, -0.630881, 0.714847 ,-0.230378};
	const static WaveFilter db4_d = {vector<double>(db4_Lo_D, db4_Lo_D + 8), vector<double>(db4_Hi_D, db4_Hi_D + 8)};
	const static WaveFilter db4_r = {vector<double>(db4_Lo_R, db4_Lo_R + 8), vector<double>(db4_Hi_R, db4_Hi_R + 8)};

	const WaveFilter& WFilters(
		const char* strWaveName, // 小波名
		const char d_or_r // 分解或重构
		);

	// 小波多分解
	C_L WaveDec(
		const vector<double>& signal, // 载入信号
		const int nMaxLevel, // 分解级数
		const char* strWaveName // 使用小波类型名
		);

	// 离散小波变化
	WaveCoeff DWT(
		const vector<double>& signal, // 载入信号
		const vector<double>& Lo_D, // 分解低通滤波器
		const vector<double>& Hi_D // 分解高通滤波器
		);

	// 通过一维小波系数重构单分支信号
	vector<double> WRCoef(
		const char a_or_d, // 重构细节或近似信号
		const vector<double>& C, // 有分解得到的小波细节和近似系数
		const vector<int>& L, // 各层系数的长度
		const char* strWaveName, // 重构小波类型名
		const int nLevel // 重构级数
		);

	// 一维近似系数
	vector<double> AppCoef(
		const vector<double>& C, // 有分解得到的小波细节和近似系数
		const vector<int>& L, // 各层系数的长度
		const char* strWaveName, // 重构小波类型名
		const int nLevel // 重构级数
		);

	// 一维细节系数
	vector<double> DetCoef(
		const vector<double>& C, // 有分解得到的小波细节和近似系数
		const vector<int>& L, // 各层系数的长度
		const int nLevel // 重构级数
		);

	// 上采样（2插值）卷积
	vector<double> UpsConv1(
		const vector<double>& signal,
		const vector<double>& filter,
		const int nLen,
		const char* strMode = "sym"
		);

	// 卷积
	vector<double> Conv(
		const vector<double>& vecSignal, // 信号
		const vector<double>& vecFilter // 滤波器
		);

	// 逆一维小波变换
	vector<double> IDWT(
		const vector<double>& app, // 近似系数
		const vector<double>& det, // 细节系数
		const vector<double>& Lo_R, // 重构低通滤波器
		const vector<double>& Hi_R, // 重构高通滤波器
		const int nLenCentral
		);

	// 扩展向量
	vector<double> WExtend(
		const vector<double>& signal, // 信号
		const int nLenExt,
		const char* mode = "sym"
		);
	// 卷积
	vector<double> WConv1(
		const vector<double>& signal,
		const vector<double>& filter,
		const char* shape = "valid"
		);
}
#endif