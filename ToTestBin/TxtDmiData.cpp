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

	if (fs.eof())
		return 1;

	getline(fs, line);
	if (strlen(line.c_str()) <= 5)
		return 1;

	vector<double>  dd;
	string word;
	istringstream devide(line);
	while (devide >> word)
	{
		dd.push_back(std::atof(word.c_str()));
	}

	time = dd[0];
	if (dd.size() == 2)
	{
		time = dd[0];
		dmi1 = dd[1];
		dmi2 = dmi3 = dmi4 = 0;
		status = 0x01;
		update = true;
	}
	else if (dd.size() == 5)
	{
		time = dd[0];
		dmi1 = dd[1];
		dmi2 = dd[2];
		dmi3 = dd[3];
		dmi4 = dd[4];
		status = 0x0F;
		update = true;
	}
	else
	{
		update = false;
		return 1;
	}

	return 0;
}