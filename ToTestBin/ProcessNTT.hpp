#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "TxtGnssData.hpp"
#include "TxtDmiData.hpp"
#include "TestBin.hpp"

using	namespace  std;


/*
* IMU����LOG��ȡ����
* GNSS DMR��txt��ȡ����
*/
class ProcessNTT
{
public:
	friend class NovatelImuData;
	friend class TxtGnssData;
	friend class TxtDmiData;
	friend class TestBin;

	NovatelImuData				imuN;			//NovatelЭ��IMU����
	TxtGnssData					gnssT;			//txt�ļ�GNSS����
	TxtDmiData					dmiT;			//txt�ļ�DMI����
	TestBinData					testBin;

	int							imuEnable;
	int							gnssEnable;
	int							dmiEnable;
	int							outEnable;

	ProcessNTT();
	ProcessNTT( string imuNovatelFile,int imuEn,
				string gnssTxtFile, int gnssEn,
				string dmiTxtFile,  int dmiEn,
				string testBinFile, int outEn);
	~ProcessNTT();
	int Process();

private:

};

