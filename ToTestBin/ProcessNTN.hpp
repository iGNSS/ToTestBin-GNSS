#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "TxtGnssData.hpp"
#include "NovatelDmiData.hpp"
#include "TestBin.hpp"

using	namespace  std;

/*
* IMU GNSS DMI����LOG��ȡ����
*/
class ProcessNTN
{
public:
	friend class NovatelImuData;
	friend class TxtGnssData;
	friend class NovatelDmiData;
	friend class TestBin;

	NovatelImuData				imuN;			//NovatelЭ��IMU����
	TxtGnssData					gnssT;			//txt�ļ�GNSS����
	NovatelDmiData				dmiN;			//txt�ļ�DMI����
	TestBinData					testBin;

	int							imuEnable;
	int							gnssEnable;
	int							dmiEnable;
	int							outEnable;

	ProcessNTN();
	ProcessNTN(string imuNovatelFile, int imuEn,
				string gnssTxtFile, int gnssEn,
				string dmiNovatelFile, int dmiEn,
				string testBinFile, int outEn);
	~ProcessNTN();
	int Process();

private:

};