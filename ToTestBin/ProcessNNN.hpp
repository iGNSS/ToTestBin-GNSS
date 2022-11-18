#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "NovatelGnssData.hpp"
#include "NovatelDmiData.hpp"
#include "TestBin.hpp"

using	namespace  std;

/*
* IMU GNSS DMI����LOG��ȡ����
*/
class ProcessNNN
{
public:
	friend class NovatelImuData;
	friend class NovatelGnssData;
	friend class NovatelDmiData;
	friend class TestBin;

	NovatelImuData				imuN;			//NovatelЭ��IMU����
	NovatelGnssData				gnssN;			//NovatelЭ��GNSS����
	NovatelDmiData				dmiN;			//txt�ļ�DMI����
	TestBinData					testBin;

	int							imuEnable;
	int							gnssEnable;
	int							dmiEnable;
	int							outEnable;

	ProcessNNN();
	ProcessNNN(string imuNovatelFile,int imuEn,
				string gnssNovatelFile, int gnssEn,
				string dmiNovatelFile,  int dmiEn,
				string testBinFile, int outEn);
	~ProcessNNN();
	int Process();

private:

};