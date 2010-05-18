/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat 6. Feb 18:11:09 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "qbanks.h"
#include "qclavier.h"
#include "qinstrument.h"
#include "qoperateur.h"
#include "qvoice.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionOnline_help;
    QAction *actionLoad_set;
    QAction *actionSave_set;
    QAction *actionLoad_voice;
    QAction *actionSave_voice;
    QAction *actionRead_this;
    QAction *actionSend_current_set;
    QAction *actionSend_current_voice;
    QAction *actionGet_current_set;
    QAction *actionGet_current_voice;
    QAction *actionGet_current_config;
    QAction *actionSend_current_config;
    QAction *actionRandomize;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionInitialize;
    QAction *actionGet_all_banks;
    QAction *actionRam_1;
    QAction *actionRam_2;
    QAction *actionExchange;
    QAction *actionLoad_bank;
    QAction *actionSave_bank;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_general;
    QGroupBox *grpBox_MIDI;
    QComboBox *cmbBox_MIDIIn;
    QComboBox *cmbBox_MIDIOut;
    QPushButton *pshBut_refresh_midi;
    QSpinBox *spnBox_syschan;
    QLabel *lbl_syschan;
    QLabel *lbl_MIDIIn;
    QLabel *lbl_MIDIIn_2;
    QSpinBox *spnBox_kybchan;
    QLabel *lbl_kybchan;
    QGroupBox *grpBox_config;
    QLabel *lbl_combine;
    QLabel *lbl_reception;
    QComboBox *cmbBox_reception;
    QPushButton *pshBut_combine;
    QPushButton *pshBut_memory;
    QLabel *lbl_memory;
    QSpinBox *spnBox_confnum;
    QLabel *lbl_confnum;
    QLabel *lbl_mastvol;
    QSlider *hzSlider_mastvol;
    QLabel *label;
    QWidget *tab_banks;
    QBanks *widget_banks;
    QWidget *tab_set;
    QLabel *lbl_notes;
    QLabel *lbl_midichan;
    QLabel *lbl_upper;
    QLabel *lbl_lower;
    QLabel *lbl_bank;
    QLabel *lbl_voice;
    QLabel *lbl_detune;
    QLabel *lbl_voice_2;
    QLabel *lbl_volume;
    QLabel *lbl_pan;
    QLabel *lbl_LFO;
    QLabel *lbl_porta;
    QLabel *lbl_pitch;
    QLabel *lbl_poly;
    QLabel *lbl_pmdctl;
    QPushButton *pshBut_next;
    QFrame *frame_page_1;
    QInstrument *widget_instru_4;
    QInstrument *widget_instru_1;
    QInstrument *widget_instru_2;
    QInstrument *widget_instru_3;
    QPushButton *pshBut_inst_cur_4;
    QPushButton *pshBut_inst_cur_2;
    QPushButton *pshBut_inst_cur_3;
    QPushButton *pshBut_inst_cur_1;
    QFrame *frame_page_2;
    QInstrument *widget_instru_8;
    QInstrument *widget_instru_5;
    QInstrument *widget_instru_6;
    QInstrument *widget_instru_7;
    QPushButton *pshBut_inst_cur_8;
    QPushButton *pshBut_inst_cur_6;
    QPushButton *pshBut_inst_cur_7;
    QPushButton *pshBut_inst_cur_5;
    QPlainTextEdit *txtEdit_setname;
    QWidget *tab_voice;
    QVoice *widget_voice;
    QWidget *tab_operas;
    QOperateur *widget_opera_1;
    QPushButton *pshBut_OPon_1;
    QOperateur *widget_opera_2;
    QPushButton *pshBut_OPon_2;
    QOperateur *widget_opera_3;
    QPushButton *pshBut_OPon_3;
    QOperateur *widget_opera_4;
    QPushButton *pshBut_OPon_4;
    QPushButton *pshBut_op_cur_1;
    QPushButton *pshBut_op_cur_2;
    QPushButton *pshBut_op_cur_3;
    QPushButton *pshBut_op_cur_4;
    QClavier *lbl_clavier;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuHelp;
    QMenu *menuConfig;
    QMenu *menuSend_bank;
    QMenu *menuEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(620, 630);
        MainWindow->setMaximumSize(QSize(620, 630));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionOnline_help = new QAction(MainWindow);
        actionOnline_help->setObjectName(QString::fromUtf8("actionOnline_help"));
        actionLoad_set = new QAction(MainWindow);
        actionLoad_set->setObjectName(QString::fromUtf8("actionLoad_set"));
        actionSave_set = new QAction(MainWindow);
        actionSave_set->setObjectName(QString::fromUtf8("actionSave_set"));
        actionLoad_voice = new QAction(MainWindow);
        actionLoad_voice->setObjectName(QString::fromUtf8("actionLoad_voice"));
        actionSave_voice = new QAction(MainWindow);
        actionSave_voice->setObjectName(QString::fromUtf8("actionSave_voice"));
        actionRead_this = new QAction(MainWindow);
        actionRead_this->setObjectName(QString::fromUtf8("actionRead_this"));
        actionSend_current_set = new QAction(MainWindow);
        actionSend_current_set->setObjectName(QString::fromUtf8("actionSend_current_set"));
        actionSend_current_voice = new QAction(MainWindow);
        actionSend_current_voice->setObjectName(QString::fromUtf8("actionSend_current_voice"));
        actionGet_current_set = new QAction(MainWindow);
        actionGet_current_set->setObjectName(QString::fromUtf8("actionGet_current_set"));
        actionGet_current_voice = new QAction(MainWindow);
        actionGet_current_voice->setObjectName(QString::fromUtf8("actionGet_current_voice"));
        actionGet_current_config = new QAction(MainWindow);
        actionGet_current_config->setObjectName(QString::fromUtf8("actionGet_current_config"));
        actionSend_current_config = new QAction(MainWindow);
        actionSend_current_config->setObjectName(QString::fromUtf8("actionSend_current_config"));
        actionRandomize = new QAction(MainWindow);
        actionRandomize->setObjectName(QString::fromUtf8("actionRandomize"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionInitialize = new QAction(MainWindow);
        actionInitialize->setObjectName(QString::fromUtf8("actionInitialize"));
        actionGet_all_banks = new QAction(MainWindow);
        actionGet_all_banks->setObjectName(QString::fromUtf8("actionGet_all_banks"));
        actionRam_1 = new QAction(MainWindow);
        actionRam_1->setObjectName(QString::fromUtf8("actionRam_1"));
        actionRam_2 = new QAction(MainWindow);
        actionRam_2->setObjectName(QString::fromUtf8("actionRam_2"));
        actionExchange = new QAction(MainWindow);
        actionExchange->setObjectName(QString::fromUtf8("actionExchange"));
        actionLoad_bank = new QAction(MainWindow);
        actionLoad_bank->setObjectName(QString::fromUtf8("actionLoad_bank"));
        actionSave_bank = new QAction(MainWindow);
        actionSave_bank->setObjectName(QString::fromUtf8("actionSave_bank"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(2000, 2000));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 641, 561));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMaximumSize(QSize(65535, 65535));
        tabWidget->setAutoFillBackground(false);
        tab_general = new QWidget();
        tab_general->setObjectName(QString::fromUtf8("tab_general"));
        tab_general->setEnabled(true);
        grpBox_MIDI = new QGroupBox(tab_general);
        grpBox_MIDI->setObjectName(QString::fromUtf8("grpBox_MIDI"));
        grpBox_MIDI->setGeometry(QRect(20, 60, 321, 141));
        cmbBox_MIDIIn = new QComboBox(grpBox_MIDI);
        cmbBox_MIDIIn->setObjectName(QString::fromUtf8("cmbBox_MIDIIn"));
        cmbBox_MIDIIn->setGeometry(QRect(50, 21, 261, 21));
        cmbBox_MIDIIn->setMaxVisibleItems(15);
        cmbBox_MIDIIn->setFrame(true);
        cmbBox_MIDIOut = new QComboBox(grpBox_MIDI);
        cmbBox_MIDIOut->setObjectName(QString::fromUtf8("cmbBox_MIDIOut"));
        cmbBox_MIDIOut->setGeometry(QRect(50, 50, 261, 21));
        cmbBox_MIDIOut->setMaxVisibleItems(15);
        cmbBox_MIDIOut->setFrame(true);
        pshBut_refresh_midi = new QPushButton(grpBox_MIDI);
        pshBut_refresh_midi->setObjectName(QString::fromUtf8("pshBut_refresh_midi"));
        pshBut_refresh_midi->setGeometry(QRect(50, 80, 75, 23));
        spnBox_syschan = new QSpinBox(grpBox_MIDI);
        spnBox_syschan->setObjectName(QString::fromUtf8("spnBox_syschan"));
        spnBox_syschan->setGeometry(QRect(260, 80, 51, 22));
        spnBox_syschan->setMinimum(1);
        spnBox_syschan->setMaximum(16);
        spnBox_syschan->setValue(1);
        lbl_syschan = new QLabel(grpBox_MIDI);
        lbl_syschan->setObjectName(QString::fromUtf8("lbl_syschan"));
        lbl_syschan->setGeometry(QRect(140, 80, 111, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbl_syschan->setFont(font);
        lbl_MIDIIn = new QLabel(grpBox_MIDI);
        lbl_MIDIIn->setObjectName(QString::fromUtf8("lbl_MIDIIn"));
        lbl_MIDIIn->setGeometry(QRect(10, 22, 21, 16));
        lbl_MIDIIn->setFont(font);
        lbl_MIDIIn_2 = new QLabel(grpBox_MIDI);
        lbl_MIDIIn_2->setObjectName(QString::fromUtf8("lbl_MIDIIn_2"));
        lbl_MIDIIn_2->setGeometry(QRect(10, 52, 31, 16));
        lbl_MIDIIn_2->setFont(font);
        spnBox_kybchan = new QSpinBox(grpBox_MIDI);
        spnBox_kybchan->setObjectName(QString::fromUtf8("spnBox_kybchan"));
        spnBox_kybchan->setGeometry(QRect(260, 110, 51, 22));
        spnBox_kybchan->setMinimum(1);
        spnBox_kybchan->setMaximum(16);
        spnBox_kybchan->setValue(1);
        lbl_kybchan = new QLabel(grpBox_MIDI);
        lbl_kybchan->setObjectName(QString::fromUtf8("lbl_kybchan"));
        lbl_kybchan->setGeometry(QRect(140, 110, 111, 20));
        lbl_kybchan->setFont(font);
        grpBox_config = new QGroupBox(tab_general);
        grpBox_config->setObjectName(QString::fromUtf8("grpBox_config"));
        grpBox_config->setGeometry(QRect(360, 20, 231, 221));
        lbl_combine = new QLabel(grpBox_config);
        lbl_combine->setObjectName(QString::fromUtf8("lbl_combine"));
        lbl_combine->setGeometry(QRect(10, 20, 101, 16));
        lbl_combine->setFont(font);
        lbl_reception = new QLabel(grpBox_config);
        lbl_reception->setObjectName(QString::fromUtf8("lbl_reception"));
        lbl_reception->setGeometry(QRect(10, 50, 101, 16));
        lbl_reception->setFont(font);
        cmbBox_reception = new QComboBox(grpBox_config);
        cmbBox_reception->setObjectName(QString::fromUtf8("cmbBox_reception"));
        cmbBox_reception->setGeometry(QRect(140, 50, 81, 22));
        pshBut_combine = new QPushButton(grpBox_config);
        pshBut_combine->setObjectName(QString::fromUtf8("pshBut_combine"));
        pshBut_combine->setGeometry(QRect(140, 20, 81, 21));
        pshBut_combine->setCheckable(true);
        pshBut_memory = new QPushButton(grpBox_config);
        pshBut_memory->setObjectName(QString::fromUtf8("pshBut_memory"));
        pshBut_memory->setGeometry(QRect(140, 80, 81, 21));
        pshBut_memory->setCheckable(true);
        lbl_memory = new QLabel(grpBox_config);
        lbl_memory->setObjectName(QString::fromUtf8("lbl_memory"));
        lbl_memory->setGeometry(QRect(10, 80, 111, 21));
        lbl_memory->setFont(font);
        spnBox_confnum = new QSpinBox(grpBox_config);
        spnBox_confnum->setObjectName(QString::fromUtf8("spnBox_confnum"));
        spnBox_confnum->setGeometry(QRect(140, 112, 81, 20));
        spnBox_confnum->setMinimum(1);
        spnBox_confnum->setMaximum(20);
        spnBox_confnum->setValue(1);
        lbl_confnum = new QLabel(grpBox_config);
        lbl_confnum->setObjectName(QString::fromUtf8("lbl_confnum"));
        lbl_confnum->setGeometry(QRect(10, 110, 101, 20));
        lbl_confnum->setFont(font);
        lbl_mastvol = new QLabel(grpBox_config);
        lbl_mastvol->setObjectName(QString::fromUtf8("lbl_mastvol"));
        lbl_mastvol->setGeometry(QRect(10, 140, 101, 20));
        lbl_mastvol->setFont(font);
        hzSlider_mastvol = new QSlider(grpBox_config);
        hzSlider_mastvol->setObjectName(QString::fromUtf8("hzSlider_mastvol"));
        hzSlider_mastvol->setGeometry(QRect(140, 140, 81, 21));
        hzSlider_mastvol->setMaximum(127);
        hzSlider_mastvol->setOrientation(Qt::Horizontal);
        label = new QLabel(grpBox_config);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 170, 211, 41));
        tabWidget->addTab(tab_general, QString());
        tab_banks = new QWidget();
        tab_banks->setObjectName(QString::fromUtf8("tab_banks"));
        widget_banks = new QBanks(tab_banks);
        widget_banks->setObjectName(QString::fromUtf8("widget_banks"));
        widget_banks->setGeometry(QRect(0, 0, 620, 532));
        tabWidget->addTab(tab_banks, QString());
        tab_set = new QWidget();
        tab_set->setObjectName(QString::fromUtf8("tab_set"));
        lbl_notes = new QLabel(tab_set);
        lbl_notes->setObjectName(QString::fromUtf8("lbl_notes"));
        lbl_notes->setGeometry(QRect(10, 40, 81, 16));
        lbl_notes->setFont(font);
        lbl_midichan = new QLabel(tab_set);
        lbl_midichan->setObjectName(QString::fromUtf8("lbl_midichan"));
        lbl_midichan->setGeometry(QRect(10, 70, 81, 16));
        lbl_midichan->setFont(font);
        lbl_upper = new QLabel(tab_set);
        lbl_upper->setObjectName(QString::fromUtf8("lbl_upper"));
        lbl_upper->setGeometry(QRect(10, 100, 81, 16));
        lbl_upper->setFont(font);
        lbl_lower = new QLabel(tab_set);
        lbl_lower->setObjectName(QString::fromUtf8("lbl_lower"));
        lbl_lower->setGeometry(QRect(10, 130, 81, 16));
        lbl_lower->setFont(font);
        lbl_bank = new QLabel(tab_set);
        lbl_bank->setObjectName(QString::fromUtf8("lbl_bank"));
        lbl_bank->setGeometry(QRect(10, 160, 81, 16));
        lbl_bank->setFont(font);
        lbl_voice = new QLabel(tab_set);
        lbl_voice->setObjectName(QString::fromUtf8("lbl_voice"));
        lbl_voice->setGeometry(QRect(10, 190, 81, 16));
        lbl_voice->setFont(font);
        lbl_detune = new QLabel(tab_set);
        lbl_detune->setObjectName(QString::fromUtf8("lbl_detune"));
        lbl_detune->setGeometry(QRect(10, 250, 81, 16));
        lbl_detune->setFont(font);
        lbl_voice_2 = new QLabel(tab_set);
        lbl_voice_2->setObjectName(QString::fromUtf8("lbl_voice_2"));
        lbl_voice_2->setGeometry(QRect(10, 220, 81, 16));
        lbl_voice_2->setFont(font);
        lbl_volume = new QLabel(tab_set);
        lbl_volume->setObjectName(QString::fromUtf8("lbl_volume"));
        lbl_volume->setGeometry(QRect(10, 280, 81, 16));
        lbl_volume->setFont(font);
        lbl_pan = new QLabel(tab_set);
        lbl_pan->setObjectName(QString::fromUtf8("lbl_pan"));
        lbl_pan->setGeometry(QRect(10, 310, 81, 16));
        lbl_pan->setFont(font);
        lbl_LFO = new QLabel(tab_set);
        lbl_LFO->setObjectName(QString::fromUtf8("lbl_LFO"));
        lbl_LFO->setGeometry(QRect(10, 340, 81, 16));
        lbl_LFO->setFont(font);
        lbl_porta = new QLabel(tab_set);
        lbl_porta->setObjectName(QString::fromUtf8("lbl_porta"));
        lbl_porta->setGeometry(QRect(10, 400, 81, 16));
        lbl_porta->setFont(font);
        lbl_pitch = new QLabel(tab_set);
        lbl_pitch->setObjectName(QString::fromUtf8("lbl_pitch"));
        lbl_pitch->setGeometry(QRect(10, 430, 81, 16));
        lbl_pitch->setFont(font);
        lbl_poly = new QLabel(tab_set);
        lbl_poly->setObjectName(QString::fromUtf8("lbl_poly"));
        lbl_poly->setGeometry(QRect(10, 370, 81, 16));
        lbl_poly->setFont(font);
        lbl_pmdctl = new QLabel(tab_set);
        lbl_pmdctl->setObjectName(QString::fromUtf8("lbl_pmdctl"));
        lbl_pmdctl->setGeometry(QRect(10, 460, 81, 16));
        lbl_pmdctl->setFont(font);
        pshBut_next = new QPushButton(tab_set);
        pshBut_next->setObjectName(QString::fromUtf8("pshBut_next"));
        pshBut_next->setGeometry(QRect(10, 10, 81, 21));
        frame_page_1 = new QFrame(tab_set);
        frame_page_1->setObjectName(QString::fromUtf8("frame_page_1"));
        frame_page_1->setGeometry(QRect(110, 10, 501, 521));
        frame_page_1->setFrameShape(QFrame::StyledPanel);
        frame_page_1->setFrameShadow(QFrame::Raised);
        widget_instru_4 = new QInstrument(frame_page_1);
        widget_instru_4->setObjectName(QString::fromUtf8("widget_instru_4"));
        widget_instru_4->setGeometry(QRect(390, 10, 111, 474));
        widget_instru_1 = new QInstrument(frame_page_1);
        widget_instru_1->setObjectName(QString::fromUtf8("widget_instru_1"));
        widget_instru_1->setGeometry(QRect(0, 10, 111, 474));
        widget_instru_2 = new QInstrument(frame_page_1);
        widget_instru_2->setObjectName(QString::fromUtf8("widget_instru_2"));
        widget_instru_2->setGeometry(QRect(130, 10, 111, 474));
        widget_instru_3 = new QInstrument(frame_page_1);
        widget_instru_3->setObjectName(QString::fromUtf8("widget_instru_3"));
        widget_instru_3->setGeometry(QRect(260, 10, 111, 474));
        pshBut_inst_cur_4 = new QPushButton(frame_page_1);
        pshBut_inst_cur_4->setObjectName(QString::fromUtf8("pshBut_inst_cur_4"));
        pshBut_inst_cur_4->setGeometry(QRect(400, 490, 81, 23));
        pshBut_inst_cur_4->setCheckable(true);
        pshBut_inst_cur_2 = new QPushButton(frame_page_1);
        pshBut_inst_cur_2->setObjectName(QString::fromUtf8("pshBut_inst_cur_2"));
        pshBut_inst_cur_2->setGeometry(QRect(140, 490, 81, 23));
        pshBut_inst_cur_2->setCheckable(true);
        pshBut_inst_cur_3 = new QPushButton(frame_page_1);
        pshBut_inst_cur_3->setObjectName(QString::fromUtf8("pshBut_inst_cur_3"));
        pshBut_inst_cur_3->setGeometry(QRect(270, 490, 81, 23));
        pshBut_inst_cur_3->setCheckable(true);
        pshBut_inst_cur_1 = new QPushButton(frame_page_1);
        pshBut_inst_cur_1->setObjectName(QString::fromUtf8("pshBut_inst_cur_1"));
        pshBut_inst_cur_1->setGeometry(QRect(10, 490, 81, 23));
        pshBut_inst_cur_1->setCheckable(true);
        frame_page_2 = new QFrame(tab_set);
        frame_page_2->setObjectName(QString::fromUtf8("frame_page_2"));
        frame_page_2->setGeometry(QRect(110, 10, 501, 521));
        frame_page_2->setFrameShape(QFrame::StyledPanel);
        frame_page_2->setFrameShadow(QFrame::Raised);
        widget_instru_8 = new QInstrument(frame_page_2);
        widget_instru_8->setObjectName(QString::fromUtf8("widget_instru_8"));
        widget_instru_8->setGeometry(QRect(390, 10, 111, 474));
        widget_instru_5 = new QInstrument(frame_page_2);
        widget_instru_5->setObjectName(QString::fromUtf8("widget_instru_5"));
        widget_instru_5->setGeometry(QRect(0, 10, 111, 474));
        widget_instru_6 = new QInstrument(frame_page_2);
        widget_instru_6->setObjectName(QString::fromUtf8("widget_instru_6"));
        widget_instru_6->setGeometry(QRect(130, 10, 111, 474));
        widget_instru_7 = new QInstrument(frame_page_2);
        widget_instru_7->setObjectName(QString::fromUtf8("widget_instru_7"));
        widget_instru_7->setGeometry(QRect(260, 10, 111, 474));
        pshBut_inst_cur_8 = new QPushButton(frame_page_2);
        pshBut_inst_cur_8->setObjectName(QString::fromUtf8("pshBut_inst_cur_8"));
        pshBut_inst_cur_8->setGeometry(QRect(400, 490, 81, 23));
        pshBut_inst_cur_8->setCheckable(true);
        pshBut_inst_cur_6 = new QPushButton(frame_page_2);
        pshBut_inst_cur_6->setObjectName(QString::fromUtf8("pshBut_inst_cur_6"));
        pshBut_inst_cur_6->setGeometry(QRect(140, 490, 81, 23));
        pshBut_inst_cur_6->setCheckable(true);
        pshBut_inst_cur_7 = new QPushButton(frame_page_2);
        pshBut_inst_cur_7->setObjectName(QString::fromUtf8("pshBut_inst_cur_7"));
        pshBut_inst_cur_7->setGeometry(QRect(270, 490, 81, 23));
        pshBut_inst_cur_7->setCheckable(true);
        pshBut_inst_cur_5 = new QPushButton(frame_page_2);
        pshBut_inst_cur_5->setObjectName(QString::fromUtf8("pshBut_inst_cur_5"));
        pshBut_inst_cur_5->setGeometry(QRect(10, 490, 81, 23));
        pshBut_inst_cur_5->setCheckable(true);
        txtEdit_setname = new QPlainTextEdit(tab_set);
        txtEdit_setname->setObjectName(QString::fromUtf8("txtEdit_setname"));
        txtEdit_setname->setGeometry(QRect(10, 496, 91, 31));
        txtEdit_setname->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_setname->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_setname->setLineWrapMode(QPlainTextEdit::NoWrap);
        txtEdit_setname->setMaximumBlockCount(0);
        tabWidget->addTab(tab_set, QString());
        tab_voice = new QWidget();
        tab_voice->setObjectName(QString::fromUtf8("tab_voice"));
        widget_voice = new QVoice(tab_voice);
        widget_voice->setObjectName(QString::fromUtf8("widget_voice"));
        widget_voice->setGeometry(QRect(20, 20, 574, 274));
        tabWidget->addTab(tab_voice, QString());
        tab_operas = new QWidget();
        tab_operas->setObjectName(QString::fromUtf8("tab_operas"));
        widget_opera_1 = new QOperateur(tab_operas);
        widget_opera_1->setObjectName(QString::fromUtf8("widget_opera_1"));
        widget_opera_1->setGeometry(QRect(30, 10, 264, 224));
        pshBut_OPon_1 = new QPushButton(widget_opera_1);
        pshBut_OPon_1->setObjectName(QString::fromUtf8("pshBut_OPon_1"));
        pshBut_OPon_1->setGeometry(QRect(220, 20, 31, 31));
        pshBut_OPon_1->setCheckable(true);
        widget_opera_2 = new QOperateur(tab_operas);
        widget_opera_2->setObjectName(QString::fromUtf8("widget_opera_2"));
        widget_opera_2->setGeometry(QRect(330, 10, 264, 224));
        pshBut_OPon_2 = new QPushButton(widget_opera_2);
        pshBut_OPon_2->setObjectName(QString::fromUtf8("pshBut_OPon_2"));
        pshBut_OPon_2->setGeometry(QRect(220, 20, 31, 31));
        pshBut_OPon_2->setCheckable(true);
        widget_opera_3 = new QOperateur(tab_operas);
        widget_opera_3->setObjectName(QString::fromUtf8("widget_opera_3"));
        widget_opera_3->setGeometry(QRect(30, 270, 264, 224));
        pshBut_OPon_3 = new QPushButton(widget_opera_3);
        pshBut_OPon_3->setObjectName(QString::fromUtf8("pshBut_OPon_3"));
        pshBut_OPon_3->setGeometry(QRect(220, 20, 31, 31));
        pshBut_OPon_3->setCheckable(true);
        widget_opera_4 = new QOperateur(tab_operas);
        widget_opera_4->setObjectName(QString::fromUtf8("widget_opera_4"));
        widget_opera_4->setGeometry(QRect(330, 270, 264, 224));
        pshBut_OPon_4 = new QPushButton(widget_opera_4);
        pshBut_OPon_4->setObjectName(QString::fromUtf8("pshBut_OPon_4"));
        pshBut_OPon_4->setGeometry(QRect(220, 20, 31, 31));
        pshBut_OPon_4->setCheckable(true);
        pshBut_op_cur_1 = new QPushButton(tab_operas);
        pshBut_op_cur_1->setObjectName(QString::fromUtf8("pshBut_op_cur_1"));
        pshBut_op_cur_1->setGeometry(QRect(120, 240, 91, 23));
        pshBut_op_cur_1->setCheckable(true);
        pshBut_op_cur_2 = new QPushButton(tab_operas);
        pshBut_op_cur_2->setObjectName(QString::fromUtf8("pshBut_op_cur_2"));
        pshBut_op_cur_2->setGeometry(QRect(420, 240, 91, 23));
        pshBut_op_cur_2->setCheckable(true);
        pshBut_op_cur_3 = new QPushButton(tab_operas);
        pshBut_op_cur_3->setObjectName(QString::fromUtf8("pshBut_op_cur_3"));
        pshBut_op_cur_3->setGeometry(QRect(120, 500, 91, 23));
        pshBut_op_cur_3->setCheckable(true);
        pshBut_op_cur_4 = new QPushButton(tab_operas);
        pshBut_op_cur_4->setObjectName(QString::fromUtf8("pshBut_op_cur_4"));
        pshBut_op_cur_4->setGeometry(QRect(420, 500, 91, 23));
        pshBut_op_cur_4->setCheckable(true);
        tabWidget->addTab(tab_operas, QString());
        lbl_clavier = new QClavier(centralWidget);
        lbl_clavier->setObjectName(QString::fromUtf8("lbl_clavier"));
        lbl_clavier->setGeometry(QRect(10, 560, 601, 51));
        lbl_clavier->setMouseTracking(true);
        lbl_clavier->setPixmap(QPixmap(QString::fromUtf8(":/CLAVIER")));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 620, 20));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuConfig = new QMenu(menuBar);
        menuConfig->setObjectName(QString::fromUtf8("menuConfig"));
        menuSend_bank = new QMenu(menuConfig);
        menuSend_bank->setObjectName(QString::fromUtf8("menuSend_bank"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuConfig->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFichier->addAction(actionLoad_bank);
        menuFichier->addAction(actionSave_bank);
        menuFichier->addSeparator();
        menuFichier->addAction(actionLoad_set);
        menuFichier->addAction(actionSave_set);
        menuFichier->addSeparator();
        menuFichier->addAction(actionLoad_voice);
        menuFichier->addAction(actionSave_voice);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionRead_this);
        menuHelp->addSeparator();
        menuHelp->addAction(actionOnline_help);
        menuConfig->addAction(actionGet_current_config);
        menuConfig->addAction(actionSend_current_config);
        menuConfig->addSeparator();
        menuConfig->addAction(actionGet_all_banks);
        menuConfig->addAction(menuSend_bank->menuAction());
        menuConfig->addSeparator();
        menuConfig->addAction(actionGet_current_set);
        menuConfig->addAction(actionSend_current_set);
        menuConfig->addSeparator();
        menuConfig->addAction(actionGet_current_voice);
        menuConfig->addAction(actionSend_current_voice);
        menuSend_bank->addAction(actionRam_1);
        menuSend_bank->addAction(actionRam_2);
        menuEdit->addAction(actionInitialize);
        menuEdit->addAction(actionRandomize);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionExchange);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FB01 : Sound Editor V1.0", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About ...", 0, QApplication::UnicodeUTF8));
        actionOnline_help->setText(QApplication::translate("MainWindow", "Online help ...", 0, QApplication::UnicodeUTF8));
        actionLoad_set->setText(QApplication::translate("MainWindow", "Load set ...", 0, QApplication::UnicodeUTF8));
        actionSave_set->setText(QApplication::translate("MainWindow", "Save set ...", 0, QApplication::UnicodeUTF8));
        actionLoad_voice->setText(QApplication::translate("MainWindow", "Load voice ...", 0, QApplication::UnicodeUTF8));
        actionSave_voice->setText(QApplication::translate("MainWindow", "Save voice ...", 0, QApplication::UnicodeUTF8));
        actionRead_this->setText(QApplication::translate("MainWindow", "Read this ...", 0, QApplication::UnicodeUTF8));
        actionSend_current_set->setText(QApplication::translate("MainWindow", "Send current set", 0, QApplication::UnicodeUTF8));
        actionSend_current_voice->setText(QApplication::translate("MainWindow", "Send current voice", 0, QApplication::UnicodeUTF8));
        actionGet_current_set->setText(QApplication::translate("MainWindow", "Get current set", 0, QApplication::UnicodeUTF8));
        actionGet_current_voice->setText(QApplication::translate("MainWindow", "Get current voice", 0, QApplication::UnicodeUTF8));
        actionGet_current_config->setText(QApplication::translate("MainWindow", "Get current config", 0, QApplication::UnicodeUTF8));
        actionSend_current_config->setText(QApplication::translate("MainWindow", "Send current config", 0, QApplication::UnicodeUTF8));
        actionRandomize->setText(QApplication::translate("MainWindow", "Randomize", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0, QApplication::UnicodeUTF8));
        actionInitialize->setText(QApplication::translate("MainWindow", "Initialize", 0, QApplication::UnicodeUTF8));
        actionGet_all_banks->setText(QApplication::translate("MainWindow", "Get all banks", 0, QApplication::UnicodeUTF8));
        actionRam_1->setText(QApplication::translate("MainWindow", "Ram 1", 0, QApplication::UnicodeUTF8));
        actionRam_2->setText(QApplication::translate("MainWindow", "Ram 2", 0, QApplication::UnicodeUTF8));
        actionExchange->setText(QApplication::translate("MainWindow", "Exchange", 0, QApplication::UnicodeUTF8));
        actionLoad_bank->setText(QApplication::translate("MainWindow", "Load bank ...", 0, QApplication::UnicodeUTF8));
        actionSave_bank->setText(QApplication::translate("MainWindow", "Save bank ...", 0, QApplication::UnicodeUTF8));
        grpBox_MIDI->setTitle(QApplication::translate("MainWindow", "MIDI Ports", 0, QApplication::UnicodeUTF8));
        pshBut_refresh_midi->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        lbl_syschan->setText(QApplication::translate("MainWindow", "System channel :", 0, QApplication::UnicodeUTF8));
        lbl_MIDIIn->setText(QApplication::translate("MainWindow", "IN :", 0, QApplication::UnicodeUTF8));
        lbl_MIDIIn_2->setText(QApplication::translate("MainWindow", "OUT :", 0, QApplication::UnicodeUTF8));
        lbl_kybchan->setText(QApplication::translate("MainWindow", "Keyboard channel :", 0, QApplication::UnicodeUTF8));
        grpBox_config->setTitle(QApplication::translate("MainWindow", "Configuration", 0, QApplication::UnicodeUTF8));
        lbl_combine->setText(QApplication::translate("MainWindow", "Combine mode :", 0, QApplication::UnicodeUTF8));
        lbl_reception->setText(QApplication::translate("MainWindow", "Reception mode :", 0, QApplication::UnicodeUTF8));
        cmbBox_reception->clear();
        cmbBox_reception->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "All", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Even", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Odd", 0, QApplication::UnicodeUTF8)
        );
        pshBut_combine->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
        pshBut_memory->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
        lbl_memory->setText(QApplication::translate("MainWindow", "Memory protect :", 0, QApplication::UnicodeUTF8));
        lbl_confnum->setText(QApplication::translate("MainWindow", "Config. number :", 0, QApplication::UnicodeUTF8));
        lbl_mastvol->setText(QApplication::translate("MainWindow", "Master volume :", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">These informations cannot be retrieved</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">from the FB01 sound module. You must set</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">them manually.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_general), QApplication::translate("MainWindow", "General", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_banks), QApplication::translate("MainWindow", "Banks", 0, QApplication::UnicodeUTF8));
        lbl_notes->setText(QApplication::translate("MainWindow", "Num of notes :", 0, QApplication::UnicodeUTF8));
        lbl_midichan->setText(QApplication::translate("MainWindow", "MIDI Channel :", 0, QApplication::UnicodeUTF8));
        lbl_upper->setText(QApplication::translate("MainWindow", "Upper limit :", 0, QApplication::UnicodeUTF8));
        lbl_lower->setText(QApplication::translate("MainWindow", "Lower limit :", 0, QApplication::UnicodeUTF8));
        lbl_bank->setText(QApplication::translate("MainWindow", "Bank :", 0, QApplication::UnicodeUTF8));
        lbl_voice->setText(QApplication::translate("MainWindow", "Voice :", 0, QApplication::UnicodeUTF8));
        lbl_detune->setText(QApplication::translate("MainWindow", "Detune :", 0, QApplication::UnicodeUTF8));
        lbl_voice_2->setText(QApplication::translate("MainWindow", "Transpose :", 0, QApplication::UnicodeUTF8));
        lbl_volume->setText(QApplication::translate("MainWindow", "Volume :", 0, QApplication::UnicodeUTF8));
        lbl_pan->setText(QApplication::translate("MainWindow", "Pan :", 0, QApplication::UnicodeUTF8));
        lbl_LFO->setText(QApplication::translate("MainWindow", "Enable LFO :", 0, QApplication::UnicodeUTF8));
        lbl_porta->setText(QApplication::translate("MainWindow", "Porta. time :", 0, QApplication::UnicodeUTF8));
        lbl_pitch->setText(QApplication::translate("MainWindow", "Pitch bender :", 0, QApplication::UnicodeUTF8));
        lbl_poly->setText(QApplication::translate("MainWindow", "Mono / Poly :", 0, QApplication::UnicodeUTF8));
        lbl_pmdctl->setText(QApplication::translate("MainWindow", "PMD Control.", 0, QApplication::UnicodeUTF8));
        pshBut_next->setText(QApplication::translate("MainWindow", "Next page", 0, QApplication::UnicodeUTF8));
        pshBut_inst_cur_4->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_inst_cur_2->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_inst_cur_3->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_inst_cur_1->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_inst_cur_8->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_inst_cur_6->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_inst_cur_7->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_inst_cur_5->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_set), QApplication::translate("MainWindow", "Current Set", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_voice), QApplication::translate("MainWindow", "Current Voice", 0, QApplication::UnicodeUTF8));
        pshBut_OPon_1->setText(QApplication::translate("MainWindow", "On", 0, QApplication::UnicodeUTF8));
        pshBut_OPon_2->setText(QApplication::translate("MainWindow", "On", 0, QApplication::UnicodeUTF8));
        pshBut_OPon_3->setText(QApplication::translate("MainWindow", "On", 0, QApplication::UnicodeUTF8));
        pshBut_OPon_4->setText(QApplication::translate("MainWindow", "On", 0, QApplication::UnicodeUTF8));
        pshBut_op_cur_1->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_op_cur_2->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_op_cur_3->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        pshBut_op_cur_4->setText(QApplication::translate("MainWindow", "Current", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_operas), QApplication::translate("MainWindow", "Current Operators", 0, QApplication::UnicodeUTF8));
        lbl_clavier->setText(QString());
        menuFichier->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuConfig->setTitle(QApplication::translate("MainWindow", "Configuration", 0, QApplication::UnicodeUTF8));
        menuSend_bank->setTitle(QApplication::translate("MainWindow", "Send bank", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
