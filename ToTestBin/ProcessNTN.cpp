#include "iostream"
#include "iomanip"
#include "ProcessNTN.hpp"


ProcessNTN::ProcessNTN()
{
}

ProcessNTN::ProcessNTN(string imuNovatelFile, int imuEn,
						string gnssTxtFile, int gnssEn,
						string dmiNovatelFile, int dmiEn,
						string testBinFile, int outEn)
{
	imuN.file = imuNovatelFile;
	gnssT.file = gnssTxtFile;
	dmiN.file = dmiNovatelFile;
	testBin.file = testBinFile;

	imuEnable = imuEn;
	gnssEnable = gnssEn;
	dmiEnable = dmiEn;
	outEnable = outEn;
}

ProcessNTN::~ProcessNTN()
{
}

int ProcessNTN::Process()
{
	imuN.OpenFile();
	gnssT.OpenFile();
	dmiN.OpenFile();
	dmiN.Check();
	testBin.OpenFile();

	int endFlag[4] = { 0 };
	int needRead[4] = { 1, 1, 1, 0 };		//IMU GNSS DMI
	while (1)
	{
		imuN.imus.update = false;
		imuN.imusx.update = false;

		gnssT.update = false;

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
			endFlag[1] = gnssT.GetData();
			needRead[1] = 0;
		}

		//读取DMI数据
		if (!endFlag[2] && needRead[2])
		{
			endFlag[2] = dmiN.GetData();
			needRead[2] = 0;
		}


		//IMU数据时间
		double sec1 = gnssT.sec;
		double sec2 = dmiN.dmia.ms * 0.001;

		memset(&testBin.data, 0, sizeof(TestBinUnit));

		//IMU数据赋给TESTBIN
		if(imuEnable)
			testBin.GetNovatelImu(imuN);

		//GNSS数据赋给TESTBIN
		if (gnssEnable && (sec1 <= testBin.sec0) && (sec1 > testBin.sec1))
		{
			testBin.GetTxtGnss(gnssT);
			needRead[1] = 1;
			//cout << fixed << setprecision(3)<< imuN.sec[0] << "   " << setprecision(3) << sec1 << endl;
		}

		//DMI数据赋给TESTBIN
		if (dmiEnable && (sec2 <= testBin.sec0) && (sec2 > testBin.sec1))
		{
			testBin.GetNovatelDmi(dmiN);
			//			cout << fixed << setprecision(3) << imuN.sec[0] << "   " << setprecision(3) << sec1 << endl;
			needRead[2] = 1;
		}

		//if (testBin.sec0 < 116282)
		//	outEnable = 0;

		//输出数据到TestBin
		testBin.imuOutEnable = imuEnable;
		testBin.gnssOutEnable = gnssEnable;
		testBin.dmiOutEnable = dmiEnable;
		if(outEnable)
			testBin.WriteData();
	}

	return 0;
}