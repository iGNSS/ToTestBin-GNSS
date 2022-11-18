#pragma once

struct MsgHeader
{
	unsigned char			sync[3];					//1-3
	unsigned char			HeaderLength;				//4
	unsigned short			MessageID;					//5
	char					MessageType;				//6
	unsigned char			PortAddress;				//7
	unsigned short			MessageLength;				//8
	unsigned short			Sequence;					//9
	unsigned char			IdleTime;					//10
	int						timeStatus;					//11
	unsigned short			week;						//12
	unsigned long			ms;							//13
	unsigned long			receiverStatus;				//14
	unsigned short			reserved;					//15
	unsigned short			receiverSWVersion;			//16
};
