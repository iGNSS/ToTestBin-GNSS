#include "iostream"
#include "iomanip"
#include "ProcessNNN.hpp"
#include "ProcessNNT.hpp"
#include "ProcessNTN.hpp"
#include "ProcessNTT.hpp"

using namespace std;

enum NT_Slect
{
	NNN = 1,
	NNT = 2,
	NTN = 3,
	NTT = 4,
	OTHER = 5,
};

int funNNN()
{
	string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string gnssNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string dmiNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	//NNN
	//第1个N代表IMU使用Novatel的数据格式,若为T，代表txt文件
	//第2个N代表GNSS使用Novatel的数据格式,若为T，代表txt文件
	//第3个n代表DMI使用Novatel的数据格式,若为T，代表txt文件
	ProcessNNN NNN(imuNovatelFile, 1, gnssNovatelFile, 1, dmiNovatelFile, 1, testBinFile, 1);
	NNN.Process();

	return 0;
}

int funNNT()
{
	string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string gnssNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string dmiNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.dmr.txt";
	string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	ProcessNNT NNT(imuNovatelFile, 1, gnssNovatelFile, 1, dmiNovatelFile, 1, testBinFile, 1);
	NNT.Process();
	return 0;
}


int funNTN()
{
	string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string gnssTxtFile = "D:\\IE\\Group1\\data\\Group1-gnss.txt";
	string dmiTxtFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	ProcessNTN NTN(imuNovatelFile, 1,  gnssTxtFile, 1,  dmiTxtFile, 1,  testBinFile, 1);
	NTN.Process();
	return 0;
}

int funNTT()
{
	string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string gnssTxtFile = "D:\\IE\\Group1\\data\\Group1-gnss.txt";
	string dmiTxtFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.dmr.txt";
	string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	ProcessNTT NTT(imuNovatelFile, 1, gnssTxtFile, 1, dmiTxtFile, 1, testBinFile, 1);
	NTT.Process();
	return 0;
}


int funOther()
{
	return 0;
}

int main()
{
	NT_Slect nt = NTT;
	switch (nt)
	{
	case NNN:
		funNNN();
		break;

	case NNT:
		funNNT();
		break;

	case NTN:
		funNTN();
		break;

	case NTT:
		funNTT();
		break;

	case OTHER:
		funOther();

	default:
		break;
	}

	cout << "Hello TestBin!!!" << endl;
	//std::cin.ignore();
	return 0;
}