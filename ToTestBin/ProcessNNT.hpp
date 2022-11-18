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
	
	ProcessNNT();
	ProcessNNT(string imuNovatelFile, string gnssNovatelFile, string dmiTxtFile, string testBinFile);
	~ProcessNNT();
	int Process();

private:

};

