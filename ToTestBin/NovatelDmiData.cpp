#include "iostream"
#include "NovatelDmiData.hpp"

using namespace std;

NovatelDmiData::NovatelDmiData()
{
	update = false;
	opened = false;

	dmia.update = false;
}

NovatelDmiData::~NovatelDmiData()
{
	update = false;
	opened = false;

	dmia.update = false;
}

int NovatelDmiData::OpenFile()
{
	fs = fopen(file.c_str(), "rb");
	if (!fs)
	{
		cout << "DMI Novatel文件打开失败" << endl;
		return 1;
	}
	opened = true;
	fseek(fs, 0, SEEK_SET);
	return 0;
}

int NovatelDmiData::CloseFile()
{
	fclose(fs);
	return 0;
}

int NovatelDmiData::Check()
{
	char buff[10] = { 0 };
	int  buffN = 0;
	int  dmiai = 0;

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
			if (MessageID == 2269)
			{
				dmiai++;
				if (dmiai >= 10)
				{
					dmiaHaved = 1;
					break;
				}
				else
					dmiaHaved = 0;
			}

		}
	}
	CloseFile();
	OpenFile();
	return 0;
}

int NovatelDmiData::GetData()
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
			if (MessageID == 2269)
			{
				flag = GetRAWDMIA();
				if (flag) return 1;
			}

			if (dmiaHaved && dmia.update) break;
		}
	}
	return 0;
}

int NovatelDmiData::GetRAWDMIA()
{
	char buff[10] = { 0 };
	int  buffN = 0;

	dmia.sync[0] = sync[0];
	dmia.sync[1] = sync[1];
	dmia.sync[2] = sync[2];
	dmia.HeaderLength = HeaderLength;
	dmia.MessageID = MessageID;

	buffN = fread(&dmia.MessageType, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.PortAddress, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.MessageLength, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.Sequence, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.IdleTime, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.timeStatus, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.week, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.ms, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.receiverStatus, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.reserved1, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.receiverSWVersion, 2, 1, fs); if (buffN <= 0) return 1;

	buffN = fread(&dmia.dmi1, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.dmi2, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.dmi3, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.dmi4, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&dmia.status, 4, 1, fs); if (buffN <= 0) return 1;

	dmia.update = true;

	return 0;
}