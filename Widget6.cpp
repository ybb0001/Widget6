#include "widget6.h"
#include "ui_widget6.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>
#include <afx.h>
#include<iostream>
#include<fstream>   
#include <string>
#include<sstream>
#include <vector> 
#include <algorithm> 
#include <dclib.h>

using namespace std;

char D[16384][2];
unsigned char DecData[16384];
int LSC[13][17][4],LSC_LSI1[25][33][4], LSC_LSI2[11][13][4];
int PDgainLeft[13][17], PDgainRight[13][17];
int GainMostBrightLeft[13][17], GainMostBrightRight[13][17];
int DCC[6][8], FV[6][8], PD[6][8], PDAF[6][8][10],LRC[2][12][16],DCC_Sony[6][8], Foucus_Map[6][8];
char chk[2], Fuse_ID[22];  int fuse_ID_Length = 22;

// Function Area Start & End address
int infoStart = 0, infoEnd = 0x1F;
int fuseIDStart = 0, fuseIDEnd = 0;
int productDateStart = 0x03, productDateEnd = 0x44;
int serialNumberStart = 0x45, serialNumberEnd = 0x65;

int hallStart = 0x30, hallEnd = 0x3F, AFhallStart = 0x100, AFhallEnd= 0x109;
int oisFW = 0x85, dualAWBStart = 0x0D40, dualAWBEnd = 0x0D81;
int afStart = 0x40, afEnd = 0x56;
int awbStart = 0x5F, awbEnd = 0x85, awbStart3100 = 0x002F, awbEnd3100 = 0x0044,awbStart4000 = 0x0051, awbEnd4000 = 0x0066;
int awbLightStart = 0x45, awbLightEnd = 0x4E, awbLightStart4000 = 0x61, awbLightEnd4000 = 0x68, awbLightStart3100 = 0x49, awbLightEnd3100 = 0x50;
int lscStart = 0x8F, lscEnd = 0x04E6;
int pdafGainStart = 0x04EF, pdafGainEnd = 0x0995;
int DCCStart = 0x086C, DCCEnd = 0 ,SonyDCCStart = 0x0CCA, SonyDCCEnd = 0x0D2D;
int FVStart = 0x08D5, PDStart = 0x0935, LRCStart = 0x0AFA, LRCEnd = 0x0D2B;
int oisStart1 = 0x09A0, oisEnd1 = 0x09B1;
int oisStart2 = 0x09B4, oisEnd2 = 0x09BD;
int distortionStart = 0x0D90, distortionEnd = 0x0E91;

int DAStart = 0x09C0, DAEnd = 0x09C3;
int dualCalStart = 0x09D0, dualCalEnd = 0x11EC;
int dualVerifyStart = 0x11F0, dualVerifyEnd = 0x1209;
int AECStart = 0x1210, AECEnd = 0x1234;
int QSCStart = 0x3068, QSCEnd = 0x3969;

int barCodeStart = 0x1240;
int afDriftStart = 0x12CB, afDriftEnd = 0x12EF;
int confidenceStart = 0x1300, confidenceEnd = 0x16C0;
int pdaf_max_roiStart = 0x16D0, pdaf_max_roiEnd = 0x1A48;
int totalCheckSum = 0x1A50;
//LSI
int focusMapStart = 3200, focusMapEnd = 3311, headerLSIStart = 0, headerLSIEnd = 0;
int moduleLSIStart = 0, moduleLSIEnd = 0, awbLSIStart = 0, awbLSIEnd = 0, afLSIStart = 0, afLSIEnd = 0;
int lscLSIStart = 0, lscLSIEnd = 0, pdafLSIStart = 0, pdafLSIEnd = 0, oisLSIStart = 0, oisLSIEnd = 0;

int AAStart = 0x1E90;

//product date
int hallDate = 0x1EB0;
int af_infDate = 0x1EC0;
int af_macDate = 0x1ED0;
int awbDate = 0x1EE0;
int pdafDate = 0x1EF0;
int oisDate1 = 0x1F00;
int oisDate2 = 0x1F10;
int daDate = 0x1F20;
int dual_calDate = 0x1F30;
int dual_verDate = 0x1F40;
int aecDate = 0x1F50;
int dual_resolutionDate = 0x1F60;

//SFR
int infSFRStart = 0x1F70, infSFRStart2 = 0x3AEF;
int macSFRStart = 0x1F90;

//Master sample
int MasterSPLStart = 0x1FB0;

//Dual_INF_SFR
int Dual_INF_SFRStart = 0x1FD0;

float R_Gr51 = 0, B_Gr51 = 0, Gr_Gb51 = 0;
float R_Gr31 = 0, B_Gr31 = 0, Gr_Gb31 = 0;
int cnt1 = 0, cnt2 = 0, gainSpec = 550;

////////////////////////////
unsigned char slave, addr_H, addr_L, data_LSB;

int Value_init = -1;
int Value_Cards = -1;
int Value_Version = -1;
DWORD DllVer;
DWORD DrvVer;
DWORD ChipVer;
int Value_GPIOread = -1;
DWORD GPIO_Data = 0;
int Value_GPIOwrite = -1;
int Value_Channels = -1;
int Value_I2cStart = -1;
int Value_I2cWrite = -1;
int Value_I2cRead = -1;
int EEP_Size = 8192;

char id1[18], code1[12];
float inf_SFR_Spec[27] = {61,  51,51,51,51,51,51,51,51,51,51,  
                          50,50,50,50,50,50,50,50,  28,28,28,28,28,28,28,28};
float mac_SFR_Spec[27] = {58,  11,11,11,11,11,11,11,11  ,0 };
float SR_X1 = 27, SR_Y1  = 27;
float R_Gr1, B_Gr1, Gr_Gr1;
float R_Gr_Golden51=0, B_Gr_Golden51=0, Gr_Gb_Golden51=0;
float R_Gr_Golden31 = 0, B_Gr_Golden31 = 0, Gr_Gb_Golden31 = 0;


typedef struct {
	unsigned char addH, addL, data;
}ByteData;


ByteData CA[100] = { 0 };
ByteData Sensor[300]{ 0 };
int ca = 10, sensorReg = 0;

string s,fuseId,barCode;

int modelSelect = 1;
string EEPROM_Map = ".\\Setting\\EEPROM_Map_V1_797.ini";

//int sum1 = 0, sum2 = 0;
string src;
ofstream fout(".\\MemoryParseData.txt");


typedef struct EEPData
{
	float total_Weight = 0,awb_Weight = 0xffff;
	int sfr_Weight = 0xffff ,ois_Weight = 0xffff;
//	int awb_No = 99999999, sfr_No = 99999999, ois_No = 99999999, total_No = 99999999;
	char  FuseID[22] = { 0 }; 
	char  Date[11] = { 0 };
	float R_Gr51 = 0, B_Gr51 = 0, Gr_Gb51 = 0;
	float R_Gr31 = 0, B_Gr31 = 0, Gr_Gb31 = 0;
	short inf_SFR[27], mac_SFR[27], mac=0,inf=0;
	int SR_X1 = 0xffff, SR_Y1 = 0xffff, SR_X2 = 0xffff, SR_Y2 = 0xffff;
	char  barCode[13] = { 0 };
	char  Time[19] = { 0 };
}EEPData;

vector<EEPData> vecTest;

typedef struct gainmapData
{
	char  FuseID[18] = { 0 };
	char  Date[10] = { 0 };
	int sum;
	int left[13][17], right[13][17];

}gainmapData;

vector<gainmapData> gainData;

void widget6::Err_display(MyEnum code) {

	switch (code)
	{
	case len:
		ui->log->insertPlainText("Code Length Error!\n");
		break;

	case I2C_Read:
		ui->log->insertPlainText("EEPROM Read Error!\n");
		break;

	case I2C_Write:
		ui->log->insertPlainText("EEPROM Write Error!\n");
		break;

	case tCheckSum:
		ui->log->insertPlainText("Total Check Sum NG!\n");
		break;

	case hallCheckSum:
		ui->log->insertPlainText("Hall Cal Data NG!\n");
		break;

	case dataReCheck:
		ui->log->insertPlainText("Write Date Recheck NG!\n");
		break;

	default:
		break;
	}
	
}

int checkFF(int x) {
	if (x == 255)
		return 0;
	return x;
}

int hex2Dec(int x) {
	int s = 0;
	for (int i = 0; i < 2; i++) {
		s = s * 16;
		if (D[x][i] >= 'a')
			s += D[x][i] - 'a' + 10;
		else if (D[x][i] >= 'A')
			s += D[x][i] - 'A' + 10;
		else
			s += D[x][i] - '0';
	}
	return s;
}

string GetASCII(int x, int y) {
	string s = "";
	for (int i = 0; i < y; i++) {
		char a = hex2Dec(x + i);
		s += a;
	}
	return s;
}

void getHex(unsigned int tmp) {
	int a = tmp / 16;
	int b = tmp % 16;
	if (a < 10)
		chk[0] = '0' + a;
	else
		chk[0] = 'A' + a - 10;

	if (b < 10)
		chk[1] = '0' + b;
	else
		chk[1] = 'A' + b - 10;
}

unsigned char getHexValue(char x) {
	unsigned char s = 0;
	if (x >= 'a')
		s = x - 'a' + 10;
	else if (x >= 'A')
		s = x - 'A' + 10;
	else
		s = x - '0';
	return s;
}


unsigned char getUchar() {
	if (src.length() < 2)
		return 0;
	unsigned char s = getHexValue(src[0]) * 16 + getHexValue(src[1]);
	return s;
}


QString address2hex(int x) {

	QString s = "0x";
	char c[4] = { 0 };
	int a = x;
	for (int i = 0; i < 4; i++) {
		a = x % 16;
		if (a > 9)
			c[3 - i] = 'A' + a - 10;
		else
			c[3 - i] = '0' + a;
		x /= 16;
	}

	for (int i = 0; i < 4; i++)
		s.append(c[i]);

	return s;
}

string getFlag(int s) {
	if (DecData[s] == 0)
		return "Empty";
	else if (DecData[s] == 0x40 || DecData[s] == 0x01)
		return "Valid";
	else if (DecData[s] == 0x80 || DecData[s] == 0x10)
		return "Invalid";

	return " N/A ";
}

LPTSTR lptstr2int(int v) {
	CString ctmp;
	ctmp.Format(_T("%d"), v);
	//	LPTSTR re = ctmp.AllocSysString();
	//	LPTSTR lptstr_tmp = new TCHAR(ctmp.GetLength() + 1);
	//	lstrcpy(lptstr_tmp, ctmp);
	return ctmp.AllocSysString();
}


unsigned char widget6::my_DC_I2cRead(unsigned char s, int hi, int lo) {

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, s);
	if (hi >= 0)
		Value_I2cWrite = DC_I2cWrite(0, 0, hi);
	Value_I2cWrite = DC_I2cWrite(0, 0, lo);
	DC_I2cStop(0, 0);

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, s + 1);

	unsigned char tmp = DC_I2cRead(0, 0, 1);
	DC_I2cStop(0, 0);
	Sleep(10);
	return tmp;
}


int widget6::my_DC_I2cWrite(unsigned char s, int hi, int lo, unsigned char data) {

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, s);
	if (hi >= 0)
		Value_I2cWrite = DC_I2cWrite(0, 0, hi);
	Value_I2cWrite = DC_I2cWrite(0, 0, lo);
	Value_I2cWrite = DC_I2cWrite(0, 0, data);
	DC_I2cStop(0, 0);
	if (Value_I2cWrite != 0){
		return Value_I2cWrite;
	}
	Sleep(10);
	unsigned char tmp = my_DC_I2cRead(s,hi,lo);
	if (tmp != data)
		return -1000;

	return 0;
}
////////////////////////////////////////
/////////////////////////////////////
void load_EEPROM_Address() {

	infoEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("infoEnd"), infoEnd, CA2CT(EEPROM_Map.c_str()));

	fuseIDStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("fuseIDStart"), infoEnd, CA2CT(EEPROM_Map.c_str()));
	fuseIDEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("fuseIDEnd"), infoEnd, CA2CT(EEPROM_Map.c_str()));

	productDateStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("productDateStart"), infoEnd, CA2CT(EEPROM_Map.c_str()));
	productDateEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("productDateEnd"), infoEnd, CA2CT(EEPROM_Map.c_str()));

	serialNumberStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("serialNumberStart"), infoEnd, CA2CT(EEPROM_Map.c_str()));
	serialNumberEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("serialNumberEnd"), infoEnd, CA2CT(EEPROM_Map.c_str()));

	AFhallStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("AFhallStart"), AFhallStart, CA2CT(EEPROM_Map.c_str()));
	AFhallEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("AFhallEnd"), AFhallEnd, CA2CT(EEPROM_Map.c_str()));

	hallStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("hallStart"), hallStart, CA2CT(EEPROM_Map.c_str()));
	hallEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("hallEnd"), hallEnd, CA2CT(EEPROM_Map.c_str()));
	oisFW = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisFW"), 0, CA2CT(EEPROM_Map.c_str()));


	afStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("afStart"), afStart, CA2CT(EEPROM_Map.c_str()));
	afEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("afEnd"), afEnd, CA2CT(EEPROM_Map.c_str()));

	awbStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("awbStart"), awbStart, CA2CT(EEPROM_Map.c_str()));
	awbEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("awbEnd"), awbEnd, CA2CT(EEPROM_Map.c_str()));
	awbStart4000 = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("awbStart4"), awbStart, CA2CT(EEPROM_Map.c_str()));
	awbEnd4000 = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("awbEnd4"), awbEnd, CA2CT(EEPROM_Map.c_str()));
	dualAWBStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dualAWBStart"), dualAWBStart, CA2CT(EEPROM_Map.c_str()));
	dualAWBEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dualAWBEnd"), dualAWBEnd, CA2CT(EEPROM_Map.c_str()));


	lscStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("lscStart"), lscStart, CA2CT(EEPROM_Map.c_str()));
	lscEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("lscEnd"), lscEnd, CA2CT(EEPROM_Map.c_str()));

	pdafGainStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("pdafGainStart"), pdafGainStart, CA2CT(EEPROM_Map.c_str()));
	pdafGainEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("pdafGainEnd"), pdafGainEnd, CA2CT(EEPROM_Map.c_str()));
	
	DCCStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("DCCStart"), DCCStart, CA2CT(EEPROM_Map.c_str()));
	DCCEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("DCCEnd"), DCCEnd, CA2CT(EEPROM_Map.c_str()));

	LRCStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("LRCStart"), LRCStart, CA2CT(EEPROM_Map.c_str()));
	LRCEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("LRCEnd"), LRCEnd, CA2CT(EEPROM_Map.c_str()));

	SonyDCCStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("SonyDCCStart"), SonyDCCStart, CA2CT(EEPROM_Map.c_str()));
	SonyDCCEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("SonyDCCEnd"), SonyDCCEnd, CA2CT(EEPROM_Map.c_str()));

	FVStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("FVStart"), PDStart, CA2CT(EEPROM_Map.c_str()));
	PDStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("PDStart"), PDStart, CA2CT(EEPROM_Map.c_str()));

	oisStart1 = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisStart1"), oisStart1, CA2CT(EEPROM_Map.c_str()));
	oisEnd1 = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisEnd1"), oisEnd1, CA2CT(EEPROM_Map.c_str()));

	oisStart2 = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisStart2"), oisStart2, CA2CT(EEPROM_Map.c_str()));
	oisEnd2 = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisEnd2"), oisEnd2, CA2CT(EEPROM_Map.c_str()));

	DAStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("DAStart"), DAStart, CA2CT(EEPROM_Map.c_str()));
	DAEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("DAEnd"), DAEnd, CA2CT(EEPROM_Map.c_str()));

	dualCalStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dualCalStart"), dualCalStart, CA2CT(EEPROM_Map.c_str()));
	dualCalEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dualCalEnd"), dualCalEnd, CA2CT(EEPROM_Map.c_str()));

	dualVerifyStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dualVerifyStart"), dualVerifyStart, CA2CT(EEPROM_Map.c_str()));
	dualVerifyEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dualVerifyEnd"), dualVerifyEnd, CA2CT(EEPROM_Map.c_str()));

	AECStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("AECStart"), AECStart, CA2CT(EEPROM_Map.c_str()));
	AECEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("AECEnd"), AECEnd, CA2CT(EEPROM_Map.c_str()));

	barCodeStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("barCodeStart"), barCodeStart, CA2CT(EEPROM_Map.c_str()));

	afDriftStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("afDriftStart"), afDriftStart, CA2CT(EEPROM_Map.c_str()));
	afDriftEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("afDriftEnd"), afDriftEnd, CA2CT(EEPROM_Map.c_str()));

	confidenceStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("confidenceStart"), confidenceStart, CA2CT(EEPROM_Map.c_str()));
	confidenceEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("confidenceEnd"), confidenceEnd, CA2CT(EEPROM_Map.c_str()));

	pdaf_max_roiStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("pdaf_max_roiStart"), pdaf_max_roiStart, CA2CT(EEPROM_Map.c_str()));
	pdaf_max_roiEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("pdaf_max_roiEnd"), pdaf_max_roiEnd, CA2CT(EEPROM_Map.c_str()));

	totalCheckSum = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("totalCheckSum"), totalCheckSum, CA2CT(EEPROM_Map.c_str()));

	focusMapStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("focusMapStart"), focusMapStart, CA2CT(EEPROM_Map.c_str()));
	focusMapEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("focusMapEnd"), focusMapEnd, CA2CT(EEPROM_Map.c_str()));

	QSCStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("QSCStart"), QSCStart, CA2CT(EEPROM_Map.c_str()));
	QSCEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("QSCEnd"), QSCEnd, CA2CT(EEPROM_Map.c_str()));

	distortionStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("distortionStart"), distortionStart, CA2CT(EEPROM_Map.c_str()));
	distortionEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("distortionEnd"), distortionEnd, CA2CT(EEPROM_Map.c_str()));


	/////////////////////////V983-LSI	
	headerLSIStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("headerLSIStart"), headerLSIStart, CA2CT(EEPROM_Map.c_str()));
	headerLSIEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("headerLSIEnd"), headerLSIEnd, CA2CT(EEPROM_Map.c_str()));

	moduleLSIStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("moduleLSIStart"), moduleLSIStart, CA2CT(EEPROM_Map.c_str()));
	moduleLSIEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("moduleLSIEnd"), moduleLSIEnd, CA2CT(EEPROM_Map.c_str()));

	awbLSIStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("awbLSIStart"), awbLSIStart, CA2CT(EEPROM_Map.c_str()));
	awbLSIEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("awbLSIEnd"), awbLSIEnd, CA2CT(EEPROM_Map.c_str()));

	afLSIStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("afLSIStart"), afLSIStart, CA2CT(EEPROM_Map.c_str()));
	afLSIEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("afLSIEnd"), afLSIEnd, CA2CT(EEPROM_Map.c_str()));

	lscLSIStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("lscLSIStart"), lscLSIStart, CA2CT(EEPROM_Map.c_str()));
	lscLSIEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("lscLSIEnd"), lscLSIEnd, CA2CT(EEPROM_Map.c_str()));

	pdafLSIStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("pdafLSIStart"), pdafLSIStart, CA2CT(EEPROM_Map.c_str()));
	pdafLSIEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("pdafLSIEnd"), pdafLSIEnd, CA2CT(EEPROM_Map.c_str()));

	oisLSIStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisLSIStart"), oisLSIStart, CA2CT(EEPROM_Map.c_str()));
	oisLSIEnd = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisLSIEnd"), oisLSIEnd, CA2CT(EEPROM_Map.c_str()));

	////////////// Semco self area
	AAStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("AAStart"), AAStart, CA2CT(EEPROM_Map.c_str()));
	hallDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("hallDate"), hallDate, CA2CT(EEPROM_Map.c_str()));
	af_infDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("af_infDate"), af_infDate, CA2CT(EEPROM_Map.c_str()));
	af_macDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("af_macDate"), af_macDate, CA2CT(EEPROM_Map.c_str()));
	awbDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("awbDate"), awbDate, CA2CT(EEPROM_Map.c_str()));
	AAStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("AAStart"), AAStart, CA2CT(EEPROM_Map.c_str()));
	pdafDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("pdafDate"), pdafDate, CA2CT(EEPROM_Map.c_str()));
	oisDate1 = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisDate1"), oisDate1, CA2CT(EEPROM_Map.c_str()));
	oisDate2 = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("oisDate2"), oisDate2, CA2CT(EEPROM_Map.c_str()));

	daDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("daDate"), daDate, CA2CT(EEPROM_Map.c_str()));
	dual_calDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dual_calDate"), dual_calDate, CA2CT(EEPROM_Map.c_str()));
	dual_verDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dual_verDate"), dual_verDate, CA2CT(EEPROM_Map.c_str()));
	aecDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("aecDate"), aecDate, CA2CT(EEPROM_Map.c_str()));
	dual_resolutionDate = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("dual_resolutionDate"), dual_resolutionDate, CA2CT(EEPROM_Map.c_str()));

	infSFRStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("infSFRStart"), infSFRStart, CA2CT(EEPROM_Map.c_str()));
	macSFRStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("macSFRStart"), macSFRStart, CA2CT(EEPROM_Map.c_str()));
	MasterSPLStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("MasterSPLStart"), MasterSPLStart, CA2CT(EEPROM_Map.c_str()));
	Dual_INF_SFRStart = GetPrivateProfileInt(_T("EEPROM_Address"), TEXT("Dual_INF_SFRStart"), Dual_INF_SFRStart, CA2CT(EEPROM_Map.c_str()));

}

void save_EEPROM_Address() {

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("infoEnd"), lptstr2int(infoEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("fuseIDStart"), lptstr2int(fuseIDStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("fuseIDEnd"), lptstr2int(fuseIDEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("productDateStart"), lptstr2int(productDateStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("productDateEnd"), lptstr2int(productDateEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("serialNumberStart"), lptstr2int(serialNumberStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("serialNumberEnd"), lptstr2int(serialNumberEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("AFhallStart"), lptstr2int(AFhallStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("AFhallEnd"), lptstr2int(AFhallEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("hallStart"), lptstr2int(hallStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("hallEnd"), lptstr2int(hallEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisFW"), lptstr2int(oisFW), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("afStart"), lptstr2int(afStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("afEnd"), lptstr2int(afEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("awbStart"), lptstr2int(awbStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("awbEnd"), lptstr2int(awbEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("awbStart4"), lptstr2int(awbStart4000), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("awbEnd4"), lptstr2int(awbEnd4000), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dualAWBStart"), lptstr2int(dualAWBStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dualAWBEnd"), lptstr2int(dualAWBEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("lscStart"), lptstr2int(lscStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("lscEnd"), lptstr2int(lscEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("pdafGainStart"), lptstr2int(pdafGainStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("pdafGainEnd"), lptstr2int(pdafGainEnd), CA2CT(EEPROM_Map.c_str()));
	
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("DCCStart"), lptstr2int(DCCStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("DCCEnd"), lptstr2int(DCCEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("LRCStart"), lptstr2int(LRCStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("LRCEnd"), lptstr2int(LRCEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("SonyDCCStart"), lptstr2int(SonyDCCStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("SonyDCCEnd"), lptstr2int(SonyDCCEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("FVStart"), lptstr2int(FVStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("PDStart"), lptstr2int(PDStart), CA2CT(EEPROM_Map.c_str()));
	
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("QSCStart"), lptstr2int(QSCStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("QSCEnd"), lptstr2int(QSCEnd), CA2CT(EEPROM_Map.c_str()));
	
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("distortionStart"), lptstr2int(distortionStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("distortionEnd"), lptstr2int(distortionEnd), CA2CT(EEPROM_Map.c_str()));

	//////////////////  for V983
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("focusMapStart"), lptstr2int(focusMapStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("focusMapEnd"), lptstr2int(focusMapEnd), CA2CT(EEPROM_Map.c_str()));

	//////////////////  for LSI
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("headerLSIStart"), lptstr2int(headerLSIStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("headerLSIEnd"), lptstr2int(headerLSIEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("moduleLSIStart"), lptstr2int(moduleLSIStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("moduleLSIEnd"), lptstr2int(moduleLSIEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("awbLSIStart"), lptstr2int(awbLSIStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("awbLSIEnd"), lptstr2int(awbLSIEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("afLSIStart"), lptstr2int(afLSIStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("afLSIEnd"), lptstr2int(afLSIEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("lscLSIStart"), lptstr2int(lscLSIStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("lscLSIEnd"), lptstr2int(lscLSIEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("pdafLSISatrt"), lptstr2int(pdafLSIStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("pdafLSIEnd"), lptstr2int(pdafLSIEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisLSISatrt"), lptstr2int(oisLSIStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisLSIEnd"), lptstr2int(oisLSIEnd), CA2CT(EEPROM_Map.c_str()));

	/////////////////////////////////////////////////////////////////////////////////////////////

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisStart1"), lptstr2int(oisStart1), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisEnd1"), lptstr2int(oisEnd1), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisStart2"), lptstr2int(oisStart2), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisEnd2"), lptstr2int(oisEnd2), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("DAStart"), lptstr2int(DAStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("DAEnd"), lptstr2int(DAEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dualCalStart"), lptstr2int(dualCalStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dualCalEnd"), lptstr2int(dualCalEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dualVerifyStart"), lptstr2int(dualVerifyStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dualVerifyEnd"), lptstr2int(dualVerifyEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("AECStart"), lptstr2int(AECStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("AECEnd"), lptstr2int(AECEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("barCodeStart"), lptstr2int(barCodeStart), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("afDriftStart"), lptstr2int(afDriftStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("afDriftEnd"), lptstr2int(afDriftEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("confidenceStart"), lptstr2int(confidenceStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("confidenceEnd"), lptstr2int(confidenceEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("pdaf_max_roiStart"), lptstr2int(pdaf_max_roiStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("pdaf_max_roiEnd"), lptstr2int(pdaf_max_roiEnd), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("totalCheckSum"), lptstr2int(totalCheckSum), CA2CT(EEPROM_Map.c_str()));

	// Semco self area
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("AAStart"), lptstr2int(AAStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("hallDate"), lptstr2int(hallDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("af_infDate"), lptstr2int(af_infDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("af_macDate"), lptstr2int(af_macDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("awbDate"), lptstr2int(awbDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("pdafDate"), lptstr2int(pdafDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisDate1"), lptstr2int(oisDate1), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("oisDate2"), lptstr2int(oisDate2), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("daDate"), lptstr2int(daDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dual_calDate"), lptstr2int(dual_calDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dual_verDate"), lptstr2int(dual_verDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("aecDate"), lptstr2int(aecDate), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("dual_resolutionDate"), lptstr2int(dual_resolutionDate), CA2CT(EEPROM_Map.c_str()));

	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("infSFRStart"), lptstr2int(infSFRStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("macSFRStart"), lptstr2int(macSFRStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("MasterSPLStart"), lptstr2int(MasterSPLStart), CA2CT(EEPROM_Map.c_str()));
	WritePrivateProfileString(TEXT("EEPROM_Address"), TEXT("Dual_INF_SFRStart"), lptstr2int(Dual_INF_SFRStart), CA2CT(EEPROM_Map.c_str()));

}

void save_EEPROM_Setting() {

	WritePrivateProfileString(TEXT("Default_Setting"), TEXT("Model_Select"), lptstr2int(modelSelect), TEXT(".\\Setting\\EEPROM_Tool_Setting.ini"));
	WritePrivateProfileString(TEXT("Model_List"), TEXT("1"), TEXT("EEPROM_Map_V1_797.ini"), TEXT(".\\Setting\\EEPROM_Tool_Setting.ini"));

}


widget6::widget6(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EEPROM)
{
	ui->setupUi(this);

	ui->output->insertPlainText("Please Select Model: \n");
	ifstream in(".\\Setting\\EEPROM_Tool_Setting.ini");
	ostringstream outStr;
	outStr << in.rdbuf();
	string outContent = outStr.str();
	ui->output->insertPlainText(outContent.c_str());

	modelSelect = GetPrivateProfileInt(_T("Default_Setting"), TEXT("Model_Select"), 1, TEXT(".\\Setting\\EEPROM_Tool_Setting.ini"));
	ui->model->setText(QString::number(modelSelect, 10));

	Value_init = DC_Init();
	Value_Cards = DC_GetMaxCards();
	Value_Version = DC_GetVersion(0, &DllVer, &DrvVer, &ChipVer);
	Value_Channels = DC_GetMaxChannels(0);

	getHex(DllVer / 256);
	string temp = "DllVer: ";
	temp = temp + chk[0] + chk[1];
	getHex(DllVer % 256);
	temp = temp + chk[0] + chk[1];
	ui->log->insertPlainText(temp.c_str());

	getHex(DrvVer / 256);
	temp = ",  DrvVer: ";
	temp = temp + chk[0] + chk[1];
	getHex(DrvVer % 256);
	temp = temp + chk[0] + chk[1];
	ui->log->insertPlainText(temp.c_str());

	getHex(ChipVer / 256);
	temp = ",  ChipVer: ";
	temp = temp + chk[0] + chk[1];
	getHex(ChipVer % 256);
	temp = temp + chk[0] + chk[1] + '\n';
	ui->log->insertPlainText(temp.c_str());

	DC_GpioWriteOE(0, 0xFFF00);

	on_pushButton_GPIO_read_clicked();
	DC_I2cInit(0, 0, 1, 1);

}

widget6::~widget6()
{
	delete ui;
}

void Delay(DWORD delayTime)
{
	Sleep(delayTime);
	//DWORD delayTimeBegin;
	//DWORD delayTimeEnd;
	//delayTimeBegin = timeGetTime();
	//do{
	//	delayTimeEnd = timeGetTime();
	//} while (delayTimeEnd - delayTimeBegin < delayTime);
	//int x = 0;
}


void widget6::DisplayOutput() {

	ui->output->clear();
	ui->output->setFontPointSize(9);
	ifstream in(".\\MemoryParseData.txt");
	ostringstream outStr;
	outStr << in.rdbuf();
	string outContent = outStr.str();
	ui->output->insertPlainText(outContent.c_str());

}

void widget6::on_pushButton_GPIO_read_clicked()
{
	GPIO_Data = 0;
	Value_GPIOread = DC_GpioReadIn(0, &GPIO_Data);
	GPIO_Data %= 0x40000;
	ui->GPIO_Value->setText(QString::number(GPIO_Data, 10));
	GPIO_display();
}


void widget6::on_pushButton_GPIO_write_clicked()
{
	GPIO_Data = ui->GPIO_Value->document()->toPlainText().toInt();
	GPIO_Data %= 0x40000;
	Value_GPIOwrite = DC_GpioWriteOut(0, GPIO_Data);
	Sleep(50);
	on_pushButton_GPIO_read_clicked();

}


void eepLockOpen() {
	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x06);
	DC_I2cStop(0, 0);
	Sleep(10);
}

void eepLockClose() {
	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x0E);
	DC_I2cStop(0, 0);
	Sleep(10);
}

void widget6::read_EEPROM(unsigned char s, int size) {

	memset(DecData, 0, sizeof(DecData));
	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, s);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0);
	DC_I2cStop(0, 0);

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, s + 1);
	Value_I2cRead = DC_SoftI2cRead(0, 0, size, 0xFF, DecData);
	DC_I2cStop(0, 0);
	Sleep(10);

}


void widget6::on_pushButton_read_all_clicked()
{
	src = ui->slave->document()->toPlainText().toLocal8Bit();
	EEP_Size = ui->eep_size->document()->toPlainText().toInt();
	slave = getUchar();

	read_EEPROM(slave, EEP_Size);

	ui->input->clear();
	ui->input->setTextColor(QColor(0, 0, 0, 255));
	ui->input->setFontPointSize(8);

	display_EEP();
}


void widget6::on_pushButton_write_all_clicked()
{
	EEP_Size = ui->eep_size->document()->toPlainText().toInt();
	src = ui->input->document()->toPlainText().toLocal8Bit();
	int now = 0, e = 0, len = src.length() - 1, TCSum = 0;

	while (now < len && e < 8192) {
		if ((now == 0 || src[now - 1] == ' ' || src[now - 1] == '	' || src[now - 1] == '\n') &&
			((src[now + 2] == ' '&&src[now + 5] == ' '&&src[now + 8] == ' ')
				|| (src[now + 2] == '	'&&src[now + 5] == '	'&&src[now + 8] == '	'))) {

			for (int i = 0; i < 16; i++) {
				D[e][0] = src[now++];
				D[e][1] = src[now++];
				DecData[e] = hex2Dec(e);
				e++;
				now++;
			}
		}
		else now++;
	}

	src = ui->slave->document()->toPlainText().toLocal8Bit();
	slave = getUchar();

	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x06);
	DC_I2cStop(0, 0);
	Sleep(10);

	////////////////
	DC_I2cInit(0, 0, 1, 1);
	for (int i = 0; i < EEP_Size; i += 64) {

		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave);
		Value_I2cWrite = DC_I2cWrite(0, 0, i / 256);
		Value_I2cWrite = DC_I2cWrite(0, 0, i % 256);
		Value_I2cWrite = DC_SoftI2cWrite(0, 0, 64, 0x00, 0x00, DecData + i);
		DC_I2cStop(0, 0);
		Sleep(10);
	}
	///////////////////

	Sleep(10);
	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x0E);
	DC_I2cStop(0, 0);

	ui->log->insertPlainText("EEPROM save finished \n");

}


void widget6::on_pushButton_read_clicked()
{
	src = ui->slave->document()->toPlainText().toLocal8Bit();
	slave = getUchar();
	src = ui->addH->document()->toPlainText().toLocal8Bit();
	addr_H = getUchar();
	src = ui->addL->document()->toPlainText().toLocal8Bit();
	addr_L = getUchar();

	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave);
	if (ui->addH_use->isChecked())
		Value_I2cWrite = DC_I2cWrite(0, 0, addr_H);
	Value_I2cWrite = DC_I2cWrite(0, 0, addr_L);
	DC_I2cStop(0, 0);

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave + 1);

	data_LSB = 0;
	data_LSB = DC_I2cRead(0, 0, 1);
	DC_I2cStop(0, 0);

	getHex(data_LSB);
	string s = chk;
	s[2] = ' ';
	s[3] = '\0';
	ui->readData->setText(QString::fromStdString(s.c_str()));

}


void widget6::on_pushButton_write_clicked()
{
	src = ui->slave->document()->toPlainText().toLocal8Bit();
	slave = getUchar();
	src = ui->addH->document()->toPlainText().toLocal8Bit();
	addr_H = getUchar();
	src = ui->addL->document()->toPlainText().toLocal8Bit();
	addr_L = getUchar();

	src = ui->writeData->document()->toPlainText().toLocal8Bit();
	data_LSB = getUchar();
	///////////////////////
	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave);
	if (ui->addH_use->isChecked())
		Value_I2cWrite = DC_I2cWrite(0, 0, addr_H);
	Value_I2cWrite = DC_I2cWrite(0, 0, addr_L);
	Value_I2cWrite = DC_I2cWrite(0, 0, data_LSB);

	DC_I2cStop(0, 0);
}


void widget6::GPIO_display() {

	if ((GPIO_Data & 0x1) > 0) {
		ui->checkBox->setChecked(true);
	}
	else
		ui->checkBox->setChecked(false);

	if ((GPIO_Data & 0x2) > 0) {
		ui->checkBox_1->setChecked(true);
	}
	else
		ui->checkBox_1->setChecked(false);

	if ((GPIO_Data & 0x4) > 0) {
		ui->checkBox_2->setChecked(true);
	}
	else
		ui->checkBox_2->setChecked(false);

	if ((GPIO_Data & 0x8) > 0) {
		ui->checkBox_3->setChecked(true);
	}
	else
		ui->checkBox_3->setChecked(false);

	if ((GPIO_Data & 0x10)> 0) {
		ui->checkBox_4->setChecked(true);
	}
	else
		ui->checkBox_4->setChecked(false);

	if ((GPIO_Data & 0x20) > 0) {
		ui->checkBox_5->setChecked(true);
	}
	else
		ui->checkBox_5->setChecked(false);

	if ((GPIO_Data & 0x40) > 0) {
		ui->checkBox_6->setChecked(true);
	}
	else
		ui->checkBox_6->setChecked(false);

	if ((GPIO_Data & 0x80) > 0) {
		ui->checkBox_7->setChecked(true);
	}
	else
		ui->checkBox_7->setChecked(false);

	if ((GPIO_Data & 0x100) > 0) {
		ui->checkBox_8->setChecked(true);
	}
	else
		ui->checkBox_8->setChecked(false);

	if ((GPIO_Data & 0x200) > 0) {
		ui->checkBox_9->setChecked(true);
	}
	else
		ui->checkBox_9->setChecked(false);

	if ((GPIO_Data & 0x400) > 0) {
		ui->checkBox_10->setChecked(true);
	}
	else
		ui->checkBox_10->setChecked(false);

	if ((GPIO_Data & 0x800) > 0) {
		ui->checkBox_11->setChecked(true);
	}
	else
		ui->checkBox_11->setChecked(false);

	if ((GPIO_Data & 0x1000) > 0) {
		ui->checkBox_12->setChecked(true);
	}
	else
		ui->checkBox_12->setChecked(false);

	if ((GPIO_Data & 0x2000) > 0) {
		ui->checkBox_13->setChecked(true);
	}
	else
		ui->checkBox_13->setChecked(false);

	if ((GPIO_Data & 0x4000) > 0) {
		ui->checkBox_14->setChecked(true);
	}
	else
		ui->checkBox_14->setChecked(false);

	if ((GPIO_Data & 0x8000) > 0) {
		ui->checkBox_15->setChecked(true);
	}
	else
		ui->checkBox_15->setChecked(false);

	if ((GPIO_Data & 0x10000) > 0) {
		ui->checkBox_16->setChecked(true);
	}
	else
		ui->checkBox_16->setChecked(false);

	if ((GPIO_Data & 0x20000) > 0) {
		ui->checkBox_17->setChecked(true);
	}
	else
		ui->checkBox_17->setChecked(false);


	ui->GPIO_Value->setText(QString::number(GPIO_Data, 10));
}


void widget6::on_checkBox_clicked() {
	GPIO_Data ^= 0x1;
	GPIO_display();
}
void widget6::on_checkBox_1_clicked() {
	GPIO_Data ^= 0x2;
	GPIO_display();
}
void widget6::on_checkBox_2_clicked() {
	GPIO_Data ^= 0x4;
	GPIO_display();
}
void widget6::on_checkBox_3_clicked() {
	GPIO_Data ^= 0x8;
	GPIO_display();
}
void widget6::on_checkBox_4_clicked() {
	GPIO_Data ^= 0x10;
	GPIO_display();
}
void widget6::on_checkBox_5_clicked() {
	GPIO_Data ^= 0x20;
	GPIO_display();
}
void widget6::on_checkBox_6_clicked() {
	GPIO_Data ^= 0x40;
	GPIO_display();
}
void widget6::on_checkBox_7_clicked() {
	GPIO_Data ^= 0x80;
	GPIO_display();
}
void widget6::on_checkBox_8_clicked() {
	GPIO_Data ^= 0x100;
	GPIO_display();
}
void widget6::on_checkBox_9_clicked() {
	GPIO_Data ^= 0x200;
	GPIO_display();
}
void widget6::on_checkBox_10_clicked() {
	GPIO_Data ^= 0x400;
	GPIO_display();
}
void widget6::on_checkBox_11_clicked() {
	GPIO_Data ^= 0x800;
	GPIO_display();
}
void widget6::on_checkBox_12_clicked() {
	GPIO_Data ^= 0x1000;
	GPIO_display();
}
void widget6::on_checkBox_13_clicked() {
	GPIO_Data ^= 0x2000;
	GPIO_display();
}
void widget6::on_checkBox_14_clicked() {
	GPIO_Data ^= 0x4000;
	GPIO_display();
}
void widget6::on_checkBox_15_clicked() {
	GPIO_Data ^= 0x8000;
	GPIO_display();
}
void widget6::on_checkBox_16_clicked() {
	GPIO_Data ^= 0x10000;
	GPIO_display();
}
void widget6::on_checkBox_17_clicked() {
	GPIO_Data ^= 0x20000;
	GPIO_display();
}

void widget6::on_pushButton_GPIO_All_clicked() {
	GPIO_Data = 262143;
	GPIO_display();
	Sleep(5);
	on_pushButton_GPIO_write_clicked();
}

/*
/////////////////////////////

*/
void char_Out(int e) {

	int tmp = DecData[e];
	if (tmp > 0x7F)
		tmp = tmp - 0x100;
	fout << tmp << endl;
}


void short_Out(int e, bool HL) {

	int tmp = 0;
	if (HL) {
		tmp = DecData[e] * 256 + DecData[e + 1];
	}
	else {
		tmp = DecData[e + 1] * 256 + DecData[e];
	}
	if (tmp > 0x7FFF)
		tmp = tmp - 65536;

	fout << tmp << endl;

}
void gyro_Out(int e, bool HL) {

	unsigned int tmp = 0;
	if (HL) {
		for (int i = 0; i <4; i++) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
	}
	else {
		for (int i = 3; i >= 0; i--) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
	}
	fout << (float)tmp / 0x80000000 << endl;

}

void int_Out(int e,bool HL) {
	
	unsigned int tmp = 0;
	int* fp = (int*)&tmp;

	if (HL) {
		for (int i = 0; i <4; i++) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
	}
	else {
		for (int i = 3; i >= 0; i--) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
	}
	fout << *fp << endl;
}


void flt_Out(int e, bool HL) {

	int tmp = 0;
	float* fp = (float*)&tmp;

	if (HL) {
		for (int i = 0; i <4; i++) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
	}
	else {
		for (int i = 3; i >= 0; i--) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
	}
	fout << *fp << endl;
}


void widget6::selectModel() {
	//Load EEPROM_Map.ini
	modelSelect = ui->model->document()->toPlainText().toInt();

	TCHAR lpTexts[25];
	string temp_model = to_string(modelSelect);
	GetPrivateProfileString(TEXT("Model_List"), CA2CT(temp_model.c_str()), TEXT("EEPROM_Map_V1_797.ini"), lpTexts, 25, TEXT(".\\Setting\\EEPROM_Tool_Setting.ini"));
	EEPROM_Map = CT2A(lpTexts);

	string str1 = ".\\Setting\\";
	EEPROM_Map = str1 + EEPROM_Map;
	save_EEPROM_Setting();

	if (modelSelect == 3 || modelSelect == 5 || modelSelect == 8)
		EEP_Size = 16384;
	else if (modelSelect == 6 || modelSelect == 7)
		EEP_Size = 12288;
	else 
		EEP_Size = 8192;

}


void lsc_Parse(int S, int E) {

	fout << "-------LSC CAL Data------" << endl;
	if (modelSelect < 3 ) {
		int e = S;

		if (modelSelect < 3){
			e ++;
			fout << "Horizontal Lens Correction Size:	" << (int)DecData[e] << endl;
			fout << "Vertical Lens Correction Size:	" << (int)DecData[e + 1] << endl;
		}
		e = e + 2;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				for (int k = 0; k < 4; k++) {
					LSC[i][j][k] = DecData[e + k];
					LSC[i][j][k] += 256 * ((DecData[e + 4] >> (6 - 2 * k)) & 3);
				}
				e += 5;
			}
	}

	if (modelSelect == 3|| modelSelect == 4 || modelSelect == 8 || modelSelect == 6) {
		int e = S;
		if (modelSelect == 8)
			e += 2;
		if (modelSelect == 6)
			e += 4;

		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				for (int k = 0; k < 4; k++) {
					LSC[i][j][k] = DecData[e + k];
					LSC[i][j][k] += 256 * ((DecData[e + 4] >> (6 - 2 * k)) & 3);
				}
				e += 5;
				if ((i * 17 + j + 1) % 51 == 0) {
					e++;
				}
			}
	}

	if (modelSelect == 5) {
		int e = S+2;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) 
				for (int k = 0; k < 4; k++) {			
					LSC[i][j][k] = 256 * DecData[e] + DecData[e+1];
					e += 2;
				}	
	}

	fout << "~~~Red Channel LSC:" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			fout << LSC[i][j][0] << "	";
		}
		fout << endl;
	}

	fout << "~~~Gr Channel LSC:" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			fout << LSC[i][j][1] << "	";
		}
		fout << endl;
	}

	fout << "~~~Gb Channel LSC:" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			fout << LSC[i][j][2] << "	";
		}
		fout << endl;
	}

	fout << "~~~Blue Channel LSC:" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			fout << LSC[i][j][3] << "	";
		}
		fout << endl;
	}
	fout << endl;

}


void lscLSI_Parse(int S, int E) {

	if (S > 0) {
		int e = S + 1;		unsigned int tmp = 0;		float* fp = (float*)&tmp;
		
		fout << "~~~~~~~~~~ LSI LSC ~~~~~~~~~~:	" << endl;
		fout << "LSI LSC Version:	" << DecData[e] * 256 + DecData[e + 1] << endl;
		e += 2;
		fout << "Grid width for gridBugger[0]:	" << (int)DecData[e++] << endl;
		fout << "Grid height for gridBugger[0]:	" << (int)DecData[e++] << endl;
		fout << "Grid width for gridBugger[1]:	" << (int)DecData[e++] << endl;
		fout << "Grid height for gridBugger[1]:	" << (int)DecData[e++] << endl;
		fout << "Bit Length for Grid[0]:	" << (int)DecData[e++] << endl;
		fout << "Bit Length for Grid[1]:	" << (int)DecData[e++] << endl;
		fout << "Orientation(Mirror_flip:	0x" << D[e][0] << D[e][1] << D[e + 1][0] << D[e + 1][1] << endl;
		e += 2;
		fout << "Center position X:	" << DecData[e] * 256 + DecData[e + 1] << endl;
		e += 2;
		fout << "Center position Y:	" << DecData[e] * 256 + DecData[e + 1] << endl;
		e += 2;
		fout << "Scale coefficient:	" << DecData[e] * 256 + DecData[e + 1] << endl;
		e += 2;
		tmp = 0;
		for (int i = 0; i < 4; i++) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
		fout << "Polynomial coefficient A:	" << *fp << endl;
		e += 4;
		tmp = 0;
		for (int i = 0; i < 4; i++) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
		fout << "Polynomial coefficient B:	" << *fp << endl;
		e += 4;

		for (int i = 0; i < 25; i++)
			for (int j = 0; j < 33; j++) {
				LSC_LSI1[i][j][0] = DecData[e] * 16 + (DecData[e + 1] >> 4);
				LSC_LSI1[i][j][1] = (DecData[e + 1] & 0x0F) * 256 + DecData[e + 2];
				LSC_LSI1[i][j][2] = DecData[e + 3] * 16 + (DecData[e + 4] >> 4);
				LSC_LSI1[i][j][3] = (DecData[e + 4] & 0x0F) * 256 + DecData[e + 5];
				e += 6;
			}

		fout << "LSI lsc buffer[0]:	" << endl;

		for (int k = 0; k < 4; k++) {
			for (int i = 0; i < 25; i++){
				for (int j = 0; j < 33; j++) {
					fout << LSC_LSI1[i][j][k] << "	";
				}
				fout << endl;
			}
			fout << endl;
		}

		e += 2;
		for (int i = 0; i < 11; i++)
			for (int j = 0; j < 13; j++) {
				LSC_LSI2[i][j][0] = DecData[e] * 16 + (DecData[e + 1] >> 4);
				LSC_LSI2[i][j][1] = (DecData[e + 1] & 0x0F) * 256 + DecData[e + 2];
				LSC_LSI2[i][j][2] = DecData[e + 3] * 16 + (DecData[e + 4] >> 4);
				LSC_LSI2[i][j][3] = (DecData[e + 4] & 0x0F) * 256 + DecData[e + 5];
				e += 6;
			}

		fout << "LSI lsc buffer[1]:	" << endl;

		for (int k = 0; k < 4; k++) {
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 13; j++) {
					fout << LSC_LSI2[i][j][k] << "	";
				}
				fout << endl;
			}
			fout << endl;
		}
	}

}


void pushData() {
	int e = 0;
	EEPData mEEP;
	// Fuse ID date
	e = fuseIDStart;
	if (modelSelect != 1)
		e++;
	for (int i = 0; i < 9; i ++) {
		mEEP.FuseID[2 * i] = D[e + i][0];
		mEEP.FuseID[2 * i + 1] = D[e + i][1];
	}
	//// product date
	//e = infoStart + 0x25;
	//int a = 0;
	//for (int i = 0; i < 5; i++) {
	//	mEEP.Date[a++] = D[e + i][0];
	//	mEEP.Date[a++] = D[e + i][1];
	//}

	//AWBgolden
	if (awbStart > 0) {

		e = awbStart + 1;

		mEEP.R_Gr51 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
		e += 2;
		mEEP.B_Gr51 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
		e += 2;
		mEEP.Gr_Gb51 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
		e += 2;
		if (cnt1 == 0&& R_Gr_Golden51 ==0) {
			R_Gr_Golden51 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
			e += 2;
			B_Gr_Golden51 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
			e += 2;
			Gr_Gb_Golden51 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
			e += 2;

		}
		else
			e += 6;

		mEEP.R_Gr31 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
		e += 2;
		mEEP.B_Gr31 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
		e += 2;
		mEEP.Gr_Gb31 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
		e += 2;

		if (cnt1 == 0 && R_Gr_Golden31 == 0) {
			R_Gr_Golden31 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
			e += 2;
			B_Gr_Golden31 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
			e += 2;
			Gr_Gb_Golden31 = (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024;
			e += 2;
		}

		mEEP.awb_Weight = pow(mEEP.R_Gr51 - R_Gr_Golden51, 2) + pow(mEEP.B_Gr51 - B_Gr_Golden51, 2) + pow(mEEP.Gr_Gb51 - Gr_Gb_Golden51, 2);
		
		if(mEEP.R_Gr31<1)
		mEEP.awb_Weight +=pow(mEEP.R_Gr31 - R_Gr_Golden31, 2) + pow(mEEP.B_Gr31 - B_Gr_Golden31, 2) + pow(mEEP.Gr_Gb31 - Gr_Gb_Golden31, 2);

		mEEP.awb_Weight = mEEP.awb_Weight ;
		mEEP.total_Weight -= mEEP.awb_Weight * 1000;

	}
	//----------infSFR
	e = infSFRStart+1;
	for (int i = 0; i < 27; i++)
		mEEP.inf_SFR[i] = DecData[e + i]%255;

	for (int i = 0; i < 27; i++) {
		if (inf_SFR_Spec[i]!=0 && mEEP.inf_SFR[i] - inf_SFR_Spec[i] < mEEP.sfr_Weight)
			mEEP.sfr_Weight = mEEP.inf_SFR[i] - inf_SFR_Spec[i];
	}

	//----------macSFR
	e = macSFRStart ;
	for (int i = 0; i < 27; i++)
		mEEP.mac_SFR[i] = DecData[e + i]%255;

	for (int i = 0; i < 27; i++) {
		if (mac_SFR_Spec[i] != 0 && mEEP.mac_SFR[i] - mac_SFR_Spec[i] < mEEP.sfr_Weight)
			mEEP.sfr_Weight = mEEP.mac_SFR[i] - mac_SFR_Spec[i];
	}
	mEEP.total_Weight += mEEP.sfr_Weight;
	//----------OIS1
	if (oisStart1 > 0) {
		e = oisStart1 + 9;
		mEEP.SR_X1 = (256 * DecData[e] + DecData[e + 1])%65535;
		if (mEEP.SR_X1-270  < mEEP.ois_Weight)
			mEEP.ois_Weight = mEEP.SR_X1-270;

		e += 2;
		mEEP.SR_Y1 = (256 * DecData[e] + DecData[e + 1]) % 65535;;
		if (mEEP.SR_Y1-270 < mEEP.ois_Weight)
			mEEP.ois_Weight = mEEP.SR_Y1-270;

		if (mEEP.ois_Weight > 1000)
			mEEP.ois_Weight = -270;

		mEEP.total_Weight += (float)mEEP.ois_Weight/20;

	}
	//----------OIS2
	if (oisStart2 > 0) {
		e = oisStart2 + 1;
		mEEP.SR_X2 = (float)(256 * DecData[e] + DecData[e + 1]);
		e += 2;
		mEEP.SR_Y2 = (float)(256 * DecData[e] + DecData[e + 1]);
	}

	vecTest.push_back(mEEP);
	cnt1++;
}

bool comp_AWB_Weight(const EEPData &a, const EEPData &b)
{
	return a.awb_Weight < b.awb_Weight;
}

bool comp_SFR_Weight(const EEPData &a, const EEPData &b)
{
	return a.sfr_Weight > b.sfr_Weight;
}

bool comp_OIS_Weight(const EEPData &a, const EEPData &b)
{
	return a.ois_Weight > b.ois_Weight;
}

bool comp_Total_Weight(const EEPData &a, const EEPData &b)
{
	return a.total_Weight > b.total_Weight;
}

//bool comp_Total_No(const EEPData &a, const EEPData &b)
//{
//	return a.total_No < b.total_No;
//}


void widget6::on_pushButton_clear_clicked()
{
	ui->pushButton_parser->setEnabled(true);
	ui->pushButton_golden->setEnabled(true);

	cnt1 = 0, cnt2 = 0;

	memset(DecData, 0, sizeof(DecData));
	memset(D, 0, sizeof(D));
	ui->input->document()->clear();
	ui->output->clear();
	ui->log->clear();
	fout.open(".\\MemoryParseData.txt");

}

void widget6::awbGolden() {

	selectModel();
	load_EEPROM_Address();
	save_EEPROM_Address();

	int now = 0, e = 0, len = src.length() - 1;
	while (now < len) {

		if ((now == 0 || src[now - 1] == ' ' || src[now - 1] == '	' || src[now - 1] == '\n') &&
			((src[now + 2] == ' '&&src[now + 5] == ' '&&src[now + 8] == ' ')
				|| (src[now + 2] == '	'&&src[now + 5] == '	'&&src[now + 8] == '	')
				|| (src[now + 2] == '\n'&&src[now + 5] == '\n'&&src[now + 8] == '\n'))) {

			for (int i = 0; i < 16; i++) {
				D[e][0] = src[now++];
				D[e][1] = src[now++];
				DecData[e] = hex2Dec(e);
				e++;
				now++;
			}

			if (e >= 8192) {
				pushData();
				e = 0;
			}
		}
		else now++;
	}

	sort(vecTest.begin(), vecTest.end(), comp_AWB_Weight);
	fout << "~~~~~	Total CNT =	" << cnt1 << endl;

	fout << "FuseID" << '	' << "Date" << '	';
	fout << R_Gr51 << '	' << B_Gr51 << '	' << Gr_Gb51 << '	';
	fout << R_Gr31 << '	' << B_Gr31 << '	' << Gr_Gb31 << '	';
	fout << "Var" << endl;

	int c = 0;
	for (vector<EEPData>::iterator it = vecTest.begin(); it != vecTest.end(); it++) {

		for (int i = 0; i < 18; i++) {
			fout << it->FuseID[i];
		}
		fout << '	';
		for (int i = 0; i < 10; i++) {
			fout << it->Date[i];
			if (i == 5)
				fout << '_';
		}
		fout << '	';
		fout << it->R_Gr51 << '	' << it->B_Gr51 << '	' << it->Gr_Gb51 << '	';
		fout << it->R_Gr31 << '	' << it->B_Gr31 << '	' << it->Gr_Gb31 << '	';
		fout << it->awb_Weight;
		fout << endl;

		if (c == 19) {
			DisplayOutput();
		}
		c++;
	}

	if (c < 20)
		DisplayOutput();
}

void widget6::on_pushButton_golden_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open TXT"), "", tr("EEPROM File(*.txt)"));
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string name = code->fromUnicode(filename).data();

	ifstream in(name);
	ostringstream sin;
	sin << in.rdbuf();
	src = sin.str();

	if (src.size()>8191)
	{
		QString strDisplay = "EEPROM txt file read finished ";
		strDisplay += '\n';
		ui->log->insertPlainText(strDisplay);
	}

	awbGolden();
	fout << endl;
	fout.close();
	ui->pushButton_golden->setEnabled(false);
}

void widget6::gainMapData() {
	int e = pdafGainStart + 7;
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 17; j++) {
			PDgainLeft[i][j] = 256 * DecData[e] + DecData[e + 1];
			sum1 += PDgainLeft[i][j];
			e += 2;
		}

	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 17; j++) {
			PDgainRight[i][j] = 256 * DecData[e] + DecData[e + 1];
			sum2 += PDgainRight[i][j];
			e += 2;
		}
	sum1 /= 221; sum2 /= 221;

	if ((sum1<1000 && sum1 > gainSpec) || (sum2<1000 && sum2 > gainSpec)) {

		e = infoStart + 0x0D;
		for (int i = 0; i < 9; i++) {
			fout << D[e + i][0] << D[e + i][1];
		}
		fout << '	';

		e = infoStart + 0x25;
		for (int i = 0; i < 5; i++) {
			fout << D[e + i][0] << D[e + i][1];
			if (i == 2)
				fout << '_';
		}
		fout << endl;

		fout << "~~~Left Gain map:	AVG=	" << sum1 << endl;
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 17; j++) {
				fout << PDgainLeft[i][j] << "	";

			}
			fout << endl;
		}

		fout << "~~~Right Gain map:	AVG=	" << sum2 << endl;
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 17; j++) {
				fout << PDgainRight[i][j] << "	";
			}
			fout << endl;
		}

		fout << "~~~DCC Data map:	" << endl;
		e = DCCStart + 6;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
				fout << 256 * DecData[e] + DecData[e + 1] << '	';
				e += 2;
			}
			fout << endl;
		}
		fout << endl;
		cnt2++;

		if (cnt2 == 1)
			DisplayOutput();
	}

}

void dumpOut() {
	int e = 0;
	fout << "Sensor Fuse ID:	";

	fout << "Hall Offset X:	";
	fout << "Hall Offset Y:	";
	fout << "Hall Center X:	";
	fout << "Hall Center Y:	";
	fout << "Hall Bias X:	";
	fout << "Hall Bias Y:	";


	fout << endl;


	e = fuseIDStart + 1;
	
	for (int i = 0; i < 18; i++) {
		fout << D[e + i][0] << D[e + i][1];
	}
	fout <<"	";
	e = hallStart;
	fout << hex2Dec(e + 1) * 256 + hex2Dec(e + 2) << "	";
	fout << hex2Dec(e + 3) * 256 + hex2Dec(e + 4) << "	";
	fout << hex2Dec(e + 5) * 256 + hex2Dec(e + 6) << "	";
	fout << hex2Dec(e + 7) * 256 + hex2Dec(e + 8) << "	";
	fout << hex2Dec(e + 9) << "	";
	fout << hex2Dec(e + 0x0A) << "	";

}


void widget6::findData(){

	int e = 0;
	EEPData mEEP;
	if (fuseId.length() > 15) {
		// Fuse ID date
		e = fuseIDStart;
		if (modelSelect != 1)
			e++;

		for (int i = 0; i < 18; i++) {
			mEEP.FuseID[i] = src[i+18];

		}

		//for (int i = 0; i < 9; i++) {
		//	mEEP.FuseID[2 * i] = D[e + i][0];
		//	mEEP.FuseID[2 * i + 1] = D[e + i][1];
		//}

		for (int i = 0; i < 18; i++) {
			mEEP.Time[i] = src[i];
		}

		string tf = mEEP.FuseID;
		if (tf.compare(fuseId) == 0) {
			fout << mEEP.Time << mEEP.FuseID << endl;
			display_EEP();
		}

	}
	else if(barCode.length()>10)
	{
		e = serialNumberStart + 1;
		for (int i = 0; i < 12; i++) {
			if ((char)DecData[e + i] != 0)
				mEEP.barCode[i] = (char)DecData[e + i];
		}

		string tf = mEEP.barCode;
		if (tf.compare(barCode) == 0) {
			fout << mEEP.Time << mEEP.FuseID << endl;
			display_EEP();
		}
	}
}


void fuse_ID_out() {

	for (int i = 0; i < fuse_ID_Length; i++) {
		fout << Fuse_ID[i] ;
	}
	fout << "	";

}

void widget6::Item_Output() {

	if (lscStart > 0&&ui->checkBox_LSC->isChecked()) {
		lsc_Parse(lscStart, lscEnd);
	}

	if (afStart> 0 && ui->checkBox_AF->isChecked()) {

		fuse_ID_out();
		int e = afStart;
		if (modelSelect == 3 || modelSelect == 4) {
			//	fout << "AF Start DAC:	" << DecData[e] + DecData[e + 1] * 256 << endl;
			e = e + 2;
			fout << DecData[e] + DecData[e + 1] * 256 << "	";
			e = e + 2;
			fout << DecData[e] + DecData[e + 1] * 256 << "	";
		}
	}



}


void widget6::EEPROM_dumpRead(int f) {

	selectModel();
	load_EEPROM_Address();
	save_EEPROM_Address();

	QString filename = QFileDialog::getOpenFileName(this, tr("Open TXT"), "", tr("EEPROM File(*.txt)"));
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string name = code->fromUnicode(filename).data();

	ifstream in(name);

	if (!in.is_open())
	{
		QString strDisplay = "File open Failed";
		strDisplay += '\n';
		ui->log->insertPlainText(strDisplay);
	}

	int now = 0, e = 0;

	while (getline(in, src))
	{
		now = 0;
		int len = src.length() - 1;
		while (now < len) {
			if (e < 8192) {

				if ((now == 0 || src[now - 1] == ' ' || src[now - 1] == '	' || src[now - 1] == '\n') &&
					((src[now + 2] == ' '&&src[now + 5] == ' '&&src[now + 8] == ' ')
						|| (src[now + 2] == '	'&&src[now + 5] == '	'&&src[now + 8] == '	')
						|| (src[now + 2] == '\n'&&src[now + 5] == '\n'&&src[now + 8] == '\n'))) {

					for (int i = 0; i < 16; i++) {
						D[e][0] = src[now++];
						D[e][1] = src[now++];
						DecData[e] = hex2Dec(e);
						e++;
						now++;
					}

				}
				else now++;
			}
			else {

				switch (f)
				{
				case 0:
					pushData();
					break;
				case 1:
					findData();
					break;
				case 2:
					Item_Output();
					break;
				default:
					break;
				}

				e = 0;
			}
		}
	}
	QString strDisplay = "Dump Data Read finished";
	strDisplay += '\n';
	ui->log->insertPlainText(strDisplay);

}

void widget6::on_pushButton_find_clicked() {

	fuseId = ui->fuseId->document()->toPlainText().toLocal8Bit();
	barCode = ui->barCode->document()->toPlainText().toLocal8Bit();

	EEPROM_dumpRead(2);

}


void widget6::on_pushButton_dumpRead_clicked()
{
	selectModel();
	load_EEPROM_Address();
	save_EEPROM_Address();

	R_Gr_Golden51 = ui->R_Gr51->document()->toPlainText().toInt();
	B_Gr_Golden51 = ui->B_Gr51->document()->toPlainText().toInt();
	Gr_Gb_Golden51 = ui->Gr_Gb51->document()->toPlainText().toInt();

	R_Gr_Golden31 = ui->R_Gr31->document()->toPlainText().toInt();
	B_Gr_Golden31 = ui->B_Gr31->document()->toPlainText().toInt();
	Gr_Gb_Golden31 = ui->Gr_Gb31->document()->toPlainText().toInt();

	QString filename = QFileDialog::getOpenFileName(this, tr("Open TXT"), "", tr("EEPROM File(*.txt)"));
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string name = code->fromUnicode(filename).data();

	ifstream in(name);

	if (!in.is_open())
	{
		QString strDisplay = "File open Failed";
		strDisplay += '\n';
		ui->log->insertPlainText(strDisplay);
	}

	int now = 0, e = 0;
	int skip_line = 0;
	while (getline(in, src))
	{
		now = 0;
		int len = src.length() - 1;
		if (skip_line > 0) {

			for (int i = 0; i < 22; i++) {
				Fuse_ID[i] = src[15 + i];
			}

			while (now < len) {
				if (e < EEP_Size) {

					if ((now == 0 || src[now - 1] == ' ' || src[now - 1] == '	' || src[now - 1] == '\n') &&
						((src[now + 2] == ' '&&src[now + 5] == ' '&&src[now + 8] == ' ')
							|| (src[now + 2] == '	'&&src[now + 5] == '	'&&src[now + 8] == '	')
							|| (src[now + 2] == '\n'&&src[now + 5] == '\n'&&src[now + 8] == '\n'))) {

						for (int i = 0; i < 16; i++) {
							D[e][0] = src[now++];
							D[e][1] = src[now++];
							DecData[e] = hex2Dec(e);
							e++;
							now++;
						}

					}
					else now++;
				}
				else {
				//	Item_Output();
				//	e = 0;
				}
			}
			Item_Output();
			e = 0;

		}
		fout << endl;
		skip_line++;
	}
	QString strDisplay = "Dump Data Read finished";
	strDisplay += '\n';
	ui->log->insertPlainText(strDisplay);

}


void widget6::on_pushButton_golden_select_clicked() {

	fout << "FuseID	";

	if (ui->checkBox_AWB->isChecked()) {

	/*	sort(vecTest.begin(), vecTest.end(), comp_AWB_Weight);
		int i = 0;
		for (vector<EEPData>::iterator it = vecTest.begin(); it != vecTest.end(); it++) {
			it->awb_No = i++;
			it->total_No += it->awb_No;
		}*/
		fout << "R_Gr51	B_Gr51	Gr_Gb51	R_Gr31	B_Gr31	Gr_Gb31	";
	}	

	if (ui->checkBox_OIS->isChecked()) {

	/*	sort(vecTest.begin(), vecTest.end(), comp_OIS_Weight);
		int i = 0;
		for (vector<EEPData>::iterator it = vecTest.begin(); it != vecTest.end(); it++) {
			it->ois_No = i++;
			it->total_No += it->ois_No;
			if (it->ois_Weight < 250)
				it->total_No += it->ois_No;
		}*/
		fout << "OIS1_SR_X	OIS1_SR_Y	";
	}

	if (ui->checkBox_SFR->isChecked()) {

	/*	sort(vecTest.begin(), vecTest.end(), comp_SFR_Weight);
		int i = 0;
		for (vector<EEPData>::iterator it = vecTest.begin(); it != vecTest.end(); it++) {
			it->sfr_No = i++;
			it->total_No += it->sfr_No;
			if (it->sfr_Weight < -5)
				it->total_No += it->sfr_No;
		}*/
		fout << "INF_SFR	MAC_SFR	";
	}
	
	fout << endl;
	sort(vecTest.begin(), vecTest.end(), comp_Total_Weight);

	for (vector<EEPData>::iterator it = vecTest.begin(); it != vecTest.end(); it++) {


		int e = fuseIDStart;
		if (modelSelect != 1)
			e++;
		for (int i = 0; i < 9; i ++) {
			fout<<it->FuseID[2 * i]<<it->FuseID[2 * i + 1];
		}
		fout << "	";

		if (ui->checkBox_AWB->isChecked())
			fout << it->R_Gr51 << "	"<<it->B_Gr51 << "	"<<it->Gr_Gb51 << "	"<<it->R_Gr31 << "	" << it->B_Gr31 << "	" << it->Gr_Gb31 << "	";

		if (ui->checkBox_OIS->isChecked())
			fout << (float)(it->SR_X1)/10 << "	" << (float)(it->SR_Y1)/10 << "	";

		if (ui->checkBox_SFR->isChecked()) {
			
			for (int i = 0; i < 27; i++)
				fout << (float)(it->inf_SFR[i])/100 << "	";

			for (int i = 0; i < 9; i++)
				fout << (float)(it->mac_SFR[i])/100 << "	";
		
		}
		fout << endl;
	}

	fout << "Total Data Cnt=	" << cnt1 << endl;
	QString strDisplay = "Data Output finished";
	strDisplay += '\n';
	ui->log->insertPlainText(strDisplay);

	DisplayOutput();
	fout << endl;
	fout.close();

}


void widget6::CheckSum_Check(int checkSumStart, int checkSumEnd, int offset1, int offset2, QString item) {

	if (checkSumEnd > 0) {
		int tmp = 0, end = checkSumEnd, start = checkSumStart;
		if (modelSelect == 3 || modelSelect == 4) {
			end = checkSumEnd - offset1;
			start = start + offset2;
		}
		if (modelSelect == 8)	start++;
		if (modelSelect == 6)	end--;

		if (modelSelect == 5){	
			if(checkSumEnd- checkSumStart<4){
				end = checkSumEnd - offset1;
				start = start + offset2;
			}
		}

		for (int i = start; i < end; i++)
			tmp += DecData[i];

		fout << item.toStdString() << "	";
		fout << D[checkSumEnd][0] << D[checkSumEnd][1] << "	";

		tmp %= 255;
		if (tmp == 0)
			tmp = 255;
		if (offset1 < 0)
			tmp++;
		getHex(tmp);
		if (tmp % 255 != DecData[checkSumEnd] % 255) {

			QString strDisplay = item;
			strDisplay = strDisplay + " CheckSum in ";
			strDisplay += address2hex(checkSumEnd);
			strDisplay += " NG: 0x";
			strDisplay.append(D[checkSumEnd][0]);
			strDisplay.append(D[checkSumEnd][1]);
			strDisplay += ", real is 0x";
			strDisplay.append(chk[0]);
			strDisplay.append(chk[1]);

			DecData[checkSumEnd] = tmp;
			D[checkSumEnd][0] = chk[0];
			D[checkSumEnd][1] = chk[1];

			strDisplay += '\n';
			ui->log->insertPlainText(strDisplay);
		}

		fout << chk[0] << chk[1] << "	";
		if (modelSelect == 3|| modelSelect==4|| modelSelect == 6 || (checkSumStart>checkSumEnd&&offset2==0))
			fout << getFlag(checkSumEnd - 1) << "	" << endl;
		else
			fout << getFlag(checkSumStart) << "	" << endl;
	}
}


void basicInfo_Parse(int S,int E) {

	int e = S;
	if ( modelSelect == 1) {

		fout << "Module ID:	0x" << D[e + 1][0] << D[e + 1][1] << "	/SEMCO = 0x08" << endl;
		fout << "Sensor ID:	0x" << D[e + 3][0] << D[e + 3][1] << D[e + 4][0] << D[e + 4][1] << "	/IMX363=0x0363" << endl;
		fout << "IR filter ID:	0x" << D[e + 5][0] << D[e + 5][1] << "	/Blue Glass = 0x00, Film = 0x01" << endl;
		fout << "Lens ID:	0x" << D[e + 6][0] << D[e + 6][1] << "	/SEMCO Lens= 0x09" << endl;
		fout << "VCM ID:	0x" << D[e + 7][0] << D[e + 7][1] << "	/SEMCo OIS= 0x10" << endl;
		fout << "Gyro in Module:	0x" << D[e + 8][0] << D[e + 8][1] << "	/Gyro in the module = 0x01, Gyro not in the module = 0xFF" << endl;
		fout << "Driver IC ID:	0x" << D[e + 9][0] << D[e + 9][1] << "	/ONSEMI LC898217= 0X02" << endl;
		fout << "AP ID:	0x" << D[e + 10][0] << D[e + 10][1] << "	/MTK : 0x01, QCT : 0x02" << endl;
		fout << "VCM Hall sensor:	0x" << D[e + 11][0] << D[e + 11][1] << "	/Nanos hall sensor =  0x11, AKM hall sensor =  0x22" << endl;


		// Sensor Fuse ID
		fout << "Sensor Fuse ID:	";
		for (int i = 0; i < 9; i++) {
			fout << D[e + 0x0D + i][0] << D[e + 0x0D + i][1];
		}
		fout << endl;

		// version info
		fout << "AA type:	0x" << D[e + 0x1A][0] << D[e + 0x1A][1] << "	/Non-AA/AA type indicates Non-AA model or AA model. Non-AA=0x00, AA=0x01" << endl;
		fout << "FPC/PCB Version:	0x" << D[e + 0x1B][0] << D[e + 0x1B][1] << endl;
		fout << "OIS Housing Version:	0x" << D[e + 0x1C][0] << D[e + 0x1C][1] << endl;
		fout << "AWB calibration Version:	0x" << D[e + 0x1D][0] << D[e + 0x1D][1] << endl;
		fout << "LSC calibration Version:	0x" << D[e + 0x1E][0] << D[e + 0x1E][1] << endl;
		fout << "PDAF calibration Version:	0x" << D[e + 0x1F][0] << D[e + 0x1F][1] << endl;
		fout << "Production Factory:	0x" << D[e + 0x24][0] << D[e + 0x24][1] << "	/HQ = 0x01, STEM=0x10" << endl;
		fout << "Production Date:	";
		for (int i = 0; i < 5; i++) {
			fout << D[e + 0x25 + i][0] << D[e + 0x25 + i][1];
			if (i < 2)
				fout << "-";
			if (i == 3)
				fout << ":";
			if (i == 2)
				fout << " ";
		}
		fout << endl;
	}

	if (modelSelect == 3 || modelSelect == 4) {

		fout << "Vender ID:	0x" << D[e][0] << D[e][1] << "	//SEMCO = 0x03" << endl;
		e += 6;
		fout << "Sensor ID:	0x" << D[e][0] << D[e][1] << "	//S5K3M5=0x6A; IMX586=0x56; IMX481=0x57" << endl;
		e += 2;
		fout << "Lens ID:	0x" << D[e][0] << D[e][1] << "	//133LOH=0x2B; 482SOC=0x2A; 163SVB=0x2C" << endl;
		e += 2;
		fout << "VCM ID:	0x" << D[e][0] << D[e][1] << "	//S03600=0x4B; S02820=0x4A; SI3612=0x4C" << endl;
		e += 2;
		fout << "Module Ver:	0x" << D[e][0] << D[e][1] << "	//T0/EVT=0x00;Final=0x0F" << endl;

	}

	if (modelSelect == 5) {
		e++;
		fout << "Vender ID:	0x" << D[e][0] << D[e][1] << "	//SEMCO = 0x08" << endl;
		e ++;
		fout << "Platform ID:	0x" << D[e][0] << D[e][1] << "	//MTK=0x01; QC=0x02;" << endl;
		e+=3;
		fout << "Sensor ID:	0x" << D[e][0] << D[e][1] << D[e+1][0] << D[e+1][1] << "	//3M5SX05=0x30D5; " << endl;
		e += 2;
		fout << "Lens ID:	0x" << D[e][0] << D[e][1] << "	//SEMCO LENS=0x09" << endl;
		e += 1;
		fout << "VCM ID:	0x" << D[e][0] << D[e][1] << "	//SEMCO VCM=0x10" << endl;
		e += 1;
		fout << "Driver IC:	0x" << D[e][0] << D[e][1] << "	//SEMCO IC=0x08" << endl;
		e += 1;
		fout << "Model No.:	" << D[e][0] << D[e][1] << D[e+1][0] << D[e+1][1] << D[e+2][0] << D[e+2][1] << D[e+3][0] << D[e+3][1] << "	//2370983" << endl;
		e += 9;
		fout << "PCB Version:	0x" << D[e][0] << D[e][1] << endl;
		e += 1;
		fout << "Lens Version:	0x" << D[e][0] << D[e][1] << endl;
		e += 1;
		fout << "VCM Version:	0x" << D[e][0] << D[e][1] << endl;
		e += 1;
		fout << "OIS IC Version:	0x" << D[e][0] << D[e][1] << endl;

	}

	if (modelSelect > 5&& modelSelect<9) {
		if(modelSelect==8)
			e++;
		fout << "Vender ID:	0x" << D[e][0] << D[e][1] << "	//SEMCO = 0x03" << endl;
		e+=2;
		fout << "Production Date:	" << D[e+2][0] << D[e+2][1] << D[e + 3][0] << D[e + 3][1] << "-" <<DecData[e+1] << "-" << DecData[e] << endl;
		e += 4;
		fout << "Sensor ID:	0x" << D[e][0] << D[e][1] << D[e + 1][0] << D[e + 1][1] <<  endl;
		e += 2;
		fout << "Lens ID:	0x" << D[e][0] << D[e][1] <<  endl;
		e += 2;
		fout << "VCM ID:	0x" << D[e][0] << D[e][1] <<  endl;
		e += 2;
		fout << "Driver IC:	0x" << D[e][0] << D[e][1] << "	//SEMCO IC=0x08" << endl;
		e += 2;
		fout << "Module Version:	0x" << D[e][0] << D[e][1] << endl;
		e += 1;
		fout << "Mirror/Flip:	0x" << D[e][0] << D[e][1] << endl;

	}

	fout << endl;
}


void date_Parse(int S, int E) {

	fout << "Production Date:	";
	int e = S;

	if (modelSelect < 3 || modelSelect > 5) {
		fout << (int)DecData[e] << '-' << (int)DecData[e + 1] << '-' << (int)DecData[e + 2];
		e += 3;
		if (e < E) {
			fout << '	' << (int)DecData[e] << ':' << (int)DecData[e + 1];
		}
	}

	if (modelSelect >= 3 && modelSelect <= 4) {
		fout << (int)DecData[e + 3] << (int)DecData[e + 2] << '-' << (int)DecData[e + 1] << '-' << (int)DecData[e];
	}
	fout << endl;

}


void fuse_Parse(int S, int E) {

	if (fuseIDStart > 0) {
		int e = S + 1, len =9;

		if (modelSelect == 6) {
			e--;
		}
		fout << "Sensor Fuse ID:	";
		for (int i = 0; i < len; i++) {
			fout << D[e + i][0] << D[e + i][1];
		}
		fout << endl;
		fout << endl;
	}
}


void QR_Parse(int S, int E) {
	int e = S + 1;
	int qrl = 12;
	if (modelSelect == 3) {
		e--;
		qrl = 17;
	}
	if(modelSelect == 8|| modelSelect == 6) {
		qrl = 19;
	}
	fout << "QR Code:	";
	for (int i = 0; i < qrl; i++) {
		if ((char)DecData[e + i] != 0)
			fout << (char)DecData[e + i];
	}
	fout << endl; fout << endl;
}


void OIS_Hall_Parse(int S, int E) {
	
	fout << "-------OIS Hall Cal------" << endl;
	int e = S; unsigned int tmp = 0;
	float* fp = (float*)&tmp;

	if (modelSelect < 3) {
		fout << "Hall Offset X:	" << hex2Dec(e + 1) * 256 + hex2Dec(e + 2) << endl;
		fout << "Hall Offset Y:	" << hex2Dec(e + 3) * 256 + hex2Dec(e + 4) << endl;
		fout << "Hall Center X:	" << hex2Dec(e + 5) * 256 + hex2Dec(e + 6) << endl;
		fout << "Hall Center Y:	" << hex2Dec(e + 7) * 256 + hex2Dec(e + 8) << endl;
		fout << "Hall Bias X:	" << hex2Dec(e + 9) << endl;
		fout << "Hall Bias Y:	" << hex2Dec(e + 0x0A) << endl;

		e = e + 0x0B;
		if (e < oisFW) {
			fout << "Hall Gain X:	" << hex2Dec(e) << endl;
			e++;
			fout << "Hall Gain Y:	" << hex2Dec(e) << endl;
			e++;
			fout << "Hall Max X:	" << hex2Dec(e) * 256 + hex2Dec(e + 1) << endl;
			e += 2;
			fout << "Hall Max Y:	" << hex2Dec(e) * 256 + hex2Dec(e + 1) << endl;
			e += 2;
			fout << "Hall Min X:	" << hex2Dec(e) * 256 + hex2Dec(e + 1) << endl;
			e += 2;
			fout << "Hall Min Y:	" << hex2Dec(e) * 256 + hex2Dec(e + 1) << endl;
		}

		fout << "OIS Firmware Bin version:	";
		e = oisFW;
		tmp = 0;
		for (int i = 0; i < 4; i++) {
			tmp *= 256;
			tmp += hex2Dec(e + i);
			fout << D[e + i][0] << D[e + i][1];
		}
		fout << endl;
		fout << "OIS Firmware DEC version:	" << tmp << endl;
	}

	if (modelSelect == 3 || modelSelect == 4) {
	
		fout << "OIS Driver IC:	0x" << D[e][0] << D[e][1] << endl;
		e = e + 2;
		tmp = 0;
		for (int i = 3; i >= 0; i--) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
		e = e + 2;
		//	float* fp = (float*)&tmp;
		
		fout << "OIS Hall X max Before:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall X min Before:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall X max After:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall X min After:	";
		short_Out(e, false);
		e = e + 4;

		fout << "OIS Hall Y max Before:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall Y min Before:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall Y max After:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall Y min After:	";
		short_Out(e, false);
		e = e + 4;

		fout << "OIS Hall Bias X :	";
		short_Out(e, false);
		e = e + 3;
		fout << "OIS Hall Offset X :	";
		char_Out(e);
		e = e + 5;

		fout << "OIS Hall Bias Y :	";
		short_Out(e, false);
		e = e + 3;
		fout << "OIS Hall Offset Y :	";
		char_Out(e);
		e = e + 5;

		fout << "Loop Gain X :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Loop Gain Y :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Neutral Center X :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Neutral Center Y :	";
		short_Out(e, false);
		e = e + 10;

		fout << "Gyro Offset X :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Gyro Offset Y :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Gyro Gain X :	";
		gyro_Out(e, false);
		e = e + 4;

		fout << "Gyro Gain Y :	";
		gyro_Out(e, false);

	}

	if (modelSelect == 5) {
		e = S;
		fout << "Gyro Offset X:	" << hex2Dec(e + 1) * 256 + hex2Dec(e + 2) << endl;
		fout << "Gyro Offset Y:	" << hex2Dec(e + 3) * 256 + hex2Dec(e + 4) << endl;
		e += 5;

		tmp = 0;
		for (int i = 0; i < 4; i++) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
		//	float* fp = (float*)&tmp;
		fout << "Gyro Gain X:	" << *fp << endl;
		e += 4;
		tmp = 0;
		for (int i = 0; i < 4; i++) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
		//	float* fp = (float*)&tmp;
		fout << "Gyro Gain Y:	" << *fp << endl;
		e += 4;
		fout << "Mechanical Center_X:	" << DecData[e] * 256 + DecData[e + 1] << endl;
		fout << "Mechanical Center_Y:	" << DecData[e + 2] * 256 + DecData[e + 3] << endl;
		e += 4;
		fout << "Hall Bias_X:	" << hex2Dec(e) << endl;
		fout << "Hall Bias_Y:	" << hex2Dec(e + 1)<< endl;
		e += 2;
		fout << "Loop Gain_X:	0x" << D[e + 3][0]<< D[e + 3][1] << endl;
		e += 4;
		fout << "Loop Gain_Y:	0x" << D[e + 3][0] << D[e + 3][1] << endl;
		e += 4;
		fout << "Hall_offset_X:	" << DecData[e] * 256 + DecData[e + 1] << endl;
		fout << "Hall_offset_Y:	" << DecData[e + 2] * 256 + DecData[e + 3] << endl;
		e += 4;
		fout << "Hall_Max_X:	" << DecData[e] * 256 + DecData[e + 1] << endl;
		fout << "Hall_Max_Y:	" << DecData[e + 2] * 256 + DecData[e + 3] << endl;
		e += 4;
		fout << "Hall_Min_X:	" << DecData[e] * 256 + DecData[e + 1] << endl;
		fout << "Hall_Min_Y:	" << DecData[e + 2] * 256 + DecData[e + 3] << endl;
		e += 4;
		fout << "SR_X:	" << DecData[e] + (float)(DecData[e + 1])/100 << endl;
		fout << "SR_Y:	" << DecData[e + 2] + (float)(DecData[e + 3]) /100 << endl;

	}

	if (modelSelect == 6) {

		tmp = 0;
		for (int i = 3; i >= 0; i--) {
			tmp *= 256;
			tmp += DecData[e + i];
		}
		e = e + 2;
		//	float* fp = (float*)&tmp;

		fout << "OIS Hall X max Before:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall X min Before:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall X max After:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall X min After:	";
		short_Out(e, false);
		e = e + 4;

		fout << "OIS Hall Y max Before:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall Y min Before:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall Y max After:	";
		short_Out(e, false);
		e = e + 4;
		fout << "OIS Hall Y min After:	";
		short_Out(e, false);
		e = e + 4;

		fout << "OIS Hall Bias X :	";
		short_Out(e, false);
		e = e + 3;
		fout << "OIS Hall Offset X :	";
		char_Out(e);
		e = e + 5;

		fout << "OIS Hall Bias Y :	";
		short_Out(e, false);
		e = e + 3;
		fout << "OIS Hall Offset Y :	";
		char_Out(e);
		e = e + 5;

		fout << "Loop Gain X :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Loop Gain Y :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Neutral Center X :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Neutral Center Y :	";
		short_Out(e, false);
		e = e + 6;

		fout << "Gyro Offset X :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Gyro Offset Y :	";
		short_Out(e, false);
		e = e + 4;

		fout << "Gyro Gain X :	";
		gyro_Out(e, false);
		e = e + 4;

		fout << "Gyro Gain Y :	";
		gyro_Out(e, false);

		e = e + 4;
		fout << "SR X:	" << (float)(256 * DecData[e] + DecData[e + 1]) / 10 << endl;
		e += 2;
		fout << "SR Y:	" << (float)(256 * DecData[e] + DecData[e + 1]) / 10 << endl;
	}

	fout << endl;
}


void drift_Parse(int S, int E) {
	//AF Drift Compensation Data:
	fout << "--------AF Drift Compensation Data-------" << endl;
	int e = S;

	if (modelSelect != 3 && modelSelect != 4) {

		for (int i = 0; i < 9; i++) {
			fout << "X_Position_" << to_string(i) << ":	";
			short_Out(e, false);
			e += 2;
		}
		fout << endl;
		for (int i = 0; i < 9; i++) {
			fout << "Y_Position_" << to_string(i) << ":	";
			short_Out(e, false);
			e += 2;
		}
	}

	///////////////~~~~~~~~~~~~~~~~OPPO Guide~~~~~~~~~~~~~~~~~~
	if (modelSelect == 3 || modelSelect == 4) {

		for (int i = 0; i < 9; i++) {
			fout << "X_Position_" << to_string(i) << ":	";
			int_Out(e, false);
			e += 4;
		}
		fout << endl;
		for (int i = 0; i < 9; i++) {
			fout << "Y_Position_" << to_string(i) << ":	";
			int_Out(e, false);
			e += 4;
		}
	}
	fout << endl;
}


void af_Parse(int S, int E) {

	fout << "-------AF CAL Data------" << endl;
	int e = S;
	if (modelSelect == 1 || modelSelect == 2 || modelSelect == 5) {
		fout << "~~~ Face Forward AF ~~~" << endl;
		e += 1;
		if (modelSelect == 2) {
			e += 2;
			fout << "LIN MIN:	" << (hex2Dec(e) & 0x0F) * 256 + hex2Dec(e + 1) << endl;
			e += 2;
			fout << "LIN MAX:	" << (hex2Dec(e) & 0x0F) * 256 + hex2Dec(e + 1) << endl;
			e += 2;
		}

		fout << "AF Code1:	" << (hex2Dec(e) & 0x03) * 256 + hex2Dec(e + 1) << endl;
		e += 2;
		fout << "AF Code2:	" << (hex2Dec(e) & 0x03) * 256 + hex2Dec(e + 1) << endl;
		e += 2;
		

		// Sensor Thermal Data

		int tmp = hex2Dec(e);
		if (tmp > 129 && tmp < 236)
			tmp = -20;
		else if (tmp >= 236)
			tmp = 256 - tmp;
		fout << "Sensor thermal(Inf):	" << tmp << endl;
		e += 1;
		tmp = hex2Dec(e);
		if (tmp > 129 && tmp < 236)
			tmp = -20;
		else if (tmp >= 236)
			tmp = 256 - tmp;
		fout << "Sensor thermal(Mac):	" << tmp << endl;
	}

	if (modelSelect == 8) {
		e++;
		fout << "Mac:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e += 2;
		fout << "Inf:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e += 2;
		fout << "50cm:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e += 2;
		fout << "100cm:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e += 2;
		fout << "Sensor thermal(Inf):	" << (int)DecData[e] << endl;
		e += 1;
		fout << "Sensor thermal(Mac):	" << (int)DecData[e] << endl;
	}

	if (modelSelect == 6) {
		fout << "Mac:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		fout << "Sensor thermal(Mac):	" << (int)DecData[e+2] << endl;
		e += 4;
		fout << "Inf:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		fout << "Sensor thermal(Inf):	" << (int)DecData[e+2] << endl;
		e += 4;
		fout << "50cm:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e += 4;
		fout << "100cm:	" << DecData[e] + DecData[e + 1] * 256 << endl;
	}

	if (modelSelect == 3 || modelSelect == 4) {
		fout << "AF Start DAC:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e = e + 2;
		fout << "AF MAC DAC:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e = e + 2;
		fout << "AF INF DAC:	" << DecData[e] + DecData[e + 1] * 256 << endl;

		fout << "~~~ AF Hall, 0x13, LC898217  ~~~" << endl;
		e = AFhallStart;
		if (E > 0x1000)
			e += 0x1000;
		fout << "AF Driver IC:	0x" << D[e][0] << D[e][1] << endl;
		e = e + 2;
		fout << "AF Hall Max:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e = e + 2;
		fout << "AF Hall Min:	" << DecData[e] + DecData[e + 1] * 256 << endl;
		e = e + 1;
		if (modelSelect == 3){
			fout << "AF Hall_Offset:	" << (int)DecData[e] << endl;
			e = e + 1;
			fout << "AF Hall_BIAS:	" << (int)DecData[e] << endl;
		}
	}
	fout << endl;
}


void af_hall_Parse(int S, int E) {

	fout << "-------AF CAL Data------" << endl;
	int e = S+1;
	fout << "Hall_Max:	" << DecData[e] + DecData[e + 1] * 256 << endl;
	e += 2;
	fout << "Hall_Min:	" << DecData[e] + DecData[e + 1] * 256 << endl;
	fout << endl;
}


void Oppo_AWB_Parse(int S, int E, string str) {
	int e = S;

	fout << "Main_Red :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Main_Gr :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Main_Gb :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Main_Blue :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << str << "Red :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << str << "Gr :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << str << "Gb :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << str << "Blue :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;

	if (modelSelect > 6 && modelSelect < 9) {
		e = e + 2;
		fout << str << "light source R/G:	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
		e = e + 2;
		fout << str << "light source B/G:	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	}
	fout << endl;
}

void triple_AWB_Parse(int S, int E, string str) {
	int e = S;

	fout << str << endl;
	fout << "Main_Red :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Main_Gr :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Main_Gb :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Main_Blue :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout  << "Wide_Red :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Wide_Gr :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Wide_Gb :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Wide_Blue :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout << "Tele_Red :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout  << "Tele_Gr :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout  << "Tele_Gb :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;
	e = e + 2;
	fout  << "Tele_Blue :	" << (float)(hex2Dec(e) + hex2Dec(e + 1) * 256) << endl;

	fout << endl;
}

void awb_Parse(int S, int E){

	int e = awbStart + 1;
	if (modelSelect < 3 || modelSelect==5) {
		fout << "~~~5100K AWB Cal Data:" << endl;
		fout << "Gain R/Gr :	" << (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024 << endl;
		fout << "Gain B/Gr :	" << (float)(hex2Dec(e + 2) * 256 + hex2Dec(e + 3)) / 1024 << endl;
		fout << "Gain Gr/Gb :	" << (float)(hex2Dec(e + 4) * 256 + hex2Dec(e + 5)) / 1024 << endl;
		fout << "Golden Sample,Gain R/Gr :	" << (float)(hex2Dec(e + 6) * 256 + hex2Dec(e + 7)) / 1024 << endl;
		fout << "Golden Sample,Gain B/Gr :	" << (float)(hex2Dec(e + 8) * 256 + hex2Dec(e + 9)) / 1024 << endl;
		fout << "Golden Sample,Gain Gr/Gb :	" << (float)(hex2Dec(e + 0xA) * 256 + hex2Dec(e + 0xB)) / 1024 << endl;
		e += 12;
		if (modelSelect == 5) {		
			fout << "5100k light source R/G calibration :	" << (float)(hex2Dec(e)*256 + hex2Dec(e + 1)) << endl;
			e += 2;
			fout << "5100k light source B/G calibration :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) << endl;
			e += 2;
		}
		fout << endl;
		fout << "~~~3100K AWB Cal Data:" << endl;
		fout << "Gain R/Gr :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) / 1024 << endl;
		e += 2;
		fout << "Gain B/Gr :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) / 1024 << endl;
		e += 2;
		fout << "Gain Gr/Gb :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) / 1024 << endl;
		e += 2;
		fout << "Golden Sample,Gain R/Gr :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) / 1024 << endl;
		e += 2;
		fout << "Golden Sample,Gain B/Gr :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) / 1024 << endl;
		e += 2;
		fout << "Golden Sample,Gain Gr/Gb :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) / 1024 << endl;
		e += 2;
		if (modelSelect == 5) {
			fout << "3100k light source R/G calibration :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) << endl;
			e += 2;
			fout << "3100k light source B/G calibration :	" << (float)(hex2Dec(e) * 256 + hex2Dec(e + 1)) << endl;
		}

	}

	if (modelSelect == 3 || modelSelect == 4 || modelSelect == 8 || modelSelect == 6) {

		if (modelSelect == 6)e--;

		fout << "~~~5100K AWB Cal Data:" << endl;
		Oppo_AWB_Parse(e, 0, "Golden_");

		e += 20;
		if (modelSelect <6)
			e = awbStart4000 + E;

		fout << "~~~4000K AWB Cal Data:" << endl;
		Oppo_AWB_Parse(e, 0, "Golden_");

		e += 20;
		if (modelSelect <6)
			e = awbStart3100 + E;

		fout << "~~~3100K AWB Cal Data:" << endl;
		Oppo_AWB_Parse(e, 0, "Golden_");

		if (modelSelect == 3 || modelSelect == 4) {
			e = awbLightStart + E;
			fout << "5100k light source R/G calibration :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) << endl;
			e = e + 2;
			fout << "5100k light source B/G calibration :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) << endl;
			e = awbLightStart4000 + E;
			fout << "4000k light source R/G calibration :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) << endl;
			e = e + 2;
			fout << "4000k light source B/G calibration :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) << endl;
			e = awbLightStart3100 + E;
			fout << "3100k light source R/G calibration :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) << endl;
			e = e + 2;
			fout << "3100k light source B/G calibration :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) << endl;
		}
	}

	if (modelSelect == 6) {

		triple_AWB_Parse(dualAWBStart, 0, "Triple AWB 5100K:	");
		triple_AWB_Parse(dualAWBStart+24, 0, "Triple AWB 4000K:	");
		triple_AWB_Parse(dualAWBStart+48, 0, "Triple AWB 3100K:	");

	}

	fout << endl;
}


void gain_Map_Parse(int S, int E) {

	fout << "-------PDAF CAL Data------" << endl;

	if (modelSelect == 1 || modelSelect == 2 || modelSelect == 5) {
		int e = S + 1;
		fout << "PDAF Version:	" << DecData[e + 0] * 256 + DecData[e + 1] << endl;
		fout << "Gain map Width:	" << DecData[e + 2] * 256 + DecData[e + 3] << endl;
		fout << "Gain map Height:	" << DecData[e + 4] * 256 + DecData[e + 5] << endl;

		e = e + 6;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				PDgainLeft[i][j] = 256 * DecData[e] + DecData[e + 1];
				e += 2;
			}

		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				PDgainRight[i][j] = 256 * DecData[e] + DecData[e + 1];
				e += 2;
			}

	}

	if (modelSelect == 3 || modelSelect == 4 || modelSelect == 8) {
		int e = S;
		if (modelSelect == 8)
			e++;

		fout << "PDAF Version:	" << DecData[e + 0] + DecData[e + 1] * 256 << endl;
		fout << "Gain map Width:	" << DecData[e + 2] + DecData[e + 3] * 256 << endl;
		fout << "Gain map Height:	" << DecData[e + 4] + DecData[e + 5] * 256 << endl;
		e = e + 6;

		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				PDgainLeft[i][j] = DecData[e] + DecData[e + 1] * 256;
				e += 2;
			}

		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				PDgainRight[i][j] = DecData[e] + DecData[e + 1] * 256;
				e += 2;
			}
	}

	if (modelSelect == 6) {
		int e = S;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				PDgainLeft[i][j] = DecData[e] + DecData[e + 1] * 256;
				e += 2;
			}

		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				PDgainRight[i][j] = DecData[e] + DecData[e + 1] * 256;
				e += 2;
			}
	}

	fout << "~~~Left Gain map:" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			fout << PDgainLeft[i][j] << "	";
		}
		fout << endl;
	}

	fout << "~~~Right Gain map:" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			fout << PDgainRight[i][j] << "	";
		}
		fout << endl;
	}
	fout << endl;

}


void FocusMap_Parse(int S, int E) {

	if (S>0) {
		int e = S + 1;
		fout << "~~~~~ LSI FocusMap ~~~~~:	" << endl;
		fout << "FocusMap Version:	" << DecData[e + 0] * 256 + DecData[e + 1] << endl;
		fout << "FocusMap Width:	" << DecData[e + 2] * 256 + DecData[e + 3] << endl;
		fout << "FocusMap Height:	" << DecData[e + 4] * 256 + DecData[e + 5] << endl;	

		e = e + 6;
		for (int i = 0; i < 6; i++) 
			for (int j = 0; j < 8; j++) {
				Foucus_Map[i][j] = 256 * DecData[e] + DecData[e + 1];
				e += 2;
			}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
				fout << DCC[i][j] << "	";
			}
			fout << endl;
		}
		fout << endl;
	}
	fout << endl;

}


void DCC_Parse(int S, int E) {
	fout << "~~~DCC Data map:" << endl;
	int e = S;
	if (modelSelect == 1 || modelSelect == 2 || modelSelect == 5) {

		if (E > 0)
			e = DCCStart + 1;
		fout << "DCC QC Version:	" << DecData[e + 0] * 256 + DecData[e + 1] << endl;
		fout << "DCC map Width:	" << DecData[e + 2] * 256 + DecData[e + 3] << endl;
		fout << "DCC map Height:	" << DecData[e + 4] * 256 + DecData[e + 5] << endl;

		//DCC Data map:
		e = e + 6;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
				DCC[i][j] = 256 * DecData[e] + DecData[e + 1];
				e += 2;
			}
		}
	}

	if (modelSelect == 3 || modelSelect == 4 || modelSelect == 8) {

		if (modelSelect == 8)
			e++;

		fout << "DCC QC Version:	" << DecData[e + 0] + DecData[e + 1] * 256 << endl;
		fout << "DCC map Width:	" << DecData[e + 2] + DecData[e + 3] * 256 << endl;
		fout << "DCC map Height:	" << DecData[e + 4] + DecData[e + 5] * 256 << endl;

		//DCC Data map:
		e = e + 6;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
				DCC[i][j] = DecData[e] + 256 * DecData[e + 1];
				e += 2;
			}
		}
	}

	if ( modelSelect == 6) {

		for (int i = 0; i < 6; i++) 
			for (int j = 0; j < 8; j++) {
				DCC[i][j] = DecData[e] + 256 * DecData[e + 1];
				e += 2;		
		}
	}

	fout << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			fout << DCC[i][j] << "	";
		}
		fout << endl;
	}
	fout << endl;

}


void QC_Five_DCC_Parse(int S, int E) {

	int e = S;

	fout << "DCC Version:	0x" << D[e+1][0] << D[e + 1][1] << D[e][0] << D[e][1] << endl;
	e += 2;
	fout << "DCC Type:	0x" << D[e + 1][0] << D[e + 1][1] << D[e][0] << D[e][1] << endl;
	e += 2;
	fout << "Map Width:	" << DecData[e] + DecData[e + 1] * 256 << endl;
	e += 2;
	fout << "Map Height:	" << DecData[e] + DecData[e + 1] * 256 << endl;
	e += 2;
	fout << "DCC Qformat:	0x" << D[e + 1][0] << D[e + 1][1] << D[e][0] << D[e][1] << endl;
	e += 2;
	fout << "DCC Width:	" << DecData[e] + DecData[e + 1] * 256 << endl;
	e += 2;
	fout << "DCC Height:	" << DecData[e] + DecData[e + 1] * 256 << endl;
	e += 2;
	fout << "Num_Body_in_use:	" << DecData[e] + DecData[e + 1] * 256 << endl;
	//DCC Data map:
	
	gain_Map_Parse(S + 20, E);
	DCC_Parse(S + 20+888, E);
	gain_Map_Parse(S + 20 + 988, E);
	DCC_Parse(S + 20 + 988+ 888, E);
	gain_Map_Parse(S+20 + 988 * 2, E);
	DCC_Parse(S + 20 + 988 * 2+ 888, E);
	gain_Map_Parse(S + 2984, E);
	DCC_Parse(S + 2984 + 888, E);
	gain_Map_Parse(S + 3972, E);
	DCC_Parse(S + 3972 + 888, E);

	fout << endl;

}


void sony_LRC_Parse(int S, int E) {

	fout << "~~~Sony LRC Data map:" << endl;
	int e = S;
	if (modelSelect == 8) 
		e++;
	if (modelSelect == 3 || modelSelect == 8){
		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 16; j++) {
				LRC[0][i][j] = DecData[e];
				e++;
			}

		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 16; j++) {
				LRC[1][i][j] = DecData[e];
				e++;
			}

		fout << endl;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 16; j++) {
				fout << LRC[0][i][j] << "	";
			}
			fout << endl;
		}
		fout << endl;

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 16; j++) {
				fout << LRC[1][i][j] << "	";
			}
			fout << endl;
		}
	}
	if (modelSelect == 4) {
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 10; j++) {
				LRC[0][i][j] = DecData[e];
				e++;
			}

		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 10; j++) {
				LRC[1][i][j] = DecData[e];
				e++;
			}

		fout << endl;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 10; j++) {
				fout << LRC[0][i][j] << "	";
			}
			fout << endl;
		}
		fout << endl;

		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 10; j++) {
				fout << LRC[1][i][j] << "	";
			}
			fout << endl;
		}
	}
	fout << endl;

}


void sony_DCC_Parse(int S, int E) {

	fout << "~~~Sony DCC Data map:" << endl;
	int e = S;
	if (modelSelect == 8)
		e++;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			DCC_Sony[i][j] = DecData[e] + 256 * DecData[e + 1];
			e += 2;
		}
	}

	fout << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			fout << DCC_Sony[i][j] << "	";
		}
		fout << endl;
	}
	fout << endl;

}


void AEC_Parse(int S, int E) {

	if (AECStart > 0) {

		fout << "--------AEC Cal Data-------" << endl;
		int e = AECStart + 1;

		if (modelSelect == 1 || modelSelect == 2 ) {

			//AEC Cal Data:	
			fout << "Brightness_Ratio:	" << (float)(256 * DecData[e] + DecData[e + 1]) / 1024 << endl;
			e += 2;
			fout << "Ref_Sub_Gain:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;
			fout << "Ref_Sub_Linecount:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;
			fout << "Ref_Main_Gain:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;
			fout << "Ref_Main_Linecount:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;
			fout << "Ref_Color_temp:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;

			unsigned int tmp = 0;
			for (int i = 0; i < 4; i++) {
				tmp *= 256;
				tmp += DecData[e + i];
			}
			fout << "Ref_SUB_Shutter :	" << tmp << endl;
			e += 4;
			fout << "Ref_Sub_line length pclk:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;

			tmp = 0;
			for (int i = 0; i < 4; i++) {
				tmp *= 256;
				tmp += DecData[e + i];
			}
			fout << "Ref_Sub_pclk:	" << tmp << endl;
			e += 4;

			tmp = 0;
			for (int i = 0; i < 4; i++) {
				tmp *= 256;
				tmp += DecData[e + i];
			}
			fout << "Ref_Main_Shutter :	" << tmp << endl;
			e += 4;

			fout << "Ref_Main_line length pclk:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;

			tmp = 0;
			for (int i = 0; i < 4; i++) {
				tmp *= 256;
				tmp += DecData[e + i];
			}
			fout << "Ref_Main_pclk:	" << tmp << endl;
			e += 4;
		}

		if (modelSelect == 8|| modelSelect == 6) {
			fout << "Brightness_Ratio:	" << (float)( DecData[e] + 256 * DecData[e + 1]) / 1024 << endl;
			e += 2;
			fout << "Ref_Sub_Gain:	" << DecData[e] + 256 * DecData[e + 1] << endl;
			e += 2;
			fout << "ref_Sub_exposure_time_ms:	" << DecData[e] + 256 * DecData[e + 1] << endl;
			e += 2;
			fout << "Ref_Main_Gain:	" << DecData[e] + 256 * DecData[e + 1] << endl;
			e += 2;
			fout << "ref_Main_exposure_time_ms:	" << DecData[e] + 256 * DecData[e + 1] << endl;
		}
	}

}


void dual_Cal_Parse(int S, int E) {

	unsigned int Dou[2] = { 0,0 };
	double* dp = (double*)Dou;
	int e = S;

	if (modelSelect == 8)
		e++;

	if (modelSelect < 3 || modelSelect == 8){
		S++;
		for (int p = 0; p < 2; p++) {
			for (int i = 0; i < 4; i++) {
				Dou[p] *= 256;
				Dou[p] += DecData[e + i];
			}
			e += 4;
		}
		fout << "Pan:	" << *dp << endl;

		for (int p = 0; p < 2; p++) {
			Dou[p] = 0;
			for (int i = 0; i < 4; i++) {
				Dou[p] *= 256;
				Dou[p] += DecData[e + i];
			}
			e += 4;
		}
		fout << "Roll:	" << *dp << endl;

		for (int p = 0; p < 2; p++) {
			Dou[p] = 0;
			for (int i = 0; i < 4; i++) {
				Dou[p] *= 256;
				Dou[p] += DecData[e + i];
			}
			e += 4;
		}
		fout << "Tilt:	" << *dp << endl;	

		fout << "AF_calibration_code:	" << 256 * DecData[e] + DecData[e + 1] << endl;
	}

	if (modelSelect ==3 || modelSelect == 4) {
		e = e + 7;
		for (int p = 1; p >=0; p--) {
			for (int i = 0; i < 4; i++) {
				Dou[p] *= 256;
				Dou[p] += DecData[e--];
			}
		}
		fout << "Pan:	" << *dp << endl;
		e = S + 15;
		for (int p = 1; p >= 0; p--) {
			Dou[p] = 0;
			for (int i = 0; i < 4; i++) {
				Dou[p] *= 256;
				Dou[p] += DecData[e--];
			}
		}
		fout << "Roll:	" << *dp << endl;
		e = S + 23;
		for (int p = 1; p >= 0; p--) {
			Dou[p] = 0;
			for (int i = 0; i < 4; i++) {
				Dou[p] *= 256;
				Dou[p] += DecData[e --];
			}
		}
		fout << "Tilt:	" << *dp << endl;

	}
}


void SFR_display(int group, int e) {

	fout << "SFR Garde:	0x" << D[e][0] << D[e][1] << endl;
	e++;

	fout << "Center_1	"; 
	int g = group - 1;
	if (modelSelect >2) {
		fout << "Center_2	";
		g--;
	}

	for (int i = 0; i < g; i++) {
		fout << "Group_" << i / 8 + 1 << "_" << i % 8 + 1 << "	";
	}
	fout << endl;

	for (int i = 0; i < group; i++) {
		fout << "0.";
		if (DecData[e + i] < 10)
			fout << "0";
		fout << checkFF(DecData[e + i]) << "	";
	}
	fout << endl;


}


void Test_Date_display(int e, string str) {

	if (e > 0) {
		fout << str<< "	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
		fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
	}

}


void OIS_Parse(int S, int E ,string s) {
	if (S > 0) {
		fout << "-------" << s << "------" << endl;
		int e = S;
		if (modelSelect != 3){
			e++;
			fout << "Suppression Ratio X:	" << (float)(256 * DecData[e] + DecData[e + 1]) / 10 << endl;
			e += 2;
			fout << "Suppression Ratio Y:	" << (float)(256 * DecData[e] + DecData[e + 1]) / 10 << endl;
		}
		else {
			fout << "Suppression Ratio X:	" <<  (int)DecData[e] <<"."<< (int)DecData[e + 1] << endl;
			e += 2;
			fout << "Suppression Ratio Y:	" << (int)DecData[e] <<"."<< (int)DecData[e + 1] << endl;


		}
	}
}


void LSI_AF_Parse(int S, int E, string s) {
	if (S > 0) {
		int e = S;
		fout << "LSI_AF Infinity Distance:	" << 256 * DecData[e+1] + DecData[e] << endl;
		e += 4;
		fout << "LSI_AF Infinity Position:	" << 256 * DecData[e+1] + DecData[e] << endl;
		e += 4;
		fout << "LSI_AF Middle Distance:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 4;
		fout << "LSI_AF Middle Position:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 4;
		fout << "LSI_AF Macro Distance:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 4;
		fout << "LSI_AF Macro Position:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 4;
		fout << "LSI_AF Focal length:	" << 0x1000000 * DecData[e + 3] + 0x10000 * DecData[e + 2]+ 256 * DecData[e + 1] + DecData[e] << endl;


	}
}


void LSI_OIS_Parse(int S, int E, string s) {
	if (S > 0) {
		unsigned int tmp = 0;
		float* fp = (float*)&tmp;
		int e = S;
		fout << "------- LSI_OIS -------" << endl;
		fout << "Gyro Offset X value:	"; 
		short_Out(e,0) ;
		e += 2;
		fout << "Gyro Offset Y value:	";
		short_Out(e, 0);
		e += 2;

		tmp = 0;
		for (int i = 3; i >=0; i--)
			tmp = tmp * 256 + DecData[e + i];
		fout << "Gyro Gain X value:	" << *fp << endl;
		e += 4;

		tmp = 0;
		for (int i = 3; i >= 0; i--)
			tmp = tmp * 256 + DecData[e + i];
		fout << "Gyro Gain Y value:	" << *fp << endl;
		e += 4;

		fout << "X Mechanical Center:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 2;
		fout << "Y Mechanical Center:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 2;
		fout << "X Hall Bias:	";
		char_Out(e);
		e++;
		fout << "Y Hall Bias:	";
		char_Out(e);
		e++;
		fout << "Hall Gain X value:	0x";
		for (int i = 3; i >= 0; i--)
			fout << D[e + i][0] << D[e + i][1];
		e += 4;
		fout << "Hall Gain Y value:	0x";
		for (int i = 3; i >= 0; i--)
			fout << D[e + i][0] << D[e + i][1];
		e += 4;
		fout << "X Hall Offset:	";
		short_Out(e, 0);
		e += 2;
		fout << "Y Hall Offset:	";
		short_Out(e, 0);
		e += 2;
		fout << "Hall X Max Value:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 2;
		fout << "Hall Y Max Value:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 2;
		fout << "Hall X Min Value:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 2;
		fout << "Hall Y Min Value:	" << 256 * DecData[e + 1] + DecData[e] << endl;
		e += 2;
		fout << "Suppression Ratio X1:	" << DecData[e ] + DecData[e+1]/100 << endl;
		e += 2;
		fout << "Suppression Ratio Y1:	" << DecData[e] + DecData[e + 1] / 100 << endl;
	}
}


void widget6::on_pushButton_parser_clicked()
{

	src = ui->input->document()->toPlainText().toLocal8Bit();
	memset(DecData, 0, sizeof(DecData));

	int now = 0, e = 0, len = src.length() - 1,TCSum=0;
	unsigned int tmp = 0;
	float* fp = (float*)&tmp;
	ui->output->clear();

	//Load EEPROM_Map.ini
	selectModel();

	TCHAR lpTexts[25];
	string temp_model = to_string(modelSelect);
	GetPrivateProfileString(TEXT("Model_List"), CA2CT(temp_model.c_str()), TEXT("EEPROM_Map_V1_797.ini"), lpTexts, 25, TEXT(".\\Setting\\EEPROM_Tool_Setting.ini"));
	EEPROM_Map = CT2A(lpTexts);

	string str1= ".\\Setting\\";
	EEPROM_Map = str1+ EEPROM_Map;
	
	save_EEPROM_Setting();

	/////////////////////

		load_EEPROM_Address();
		save_EEPROM_Address();

		while (now < len && e < EEP_Size) {
			if ((now == 0 || src[now - 1] == ' ' || src[now - 1] == '	' || src[now - 1] == '\n') &&
				((src[now + 2] == ' '&&src[now + 5] == ' '&&src[now + 8] == ' ')
					|| (src[now + 2] == '	'&&src[now + 5] == '	'&&src[now + 8] == '	')
					|| (src[now + 2] == '\n'&&src[now + 5] == '\n'&&src[now + 8] == '\n'))) {

				for (int i = 0; i < 16; i++) {
					D[e][0] = src[now++];
					D[e][1] = src[now++];
					DecData[e] = hex2Dec(e);
					e++;
					now++;
				}
			}
			else now++;
		}

		display_EEP();
		fout << "-------Check Sum Compare------" << endl;
		fout << "(ChkSum)	(EEPR)	(Calc.)	(Flag)	" << endl;

		//Calc Total Check Sum
		if (totalCheckSum > 0) {
			for (int i = 0; i < totalCheckSum; i++)
				TCSum += DecData[i];
		}

		if (modelSelect == 3|| modelSelect == 4) {
			CheckSum_Check(infoStart, infoEnd, 30, 0, "Info");
		}

		if (modelSelect < 3 || modelSelect == 5 || modelSelect == 8) {
			CheckSum_Check(infoStart, infoEnd, 0, 0, "Info");
		}

		if (modelSelect == 6) {
			CheckSum_Check(infoStart, infoEnd, 1, 0, "Info");
		}

		CheckSum_Check(fuseIDStart, fuseIDEnd, 1, 0, "fuseID");
		CheckSum_Check(serialNumberStart, serialNumberEnd, 1, 0, "QRcode");
		

		if (modelSelect > 2 && modelSelect < 5) {
			CheckSum_Check(awbStart4000, awbEnd4000, 5, 0, "4000K");
			CheckSum_Check(awbStart3100, awbEnd3100, 6, 0, "3100K");
			CheckSum_Check(awbLightStart, awbLightEnd, 5, 0, "Light5");
			CheckSum_Check(awbLightStart4000, awbLightEnd4000, 3, 0, "Light4");
			CheckSum_Check(awbLightStart3100, awbLightEnd3100, 3, 0, "Light3");
			CheckSum_Check(AFhallStart, AFhallEnd, 1, 0, "AFHall");
		}
		else {
			CheckSum_Check(awbStart, awbEnd, 1, 0, "AWBCal");
		}

		CheckSum_Check(dualAWBStart, dualAWBEnd, 1, 0, "DualAWB");
		CheckSum_Check(hallStart, hallEnd, 1, 0, "OISHall");
		CheckSum_Check(afDriftStart, afDriftEnd, 1, 0, "Drift");
		CheckSum_Check(afStart, afEnd, 21, 0, "AFCal");
		CheckSum_Check(lscStart, lscEnd, 1, 0, "LSCCal");
		CheckSum_Check(pdafGainStart, pdafGainEnd, 125, 0, "GainM");

		if(modelSelect!=6)
			CheckSum_Check(DCCStart, DCCEnd, 3, 0, "DCCcal");
		else {
			CheckSum_Check(DCCStart, DCCEnd, 0, 0, "PDhead");
			CheckSum_Check(DCCStart + 20, DCCEnd + 988, 0, 0, "Hv_LR");
			CheckSum_Check(DCCStart + 20 +988, DCCEnd + 988*2, 0, 0, "Hv_UD");
			CheckSum_Check(DCCStart + 20 +988*2, DCCEnd + 988 * 3, 0, 0, "qHD_LR");
			CheckSum_Check(DCCStart + 2984, DCCEnd + 3952, 0, 0, "Full_LR");
			CheckSum_Check(DCCStart + 3972, DCCEnd + 4940, 0, 0, "Full_UD");
		}

		CheckSum_Check(LRCStart, LRCEnd, 177, 0, "SonyLRC");
		CheckSum_Check(SonyDCCStart, SonyDCCEnd, 3, 0, "SonyDCC");

		////////////////Sony DCC and Tele/////////////////////////////////////////
		if (modelSelect == 3) {
			CheckSum_Check(LRCStart, LRCEnd, 177, 0, "SonyLRC");
			CheckSum_Check(SonyDCCStart, SonyDCCEnd, 3, 0, "SonyDCC");
			fout << endl;
			fout << "~~~~~~~~~~~Tele~~~~~~~~~~~" << endl;

			CheckSum_Check(infoStart + 4096, infoEnd + 4096, 30, 0, "Info");
			CheckSum_Check(awbStart4000 + 4096, awbEnd4000 + 4096, 5, 0, "4000K");
			CheckSum_Check(awbStart3100 + 4094, awbEnd3100 + 4096, 6, 0, "3100K");
			CheckSum_Check(awbLightStart + 4096, awbLightEnd + 4096, 5, 0, "Light5");
			CheckSum_Check(awbLightStart4000 + 4096, awbLightEnd4000 + 4096, 3, 0, "Light4");
			CheckSum_Check(awbLightStart3100 + 4096, awbLightEnd3100 + 4096, 3, 0, "Light3");
			CheckSum_Check(AFhallStart + 4096, AFhallEnd + 4096, 1, 0, "AFHall");
			CheckSum_Check(hallStart + 4096, hallEnd + 4096, 1, 0, "OISHall");
			CheckSum_Check(afDriftStart + 4096, afDriftEnd + 4096, 1, 0, "Drift");
			CheckSum_Check(afStart + 4096, afEnd + 4096, 21, 0, "AFCal");
			CheckSum_Check(lscStart + 4096, lscEnd + 4096, 1, 0, "LSCCal");
			CheckSum_Check(pdafGainStart + 4096, pdafGainEnd + 4214, 243, 0, "PDAF");
			CheckSum_Check(DCCStart + 4214, DCCEnd + 4214, 3, 0, "DCCcal");

			fout << "~~~~~~~~~~~Total~~~~~~~~~~~" << endl;
		}

		if (modelSelect == 5) {
			// V983 LSI checksum
			CheckSum_Check(focusMapStart, focusMapEnd, 1, 0, "Focusmap");

			fout << "~~~~~~~~ LSI CheckSum ~~~~~~~~" << endl;
			CheckSum_Check(headerLSIStart, headerLSIEnd, -52, 0, "head");
			CheckSum_Check(moduleLSIStart, moduleLSIEnd, -58, 0, "Module");
			CheckSum_Check(awbLSIStart, awbLSIEnd, -102,0, "AWB");
			CheckSum_Check(afLSIStart, afLSIEnd, -32,0, "LSI_AF");
			CheckSum_Check(lscLSIStart, lscLSIEnd, -5844, 0, "LSC");
			CheckSum_Check(pdafLSIStart, pdafLSIEnd, -1744, 0, "PDAF");
			CheckSum_Check(oisLSIStart, oisLSIEnd, -50, -46, "OIS");
		}

		/////////////////////////////////////////////////////////////
		CheckSum_Check(oisStart1, oisEnd1, 1, 0, "OIS1");
		CheckSum_Check(oisStart2, oisEnd2, 1, 0, "OIS2");
		CheckSum_Check(DAStart, DAEnd, 1, 0, "DACal");

		CheckSum_Check(dualCalStart, dualCalEnd, 1, 0, "DualCal");
		CheckSum_Check(dualVerifyStart, dualVerifyEnd, 1, 0, "Dual_V");
		
		CheckSum_Check(confidenceStart, confidenceEnd, 1, 0, "Confid");
		CheckSum_Check(pdaf_max_roiStart, pdaf_max_roiEnd, 1, 0, "Max_ROI");
			
		CheckSum_Check(AECStart, AECEnd, 1, 0, "D_AEC");
		CheckSum_Check(QSCStart, QSCEnd, 1, 0, "QSCCal");
		CheckSum_Check(distortionStart, distortionEnd, 1, 0, "Distor");
		

		if (totalCheckSum > 0) {
			fout << "Total	";
			fout << D[totalCheckSum][0] << D[totalCheckSum][1] << "	";

			TCSum = TCSum % 255;
			if (modelSelect != 1)
				TCSum++;
			if (TCSum == 0)
				TCSum = 255;
			getHex(TCSum);

			if (TCSum != DecData[totalCheckSum]) {

				TCSum = 0;

				if (totalCheckSum > 0) {
					for (int i = 0; i < totalCheckSum; i++)
						TCSum += DecData[i];
				}

				TCSum = TCSum % 255;
				if (modelSelect != 1)
					TCSum++;

				QString strDisplay = "total CheckSum in ";
				strDisplay += address2hex(totalCheckSum);
				strDisplay += " NG: 0x";
				strDisplay.append(D[totalCheckSum][0]);
				strDisplay.append(D[totalCheckSum][1]);
				strDisplay += ", real is 0x";
				strDisplay.append(chk[0]);
				strDisplay.append(chk[1]);

				DecData[totalCheckSum] = TCSum;
				D[totalCheckSum][0] = chk[0];
				D[totalCheckSum][1] = chk[1];

				strDisplay += '\n';
				ui->log->insertPlainText(strDisplay);
			}

			fout << chk[0] << chk[1] << "	";
			fout << " N/A	" << "	" << endl;
		}

		fout << endl;
		////////////////////////////////////////////////////////////

		fout << "-------basic info------" << endl;

		if (infoEnd > 0) {
			basicInfo_Parse(infoStart, infoEnd);
		}

		if (productDateStart > 0) {
			date_Parse(productDateStart, productDateEnd);
		}

		fuse_Parse(fuseIDStart,fuseIDEnd);

		if (serialNumberStart > 0) {
			QR_Parse(serialNumberStart, serialNumberEnd);
		}

		if (hallStart > 0) {
			OIS_Hall_Parse(hallStart, hallEnd);
		}

		if (afDriftStart > 0) {
			drift_Parse(afDriftStart, afDriftEnd);
		}

		if (afStart > 0) {
			af_Parse(afStart, afEnd);
		}

		if (AFhallStart > 0) {
			af_hall_Parse(AFhallStart, AFhallEnd);
		}

		///////////////AWBdata
		if (awbStart > 0) {
			awb_Parse(awbStart, 0);
		}

		///////////////LSCdata
		if (lscStart > 0) {
			lsc_Parse(lscStart, lscEnd);
		}

		if (pdafGainStart > 0) {
			gain_Map_Parse(pdafGainStart, pdafGainEnd);

		}

		if (DCCStart > 0) {
			if(modelSelect!=6)
				DCC_Parse(DCCStart, DCCEnd);
			else 
				QC_Five_DCC_Parse(DCCStart, DCCEnd);
		}

		if (FVStart > 0 && modelSelect != 3&& modelSelect != 4) {
			//FV Data map:
			fout << "~~~FV Data map:" << endl;
			e = FVStart;

			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 8; j++) {
					FV[i][j] = 256 * DecData[e] + DecData[e + 1];
					e += 2;
				}

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << FV[i][j] << "	";
				}
				fout << endl;
			}

			fout << endl;
		}

		if (PDStart > 0 && modelSelect != 3&&modelSelect != 4) {
			//PD Data map:
			fout << "~~~PD Data map:" << endl;
			e = PDStart;

			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 8; j++) {
					PD[i][j] = 256 * DecData[e] + DecData[e + 1];
					e += 2;
				}

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PD[i][j] << "	";
				}
				fout << endl;
			}

			fout << endl;
		}

		if (focusMapStart > 0) {
			FocusMap_Parse(focusMapStart, focusMapEnd);
		}

		if (lscLSIStart > 0) {
			lscLSI_Parse(lscLSIStart, lscLSIEnd);
		}

		if (modelSelect == 3|| modelSelect == 4 || modelSelect == 8) {

			sony_LRC_Parse(LRCStart, LRCEnd);
			sony_DCC_Parse(SonyDCCStart, SonyDCCEnd);
		}

		if (modelSelect == 3) {
			basicInfo_Parse(infoStart + 0x1000, infoEnd + 0x1000);
			date_Parse(productDateStart + 0x1000, productDateEnd + 0x1000);
			OIS_Hall_Parse(hallStart + 0x1000, hallEnd + 0x1000);
			drift_Parse(afDriftStart + 0x1000, afDriftEnd + 0x1000);
			af_Parse(afStart + 0x1000, afEnd + 0x1000);
			awb_Parse(awbStart + 0x1000, 0x1000);
			lsc_Parse(lscStart + 0x1000, lscEnd + 0x1000);
			gain_Map_Parse(pdafGainStart + 0x1000, pdafGainEnd + 0x1000);
			DCC_Parse(0x1B06, DCCEnd + 0x1B6F);
		}

		if (modelSelect == 3|| modelSelect == 4) {
			e = AECStart;
			fout << "------- Dual AEC Data ------" << endl;
			fout << "Wide_length_pixel_1M:	" << hex2Dec(e) + hex2Dec(e + 1) * 256 << endl;
			e += 2;
			fout << "Wide_Frame_length_1M:	" << hex2Dec(e) + hex2Dec(e + 1) * 256 << endl;
			e += 2;
			fout << "Sub_length_pixel_1M:	" << hex2Dec(e) + hex2Dec(e + 1) * 256 << endl;
			e += 2;
			fout << "Sub_Frame_length_1M:	" << hex2Dec(e) + hex2Dec(e + 1) * 256 << endl;
			e += 2;
			fout << "Wide_length_pixel_5M:	" << hex2Dec(e) + hex2Dec(e + 1) * 256 << endl;
			e += 2;
			fout << "Wide_Frame_length_5M:	" << hex2Dec(e) + hex2Dec(e + 1) * 256 << endl;
			e += 2;
			fout << "Sub_length_pixel_5M:	" << hex2Dec(e) + hex2Dec(e + 1) * 256 << endl;
			e += 2;
			fout << "Sub_Frame_length_5M:	" << hex2Dec(e) + hex2Dec(e + 1) * 256 << endl;
			e += 2;

		}

		if (modelSelect == 4) {
			fout << "------- Dual AWB Data ------" << endl;
			e = 0xD50;
			fout << "~~~5100K AWB Cal Data:" << endl;
			Oppo_AWB_Parse(e, 0,"Sub_");

			e = 0xD60;
			fout << "~~~4000K AWB Cal Data:" << endl;
			Oppo_AWB_Parse(e, 0, "Sub_");

			e = 0xD70;
			fout << "~~~3100K AWB Cal Data:" << endl;
			Oppo_AWB_Parse(e, 0, "Sub_");


		}

		if (oisStart1 > 0) {
			fout << "-------OIS1 CAL Data------" << endl;
			//OIS1 Data map:
			e = oisStart1 + 1;
			tmp = 0;
			for (int i = 0; i < 4; i++) {
				tmp *= 256;
				tmp += DecData[e + i];
			}
			//	float* fp = (float*)&tmp;
			fout << "Gyro Gain X:	" << *fp << endl;

			e += 4;
			tmp = 0;
			for (int i = 0; i < 4; i++) {
				tmp *= 256;
				tmp += DecData[e + i];
			}
			fout << "Gyro Gain Y:	" << *fp << endl;

			e += 4;
			fout << "Suppression Ratio X:	" << (float)(256 * DecData[e] + DecData[e + 1]) / 10 << endl;

			e += 2;
			fout << "Suppression Ratio Y:	" << (float)(256 * DecData[e] + DecData[e + 1]) / 10 << endl;

			e += 2;

			int gyrotmp = 256 * DecData[e] + DecData[e + 1];
			if (gyrotmp >= 0x8000)
				gyrotmp = gyrotmp - 0x10000;

			fout << "Gyro Offset X:	" << gyrotmp << endl;

			e += 2;

			gyrotmp = 256 * DecData[e] + DecData[e + 1];
			if (gyrotmp >= 0x8000)
				gyrotmp = gyrotmp - 0x10000;

			fout << "Gyro Offset Y:	" << gyrotmp << endl;

		}

		OIS_Parse(oisStart2,0,"Main_OIS_SR");
		LSI_AF_Parse(afLSIStart, afLSIEnd, "LSI_AF");
		LSI_OIS_Parse(oisLSIStart, oisLSIEnd, "LSI_AF");

		if (modelSelect == 3) {
			OIS_Parse( oisStart2+4, 0 , "Sub_OIS_SR");
		}

		unsigned int Dou[2] = { 0,0 };
		double* dp = (double*)Dou;
		if (dualCalStart > 0) {
			//Dual Cal Data:
			fout << "-------Dual CAL Data 12------" << endl;
			dual_Cal_Parse(dualCalStart, dualCalEnd);
		}

		if (modelSelect == 3 || modelSelect == 8) {
			//Dual Cal Data:
			fout << "-------Dual CAL Data 23------" << endl;
			dual_Cal_Parse(dualCalStart + 24, dualCalEnd + 24);
		}

		if (dualVerifyStart > 0) {
			//Dual verify Data:
			fout << "-------Dual Verify Data------" << endl;

			e = dualVerifyStart + 1;

			for (int p = 0; p < 2; p++) {
				Dou[p] = 0;
				for (int i = 0; i < 4; i++) {
					Dou[p] *= 256;
					Dou[p] += DecData[e + i];
				}
				e += 4;
			}

			fout << "AvgError:	" << *dp << endl;

			for (int p = 0; p < 2; p++) {
				Dou[p] = 0;
				for (int i = 0; i < 4; i++) {
					Dou[p] *= 256;
					Dou[p] += DecData[e + i];
				}
				e += 4;
			}
			fout << "MaxError:	" << *dp << endl;

			for (int p = 0; p < 2; p++) {
				Dou[p] = 0;
				for (int i = 0; i < 4; i++) {
					Dou[p] *= 256;
					Dou[p] += DecData[e + i];
				}
				e += 4;
			}
			fout << "Range:	" << *dp << endl;
		}

		
		AEC_Parse(AECStart,AECEnd);
	

		if (confidenceStart > 0) {
			//PDAF_DCC_Vivo requested Data:
			fout << "--------PDAF_DCC_Vivo requested PD confidence-------" << endl;
			e = confidenceStart;

			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 8; j++)
					for (int k = 0; k < 10; k++) {
						PDAF[i][j][k] = 256 * DecData[e] + DecData[e + 1] - 1;
						e += 2;
					}

			fout << "~~~PD confidence 1st:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][0] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 2nd:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][1] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 3th:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][2] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 4th:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][3] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 5th:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][4] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 6th:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][5] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 7th:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][6] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 8th:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][7] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 9th:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][8] << " ";
				}
				fout << endl;
			}
			fout << endl;

			fout << "~~~PD confidence 10th:" << endl;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					fout << PDAF[i][j][9] << " ";
				}
				fout << endl;
			}
			fout << endl;

		}

		if (pdaf_max_roiStart > 0) {
			// L/R Gain map ROI_Most bright pixel value:
			fout << "--------L/R Gain map ROI_Most bright pixel value-------" << endl;
			e = pdaf_max_roiStart;

			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 17; j++) {
					GainMostBrightLeft[i][j] = 256 * DecData[e] + DecData[e + 1];
					e += 2;
				}

			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 17; j++) {
					GainMostBrightRight[i][j] = 256 * DecData[e] + DecData[e + 1];
					e += 2;
				}

			fout << "~~~Left Gain map:" << endl;
			for (int i = 0; i < 13; i++) {
				for (int j = 0; j < 17; j++) {
					fout << GainMostBrightLeft[i][j] << "	";

				}
				fout << endl;
			}

			fout << "~~~Right Gain map:" << endl;
			for (int i = 0; i < 13; i++) {
				for (int j = 0; j < 17; j++) {
					fout << GainMostBrightRight[i][j] << "	";
				}
				fout << endl;
			}
			fout << endl;
		}

		if (AAStart > 0) {
			// AA test result:
			fout << "--------AA test result-------" << endl;

			e = AAStart;

			fout << "AA Result flag :	" << getFlag(e) << endl;
			e++;
			fout << "Equipment type:	" << D[e][0] << D[e][1];
			fout << '(';                                                                                      

			if (D[e][1] == 'A')
				fout << "A_ASM";
			if (D[e][1] == 'B')
				fout << "B_Protec";

			fout << ')' << endl;

			e++;
			fout << "Equipment Number:	" << (int)DecData[e] << endl;
			e++;
			fout << "Equipment port No:	" << (int)DecData[e] << endl;
			e++;
			fout << "Manufacture Date:	";

			if (modelSelect >1 ) {
				fout << (int)DecData[e] << '-';
				e++;
			}

			for (int i = 0; i < 3; i++) {
				fout << (int)DecData[e + i];
				if (i < 1)
					fout << "-";
				if (i == 1)
					fout << " ";
			}
			e += 3;
			if (modelSelect > 1 ) {
				fout << ':' << (int)DecData[e];
				e++;
				fout << ':' << (int)DecData[e] << endl;
				e++;
			}
			else
				fout << ":00" << endl;


			tmp = 0;
			for (int i = 3; i >= 0; i--) {
				tmp *= 256;
				tmp += DecData[e + i];
			}

			if (*fp > 2 || *fp < -2) {
				tmp = 0;
				for (int i = 0; i < 4; i++) {
					tmp *= 256;
					tmp += DecData[e + i];
				}
			}

			//	fp = (float*)&tmp;
			fout << "X tilt:	" << *fp << endl;


			e += 4;
			tmp = 0;
			for (int i = 3; i >= 0; i--) {
				tmp *= 256;
				tmp += DecData[e + i];
			}

			if (*fp > 2 || *fp < -2) {
				tmp = 0;
				for (int i = 0; i < 4; i++) {
					tmp *= 256;
					tmp += DecData[e + i];
				}
			}

			//	fp = (float*)&tmp;
			fout << "Y tilt:	" << *fp << endl;

			e += 4;

			if (modelSelect >1 ) {
				fout << "Wide AA AF Code:	" << 256 * DecData[e] + DecData[e + 1] << endl;
				e += 2;
			}

			fout << "optical Center X:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;
			fout << "optical Center Y:	" << 256 * DecData[e] + DecData[e + 1] << endl;
			e += 2;

			if (modelSelect == 2 || modelSelect == 3) {
				fout << "AA OC BV:	" << (int)DecData[e] << endl;
				e++;
			}

			if (modelSelect < 3) {
				fout << "MMDM code:	";
				for (int i = 0; i < 8; i++) {
					char c = DecData[e + i];
					fout << c;
				}
			}

			if (modelSelect == 3 || modelSelect == 4) {
				e++;
				fout << "SEMCO_CPS_RES:	";
				fout <<D[e][0]<<D[e][1] ;
				fout << " 00(OK)/0F(NG)"<<endl;

				e++;
				fout << "SEMCO_CPS_DATA:	";
				fout << D[e][0] << D[e][1] << D[e+1][0] << D[e+1][1]<< endl;
				e += 2;
			}

			if (modelSelect == 3)
				fout << "K+ flag:	" << D[e][0] << D[e][1];

			fout << endl;
		}

		// Test item date:
		fout << "--------Main Test Result Data-------" << endl;
		fout << "Test_Item	" << "Flag	" << "Line No.	" << "Equip No.	" << "Date	" << endl;

		e = hallDate;
		if (e > 0) {
			fout << "(Hall)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = af_macDate;
		if (e > 0) {
			fout << "(MAC)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = af_infDate;
		if (e > 0) {
			fout << "(INF)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = awbDate;
		if (e > 0) {
			fout << "(AWB)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = pdafDate;
		if (e > 0) {
			fout << "(PDAF)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = oisDate1;
		if (e > 0) {
			fout << "(OIS1)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = oisDate2;
		if (e > 0) {
			fout << "(OIS2)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = daDate;
		if (e > 0) {
			fout << "(DuAln)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = dual_calDate;
		if (e > 0) {
			fout << "(DuCal)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = dual_verDate;
		if (e > 0) {
			fout << "(DuVrf)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00	";
			fout << "X_hall_output:	" << 256 * DecData[e + 7] + DecData[e + 8] << "	Y_hall_output:	" << 256 * DecData[e + 9] + DecData[e + 10] << endl;
		}

		e = aecDate;
		if (e > 0) {
			fout << "(AEC)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		e = dual_resolutionDate;
		if (e > 0) {
			fout << "(DuReslt)	" << getFlag(e) << "	" << D[e + 1][0] << D[e + 1][1] << "	" << D[e + 2][0] << D[e + 2][1];
			fout << "	20" << D[e + 3][0] << D[e + 3][1] << "-" << D[e + 4][0] << D[e + 4][1] << "-" << D[e + 5][0] << D[e + 5][1] << " " << D[e + 6][0] << D[e + 6][1] << ":00" << endl;
		}

		if (infSFRStart > 0) {
			// INF SFR data:
			fout << "--------Main INF SFR data-------" << endl;
			e = infSFRStart;

			if (modelSelect < 3){
				SFR_display(27, e);
				fout << "Lens postion:	" << (int)DecData[e + 26] << endl;
			}
			if (modelSelect == 3 || modelSelect == 4){
				SFR_display(34,e);
				fout << "--------Main Dual INF SFR data-------" << endl;
				e = infSFRStart + 0x38;
				SFR_display(34, e);

				e += 43;
				fout << "Triple AF Code:	";
				fout << DecData[e + 1] * 256 + DecData[e];

				e += 2;
				fout << "AF Code diff NG:	"<< D[e][0] << D[e][1] << endl;
			}

			if (modelSelect == 5) {
				SFR_display(34, e);

			}

		}


		if (modelSelect == 4) {

			e = 6800;  //0x1A90
			fout << "UW 2.5cm AF Flag:	";
			fout << D[e + 2][0] << D[e + 2][1] ;
			if (DecData[e + 2] == 1)
				fout << "	//2.5cm Real Code" << endl;
			else fout << "	//2.5cm Virtual Code" << endl;

			fout << "UW 10cm AF Code:	";
			fout << DecData[e + 1] * 256 + DecData[e]<<endl;
		}


		if (modelSelect == 3) {

			fout << "--------Sub Test Date-------" << endl;
			Test_Date_display(hallDate + 0x2A, "(Hall)");
			Test_Date_display(af_macDate + 0x2A, "(MAC)");
			Test_Date_display(af_infDate + 0x2A, "(INF)");
			Test_Date_display(awbDate + 0x2A, "(AWB)");
			Test_Date_display(pdafDate + 0x2A, "(PDAF)");
			Test_Date_display(oisDate1 + 0x2A, "(OIS1)");


			fout << "--------Sub INF SFR data-------" << endl;
			e = infSFRStart2;
			SFR_display(18, e);
			
			fout << "--------Sub Dual INF SFR data-------" << endl;
			e = infSFRStart2 + 0x38;
			SFR_display(18, e);

			e += 28;
			fout << "Triple AF Code:	";
			fout << DecData[e + 1] * 256 + DecData[e];

			e += 2;
			fout << "AF Code diff NG:	" << D[e][0] << D[e][1] << endl;

		}


		if (macSFRStart > 0) {
			fout << "--------Main Mac SFR data-------" << endl;
			e = infSFRStart;

			if (modelSelect < 3) {
				SFR_display(27, e);
				fout << "Lens postion:	" << (int)DecData[e + 26] << endl;
			}
			if (modelSelect == 5) {
				SFR_display(34, e);
			}
			fout << endl;
		}

			if (MasterSPLStart > 0) {
				fout << "--------Master SPL Info-------" << endl;
				e = MasterSPLStart;
				string str = getFlag(e);
				fout << "Master SPL flag :	" << str << endl;
				e++;

				if (str[1] != 'N') {

					fout << "~~~5100K AWB Cal Data:" << endl;

					fout << "Gain R/Gr :	" << (float)(hex2Dec(e + 0) * 256 + hex2Dec(e + 1)) / 1024 << endl;
					fout << "Gain B/Gr :	" << (float)(hex2Dec(e + 2) * 256 + hex2Dec(e + 3)) / 1024 << endl;
					fout << "Gain Gr/Gb :	" << (float)(hex2Dec(e + 4) * 256 + hex2Dec(e + 5)) / 1024 << endl;
					fout << "Golden Sample,Gain R/Gr :	" << (float)(hex2Dec(e + 6) * 256 + hex2Dec(e + 7)) / 1024 << endl;
					fout << "Golden Sample,Gain B/Gr :	" << (float)(hex2Dec(e + 8) * 256 + hex2Dec(e + 9)) / 1024 << endl;
					fout << "Golden Sample,Gain Gr/Gb :	" << (float)(hex2Dec(e + 0xA) * 256 + hex2Dec(e + 0xB)) / 1024 << endl;

					fout << "~~~3100K AWB Cal Data:" << endl;
					fout << "Gain R/Gr :	" << (float)(hex2Dec(e + 0xC) * 256 + hex2Dec(e + 0xD)) / 1024 << endl;
					fout << "Gain B/Gr :	" << (float)(hex2Dec(e + 0xE) * 256 + hex2Dec(e + 0xF)) / 1024 << endl;
					fout << "Gain Gr/Gb :	" << (float)(hex2Dec(e + 0x10) * 256 + hex2Dec(e + 0x11)) / 1024 << endl;
					fout << "Golden Sample,Gain R/Gr :	" << (float)(hex2Dec(e + 0x12) * 256 + hex2Dec(e + 0x13)) / 1024 << endl;
					fout << "Golden Sample,Gain B/Gr :	" << (float)(hex2Dec(e + 0x14) * 256 + hex2Dec(e + 0x15)) / 1024 << endl;
					fout << "Golden Sample,Gain Gr/Gb :	" << (float)(hex2Dec(e + 0x16) * 256 + hex2Dec(e + 0x17)) / 1024 << endl;

				}
			}

			if (Dual_INF_SFRStart > 0) {
				// Dual INF SFR data:
				fout << "--------Dual INF SFR data-------" << endl;
				e = Dual_INF_SFRStart;
				fout << "Dual INF SFR data:	" << endl;

				fout << "Center	" << "0.3TLV	" << "0.3TLH	" << "0.3TRV	" << "0.3TRH	" << "0.3BLH	" << "0.3BLV	" << "0.3BRH	" << "0.3BRV	" << "0.3Left	" << "0.3Righ	";
				fout << "0.7TLV	" << "0.7TLH	" << "0.7TRV	" << "0.7TRH	" << "0.7BLH	" << "0.7BLV	" << "0.7BRH	" << "0.7BRV	";
				fout << "0.9TLV	" << "0.9TLH	" << "0.9TRV	" << "0.9TRH	" << "0.9BLH	" << "0.9BLV	" << "0.9BRH	" << "0.9BRV	" << endl;

				for (int i = 0; i < 27; i++)
					fout << "0." << checkFF(DecData[e + i]) << "	";
			}


	fout << endl;
	fout << "-------- Data End-------" << endl;

	DisplayOutput();

	fout << endl;
	fout.close();
	ui->pushButton_parser->setEnabled(false);
	ui->pushButton_checkSum->setEnabled(true);
	ui->pushButton_ois_repair->setEnabled(true);
	ui->log->insertPlainText("Data Parse finished. \n");
}


void widget6::display_EEP() {

	ui->input->clear();
	ui->input->setFontPointSize(9);
	for (int i = 0; i < EEP_Size; i++) {

		if (i % 16 == 0) {		
			unsigned char a = i / 256;
			getHex(a);
			string s = chk;
			s[2] =  '\0';
			ui->input->insertPlainText(s.c_str());
			unsigned char b = i % 256;
			getHex(b);
			char st[5] = {0};
			st[0] = chk[0]; st[1] = chk[1]; st[2] = ':'; st[3] = ' ';
			ui->input->insertPlainText(st);
		}

		getHex(DecData[i]);
		char st[4] = { 0 };
		st[0] = chk[0]; st[1] = chk[1]; st[2] = ' '; st[3] = '\0';
		ui->input->insertPlainText(st);

		if (i % 16 == 15)
			ui->input->insertPlainText("\n");
	}

//	s = ui->input->document()->toPlainText().toLocal8Bit();
//	fout << s << endl<<endl;

	ui->pushButton_checkSum->setEnabled(false);
	ui->pushButton_parser->setEnabled(true);
}


void widget6::on_pushButton_checkSum_clicked() {

	display_EEP();

}


void widget6::on_pushButton_openBIN_clicked() {

	QString filename = QFileDialog::getOpenFileName(this, tr("Open Bin"), "", tr("BIN File(*.bin)"));
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string name = code->fromUnicode(filename).data();
	
	if(modelSelect==3|| modelSelect == 5||modelSelect == 8)
		EEP_Size=16384;
	else if(modelSelect == 6 || modelSelect == 7)
		EEP_Size = 12288;

	ifstream fin(name, std::ios::binary);

	unsigned char szBuf[16384] = { 0 };
	fin.read((char*)&szBuf, sizeof(char) * EEP_Size);

	for (int i = 0; i < EEP_Size; i++) {
		
		if (i % 16 == 0) {		
			unsigned char a = i / 256;
			getHex(a);
			string s = chk;
			s[2] =  '\0';
			ui->input->insertPlainText(s.c_str());
			unsigned char b = i % 256;
			getHex(b);
			char st[5] = {0};
			st[0] = chk[0]; st[1] = chk[1]; st[2] = ':'; st[3] = ' ';
			ui->input->insertPlainText(st);
		}
			
		getHex(szBuf[i]);
		string s = chk;
		s += ' ';
		ui->input->insertPlainText(s.c_str());

		if (i % 16 == 15)
			ui->input->insertPlainText("\n");
	}

	fin.close();
}


void widget6::on_pushButton_saveBIN_clicked() {

	if (modelSelect == 3 || modelSelect == 5 || modelSelect == 8)
		EEP_Size = 16384;

	if (!ui->pushButton_parser->isEnabled()){

		src = ui->input->document()->toPlainText().toLocal8Bit();
		int now = 0, e = 0, len = src.length() - 1;

		while (now < len && e < EEP_Size) {
			if ((now == 0 || src[now - 1] == ' ' || src[now - 1] == '	' || src[now - 1] == '\n') &&
				((src[now + 2] == ' '&&src[now + 5] == ' '&&src[now + 8] == ' ')
					|| (src[now + 2] == '	'&&src[now + 5] == '	'&&src[now + 8] == '	'))) {

				for (int i = 0; i < 16; i++) {
					D[e][0] = src[now++];
					D[e][1] = src[now++];
					DecData[e] = hex2Dec(e);
					e++;
					now++;
				}
			}
			else now++;
		}
	}

	std::ofstream fout("Data.bin", std::ios::binary);

	for (int i = 0; i < EEP_Size; i++) {
		fout.write((char*)&DecData[i], sizeof(char));
	}
	
	fout.close();
	ui->log->insertPlainText("Data.bin saved. \n");
}


void widget6::on_pushButton_ois_repair_clicked() {

	eepLockOpen();
	////////////////////////
	src = ui->ois_version->document()->toPlainText().toLocal8Bit();
	int L = src.length() - 1;

	for (int i = oisFW + 3; i >= oisFW; i--) {
		D[i][0] = D[i][1] = 48;
		if (L >= 0) {
			D[i][1] = src[L];
			L--;
		}
		if (L >= 0) {
			D[i][0] = src[L];
			L--;
		}
		DecData[i] = hex2Dec(i);
		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
		Value_I2cWrite = DC_I2cWrite(0, 0, i / 256);
		Value_I2cWrite = DC_I2cWrite(0, 0, i % 256);
		Value_I2cWrite = DC_I2cWrite(0, 0, DecData[i]);
		DC_I2cStop(0, 0);
		Sleep(10);
	}

	int tmp = 0;
	for (int i = hallStart; i < hallEnd; i++)
		tmp += DecData[i];

	tmp %= 255;
	if (tmp == 0)
		tmp = 255;
	DecData[hallEnd] = tmp;
	getHex(tmp);
	D[hallEnd][0] = chk[0];
	D[hallEnd][1] = chk[1];
	//////////////////////
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
	Value_I2cWrite = DC_I2cWrite(0, 0, hallEnd / 256);
	Value_I2cWrite = DC_I2cWrite(0, 0, hallEnd % 256);
	Value_I2cWrite = DC_I2cWrite(0, 0, DecData[hallEnd]);
	DC_I2cStop(0, 0);
	Sleep(10);
	/////////////////////
	tmp = 0;
	for (int i = 0; i < totalCheckSum; i++)
		tmp += DecData[i];

	tmp %= 255;
	if (tmp == 0)
		tmp = 255;
	DecData[totalCheckSum] = tmp;
	getHex(tmp);
	D[totalCheckSum][0] = chk[0];
	D[totalCheckSum][1] = chk[1];

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
	Value_I2cWrite = DC_I2cWrite(0, 0, totalCheckSum / 256);
	Value_I2cWrite = DC_I2cWrite(0, 0, totalCheckSum % 256);
	Value_I2cWrite = DC_I2cWrite(0, 0, DecData[totalCheckSum]);
	DC_I2cStop(0, 0);
	Sleep(10);
	display_EEP();
	
	if (Value_I2cWrite != 0) {
		Err_display(I2C_Write);
		eepLockClose();
		return;
	}
/////////////////////
	eepLockClose();
	
	ui->log->insertPlainText("OIS Firmware Version Fix finished \n");
}


void widget6::on_pushButton_saveBIN12_clicked() {

	std::ofstream fout12("byteResult12.bin", std::ios::binary);

	short end = 8272 + 2048;
	for (int i = 8272; i < end; i++) {
		fout12.write((char*)&DecData[i], sizeof(char));
	}
	fout12.close();

	std::ofstream fout23("byteResult23.bin", std::ios::binary);

	end = 8272 + 4096;
	for (int i = 8272 + 2048; i < end; i++) {
		fout23.write((char*)&DecData[i], sizeof(char));
	}

	fout23.close();

	ui->log->insertPlainText("Triple cal bin saved. \n");

}


void widget6::on_pushButton_load_lsc_clicked() {

	ifstream fin(".//QC_LSC.txt");

	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 13; i++) 
			for (int j = 0; j < 17; j++) {
				fin >> LSC[i][j][k];
			}

	if (modelSelect == 3 || modelSelect == 4) {
		int e = lscStart;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 17; j++) {
				DecData[e + 4] = 0;
				for (int k = 0; k < 4; k++) {
					DecData[e + k]= LSC[i][j][k]%256;
					getHex(DecData[e + k]);
					D[e + k][0] = chk[0];
					D[e + k][1] = chk[1];
					DecData[e + 4] += ( LSC[i][j][k] / 256) << (2 * (3-k));
				}
				getHex(DecData[e + 4]);
				D[e + 4][0] = chk[0];
				D[e + 4][1] = chk[1];

				e += 5;
				if ((i * 17 + j + 1) % 51 == 0) {
					e++;
				}
			}
	}

	display_EEP();

}


//////////////////////////////////////
//float x= 0.47749996;
//float * test = &x;

//unsigned char *C = (unsigned char *)test;
// //Format = IEEE754(single) ex) 0.47749996 = 0x3EF47AE0
//int a = C[0];
//int b = C[1];
//int c = C[2];
//int d = C[3];

///////////////////////////////////////////////////