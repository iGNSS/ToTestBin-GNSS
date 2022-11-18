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

	ProcessNTN();
	ProcessNTN(string imuNovatelFile, string gnssTxtFile, string dmiNovatelFile, string testBinFile);
	~ProcessNTN();
	int Process();

private:

};