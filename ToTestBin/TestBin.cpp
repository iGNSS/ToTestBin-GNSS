#include "TestBin.hpp"

TestBinData::TestBinData()
{
}

TestBinData::~TestBinData()
{
}

int TestBinData::OpenFile()
{
	fs = fopen(file.c_str(), "w");
	return 0;
}

int TestBinData::CloseFile()
{
	fclose(fs);
	return 0;
}

/*
*从NovatelImuData获取IMU数据
*/
int TestBinData::GetNovatelImu(NovatelImuData &imuN)
{
	if (imuN.imus.update || imuN.imusx.update)
	{
		if (imuN.sec[0] >= 117110.34)
			sec1 *= 1.0;

#if 1
		int tmpN1 = floor((imuN.sec[0]) * 200);
		int tmpN2 = floor((imuN.sec[1]) * 200);
		imuUpdateCnt = tmpN1 - tmpN2;

		if (imuUpdateCnt >= 2)
			imuUpdateCnt *= 1.0;

		for (int i = 0; i < imuUpdateCnt; i++)
		{
			sec[i] = (tmpN1-i) * 0.005;
			double c0, c1;
			double dt = imuN.sec[0] - imuN.sec[1];
			c0 = (sec[i] - imuN.sec[1]) / dt;
			c1 = (imuN.sec[0] - sec[i]) / dt;
			week[i] = imuN.week[0];
			gyrox[i] = c0 * imuN.gyrox[0] + c1 * imuN.gyrox[1];
			gyroy[i] = c0 * imuN.gyroy[0] + c1 * imuN.gyroy[1];
			gyroz[i] = c0 * imuN.gyroz[0] + c1 * imuN.gyroz[1];
			accx[i] = c0 * imuN.accx[0] + c1 * imuN.accx[1];
			accy[i] = c0 * imuN.accy[0] + c1 * imuN.accy[1];
			accz[i] = c0 * imuN.accz[0] + c1 * imuN.accz[1];
		}
#else
		sec0 = imuN.sec[0];
		sec1 = imuN.sec[1];
		data.nWeek = imuN.week[0];
		data.dSec_gnss = imuN.sec[0];
		data.dGyrox = imuN.gyrox[0];
		data.dGyroy = imuN.gyroy[0];
		data.dGyroz = imuN.gyroz[0];
		data.dAccx = imuN.accx[0];
		data.dAccy = imuN.accy[0];
		data.dAccz = imuN.accz[0];
#endif
	}
	return 0;
}

/*
*从NovatelGnssData获取GNSS数据
*/
int TestBinData::GetNovatelGnss(NovatelGnssData &gnssN)
{
	//BestPOS
	if (gnssN.bestPosHaved)
	{
		data.dLat_gnss = gnssN.bestPos.lat;
		data.dLon_gnss = gnssN.bestPos.lon;
		data.dH_gnss = gnssN.bestPos.hgt;

		data.dLatStd = gnssN.bestPos.latStd;
		data.dLonStd = gnssN.bestPos.lonStd;
		data.dHStd = gnssN.bestPos.hgtStd;

		if (gnssN.bestPos.posType != 0)
		{
			data.ucGnssPos_FixFlag = gnssN.bestPos.posType;
			data.ucGnssPos_Q = 1;

			if(  (gnssN.bestPos.posType == 50) || (gnssN.bestPos.posType == 58))
			{
				data.ucGnssPos_FixFlag = 1;
				data.ucGnssPos_Q = 1;
			}
		}
	}

	//BestVel
	if (gnssN.bestVelHaved)
	{
		data.dVe_gnss = gnssN.bestVel.horSpd;
		data.dVn_gnss = gnssN.bestVel.horSpd;
		data.dVu_gnss = gnssN.bestVel.trkGnd;

		data.dVeStd = gnssN.bestVel.trkGnd;
		data.dVnStd = gnssN.bestVel.trkGnd;
		data.dVuStd = gnssN.bestVel.trkGnd;

		data.dGnssVel_valid = 1;
	}

	data.ucState_gnss = data.ucState_gnss | 0x03;
	data.ucFlag_synchro = 160;

	return 0;
}

int TestBinData::GetTxtGnss(TxtGnssData &gnssT)
{
	data.dLat_gnss = gnssT.lat;
	data.dLon_gnss = gnssT.lon;
	data.dH_gnss = gnssT.hgt;

	data.dLatStd = gnssT.latStd;
	data.dLonStd = gnssT.lonStd;
	data.dHStd = gnssT.hgtStd;

	data.ucGnssPos_FixFlag = gnssT.fixFlag;
	data.ucGnssPos_Q = gnssT.Q;

	data.dVe_gnss = gnssT.ve;
	data.dVn_gnss = gnssT.vn;
	data.dVu_gnss = gnssT.vu;

	data.dVeStd = gnssT.veStd;
	data.dVnStd = gnssT.vnStd;
	data.dVuStd = gnssT.vuStd;

	data.dGnssVel_valid = 1;

	data.ucState_gnss = data.ucState_gnss | 0x03;
	data.ucFlag_synchro = 160;

	return 0;
}

/*
*从TxtDmiData获取DMI数据
*/
int TestBinData::GetTxtDmi(TxtDmiData &dmiT)
{
	data.dmiStatus = dmiT.status;
	data.dmi1 = dmiT.dmi1;
	data.dmi2 = dmiT.dmi2;
	data.dmi3 = dmiT.dmi3;
	data.dmi4 = dmiT.dmi4;

	data.ucState_gnss = data.ucState_gnss | 0x08;
	
	return 0;
}

/*
*从NovatelDmiData获取DMI数据
*/
int TestBinData::GetNovatelDmi(NovatelDmiData &dmiN)
{
	data.dmiStatus = dmiN.dmia.status;
	data.dmi1 = dmiN.dmia.dmi1;
	data.dmi2 = dmiN.dmia.dmi2;
	data.dmi3 = dmiN.dmia.dmi3;
	data.dmi4 = dmiN.dmia.dmi4;

	data.ucState_gnss = data.ucState_gnss | 0x08;
	return 0;
}

/*
*从TxtDmiData数据存储
*/
int TestBinData::WriteData()
{
	if (gnssOutEnable)
	{
		fprintf(fs, "%4d,    ", data.nWeek);
		fprintf(fs, "%.10f,    ", data.dSec_gnss);

		fprintf(fs, "%.8f,    ", data.dLat_gnss);
		fprintf(fs, "%.8f,    ", data.dLon_gnss);
		fprintf(fs, "%.4f,    ", data.dH_gnss);
		fprintf(fs, "%.4f,    ", data.dLatStd);
		fprintf(fs, "%.4f,    ", data.dLonStd);
		fprintf(fs, "%.4f,    ", data.dHStd);

		fprintf(fs, "%4d,    ", data.ucGnssPos_FixFlag);
		fprintf(fs, "%4d,    ", data.ucGnssPos_Q);

		fprintf(fs, "%.5f,    ", data.dVe_gnss);
		fprintf(fs, "%.5f,    ", data.dVn_gnss);
		fprintf(fs, "%.5f,    ", data.dVu_gnss);
		fprintf(fs, "%.5f,    ", data.dVeStd);
		fprintf(fs, "%.5f,    ", data.dVnStd);
		fprintf(fs, "%.5f,    ", data.dVuStd);

		fprintf(fs, "%4d,    ", data.dGnssVel_valid);

		fprintf(fs, "%.8f,    ", data.dAzi_gnss);
		fprintf(fs, "%.8f,    ", data.dAzi_Std_gnss);

		fprintf(fs, "%.3f,    ", data.dBaseline_gnss);
		fprintf(fs, "%d,    ", data.ucState_gnss);
	}


	if (imuOutEnable)
	{
		fprintf(fs, "%.10f,    ", data.dGyrox);
		fprintf(fs, "%.10f,    ", data.dGyroy);
		fprintf(fs, "%.10f,    ", data.dGyroz);
		fprintf(fs, "%.10f,    ", data.dAccx);
		fprintf(fs, "%.10f,    ", data.dAccy);
		fprintf(fs, "%.10f,    ", data.dAccz);

		fprintf(fs, "%d,    ", data.dwDltCnt_dmi);
	}

	if (dmiOutEnable)
	{
		fprintf(fs, "%d,    ", data.dmiStatus);
		fprintf(fs, "%.5f,    ", data.dmi1);
		fprintf(fs, "%.5f,    ", data.dmi2);
		fprintf(fs, "%.5f,    ", data.dmi3);
		fprintf(fs, "%.5f,    ", data.dmi4);
	}

	fprintf(fs, "%d,    ", data.ucFlag_synchro);
	fprintf(fs, "\n");

	return 0;
}