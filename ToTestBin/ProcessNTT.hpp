#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "TxtGnssData.hpp"
#include "TxtDmiData.hpp"
#include "TestBin.hpp"

using	namespace  std;


/*
* IMU都从LOG读取数据
* GNSS DMR从txt读取数据
*/
class ProcessNTT
{
public:
	friend class NovatelImuData;
	friend class TxtGnssData;
	friend class TxtDmiData;
	friend class TestBin;

	NovatelImuData				imuN;			//Novatel协议IMU数据
	TxtGnssData					gnssT;			//txt文件GNSS数据
	TxtDmiData					dmiT;			//txt文件DMI数据
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

