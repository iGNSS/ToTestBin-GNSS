#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "NovatelGnssData.hpp"
#include "TxtDmiData.hpp"
#include "TestBin.hpp"

using	namespace  std;

/*
* IMU GNSS����LOG��ȡ����
* DMR��txt��ȡ����
*/
class ProcessNNT
{
public:
	friend class NovatelImuData;
	friend class NovatelGnssData;
	friend class TxtDmiData;
	friend class TestBin;

	NovatelImuData				imuN;			//NovatelЭ��IMU����
	NovatelGnssData				gnssN;			//NovatelЭ��GNSS����
	TxtDmiData					dmiT;			//txt�ļ�DMI����
	TestBinData					testBin;

	int							imuEnable;
	int							gnssEnable;
	int							dmiEnable;
	int							outEnable;

	ProcessNNT();
	ProcessNNT(string imuNovatelFile,int imuEn,
				string gnssNovatelFile, int gnssEn,
				string dmiTxtFile,  int dmiEn,
				string testBinFile, int outEn);
	~ProcessNNT();
	int Process();

private:

};

