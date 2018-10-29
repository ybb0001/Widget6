#ifndef widget6_H
#define widget6_H

#include <QWidget>
#include <algorithm>
#include <QKeyEvent>
#include <QThread>
#include <String>

enum MyEnum
{
	len = 0,
	I2C_Read,
	I2C_Write,
	tCheckSum,
	hallCheckSum,
	dataReCheck
};




namespace Ui {
class EEPROM;
}

class widget6 : public QWidget
{
    Q_OBJECT

public:
    explicit widget6(QWidget *parent = 0);
    ~widget6();

private slots:
    void on_pushButton_parser_clicked();
	void on_pushButton_clear_clicked();
	void on_pushButton_golden_clicked();
	void on_pushButton_dumpRead_clicked();
	void on_pushButton_golden_select_clicked();
	void selectModel();

	void DisplayOutput();
	void awbGolden();
	void EEPROM_dumpRead(int f);
	void gainMapData();
	void on_pushButton_openBIN_clicked();
	void on_pushButton_saveBIN_clicked();
	void on_pushButton_checkSum_clicked();
	void on_pushButton_ois_repair_clicked();

	void on_pushButton_read_clicked();
	void on_pushButton_write_clicked();
	void on_pushButton_read_all_clicked();
	void on_pushButton_write_all_clicked();

	void CheckSum_Check(int checkSumStart, int checkSumEnd, int offset1, int offset2, QString item);

	void on_pushButton_find_clicked();
	void on_pushButton_GPIO_read_clicked();
	void on_pushButton_GPIO_write_clicked();
	void on_pushButton_GPIO_All_clicked();
	void GPIO_display();
	int  my_DC_I2cWrite(unsigned char s,int hi, int lo, unsigned char data);
	unsigned char my_DC_I2cRead(unsigned char s, int hi, int lo);
	void read_EEPROM(unsigned char s, int size);
	void Err_display(MyEnum code);
	void findData();
	void display_EEP();

	void on_checkBox_clicked();
	void on_checkBox_1_clicked();
	void on_checkBox_2_clicked();
	void on_checkBox_3_clicked();
	void on_checkBox_4_clicked();
	void on_checkBox_5_clicked();
	void on_checkBox_6_clicked();
	void on_checkBox_7_clicked();
	void on_checkBox_8_clicked();
	void on_checkBox_9_clicked();
	void on_checkBox_10_clicked();
	void on_checkBox_11_clicked();
	void on_checkBox_12_clicked();
	void on_checkBox_13_clicked();
	void on_checkBox_14_clicked();
	void on_checkBox_15_clicked();
	void on_checkBox_16_clicked();
	void on_checkBox_17_clicked();

public:
    Ui::EEPROM *ui;
    QImage img;
    QImage imgScaled;
	std::string name;
	struct EEPROM_Index {

		int infoStart = 0, infoEnd = 0x1F;
		int fuseIDStart = 0, fuseIDEnd = 0;
		int productDateStart = 0x03, productDateEnd = 0x44;
		int serialNumberStart = 0x45, serialNumberEnd = 0x65;

		int hallStart = 0x30, hallEnd = 0x3F, AFhallStart = 0x100, AFhallEnd = 0x109;
		int oisFW = 0x85;
		int afStart = 0x40, afEnd = 0x56;
		int awbStart = 0x5F, awbEnd = 0x85, awbStart2 = 0, awbEnd2 = 0, awbStart3 = 0, awbEnd3 = 0;
		int awbLightStart = 0x45, awbLightEnd = 0x4E, awbLightStart2 = 0x61, awbLightEnd2 = 0x68, awbLightStart3 = 0x49, awbLightEnd3 = 0x50;
		int lscStart = 0x8F, lscEnd = 0x04E6;
		int pdafGainStart = 0x04EF, pdafGainEnd = 0x0995;
		int DCCStart = 0x086C, DCCEnd = 0, SonyDCCStart = 0x0CCA, SonyDCCEnd = 0x0D2D;
		int FVStart = 0x08D5, PDStart = 0x0935, LRCStart = 0x0AFA, LRCEnd = 0x0D2B;
		int oisStart1 = 0x09A0, oisEnd1 = 0x09B1;
		int oisStart2 = 0x09B4, oisEnd2 = 0x09BD;

		int DAStart = 0x09C0, DAEnd = 0x09C3;
		int dualCalStart = 0x09D0, dualCalEnd = 0x11EC;
		int dualVerifyStart = 0x11F0, dualVerifyEnd = 0x1209;
		int AECStart = 0x1210, AECEnd = 0x1234;
		int barCodeStart = 0x1240;
		int afDriftStart = 0x12CB, afDriftEnd = 0x12EF;
		int confidenceStart = 0x1300, confidenceEnd = 0x16C0;
		int pdaf_max_roiStart = 0x16D0, pdaf_max_roiEnd = 0x1A48;
		int totalCheckSum = 0x1A50;

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
		// Tele
	}EEP;


};

#endif // widget6_H
