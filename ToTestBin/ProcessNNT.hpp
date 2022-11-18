#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "NovatelGnssData.hpp"
#include "TxtDmiData.hpp"
#include "TestBin.hpp"

using	namespace  std;

/*
* IMU GNSS都从LOG读取数据
* DMR从txt读取数据
*/
class ProcessNNT
{
public:
	friend class NovatelImuData;
	friend class NovatelGnssData;
	friend class TxtDmiData;
	friend class TestBin;

	NovatelImuData				imuN;			//Novatel协议IMU数据
	NovatelGnssData				gnssN;			//Novatel协议GNSS数据
	TxtDmiData					dmiT;			//txt文件DMI数据
	TestBinData					testBin;
	
	ProcessNNT();
	ProcessNNT(string imuNovatelFile, string gnssNovatelFile, string dmiTxtFile, string testBinFile);
	~ProcessNNT();
	int Process();

private:

};

