#include "iostream"
#include "iomanip"
#include "ProcessNNN.hpp"


ProcessNNN::ProcessNNN()
{
}

ProcessNNN::ProcessNNN(string imuNovatelFile, string gnssNovatelFile, string dmiNovatelFile, string testBinFile)
{
	imuN.file = imuNovatelFile;
	gnssN.file = gnssNovatelFile;
	dmiN.file = dmiNovatelFile;
	testBin.file = testBinFile;
}

ProcessNNN::~ProcessNNN()
{
}

int ProcessNNN::Process()
{
	imuN.OpenFile();
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
		testBin.GetNovatelImu(imuN);

		//GNSS数据赋给TESTBIN
		if ((sec1 <= testBin.sec0) && (sec1 > testBin.sec1))
		{
			testBin.GetNovatelGnss(gnssN);
			needRead[1] = 1;
			//cout << fixed << setprecision(3)<< imuN.sec[0] << "   " << setprecision(3) << sec1 << endl;
		}

		//DMI数据赋给TESTBIN
		if ((sec2 <= testBin.sec0) && (sec2 > testBin.sec1))
		{
			testBin.GetNovatelDmi(dmiN);
			//			cout << fixed << setprecision(3) << imuN.sec[0] << "   " << setprecision(3) << sec1 << endl;
			needRead[2] = 1;
		}
		testBin.WriteData();
	}

	return 0;
}