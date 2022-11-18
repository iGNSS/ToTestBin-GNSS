#include "iostream"
#include "iomanip"
#include "ProcessNNT.hpp"


ProcessNNT::ProcessNNT() 
{
}

ProcessNNT::ProcessNNT(string imuNovatelFile, string gnssNovatelFile, string dmiTxtFile, string testBinFile)
{
	imuN.file = imuNovatelFile;
	gnssN.file = gnssNovatelFile;
	dmiT.file = dmiTxtFile;
	testBin.file = testBinFile;
}

ProcessNNT::~ProcessNNT()
{
}

int ProcessNNT::Process()
{
	imuN.OpenFile();
	gnssN.OpenFile();
	gnssN.Check();
	dmiT.OpenFile();
	testBin.OpenFile();

	int endFlag[4] = { 0 };
	int needRead[4] = { 1, 1, 1, 0 };
	while (1)
	{
		imuN.imus.update = false;
		imuN.imusx.update = false;

		gnssN.bestPos.update = false;
		gnssN.bestVel.update = false;

		dmiT.update = false;

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
			endFlag[1] = gnssN.GetData();
			needRead[1] = 0;
		}

		//��ȡDMI����
		if (!endFlag[2] && needRead[2])
		{
			endFlag[2] = dmiT.GetData();
			needRead[2] = 0;
		}

		//IMU����ʱ��
		double sec1 = gnssN.bestPos.ms * 0.001;
		double sec2 = dmiT.time;

		memset(&testBin.data, 0, sizeof(TestBinUnit));

		//IMU���ݸ���TESTBIN
		testBin.GetNovatelImu(imuN);

		//GNSS���ݸ���TESTBIN
		if ((sec1 <= testBin.sec0) && (sec1 > testBin.sec1))
		{
			testBin.GetNovatelGnss(gnssN);
			needRead[1] = 1;
			//cout << fixed << setprecision(3)<< imuN.sec[0] << "   " << setprecision(3) << sec1 << endl;
		}

		//DMI���ݸ���TESTBIN
		if ((sec2 <= testBin.sec0) && (sec2 > testBin.sec1))
		{
			testBin.GetTxtDmi(dmiT);
//			cout << fixed << setprecision(3) << imuN.sec[0] << "   " << setprecision(3) << sec1 << endl;
			needRead[2] = 1;
		}
		testBin.WriteData();
	}

	return 0;
}