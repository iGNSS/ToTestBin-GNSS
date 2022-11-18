#include "iostream"
#include "sstream"
#include "vector"

#include "TxtGnssData.hpp"

using namespace std;

TxtGnssData::TxtGnssData()
{
	update = false;
}

TxtGnssData::~TxtGnssData()
{
	update = false;
}

int TxtGnssData::OpenFile()
{
	fs.open(file.data());
	opened = fs.is_open();
	if (!opened)
	{
		cout << "GNSS txt数据文件打开失败" << endl;
		return 1;
	}

	string des = "weeks";
	while (!fs.eof())
	{
		getline(fs, line);
		int ii = line.find(des);
		if (ii >= 0)
			break;		
	}
	return 0;
}

int TxtGnssData::CloseFile()
{
	fs.close();
	return 0;
}

int TxtGnssData::GetData()
{
	update = false;

	if (!opened)
		return 1;

	getline(fs, line);
	if (fs.eof())
		return 1;

	vector<string>  dd;
	string word;
	istringstream devide(line);
	while (devide >> word)
	{
		dd.push_back(word);
	}

	if (dd.size() >= 15)
	{
		week = std::atoi(dd[0].c_str());
		sec = std::atof(dd[1].c_str());
		lat = std::atof(dd[2].c_str());
		lon = std::atof(dd[3].c_str());
		hgt = std::atof(dd[4].c_str());
		ve = std::atof(dd[5].c_str());
		vn = std::atof(dd[6].c_str());
		vu = std::atof(dd[7].c_str());
		latStd = std::atof(dd[8].c_str());
		lonStd = std::atof(dd[9].c_str());
		hgtStd = std::atof(dd[10].c_str());
		veStd = std::atof(dd[11].c_str());
		vnStd = std::atof(dd[12].c_str());
		vuStd = std::atof(dd[13].c_str());
		Q = std::atoi(dd[14].c_str());

		if (dd[15].find("Fixed") >= 0)
			fixFlag = 1;
		else if (dd[15].find("Float") >= 0)
			fixFlag = 2;
		else
			fixFlag = 0;

		update = true;
	}

	return 0;
}