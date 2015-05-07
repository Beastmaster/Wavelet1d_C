//////////////////////////////////////////////////////////////////////////
// Wavelet.h С���ֽ����ع���C/C++����ʵ��
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

	// С���˲���Low��ͨ��High��ͨ
	struct WaveFilter
	{
		vector<double> Low;
		vector<double> High;
	};

	// С���ֽ��ع���Ϣ��app���ƣ�detϸ��
	struct WaveCoeff
	{
		vector<double> app;
		vector<double> det;
	};

	// sym4С���˲���
	const double sym4_Lo_D[] = {-0.0758, -0.0296, 0.4976, 0.8037, 0.2979, -0.0992, -0.0126, 0.0322};
	const double sym4_Hi_D[] = {-0.0322, -0.0126, 0.0992, 0.2979, -0.8037, 0.4976, 0.0296, -0.0758};
	const double sym4_Lo_R[] = {0.0322, -0.0126, -0.0992, 0.2979, 0.8037, 0.4976, -0.0296, -0.0758};
	const double sym4_Hi_R[] = {-0.0758, 0.0296, 0.4976, -0.8037, 0.2979, 0.0992, -0.0126, -0.0322};
	const static WaveFilter sym4_d = {vector<double>(sym4_Lo_D, sym4_Lo_D + 8), vector<double>(sym4_Hi_D, sym4_Hi_D + 8)};
	const static WaveFilter sym4_r = {vector<double>(sym4_Lo_R, sym4_Lo_R + 8), vector<double>(sym4_Hi_R, sym4_Hi_R + 8)};

	// db4С���˲���
	const double db4_Lo_D[] = {-0.010597, 0.032883, 0.030841, -0.187035, -0.027984, 0.630881, 0.714847 ,0.230378};
	const double db4_Hi_D[] = {-0.230378, 0.714847, -0.630881, -0.027984, 0.187035, 0.030841, -0.032883, -0.010597};
	const double db4_Lo_R[] = {0.230378, 0.714847, 0.630881, -0.027984, -0.187035, 0.030841, 0.032883, -0.010597};
	const double db4_Hi_R[] = {-0.010597, -0.032883, 0.030841, 0.187035, -0.027984, -0.630881, 0.714847 ,-0.230378};
	const static WaveFilter db4_d = {vector<double>(db4_Lo_D, db4_Lo_D + 8), vector<double>(db4_Hi_D, db4_Hi_D + 8)};
	const static WaveFilter db4_r = {vector<double>(db4_Lo_R, db4_Lo_R + 8), vector<double>(db4_Hi_R, db4_Hi_R + 8)};

	const WaveFilter& WFilters(
		const char* strWaveName, // С����
		const char d_or_r // �ֽ���ع�
		);

	// С����ֽ�
	C_L WaveDec(
		const vector<double>& signal, // �����ź�
		const int nMaxLevel, // �ֽ⼶��
		const char* strWaveName // ʹ��С��������
		);

	// ��ɢС���仯
	WaveCoeff DWT(
		const vector<double>& signal, // �����ź�
		const vector<double>& Lo_D, // �ֽ��ͨ�˲���
		const vector<double>& Hi_D // �ֽ��ͨ�˲���
		);

	// ͨ��һάС��ϵ���ع�����֧�ź�
	vector<double> WRCoef(
		const char a_or_d, // �ع�ϸ�ڻ�����ź�
		const vector<double>& C, // �зֽ�õ���С��ϸ�ںͽ���ϵ��
		const vector<int>& L, // ����ϵ���ĳ���
		const char* strWaveName, // �ع�С��������
		const int nLevel // �ع�����
		);

	// һά����ϵ��
	vector<double> AppCoef(
		const vector<double>& C, // �зֽ�õ���С��ϸ�ںͽ���ϵ��
		const vector<int>& L, // ����ϵ���ĳ���
		const char* strWaveName, // �ع�С��������
		const int nLevel // �ع�����
		);

	// һάϸ��ϵ��
	vector<double> DetCoef(
		const vector<double>& C, // �зֽ�õ���С��ϸ�ںͽ���ϵ��
		const vector<int>& L, // ����ϵ���ĳ���
		const int nLevel // �ع�����
		);

	// �ϲ�����2��ֵ�����
	vector<double> UpsConv1(
		const vector<double>& signal,
		const vector<double>& filter,
		const int nLen,
		const char* strMode = "sym"
		);

	// ���
	vector<double> Conv(
		const vector<double>& vecSignal, // �ź�
		const vector<double>& vecFilter // �˲���
		);

	// ��һάС���任
	vector<double> IDWT(
		const vector<double>& app, // ����ϵ��
		const vector<double>& det, // ϸ��ϵ��
		const vector<double>& Lo_R, // �ع���ͨ�˲���
		const vector<double>& Hi_R, // �ع���ͨ�˲���
		const int nLenCentral
		);

	// ��չ����
	vector<double> WExtend(
		const vector<double>& signal, // �ź�
		const int nLenExt,
		const char* mode = "sym"
		);
	// ���
	vector<double> WConv1(
		const vector<double>& signal,
		const vector<double>& filter,
		const char* shape = "valid"
		);
}
#endif