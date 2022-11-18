#pragma once

#include "iostream"
#include "fstream"
#include "stdio.h"

#include "NovatelImuData.hpp"
#include "NovatelGnssData.hpp"
#include "TxtGnssData.hpp"
#include "NovatelDmiData.hpp"
#include "TxtDmiData.hpp"

struct TestBinUnit
{
	// 以下信息来自BESTPOS BESTVEL
	unsigned int	nWeek;							// 周数，单位：周
	double			dSec_gnss;						// 周秒，单位：秒
	double			dSec_gnss1;

	// 以下信息来自BestPos
	double			dLat_gnss;						// 纬度，单位：度
	double			dLon_gnss;						// 经度，单位：度
	double			dH_gnss;						// 高度，单位：米

	int				ucGnssPos_FixFlag;				//Fix标志
	int				ucGnssPos_Q;					//GPS解算状态

	// 以下信息来自BestVel
	double			dVe_gnss;						// 东速，单位：米/秒
	double			dVn_gnss;						// 北速，单位：米/秒
	double			dVu_gnss;						// 天速，单位：米/秒
	int				dGnssVel_valid;

	double			dPit_online;					// 在线俯仰角解算值 - deg  module onlinedisplay
	double			dRol_online;					// 在线横滚角解算值 - deg  module onlinedisplay
	double			dAzi_online;					// 在线方位角解算值 - deg  module onlinedisplay
	
	// 以下信息来自RawIMU
	double			dGyrox;							// x轴陀螺测量信息 - deg/s
	double			dGyroy;							// y轴陀螺测量信息 - deg/s
	double			dGyroz;							// z轴陀螺测量信息 - deg/s
	double			dAccx;							// x轴加表测量信息 - g
	double			dAccy;							// y轴加表测量信息 - g
	double			dAccz;							// z轴加表测量信息 - g

	double			dwDltCnt_dmi;					// GNSS方位角 - deg

	// 以下信息来自Heading
	double			dAzi_gnss;						//GNSS方位角，单位：度
	double			dBaseline_gnss;					//GNSS双天线基线长度，单位：米

	unsigned char	ucNums1_gnss;					//'int' GNSS前天线星数 - None  module stGnss
	unsigned char	ucNums2_gnss;					//'int' GNSS后天线星数 - None  module stGnss
	unsigned char	ucFlag_synchro;					//'int' GI组合同步标志位 - none  module stGnss
	unsigned char	ucNavState_online;				//在线组合导航状态 - None  module onlinedisplay
	unsigned char	ucNavState_online2;				//在线组合导航状态 - None  module onlinedisplay
	unsigned char	ucState_gnss;					//'int' GNSS状态 - None  module stGnss

	double			dLatStd;						// 纬度，单位：度
	double			dLonStd;						// 经度，单位：度
	double			dHStd;							// 高度，单位：米
	int				nStat;							// 锁定整周标志，1或8为Fix，2为float，5为单点
	int				nQ;								// 定位质量标志，-1最高，表示双向fix且匹配；1为高，2、3、4顺延

	double			dVeStd;							// 东速std，单位：米/秒
	double			dVnStd;							// 北速std，单位：米/秒
	double			dVuStd;							// 天速std，单位：米/秒
	int				nVelocityValid;					// 速度有效标志，1为有效，0为无效

	double			dAzi_Std_gnss;					// GPS双天线航向std，单位：度

	int			    dmiStatus;
	double			dmi1;
	double			dmi2;
	double			dmi3;
	double			dmi4;
};


class TestBinData
{
public:
	friend						NovatelImuData;
	friend						NovatelGnssData;
	friend						TxtDmiData;

	string						file;
	FILE						*fs;

	TestBinUnit					data;
	double						sec0;
	double						sec1;

	int					       imuOutEnable;
	int						   gnssOutEnable;
	int						   dmiOutEnable;

	TestBinData();
	~TestBinData();
	int OpenFile();
	int CloseFile();

	int GetNovatelImu(NovatelImuData &imuN);

	int GetNovatelGnss(NovatelGnssData &gnssN);
	int GetTxtGnss(TxtGnssData &gnssT);

	int GetNovatelDmi(NovatelDmiData &dmiN);
	int GetTxtDmi(TxtDmiData &dmiT);

	int WriteData();
private:

};