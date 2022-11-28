#pragma once

#include "iostream"
#include "fstream"

using	namespace  std;


class TxtDmiData
{
public:
	string				file;
	bool				update;
	string				line;

	double				time;
	double				dmi1;
	double				dmi2;
	double				dmi3;
	double				dmi4;
	int					status;

	TxtDmiData();
	~TxtDmiData();
	int OpenFile();
	int CloseFile();
	int GetData();

private:
	ifstream			fs;
	bool				opened;
};
