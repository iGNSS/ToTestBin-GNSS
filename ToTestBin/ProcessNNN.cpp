#include "iostream"
#include "iomanip"
#include "ProcessNNN.hpp"


ProcessNNN::ProcessNNN()
{
}

ProcessNNN::ProcessNNN(string imuNovatelFile, int imuEn,
						string gnssNovatelFile, int gnssEn,
						string dmiNovatelFile, int dmiEn,
						string testBinFile, int outEn)
{
	imuN.file = imuNovatelFile;
	gnssN.file = gnssNovatelFile;
	dmiN.file = dmiNovatelFile;
	testBin.file = testBinFile;
	imuEnable = imuEn;
	gnssEnable = gnssEn;
	dmiEnable = dmiEn;
	outEnable = outEn;
}

ProcessNNN::~ProcessNNN()
{
}

int ProcessNNN::Process()
{
	imuN.OpenFile();
	imuN.Check();
	gnssN.OpenFile();
	gnssN.Check();
	dmiN.OpenFile();
	dmiN.Check();
	testBin.OpenFile();

	int endFlag[4] = { 0 };
	int needRead[4] = { 1, 1, 1, 0 };		//IMU GNSS DMI
	while (1)
	{
		imuN.imus.update = false;
		imuN.imusx.update = false;

		gnssN.bestPos.update = false;
		gnssN.bestVel.update = false;

		dmiN.dmia.update = false;

		//读取IMU数据
		if (!endFlag[0] && needRead[0])
		{
			endFlag[0] = imuN.GetData();
			if (endFlag[0])
				break;
		}

		//读取GNSS数据
		if (!endFlag[1] && needRead[1])
		{
			endFlag[1] = gnssN.GetData();
			needRead[1] = 0;
		}

		//读取DMI数据
		if (!endFlag[2] && needRead[2])
		{
			endFlag[2] = dmiN.GetData();
			needRead[2] = 0;
		}
	
		//IMU数据时间
		double sec1 = gnssN.bestPos.ms * 0.001;
		double sec2 = dmiN.dmia.ms * 0.001;

		memset(&testBin.data, 0, sizeof(TestBinUnit));

		//IMU数据赋给TESTBIN
		if(imuEnable)
			testBin.GetNovatelImu(imuN);

		for (int i = testBin.imuUpdateCnt - 1; i >= 0; i--)
		{
			testBin.sec1 = testBin.sec0;
			testBin.sec0 = testBin.sec[i];

			//IMU
			testBin.data.nWeek = testBin.week[i];
			testBin.data.dSec_gnss = testBin.sec[i];
			testBin.data.dGyrox = testBin.gyrox[i];
			testBin.data.dGyroy = testBin.gyroy[i];
			testBin.data.dGyroz = testBin.gyroz[i];
			testBin.data.dAccx = testBin.accx[i];
			testBin.data.dAccy = testBin.accy[i];
			testBin.data.dAccz = testBin.accz[i];
			//GNSS数据赋给TESTBIN
			if (gnssEnable && (sec1 <= testBin.sec0) && (sec1 > testBin.sec1))
			{
				testBin.GetNovatelGnss(gnssN);
				needRead[1] = 1;
				if (sec1 == 117364)
					sec1 *= 1.0;
				//cout << fixed << setprecision(5)<< testBin.sec0 << "   " << setprecision(5) << sec1 << endl;
			}

			//DMI数据赋给TESTBIN
			if (dmiEnable && (sec2 <= testBin.sec0) && (sec2 > testBin.sec1))
			{
				testBin.GetNovatelDmi(dmiN);
				//cout << fixed << setprecision(5) << testBin.sec0 << "   " << setprecision(5) << sec1 << endl;
				needRead[2] = 1;
			}
			
			if (testBin.sec0 < 116282)
				outEnable = 0;
			else
				outEnable = 1;

			//输出数据到TestBin
			testBin.imuOutEnable = imuEnable;
			testBin.gnssOutEnable = gnssEnable;
			testBin.dmiOutEnable = dmiEnable;
			if (outEnable)
				testBin.WriteData();
		}
	}

	return 0;
}