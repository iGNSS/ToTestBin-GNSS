#include "iostream"
#include "iomanip"
#include "ProcessNTT.hpp"


ProcessNTT::ProcessNTT()
{
}

ProcessNTT::ProcessNTT( string imuNovatelFile, int imuEn,
						string gnssTxtFile, int gnssEn,
						string dmiTxtFile, int dmiEn,
						string testBinFile, int outEn)
{
	imuN.file = imuNovatelFile;
	gnssT.file = gnssTxtFile;
	dmiT.file = dmiTxtFile;
	testBin.file = testBinFile;

	imuEnable = imuEn;
	gnssEnable = gnssEn;
	dmiEnable = dmiEn;
	outEnable = outEn;
}

ProcessNTT::~ProcessNTT()
{
}

int ProcessNTT::Process()
{
	imuN.OpenFile();
	imuN.Check();
	gnssT.OpenFile();
	dmiT.OpenFile();
	testBin.OpenFile();

	int endFlag[4] = { 0 };
	int needRead[4] = { 1, 1, 1, 0 };
	while (1)
	{
		imuN.imus.update = false;
		imuN.imusx.update = false;

		gnssT.update = false;

		dmiT.update = false;

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
			endFlag[1] = gnssT.GetData();
			needRead[1] = 0;
		}

		////读取DMI数据
		if (!endFlag[2] && needRead[2])
		{
			endFlag[2] = dmiT.GetData();
			needRead[2] = 0;
		}

		////IMU数据时间
		double sec1 = gnssT.sec;
		double sec2 = dmiT.time[0];

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
				testBin.GetTxtGnss(gnssT);
				needRead[1] = 1;
				//cout << fixed << setprecision(3)<< testBin.sec0 << "   " << setprecision(3) << sec1 << endl;
			}

			//DMI数据赋给TESTBIN
			if (dmiEnable && (sec2 <= testBin.sec0) && (sec2 > testBin.sec1))
			{
				testBin.GetTxtDmi(dmiT);
				//cout << fixed << setprecision(3) << testBin.sec0 << "   " << setprecision(3) << sec1 << "   " << setprecision(3) << sec2 << endl;
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