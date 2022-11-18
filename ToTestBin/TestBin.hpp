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
	// ������Ϣ����BESTPOS BESTVEL
	unsigned int	nWeek;							// ��������λ����
	double			dSec_gnss;						// ���룬��λ����
	double			dSec_gnss1;

	// ������Ϣ����BestPos
	double			dLat_gnss;						// γ�ȣ���λ����
	double			dLon_gnss;						// ���ȣ���λ����
	double			dH_gnss;						// �߶ȣ���λ����

	int				ucGnssPos_FixFlag;				//Fix��־
	int				ucGnssPos_Q;					//GPS����״̬

	// ������Ϣ����BestVel
	double			dVe_gnss;						// ���٣���λ����/��
	double			dVn_gnss;						// ���٣���λ����/��
	double			dVu_gnss;						// ���٣���λ����/��
	int				dGnssVel_valid;

	double			dPit_online;					// ���߸����ǽ���ֵ - deg  module onlinedisplay
	double			dRol_online;					// ���ߺ���ǽ���ֵ - deg  module onlinedisplay
	double			dAzi_online;					// ���߷�λ�ǽ���ֵ - deg  module onlinedisplay
	
	// ������Ϣ����RawIMU
	double			dGyrox;							// x�����ݲ�����Ϣ - deg/s
	double			dGyroy;							// y�����ݲ�����Ϣ - deg/s
	double			dGyroz;							// z�����ݲ�����Ϣ - deg/s
	double			dAccx;							// x��ӱ������Ϣ - g
	double			dAccy;							// y��ӱ������Ϣ - g
	double			dAccz;							// z��ӱ������Ϣ - g

	double			dwDltCnt_dmi;					// GNSS��λ�� - deg

	// ������Ϣ����Heading
	double			dAzi_gnss;						//GNSS��λ�ǣ���λ����
	double			dBaseline_gnss;					//GNSS˫���߻��߳��ȣ���λ����

	unsigned char	ucNums1_gnss;					//'int' GNSSǰ�������� - None  module stGnss
	unsigned char	ucNums2_gnss;					//'int' GNSS���������� - None  module stGnss
	unsigned char	ucFlag_synchro;					//'int' GI���ͬ����־λ - none  module stGnss
	unsigned char	ucNavState_online;				//������ϵ���״̬ - None  module onlinedisplay
	unsigned char	ucNavState_online2;				//������ϵ���״̬ - None  module onlinedisplay
	unsigned char	ucState_gnss;					//'int' GNSS״̬ - None  module stGnss

	double			dLatStd;						// γ�ȣ���λ����
	double			dLonStd;						// ���ȣ���λ����
	double			dHStd;							// �߶ȣ���λ����
	int				nStat;							// �������ܱ�־��1��8ΪFix��2Ϊfloat��5Ϊ����
	int				nQ;								// ��λ������־��-1��ߣ���ʾ˫��fix��ƥ�䣻1Ϊ�ߣ�2��3��4˳��

	double			dVeStd;							// ����std����λ����/��
	double			dVnStd;							// ����std����λ����/��
	double			dVuStd;							// ����std����λ����/��
	int				nVelocityValid;					// �ٶ���Ч��־��1Ϊ��Ч��0Ϊ��Ч

	double			dAzi_Std_gnss;					// GPS˫���ߺ���std����λ����

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