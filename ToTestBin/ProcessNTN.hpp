#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "TxtGnssData.hpp"
#include "NovatelDmiData.hpp"
#include "TestBin.hpp"

using	namespace  std;

/*
* IMU GNSS DMI都从LOG读取数据
*/
class ProcessNTN
{
public:
	friend class NovatelImuData;
	friend class TxtGnssData;
	friend class NovatelDmiData;
	friend class TestBin;

	NovatelImuData				imuN;			//Novatel协议IMU数据
	TxtGnssData					gnssT;			//txt文件GNSS数据
	NovatelDmiData				dmiN;			//txt文件DMI数据
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