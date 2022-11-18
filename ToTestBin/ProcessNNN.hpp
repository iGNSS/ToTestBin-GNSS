#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "NovatelGnssData.hpp"
#include "NovatelDmiData.hpp"
#include "TestBin.hpp"

using	namespace  std;

/*
* IMU GNSS DMI都从LOG读取数据
*/
class ProcessNNN
{
public:
	friend class NovatelImuData;
	friend class NovatelGnssData;
	friend class NovatelDmiData;
	friend class TestBin;

	NovatelImuData				imuN;			//Novatel协议IMU数据
	NovatelGnssData				gnssN;			//Novatel协议GNSS数据
	NovatelDmiData				dmiN;			//txt文件DMI数据
	TestBinData					testBin;

	ProcessNNN();
	ProcessNNN(string imuNovatelFile, string gnssNovatelFile, string dmiNovatelFile, string testBinFile);
	~ProcessNNN();
	int Process();

private:

};