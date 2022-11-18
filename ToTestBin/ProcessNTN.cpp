#include "iostream"
#include "iomanip"
#include "ProcessNTN.hpp"


ProcessNTN::ProcessNTN()
{
}

ProcessNTN::ProcessNTN(string imuNovatelFile, string gnssTxtFile, string dmiNovatelFile, string testBinFile)
{
	imuN.file = imuNovatelFile;
	gnssT.file = gnssTxtFile;
	dmiN.file = dmiNovatelFile;
	testBin.file = testBinFile;
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

		//��ȡIMU����
		if (!endFlag[0] && needRead[0])
		{
			endFlag[0] = imuN.GetData();
			if (endFlag[0])
				break;
		}

		//��ȡGNSS����
		if (!endFlag[1] && needRead[1])
		{
			endFlag[1] = gnssT.GetData();
			needRead[1] = 0;
		}

		//��ȡDMI����
		if (!endFlag[2] && needRead[2])
		{
			endFlag[2] = dmiN.GetData();
			needRead[2] = 0;
		}


		//IMU����ʱ��
		double sec1 = gnssT.sec;
		double sec2 = dmiN.dmia.ms * 0.001;

		memset(&testBin.data, 0, sizeof(TestBinUnit));

		//IMU���ݸ���TESTBIN
		testBin.GetNovatelImu(imuN);

		//GNSS���ݸ���TESTBIN
		if ((sec1 <= testBin.sec0) && (sec1 > testBin.sec1))
		{
			testBin.GetTxtGnss(gnssT);
			needRead[1] = 1;
			//cout << fixed << setprecision(3)<< imuN.sec[0] << "   " << setprecision(3) << sec1 << endl;
		}

		//DMI���ݸ���TESTBIN
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