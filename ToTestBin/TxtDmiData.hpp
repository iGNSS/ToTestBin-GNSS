#pragma once

#include "iostream"
#include "fstream"

using	namespace  std;

#define		TXT_DMI_LIST_N							2

class TxtDmiData
{
public:
	string				file;
	bool				update;
	string				line;

	double				time[TXT_DMI_LIST_N];
	double				dmi1[TXT_DMI_LIST_N];
	double				dmi2[TXT_DMI_LIST_N];
	double				dmi3[TXT_DMI_LIST_N];
	double				dmi4[TXT_DMI_LIST_N];
	int					status[TXT_DMI_LIST_N];

	TxtDmiData();
	~TxtDmiData();
	int OpenFile();
	int CloseFile();
	int GetData();

private:
	ifstream			fs;
	bool				opened;
};
