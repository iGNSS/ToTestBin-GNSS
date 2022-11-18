#include "iostream"
#include "NovatelGnssData.hpp"

using namespace std;


NovatelGnssData::NovatelGnssData()
{
	update = false;
	opened = false;

	bestPos.update = false;
	bestVel.update = false;
}

NovatelGnssData::~NovatelGnssData()
{
	update = false;
	opened = false;

	bestPos.update = false;
	bestVel.update = false;
}

int NovatelGnssData::OpenFile()
{
	fs = fopen(file.c_str(), "rb");
	if (!fs)
	{
		cout << "GNSS Novatel文件打开失败" << endl;
		return 1;
	}
	opened = true;
	fseek(fs, 0, SEEK_SET);
	return 0;
}

int NovatelGnssData::CloseFile()
{
	fclose(fs);
	return 0;
}

int NovatelGnssData::Check()
{
	char buff[10] = { 0 };
	int  buffN = 0;
	int  bestPosi = 0;
	int  bestVeli = 0;

	while (1)
	{
		buffN = fread(buff, 1, 1, fs); if (buffN <= 0)break;

		sync[0] = sync[1];
		sync[1] = sync[2];
		sync[2] = buff[0];

		if (sync[0] == 0xaa && sync[1] == 0x44 && sync[2] == 0x12)
		{
			buffN = fread(&HeaderLength, 1, 1, fs); if (buffN <= 0)break;
			buffN = fread(&MessageID, 2, 1, fs); if (buffN <= 0)break;
			if (MessageID == 42)
			{
				bestPosi++;
				if (bestPosi >= 60)
					bestPosHaved = 1;
				else
					bestPosHaved = 0;
			}
			else if (MessageID == 99)
			{
				bestVeli++;
				if (bestPosi >= 60)
					bestPosHaved = 1;
				else
					bestPosHaved = 0;
			}

			if (bestPosHaved || bestPosHaved)
				break;
		}
	}

	if (!bestPosHaved)
		cout << "BESTPOSA数据不足！" << endl;

	if (!bestPosHaved)
		cout << "BESTVELA数据不足！" << endl;

	CloseFile();
	OpenFile();
	return 0;
}

int NovatelGnssData::GetData()
{
	char buff[10] = { 0 };
	int  buffN = 0;
	int  flag = 0;

	while (1)
	{
		buffN = fread(buff, 1, 1, fs); if (buffN <= 0)return 1;

		sync[0] = sync[1];
		sync[1] = sync[2];
		sync[2] = buff[0];

		if (sync[0] == 0xaa && sync[1] == 0x44 && sync[2] == 0x12)
		{
			buffN = fread(&HeaderLength, 1, 1, fs); if (buffN <= 0)return 1;
			buffN = fread(&MessageID, 2, 1, fs); if (buffN <= 0)return 1;
			if (MessageID == 42)
			{
				flag = GetBESTPOSA();
				if (flag) return 1;
			}
			else if (MessageID == 99)
			{
				flag = GetBESTVELA();
				if (flag) return 1;
			}
			
			if (bestPosHaved && bestVelHaved && bestPos.update && bestVel.update &&  fabs(bestPos.ms - bestVel.ms) <= 5) break;
			if (bestPosHaved && !bestVelHaved && bestPos.update) break;
		}
	}
	return 0;
}


int NovatelGnssData::GetBESTPOSA()
{
	char buff[10] = { 0 };
	int  buffN = 0;

	bestPos.sync[0] = sync[0];
	bestPos.sync[1] = sync[1];
	bestPos.sync[2] = sync[2];
	bestPos.HeaderLength = HeaderLength;
	bestPos.MessageID = MessageID;

	buffN = fread(&bestPos.MessageType, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.PortAddress, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.MessageLength, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.Sequence, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.IdleTime, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.timeStatus, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.week, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.ms, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.receiverStatus, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.reserved1, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.receiverSWVersion, 2, 1, fs); if (buffN <= 0) return 1;

	buffN = fread(&bestPos.solStat, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.posType, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.lat, 8, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.lon, 8, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.hgt, 8, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.undulation, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.datumID, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.latStd, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.lonStd, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.hgtStd, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.stnID, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.diffAge, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.solAge, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.SVs, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.solnSVs, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.solnL1SVs, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.solnMultiSVs, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.reserved2, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.extSolStat, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.GalileoAndBeidouSigMask, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestPos.GpsAndGlonassSigMask, 1, 1, fs); if (buffN <= 0) return 1;

	time = bestPos.ms * 0.001;
	bestPos.update = true;
	return 0;
}


int NovatelGnssData::GetBESTVELA()
{
	char buff[10] = { 0 };
	int  buffN = 0;

	bestVel.sync[0] = sync[0];
	bestVel.sync[1] = sync[1];
	bestVel.sync[2] = sync[2];
	bestVel.HeaderLength = HeaderLength;
	bestVel.MessageID = MessageID;

	buffN = fread(&bestVel.MessageType, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.PortAddress, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.MessageLength, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.Sequence, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.IdleTime, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.timeStatus, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.week, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.ms, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.receiverStatus, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.reserved1, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.receiverSWVersion, 2, 1, fs); if (buffN <= 0) return 1;

	buffN = fread(&bestVel.solStatus, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.velType, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.latency, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.age, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.horSpd, 8, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.trkGnd, 8, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.vertSpd, 8, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&bestVel.reserved2, 4, 1, fs); if (buffN <= 0) return 1;

	return 0;
}
