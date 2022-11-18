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

	ProcessNTN();
	ProcessNTN(string imuNovatelFile, string gnssTxtFile, string dmiNovatelFile, string testBinFile);
	~ProcessNTN();
	int Process();

private:

};