#pragma once

#include "iostream"
#include "fstream"
#include "stdio.h"

using	namespace  std;

#define PI					3.1415926535897932
#define DEG2RAD 		    0.017453292519943
#define RAD2DEG   			57.295779513082323
#define G0					9.80665

#define	IMU_LIST_N			10

enum ImuType
{
	UNKNOWN = 0,
	HG1700_AG11 = 1,
	HG1700_AG17 = 2,
	STIM300 = 32,
	EPSON_G320 = 41,
	LITEF_MICROIMU = 52,
	EPSON_G370 = 61,
	EPSON_G320_200HZ = 62,
	EPSON_G365 = 101,
};

struct BagRAWIMUS
{
	bool					update;

	unsigned char			sync[3];					//1-3
	unsigned char			HeaderLength;				//4
	unsigned short			MessageID;					//5
	unsigned short			week;						//6
	unsigned long			ms;							//7

	unsigned long			gnssWeek;
	double					gnssSec;
	unsigned long			imuStatus;
	long					zAccel;
	long					_yAccel;
	long					xAccel;
	long					zGyro;
	long					_yGyro;
	long					xGyro;

	unsigned char			crc;
};

struct BagRAWIMUSX
{
	bool					update;

	unsigned char			sync[3];					//1-3
	unsigned char			HeaderLength;				//4
	unsigned short			MessageID;					//5
	unsigned short			week;						//6
	unsigned long			ms;							//7

	unsigned char			imuInfo;
	ImuType					imuType;
	unsigned short			gnssWeek;
	double					gnssSec;
	long					imuStatus;
	long					zAccel;
	long					_yAccel;
	long					xAccel;
	long					zGyro;
	long					_yGyro;
	long					xGyro;

	unsigned char			crc;
};

struct ImuScale
{
	double		gyro;
	double		acc;
};

class NovatelImuData
{
public:
	string					file;
	bool					update;

	ImuType					type;
	ImuScale				scale;

	unsigned char			sync[3];					//1-3
	unsigned char			HeaderLength;				//4
	unsigned short			MessageID;					//5

	BagRAWIMUS				imus;
	BagRAWIMUSX				imusx;

	int						imusHaved;
	int						imusxHaved;
	
	short					week[IMU_LIST_N];
	double					sec[IMU_LIST_N];
	double					gyrox[IMU_LIST_N];
	double					gyroy[IMU_LIST_N];
	double					gyroz[IMU_LIST_N];
	double					accx[IMU_LIST_N];
	double					accy[IMU_LIST_N];
	double					accz[IMU_LIST_N];

	int                     freq;

	NovatelImuData();
	~NovatelImuData();
	int OpenFile();
	int CloseFile();
	int Check();
	int GetData();
	int GetRAWIMUS();
	int GetRAWIMUSX();
	int GetImuScale(ImuType type);

private:
	FILE				*fs;
	bool				opened;
};

