/********************************************************************************
** Form generated from reading UI file 'qinstrument.ui'
**
** Created: Tue 18. May 13:14:31 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QINSTRUMENT_H
#define UI_QINSTRUMENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QInstrument
{
public:
    QGroupBox *grpBox_instru;
    QSpinBox *spnBox_notes;
    QSpinBox *spnBox_chan;
    QSpinBox *spnBox_bank;
    QSpinBox *spnBox_voice;
    QComboBox *cmbBox_trans;
    QSpinBox *spnBox_detune;
    QSlider *hzSlider_volume;
    QSlider *hzSlider_pan;
    QPushButton *pshBut_LFO;
    QPushButton *pshBut_poly;
    QSpinBox *spnBox_porta;
    QSpinBox *spnBox_pitch;
    QComboBox *cmbBox_pmdctl;
    QComboBox *cmbBox_upper;
    QComboBox *cmbBox_lower;

    void setupUi(QWidget *QInstrument)
    {
        if (QInstrument->objectName().isEmpty())
            QInstrument->setObjectName(QString::fromUtf8("QInstrument"));
        QInstrument->resize(104, 474);
        grpBox_instru = new QGroupBox(QInstrument);
        grpBox_instru->setObjectName(QString::fromUtf8("grpBox_instru"));
        grpBox_instru->setGeometry(QRect(0, 0, 101, 471));
        spnBox_notes = new QSpinBox(grpBox_instru);
        spnBox_notes->setObjectName(QString::fromUtf8("spnBox_notes"));
        spnBox_notes->setGeometry(QRect(11, 20, 81, 22));
        spnBox_notes->setMaximum(8);
        spnBox_chan = new QSpinBox(grpBox_instru);
        spnBox_chan->setObjectName(QString::fromUtf8("spnBox_chan"));
        spnBox_chan->setGeometry(QRect(10, 50, 81, 22));
        spnBox_chan->setMinimum(1);
        spnBox_chan->setMaximum(16);
        spnBox_bank = new QSpinBox(grpBox_instru);
        spnBox_bank->setObjectName(QString::fromUtf8("spnBox_bank"));
        spnBox_bank->setGeometry(QRect(10, 140, 81, 22));
        spnBox_bank->setMaximum(6);
        spnBox_voice = new QSpinBox(grpBox_instru);
        spnBox_voice->setObjectName(QString::fromUtf8("spnBox_voice"));
        spnBox_voice->setGeometry(QRect(10, 170, 81, 22));
        spnBox_voice->setMaximum(47);
        cmbBox_trans = new QComboBox(grpBox_instru);
        cmbBox_trans->setObjectName(QString::fromUtf8("cmbBox_trans"));
        cmbBox_trans->setGeometry(QRect(10, 200, 81, 22));
        spnBox_detune = new QSpinBox(grpBox_instru);
        spnBox_detune->setObjectName(QString::fromUtf8("spnBox_detune"));
        spnBox_detune->setGeometry(QRect(10, 230, 81, 22));
        spnBox_detune->setMinimum(-64);
        spnBox_detune->setMaximum(63);
        hzSlider_volume = new QSlider(grpBox_instru);
        hzSlider_volume->setObjectName(QString::fromUtf8("hzSlider_volume"));
        hzSlider_volume->setGeometry(QRect(10, 260, 81, 21));
        hzSlider_volume->setMaximum(127);
        hzSlider_volume->setOrientation(Qt::Horizontal);
        hzSlider_pan = new QSlider(grpBox_instru);
        hzSlider_pan->setObjectName(QString::fromUtf8("hzSlider_pan"));
        hzSlider_pan->setGeometry(QRect(10, 290, 81, 21));
        hzSlider_pan->setMaximum(127);
        hzSlider_pan->setOrientation(Qt::Horizontal);
        pshBut_LFO = new QPushButton(grpBox_instru);
        pshBut_LFO->setObjectName(QString::fromUtf8("pshBut_LFO"));
        pshBut_LFO->setGeometry(QRect(10, 320, 81, 21));
        pshBut_LFO->setCheckable(true);
        pshBut_poly = new QPushButton(grpBox_instru);
        pshBut_poly->setObjectName(QString::fromUtf8("pshBut_poly"));
        pshBut_poly->setGeometry(QRect(10, 350, 81, 21));
        pshBut_poly->setCheckable(true);
        spnBox_porta = new QSpinBox(grpBox_instru);
        spnBox_porta->setObjectName(QString::fromUtf8("spnBox_porta"));
        spnBox_porta->setGeometry(QRect(10, 380, 81, 22));
        spnBox_porta->setMaximum(127);
        spnBox_pitch = new QSpinBox(grpBox_instru);
        spnBox_pitch->setObjectName(QString::fromUtf8("spnBox_pitch"));
        spnBox_pitch->setGeometry(QRect(10, 410, 81, 22));
        spnBox_pitch->setMaximum(12);
        cmbBox_pmdctl = new QComboBox(grpBox_instru);
        cmbBox_pmdctl->setObjectName(QString::fromUtf8("cmbBox_pmdctl"));
        cmbBox_pmdctl->setGeometry(QRect(10, 440, 81, 22));
        cmbBox_upper = new QComboBox(grpBox_instru);
        cmbBox_upper->setObjectName(QString::fromUtf8("cmbBox_upper"));
        cmbBox_upper->setGeometry(QRect(10, 80, 81, 22));
        cmbBox_lower = new QComboBox(grpBox_instru);
        cmbBox_lower->setObjectName(QString::fromUtf8("cmbBox_lower"));
        cmbBox_lower->setGeometry(QRect(10, 110, 81, 22));

        retranslateUi(QInstrument);

        QMetaObject::connectSlotsByName(QInstrument);
    } // setupUi

    void retranslateUi(QWidget *QInstrument)
    {
        QInstrument->setWindowTitle(QApplication::translate("QInstrument", "Form", 0, QApplication::UnicodeUTF8));
        grpBox_instru->setTitle(QApplication::translate("QInstrument", "Instrument", 0, QApplication::UnicodeUTF8));
        cmbBox_trans->clear();
        cmbBox_trans->insertItems(0, QStringList()
         << QApplication::translate("QInstrument", "-2 Octaves", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QInstrument", "-1 Octave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QInstrument", "0 Octave", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QInstrument", "1 Octaves", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QInstrument", "2 Octaves", 0, QApplication::UnicodeUTF8)
        );
        pshBut_LFO->setText(QApplication::translate("QInstrument", "Enable", 0, QApplication::UnicodeUTF8));
        pshBut_poly->setText(QApplication::translate("QInstrument", "Poly", 0, QApplication::UnicodeUTF8));
        cmbBox_pmdctl->clear();
        cmbBox_pmdctl->insertItems(0, QStringList()
         << QApplication::translate("QInstrument", "Not assigned", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QInstrument", "After touch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QInstrument", "Mod. wheel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QInstrument", "Breath ctl.", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QInstrument", "Foot ctl.", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class QInstrument: public Ui_QInstrument {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QINSTRUMENT_H
