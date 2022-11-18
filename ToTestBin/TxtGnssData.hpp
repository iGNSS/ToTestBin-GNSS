#pragma once

#include "iostream"
#include "fstream"

using	namespace  std;


class TxtGnssData
{
public:
	string				file;
	bool				update;
	string				line;

	unsigned long		week;
	double				sec;
	double				lat;
	double				lon;
	double				hgt;
	double				ve;
	double				vn;
	double				vu;

	double				latStd;
	double				lonStd;
	double				hgtStd;

	double				veStd;
	double				vnStd;
	double				vuStd;

	int					Q;
	int					fixFlag;

	TxtGnssData();
	~TxtGnssData();
	int OpenFile();
	int CloseFile();
	int GetData();

private:
	ifstream			fs;
	bool				opened;
};

