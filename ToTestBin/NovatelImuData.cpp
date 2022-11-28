#include "iostream"
#include "NovatelImuData.hpp"

using namespace std;

NovatelImuData::NovatelImuData()
{
	update = false;
	opened = false;

	imus.update = false;
	imusx.update = false;
}

NovatelImuData::~NovatelImuData()
{
	update = false;
	opened = false;

	imus.update = false;
	imusx.update = false;
}

int NovatelImuData::OpenFile()
{
	fs = fopen(file.c_str(), "rb");
	if (!fs)
	{
		cout << "IMU Novatel数据文件打开失败" << endl;
		return 1;
	}
	opened = true;
	fseek(fs, 0, SEEK_SET);
	return 0;
}

int NovatelImuData::CloseFile()
{
	fclose(fs);
	return 0;
}

int NovatelImuData::Check()
{
	char buff[10] = { 0 };
	int  buffN = 0;
	int  imusi = 0;
	int  imusxi = 0;

	while (1)
	{
		buffN = fread(buff, 1, 1, fs); if (buffN <= 0)break;

		sync[0] = sync[1];
		sync[1] = sync[2];
		sync[2] = buff[0];

		if (sync[0] == 0xaa && sync[1] == 0x44 && sync[2] == 0x13)
		{
			buffN = fread(&HeaderLength, 1, 1, fs); if (buffN <= 0)return 1;
			buffN = fread(&MessageID, 2, 1, fs); if (buffN <= 0)return 1;
			if (MessageID == 325)
			{
				imusi++;
				if (imusi >= 60)
					imusHaved = 1;
				else
					imusHaved = 0;
			}
			else if (MessageID == 1462)
			{
				imusxi++;
				if (imusxi >= 60)
					imusxHaved = 1;
				else
					imusxHaved = 0;
			}

			//if (imusxHaved || imusxHaved)
			//	break;
		}
	}


	if (imusxHaved)
	{
		cout << "IMU使用RAWIMUSXA数据包！" << endl;
		imusHaved = 0;
	}
	else
	{
		if(imusHaved)
			cout << "IMU使用RAWIMUSA数据包！" << endl;
		else
			cout << "IMU数据不足！" << endl;
	}

	CloseFile();
	OpenFile();

	return 0;
}

int NovatelImuData::GetData()
{
	char buff[10] = {0};
	int  buffN = 0;
	int  flag = 0;

	while (1)
	{
		buffN = fread(buff, 1, 1, fs);if (buffN <= 0)return 1;

		sync[0] = sync[1];
		sync[1] = sync[2];
		sync[2] = buff[0];

		if (sync[0] == 0xaa && sync[1] == 0x44 && sync[2] == 0x13)
		{
			buffN = fread(&HeaderLength, 1, 1, fs); if (buffN <= 0)return 1;
			buffN = fread(&MessageID, 2, 1, fs); if (buffN <= 0)return 1;
			if (MessageID == 325)
			{
				flag = GetRAWIMUS();
				if (flag) return 1;
				else break;
			}
			else if (MessageID == 1462)
			{
				flag = GetRAWIMUSX();
				if (flag) return 1;
				else break;
			}
		}
	}
	return 0;
}


int NovatelImuData::GetRAWIMUS()
{
	char buff[10] = { 0 };
	int  buffN = 0;

	imus.sync[0] = sync[0];
	imus.sync[1] = sync[1];
	imus.sync[2] = sync[2];
	imus.HeaderLength = HeaderLength;
	imus.MessageID = MessageID;

	buffN = fread(&imus.week, 2, 1, fs); if (buffN <= 0) return 1;				//6
	buffN = fread(&imus.ms, 4, 1, fs); if (buffN <= 0) return 1;				//7

	buffN = fread(&imus.gnssWeek, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imus.gnssSec, 8, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imus.imuStatus, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imus.zAccel, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imus._yAccel, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imus.xAccel, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imus.zGyro, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imus._yGyro, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imus.xGyro, 4, 1, fs); if (buffN <= 0) return 1;

	imus.update = true;
	return 0;
}

int NovatelImuData::GetRAWIMUSX()
{
	char buff[10] = { 0 };
	int  buffN = 0;

	imusx.sync[0] = sync[0];
	imusx.sync[1] = sync[1];
	imusx.sync[2] = sync[2];
	imusx.HeaderLength = HeaderLength;
	imusx.MessageID = MessageID;

	buffN = fread(&imusx.week, 2, 1, fs); if (buffN <= 0) return 1;				//6
	buffN = fread(&imusx.ms, 4, 1, fs); if (buffN <= 0) return 1;				//7

	buffN = fread(&imusx.imuInfo, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx.imuType, 1, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx.gnssWeek, 2, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx.gnssSec, 8, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx.imuStatus, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx.zAccel, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx._yAccel, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx.xAccel, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx.zGyro, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx._yGyro, 4, 1, fs); if (buffN <= 0) return 1;
	buffN = fread(&imusx.xGyro, 4, 1, fs); if (buffN <= 0) return 1;

	type = imusx.imuType;
	GetImuScale(type);

	freq = 200;
	//scale.gyro = 1.0;
	//scale.acc = 1.0;
	static bool firstflag = true;
	if(firstflag)
	{
		for(int i = 0; i < IMU_LIST_N; i++)
		{
			week[i] = imusx.gnssWeek;
			sec[i] = imusx.gnssSec;
			gyrox[i] = imusx.xGyro * scale.gyro * freq;
			gyroy[i] = -imusx._yGyro * scale.gyro * freq;
			gyroz[i] = imusx.zGyro * scale.gyro * freq;

			accx[i] = imusx.xAccel * scale.acc * freq;
			accy[i] = -imusx._yAccel * scale.acc * freq;
			accz[i] = imusx.zAccel * scale.acc * freq;
		}
		firstflag = false;
	}
	else
	{
		for (int i = IMU_LIST_N-1; i >= 1; i--)
		{
			week[i] = week[i - 1];
			sec[i] = sec[i - 1];
			gyrox[i] = gyrox[i - 1];
			gyroy[i] = gyroy[i - 1];
			gyroz[i] = gyroz[i - 1];

			accx[i] = accx[i - 1];
			accy[i] = accy[i - 1];
			accz[i] = accz[i - 1];
		}
		week[0] = imusx.gnssWeek;
		sec[0] = imusx.gnssSec;
		gyrox[0] = imusx.xGyro * scale.gyro * freq;
		gyroy[0] = -imusx._yGyro * scale.gyro * freq;
		gyroz[0] = imusx.zGyro * scale.gyro * freq;

		accx[0] = imusx.xAccel * scale.acc * freq;
		accy[0] = -imusx._yAccel * scale.acc * freq;
		accz[0] = imusx.zAccel * scale.acc * freq;
	}

	imusx.update = true;

	return 0;
}

int NovatelImuData::GetImuScale(ImuType type)
{
	if (type == LITEF_MICROIMU)
	{
		scale.gyro = 1.0e-9 * RAD2DEG;
		scale.acc = 2.0e-8 / G0;
	}
	else if (type == EPSON_G365)
	{
		scale.gyro = 1.0;
		scale.acc = 1.0;
	}
	else
	{
		scale.gyro = 1.0;
		scale.acc = 1.0;
	}
	return 0;
}