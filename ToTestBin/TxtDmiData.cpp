#include "iostream"
#include "sstream"
#include "vector"

#include "TxtDmiData.hpp"

using namespace std;

TxtDmiData::TxtDmiData()
{
	update = false;
}

TxtDmiData::~TxtDmiData()
{
	update = false;
}

int TxtDmiData::OpenFile()
{
	fs.open(file.data());
	opened = fs.is_open();
	if (!opened)
	{
		cout << "DMI txt数据文件打开失败" << endl;
		return 1;
	}
	getline(fs, line);
	return 0;
}

int TxtDmiData::CloseFile()
{
	fs.close();
	return 0;
}

int TxtDmiData::GetData()
{
	update = false;
	if (!opened)
		return 1;

	getline(fs, line);
	if (fs.eof())
		return 1;

	vector<double>  dd;
	string word;
	istringstream devide(line);
	while (devide >> word)
	{
		dd.push_back(std::atof(word.c_str()));
	}

	if (dd.size() <= 1)
		return 1;

	static int firstFlag = 1;
	if (!firstFlag)
	{
		for (int i = TXT_DMI_LIST_N - 1; i >= 0; i--)
		{
			time[i] = time[i-1];
			dmi1[i] = dmi1[i - 1];
			dmi2[i] = dmi2[i - 1];
			dmi3[i] = dmi3[i - 1];
			dmi4[i] = dmi4[i - 1];
			status[i] = status[i - 1];
		}
	}

	time[0] = dd[0];
	if (dd.size() == 2)
	{
		time[0] = dd[0];
		dmi1[0] = dd[1];
		dmi2[0] = dmi3[0] = dmi4[0] = 0;
		status[0] = 0x01;
		update = true;
	}
	else if (dd.size() == 5)
	{
		time[0] = dd[0];
		dmi1[0] = dd[1];
		dmi2[0] = dd[2];
		dmi3[0] = dd[3];
		dmi4[0] = dd[4];
		status[0] = 0x0F;
		update = true;
	}
	else
	{
		update = false;
		return 1;
	}

	if (update && firstFlag)
	{
		for (int i = 1; i < TXT_DMI_LIST_N; i++)
		{
			time[i] = time[0] - i;
			dmi1[i] = dmi1[0];
			dmi2[i] = dmi2[0];
			dmi3[i] = dmi3[0];
			dmi4[i] = dmi4[0];
			status[i] = status[0];
		}
		firstFlag = 0;
	}

	return 0;
}