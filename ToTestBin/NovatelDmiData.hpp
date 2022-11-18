#pragma once

#include "iostream"
#include "fstream"

using	namespace  std;

struct BagRawDMIA
{
	bool	update;

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

	double					time;
	long					dmi1;
	long					dmi2;
	long					dmi3;
	long					dmi4;
	long					status;
};


class NovatelDmiData
{
public:
	string				file;
	bool				update;

	unsigned char			sync[3];					//1-3
	unsigned char			HeaderLength;				//4
	unsigned short			MessageID;					//5

	BagRawDMIA				dmia;
	bool					dmiaHaved;

	NovatelDmiData();
	~NovatelDmiData();
	int OpenFile();
	int CloseFile();
	int Check();
	int GetData();
	int GetRAWDMIA();

private:
	FILE				*fs;
	bool				opened;
};
