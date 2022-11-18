#pragma once

#include "iostream"
#include "fstream"
#include "stdio.h"

using	namespace  std;

/*
*BESTPOSA数据包
*/
struct BagBESTPOSA
{
	bool					update;

	unsigned char			sync[3];					//1-3
	unsigned char			HeaderLength;				//4
	unsigned short			MessageID;					//5
	char					MessageType;				//6
	unsigned char			PortAddress;				//7
	unsigned short			MessageLength;				//8
	unsigned short			Sequence;					//9
	unsigned char			IdleTime;					//10
	int						timeStatus;					//11
	unsigned short			week;						//12
	unsigned long			ms;							//13
	unsigned long			receiverStatus;				//14
	unsigned short			reserved1;					//15
	unsigned short			receiverSWVersion;			//16

	int						solStat;
	int						posType;
	double					lat;
	double					lon;
	double					hgt;
	float					undulation;
	int						datumID;
	float					latStd;
	float					lonStd;
	float					hgtStd;
	char					stnID[4];
	float					diffAge;
	float					solAge;
	unsigned char			SVs;
	unsigned char			solnSVs;
	unsigned char			solnL1SVs;
	unsigned char			solnMultiSVs;
	unsigned char			reserved2;
	char					extSolStat;
	char					GalileoAndBeidouSigMask;
	char					GpsAndGlonassSigMask;
	char					crc[4];
};


/*
*BESTVELA数据包
*/
struct BagBESTVELA
{
	bool					update;

	unsigned char			sync[3];					//1-3
	unsigned char			HeaderLength;				//4
	unsigned short			MessageID;					//5
	char					MessageType;				//6
	unsigned char			PortAddress;				//7
	unsigned short			MessageLength;				//8
	unsigned short			Sequence;					//9
	unsigned char			IdleTime;					//10
	int						timeStatus;					//11
	unsigned short			week;						//12
	unsigned long			ms;							//13
	unsigned long			receiverStatus;				//14
	unsigned short			reserved1;					//15
	unsigned short			receiverSWVersion;			//16

	int						solStatus;
	int						velType;
	float					latency;
	float					age;
	double					horSpd;
	double					trkGnd;
	double					vertSpd;
	float					reserved2;

	unsigned char			crc[4];
};

class NovatelGnssData
{
public:
	string					file;
	bool					update;

	unsigned char			sync[3];					//1-3
	unsigned char			HeaderLength;				//4
	unsigned short			MessageID;					//5

	BagBESTPOSA				bestPos;
	BagBESTVELA				bestVel;
	double					time;

	int						bestPosHaved;
	int						bestVelHaved;
	int						HeadingHaved;

	NovatelGnssData();
	~NovatelGnssData();
	int OpenFile();
	int CloseFile();
	int Check();
	int GetData();
	int GetBESTPOSA();
	int GetBESTVELA();

private:
	FILE				*fs;
	bool				opened;
};