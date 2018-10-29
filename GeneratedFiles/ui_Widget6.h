/********************************************************************************
** Form generated from reading UI file 'Widget6.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET6_H
#define UI_WIDGET6_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EEPROM
{
public:
    QTextEdit *input;
    QTextBrowser *log;
    QTextBrowser *output;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_golden;
    QTextEdit *R_Gr31;
    QGroupBox *groupBox;
    QPushButton *pushButton_dumpRead;
    QCheckBox *checkBox_OIS;
    QPushButton *pushButton_golden_select;
    QCheckBox *checkBox_AWB;
    QLabel *label_7;
    QCheckBox *checkBox_SFR;
    QCheckBox *checkBox_OC;
    QPushButton *pushButton_checkSum;
    QTextEdit *ois_version;
    QPushButton *pushButton_ois_repair;
    QTextEdit *B_Gr31;
    QLabel *label_10;
    QLabel *label_11;
    QTextEdit *Gr_Gb31;
    QTextEdit *R_Gr51;
    QTextEdit *B_Gr51;
    QTextEdit *Gr_Gb51;
    QGroupBox *groupBox_4;
    QTextEdit *fuseId;
    QLabel *label_12;
    QLabel *label_13;
    QTextEdit *barCode;
    QPushButton *pushButton_find;
    QWidget *tab_2;
    QPushButton *pushButton_read;
    QGroupBox *groupBox_2;
    QTextBrowser *GPIO_Value;
    QPushButton *pushButton_GPIO_All;
    QTextEdit *addL;
    QPushButton *pushButton_write;
    QGroupBox *groupBox_3;
    QLabel *label_9;
    QTextEdit *eep_size;
    QLabel *label_8;
    QCheckBox *addH_use;
    QCheckBox *checkBox_2;
    QPushButton *pushButton_read_all;
    QCheckBox *checkBox_1;
    QTextEdit *addH;
    QCheckBox *checkBox_15;
    QCheckBox *checkBox_4;
    QTextEdit *readData;
    QCheckBox *checkBox;
    QPushButton *pushButton_write_all;
    QCheckBox *checkBox_8;
    QTextEdit *writeData;
    QCheckBox *checkBox_17;
    QLabel *label_5;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_14;
    QLabel *label_6;
    QPushButton *pushButton_GPIO_read;
    QCheckBox *checkBox_9;
    QPushButton *pushButton_GPIO_write;
    QCheckBox *checkBox_3;
    QTextEdit *slave;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_16;
    QWidget *tab_3;
    QPushButton *pushButton_parser;
    QPushButton *pushButton_clear;
    QRadioButton *dataType_OTP;
    QLabel *label_4;
    QTextEdit *model;
    QRadioButton *dataType_EEPROM;
    QPushButton *pushButton_openBIN;
    QPushButton *pushButton_saveBIN;

    void setupUi(QWidget *EEPROM)
    {
        if (EEPROM->objectName().isEmpty())
            EEPROM->setObjectName(QStringLiteral("EEPROM"));
        EEPROM->resize(889, 764);
        input = new QTextEdit(EEPROM);
        input->setObjectName(QStringLiteral("input"));
        input->setGeometry(QRect(10, 20, 430, 500));
        log = new QTextBrowser(EEPROM);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(10, 550, 401, 141));
        output = new QTextBrowser(EEPROM);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(450, 20, 430, 500));
        output->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        label = new QLabel(EEPROM);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 0, 161, 16));
        label_2 = new QLabel(EEPROM);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(470, 0, 161, 16));
        label_3 = new QLabel(EEPROM);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 530, 131, 16));
        tabWidget = new QTabWidget(EEPROM);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(420, 530, 461, 231));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_golden = new QPushButton(tab);
        pushButton_golden->setObjectName(QStringLiteral("pushButton_golden"));
        pushButton_golden->setGeometry(QRect(-130, 50, 91, 30));
        pushButton_golden->setCheckable(false);
        R_Gr31 = new QTextEdit(tab);
        R_Gr31->setObjectName(QStringLiteral("R_Gr31"));
        R_Gr31->setGeometry(QRect(200, 75, 41, 31));
        R_Gr31->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        R_Gr31->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 441, 101));
        pushButton_dumpRead = new QPushButton(groupBox);
        pushButton_dumpRead->setObjectName(QStringLiteral("pushButton_dumpRead"));
        pushButton_dumpRead->setGeometry(QRect(350, 20, 81, 30));
        pushButton_dumpRead->setCheckable(false);
        checkBox_OIS = new QCheckBox(groupBox);
        checkBox_OIS->setObjectName(QStringLiteral("checkBox_OIS"));
        checkBox_OIS->setGeometry(QRect(10, 80, 61, 19));
        checkBox_OIS->setChecked(true);
        pushButton_golden_select = new QPushButton(groupBox);
        pushButton_golden_select->setObjectName(QStringLiteral("pushButton_golden_select"));
        pushButton_golden_select->setGeometry(QRect(350, 60, 81, 30));
        pushButton_golden_select->setCheckable(false);
        checkBox_AWB = new QCheckBox(groupBox);
        checkBox_AWB->setObjectName(QStringLiteral("checkBox_AWB"));
        checkBox_AWB->setGeometry(QRect(10, 60, 61, 19));
        checkBox_AWB->setChecked(false);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(195, 10, 31, 16));
        checkBox_SFR = new QCheckBox(groupBox);
        checkBox_SFR->setObjectName(QStringLiteral("checkBox_SFR"));
        checkBox_SFR->setGeometry(QRect(10, 40, 61, 19));
        checkBox_SFR->setChecked(true);
        checkBox_OC = new QCheckBox(groupBox);
        checkBox_OC->setObjectName(QStringLiteral("checkBox_OC"));
        checkBox_OC->setGeometry(QRect(10, 20, 61, 19));
        checkBox_OC->setCheckable(false);
        checkBox_OC->setChecked(false);
        pushButton_checkSum = new QPushButton(tab);
        pushButton_checkSum->setObjectName(QStringLiteral("pushButton_checkSum"));
        pushButton_checkSum->setEnabled(false);
        pushButton_checkSum->setGeometry(QRect(10, 120, 80, 30));
        pushButton_checkSum->setCheckable(false);
        ois_version = new QTextEdit(tab);
        ois_version->setObjectName(QStringLiteral("ois_version"));
        ois_version->setGeometry(QRect(10, 160, 71, 31));
        ois_version->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ois_version->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pushButton_ois_repair = new QPushButton(tab);
        pushButton_ois_repair->setObjectName(QStringLiteral("pushButton_ois_repair"));
        pushButton_ois_repair->setEnabled(false);
        pushButton_ois_repair->setGeometry(QRect(90, 160, 71, 30));
        pushButton_ois_repair->setCheckable(false);
        B_Gr31 = new QTextEdit(tab);
        B_Gr31->setObjectName(QStringLiteral("B_Gr31"));
        B_Gr31->setGeometry(QRect(250, 75, 41, 31));
        B_Gr31->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        B_Gr31->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_10 = new QLabel(tab);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(255, 20, 31, 16));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(300, 20, 41, 16));
        Gr_Gb31 = new QTextEdit(tab);
        Gr_Gb31->setObjectName(QStringLiteral("Gr_Gb31"));
        Gr_Gb31->setGeometry(QRect(300, 75, 41, 31));
        Gr_Gb31->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Gr_Gb31->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        R_Gr51 = new QTextEdit(tab);
        R_Gr51->setObjectName(QStringLiteral("R_Gr51"));
        R_Gr51->setGeometry(QRect(200, 40, 41, 31));
        R_Gr51->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        R_Gr51->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        B_Gr51 = new QTextEdit(tab);
        B_Gr51->setObjectName(QStringLiteral("B_Gr51"));
        B_Gr51->setGeometry(QRect(250, 40, 41, 31));
        B_Gr51->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        B_Gr51->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Gr_Gb51 = new QTextEdit(tab);
        Gr_Gb51->setObjectName(QStringLiteral("Gr_Gb51"));
        Gr_Gb51->setGeometry(QRect(300, 40, 41, 31));
        Gr_Gb51->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Gr_Gb51->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(180, 109, 271, 91));
        fuseId = new QTextEdit(groupBox_4);
        fuseId->setObjectName(QStringLiteral("fuseId"));
        fuseId->setGeometry(QRect(70, 20, 190, 30));
        fuseId->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        fuseId->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 30, 60, 16));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 65, 60, 16));
        barCode = new QTextEdit(groupBox_4);
        barCode->setObjectName(QStringLiteral("barCode"));
        barCode->setGeometry(QRect(70, 55, 111, 30));
        barCode->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        barCode->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pushButton_find = new QPushButton(groupBox_4);
        pushButton_find->setObjectName(QStringLiteral("pushButton_find"));
        pushButton_find->setGeometry(QRect(190, 55, 71, 30));
        pushButton_find->setCheckable(false);
        tabWidget->addTab(tab, QString());
        groupBox_4->raise();
        groupBox->raise();
        pushButton_golden->raise();
        R_Gr31->raise();
        pushButton_checkSum->raise();
        ois_version->raise();
        pushButton_ois_repair->raise();
        B_Gr31->raise();
        label_10->raise();
        label_11->raise();
        Gr_Gb31->raise();
        R_Gr51->raise();
        B_Gr51->raise();
        Gr_Gb51->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        pushButton_read = new QPushButton(tab_2);
        pushButton_read->setObjectName(QStringLiteral("pushButton_read"));
        pushButton_read->setGeometry(QRect(250, 120, 61, 30));
        pushButton_read->setCheckable(false);
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 441, 81));
        GPIO_Value = new QTextBrowser(groupBox_2);
        GPIO_Value->setObjectName(QStringLiteral("GPIO_Value"));
        GPIO_Value->setGeometry(QRect(70, 10, 71, 31));
        pushButton_GPIO_All = new QPushButton(groupBox_2);
        pushButton_GPIO_All->setObjectName(QStringLiteral("pushButton_GPIO_All"));
        pushButton_GPIO_All->setGeometry(QRect(160, 10, 61, 30));
        pushButton_GPIO_All->setCheckable(false);
        addL = new QTextEdit(tab_2);
        addL->setObjectName(QStringLiteral("addL"));
        addL->setGeometry(QRect(150, 120, 41, 30));
        pushButton_write = new QPushButton(tab_2);
        pushButton_write->setObjectName(QStringLiteral("pushButton_write"));
        pushButton_write->setGeometry(QRect(250, 160, 61, 30));
        pushButton_write->setCheckable(false);
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 100, 391, 95));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 65, 41, 20));
        eep_size = new QTextEdit(groupBox_3);
        eep_size->setObjectName(QStringLiteral("eep_size"));
        eep_size->setGeometry(QRect(50, 60, 51, 30));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(200, 0, 41, 16));
        addH_use = new QCheckBox(groupBox_3);
        addH_use->setObjectName(QStringLiteral("addH_use"));
        addH_use->setGeometry(QRect(120, 60, 91, 19));
        addH_use->setChecked(true);
        checkBox_2 = new QCheckBox(tab_2);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(370, 70, 16, 16));
        pushButton_read_all = new QPushButton(tab_2);
        pushButton_read_all->setObjectName(QStringLiteral("pushButton_read_all"));
        pushButton_read_all->setGeometry(QRect(320, 120, 61, 30));
        pushButton_read_all->setCheckable(false);
        checkBox_1 = new QCheckBox(tab_2);
        checkBox_1->setObjectName(QStringLiteral("checkBox_1"));
        checkBox_1->setGeometry(QRect(390, 70, 16, 16));
        addH = new QTextEdit(tab_2);
        addH->setObjectName(QStringLiteral("addH"));
        addH->setGeometry(QRect(100, 120, 41, 30));
        checkBox_15 = new QCheckBox(tab_2);
        checkBox_15->setObjectName(QStringLiteral("checkBox_15"));
        checkBox_15->setGeometry(QRect(80, 70, 16, 16));
        checkBox_4 = new QCheckBox(tab_2);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setGeometry(QRect(320, 70, 16, 16));
        readData = new QTextEdit(tab_2);
        readData->setObjectName(QStringLiteral("readData"));
        readData->setGeometry(QRect(200, 120, 41, 31));
        checkBox = new QCheckBox(tab_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(410, 70, 16, 16));
        pushButton_write_all = new QPushButton(tab_2);
        pushButton_write_all->setObjectName(QStringLiteral("pushButton_write_all"));
        pushButton_write_all->setGeometry(QRect(320, 160, 61, 30));
        pushButton_write_all->setCheckable(false);
        checkBox_8 = new QCheckBox(tab_2);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));
        checkBox_8->setGeometry(QRect(230, 70, 16, 16));
        writeData = new QTextEdit(tab_2);
        writeData->setObjectName(QStringLiteral("writeData"));
        writeData->setGeometry(QRect(200, 160, 41, 30));
        checkBox_17 = new QCheckBox(tab_2);
        checkBox_17->setObjectName(QStringLiteral("checkBox_17"));
        checkBox_17->setGeometry(QRect(30, 70, 16, 16));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 100, 51, 16));
        checkBox_7 = new QCheckBox(tab_2);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));
        checkBox_7->setGeometry(QRect(260, 70, 16, 16));
        checkBox_12 = new QCheckBox(tab_2);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));
        checkBox_12->setGeometry(QRect(140, 70, 16, 16));
        checkBox_14 = new QCheckBox(tab_2);
        checkBox_14->setObjectName(QStringLiteral("checkBox_14"));
        checkBox_14->setGeometry(QRect(100, 70, 16, 16));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(110, 100, 71, 16));
        pushButton_GPIO_read = new QPushButton(tab_2);
        pushButton_GPIO_read->setObjectName(QStringLiteral("pushButton_GPIO_read"));
        pushButton_GPIO_read->setGeometry(QRect(240, 20, 91, 30));
        pushButton_GPIO_read->setCheckable(false);
        checkBox_9 = new QCheckBox(tab_2);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));
        checkBox_9->setGeometry(QRect(210, 70, 16, 16));
        pushButton_GPIO_write = new QPushButton(tab_2);
        pushButton_GPIO_write->setObjectName(QStringLiteral("pushButton_GPIO_write"));
        pushButton_GPIO_write->setGeometry(QRect(340, 20, 91, 30));
        pushButton_GPIO_write->setCheckable(false);
        checkBox_3 = new QCheckBox(tab_2);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(350, 70, 16, 16));
        slave = new QTextEdit(tab_2);
        slave->setObjectName(QStringLiteral("slave"));
        slave->setGeometry(QRect(50, 120, 41, 30));
        checkBox_10 = new QCheckBox(tab_2);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));
        checkBox_10->setGeometry(QRect(190, 70, 16, 16));
        checkBox_11 = new QCheckBox(tab_2);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));
        checkBox_11->setGeometry(QRect(170, 70, 16, 16));
        checkBox_5 = new QCheckBox(tab_2);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setGeometry(QRect(300, 70, 16, 16));
        checkBox_6 = new QCheckBox(tab_2);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        checkBox_6->setGeometry(QRect(280, 70, 16, 16));
        checkBox_13 = new QCheckBox(tab_2);
        checkBox_13->setObjectName(QStringLiteral("checkBox_13"));
        checkBox_13->setGeometry(QRect(120, 70, 16, 16));
        checkBox_16 = new QCheckBox(tab_2);
        checkBox_16->setObjectName(QStringLiteral("checkBox_16"));
        checkBox_16->setGeometry(QRect(50, 70, 16, 16));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        pushButton_parser = new QPushButton(EEPROM);
        pushButton_parser->setObjectName(QStringLiteral("pushButton_parser"));
        pushButton_parser->setGeometry(QRect(330, 700, 80, 30));
        pushButton_parser->setCheckable(false);
        pushButton_clear = new QPushButton(EEPROM);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(330, 730, 80, 30));
        pushButton_clear->setCheckable(false);
        dataType_OTP = new QRadioButton(EEPROM);
        dataType_OTP->setObjectName(QStringLiteral("dataType_OTP"));
        dataType_OTP->setGeometry(QRect(110, 700, 81, 21));
        label_4 = new QLabel(EEPROM);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 740, 101, 16));
        model = new QTextEdit(EEPROM);
        model->setObjectName(QStringLiteral("model"));
        model->setGeometry(QRect(130, 730, 41, 31));
        model->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        model->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        dataType_EEPROM = new QRadioButton(EEPROM);
        dataType_EEPROM->setObjectName(QStringLiteral("dataType_EEPROM"));
        dataType_EEPROM->setGeometry(QRect(20, 700, 81, 19));
        dataType_EEPROM->setChecked(true);
        pushButton_openBIN = new QPushButton(EEPROM);
        pushButton_openBIN->setObjectName(QStringLiteral("pushButton_openBIN"));
        pushButton_openBIN->setGeometry(QRect(200, 700, 81, 30));
        pushButton_openBIN->setCheckable(false);
        pushButton_saveBIN = new QPushButton(EEPROM);
        pushButton_saveBIN->setObjectName(QStringLiteral("pushButton_saveBIN"));
        pushButton_saveBIN->setGeometry(QRect(200, 730, 81, 30));
        pushButton_saveBIN->setCheckable(false);
        tabWidget->raise();
        input->raise();
        log->raise();
        output->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        pushButton_parser->raise();
        pushButton_clear->raise();
        dataType_OTP->raise();
        label_4->raise();
        model->raise();
        dataType_EEPROM->raise();
        pushButton_openBIN->raise();
        pushButton_saveBIN->raise();

        retranslateUi(EEPROM);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EEPROM);
    } // setupUi

    void retranslateUi(QWidget *EEPROM)
    {
        EEPROM->setWindowTitle(QApplication::translate("EEPROM", "ISM Memory Parser V3", Q_NULLPTR));
        label->setText(QApplication::translate("EEPROM", "Input Memory Data", Q_NULLPTR));
        label_2->setText(QApplication::translate("EEPROM", "Output Parse Data", Q_NULLPTR));
        label_3->setText(QApplication::translate("EEPROM", "Result & logs", Q_NULLPTR));
        pushButton_golden->setText(QApplication::translate("EEPROM", "AWB Golden", Q_NULLPTR));
        R_Gr31->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("EEPROM", "EEP Result Dump", Q_NULLPTR));
        pushButton_dumpRead->setText(QApplication::translate("EEPROM", "Dump Read", Q_NULLPTR));
        checkBox_OIS->setText(QApplication::translate("EEPROM", "OIS", Q_NULLPTR));
        pushButton_golden_select->setText(QApplication::translate("EEPROM", "Golden", Q_NULLPTR));
        checkBox_AWB->setText(QApplication::translate("EEPROM", "AWB", Q_NULLPTR));
        label_7->setText(QApplication::translate("EEPROM", "<html><head/><body><p>R/Gr</p></body></html>", Q_NULLPTR));
        checkBox_SFR->setText(QApplication::translate("EEPROM", "SFR", Q_NULLPTR));
        checkBox_OC->setText(QApplication::translate("EEPROM", "OC", Q_NULLPTR));
        pushButton_checkSum->setText(QApplication::translate("EEPROM", "CSum\344\277\256\345\244\215", Q_NULLPTR));
        ois_version->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">5111</p></body></html>", Q_NULLPTR));
        pushButton_ois_repair->setText(QApplication::translate("EEPROM", "OIS\344\277\256\345\244\215", Q_NULLPTR));
        B_Gr31->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", Q_NULLPTR));
        label_10->setText(QApplication::translate("EEPROM", "<html><head/><body><p>B/Gr</p></body></html>", Q_NULLPTR));
        label_11->setText(QApplication::translate("EEPROM", "<html><head/><body><p>Gr/Gb</p></body></html>", Q_NULLPTR));
        Gr_Gb31->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", Q_NULLPTR));
        R_Gr51->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", Q_NULLPTR));
        B_Gr51->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", Q_NULLPTR));
        Gr_Gb51->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("EEPROM", "Search", Q_NULLPTR));
        fuseId->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">118460363C75150303</p></body></html>", Q_NULLPTR));
        label_12->setText(QApplication::translate("EEPROM", "Fuse ID", Q_NULLPTR));
        label_13->setText(QApplication::translate("EEPROM", "BarCode", Q_NULLPTR));
        barCode->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">6A1088G1603A</p></body></html>", Q_NULLPTR));
        pushButton_find->setText(QApplication::translate("EEPROM", "Find", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("EEPROM", "Parser", Q_NULLPTR));
        pushButton_read->setText(QApplication::translate("EEPROM", "Read", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("EEPROM", "GPIO", Q_NULLPTR));
        pushButton_GPIO_All->setText(QApplication::translate("EEPROM", "All_On", Q_NULLPTR));
        addL->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">00</p></body></html>", Q_NULLPTR));
        pushButton_write->setText(QApplication::translate("EEPROM", "Write", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("EEPROM", "I2C", Q_NULLPTR));
        label_9->setText(QApplication::translate("EEPROM", "Size", Q_NULLPTR));
        eep_size->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">8192</p></body></html>", Q_NULLPTR));
        label_8->setText(QApplication::translate("EEPROM", "Data", Q_NULLPTR));
        addH_use->setText(QString());
        checkBox_2->setText(QString());
        pushButton_read_all->setText(QApplication::translate("EEPROM", "R_All", Q_NULLPTR));
        checkBox_1->setText(QString());
        addH->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">80</p></body></html>", Q_NULLPTR));
        checkBox_15->setText(QString());
        checkBox_4->setText(QString());
        readData->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        checkBox->setText(QString());
        pushButton_write_all->setText(QApplication::translate("EEPROM", "W_All", Q_NULLPTR));
        checkBox_8->setText(QString());
        writeData->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        checkBox_17->setText(QString());
        label_5->setText(QApplication::translate("EEPROM", "Slave", Q_NULLPTR));
        checkBox_7->setText(QApplication::translate("EEPROM", "7", Q_NULLPTR));
        checkBox_12->setText(QString());
        checkBox_14->setText(QString());
        label_6->setText(QApplication::translate("EEPROM", "Addr_H/L", Q_NULLPTR));
        pushButton_GPIO_read->setText(QApplication::translate("EEPROM", "GPIO_Read", Q_NULLPTR));
        checkBox_9->setText(QString());
        pushButton_GPIO_write->setText(QApplication::translate("EEPROM", "GPIO_Write", Q_NULLPTR));
        checkBox_3->setText(QString());
        slave->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">A2</p></body></html>", Q_NULLPTR));
        checkBox_10->setText(QString());
        checkBox_11->setText(QString());
        checkBox_5->setText(QString());
        checkBox_6->setText(QString());
        checkBox_13->setText(QString());
        checkBox_16->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("EEPROM", "I2C_GPIO", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("EEPROM", "temp", Q_NULLPTR));
        pushButton_parser->setText(QApplication::translate("EEPROM", "Parse", Q_NULLPTR));
        pushButton_clear->setText(QApplication::translate("EEPROM", "Clear", Q_NULLPTR));
        dataType_OTP->setText(QApplication::translate("EEPROM", "OTP", Q_NULLPTR));
        label_4->setText(QApplication::translate("EEPROM", "<html><head/><body><p>Model Select</p></body></html>", Q_NULLPTR));
        model->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1</p></body></html>", Q_NULLPTR));
        dataType_EEPROM->setText(QApplication::translate("EEPROM", "EEPROM", Q_NULLPTR));
        pushButton_openBIN->setText(QApplication::translate("EEPROM", "Open Bin", Q_NULLPTR));
        pushButton_saveBIN->setText(QApplication::translate("EEPROM", "Save Bin", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EEPROM: public Ui_EEPROM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET6_H
