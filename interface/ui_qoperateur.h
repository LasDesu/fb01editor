/********************************************************************************
** Form generated from reading UI file 'qoperateur.ui'
**
** Created: Tue 18. May 13:14:30 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QOPERATEUR_H
#define UI_QOPERATEUR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include "qenveloppe.h"

QT_BEGIN_NAMESPACE

class Ui_QOperateur
{
public:
    QGroupBox *grpBox_opera;
    QSpinBox *spnBox_AR;
    QSpinBox *spnBox_D1R;
    QSpinBox *spnBox_SL;
    QSpinBox *spnBox_D2R;
    QSpinBox *spnBox_RR;
    QLabel *lbl_AR;
    QLabel *lbl_D1R;
    QLabel *lbl_SL;
    QLabel *lbl_D2R;
    QLabel *lbl_RR;
    QLabel *lbl_ARvel;
    QSpinBox *spnBox_velAR;
    QSpinBox *spnBox_vellvl;
    QLabel *lbl_lvlAR;
    QLabel *lbl_detune;
    QSpinBox *spnBox_coarse;
    QLabel *lbl_coarse;
    QSpinBox *spnBox_multiple;
    QLabel *lbl_multiple;
    QSpinBox *spnBox_fine;
    QLabel *lbl_lvldph;
    QSpinBox *spnBox_lvldph;
    QLabel *lbl_lvlcurb;
    QLabel *lbl_rtdph;
    QSpinBox *spnBox_rtdph;
    QSpinBox *spnBox_adjTL;
    QLabel *lbl_adjTL;
    QPushButton *pshBut_carrier;
    QLabel *lbl_carrmod;
    QLabel *lbl_volume;
    QComboBox *cmbBox_lvlcurb;
    QEnveloppe *label_env;
    QSlider *hzSlider_volume;

    void setupUi(QWidget *QOperateur)
    {
        if (QOperateur->objectName().isEmpty())
            QOperateur->setObjectName(QString::fromUtf8("QOperateur"));
        QOperateur->resize(264, 224);
        grpBox_opera = new QGroupBox(QOperateur);
        grpBox_opera->setObjectName(QString::fromUtf8("grpBox_opera"));
        grpBox_opera->setGeometry(QRect(0, 0, 261, 221));
        spnBox_AR = new QSpinBox(grpBox_opera);
        spnBox_AR->setObjectName(QString::fromUtf8("spnBox_AR"));
        spnBox_AR->setGeometry(QRect(10, 90, 41, 22));
        spnBox_AR->setMaximum(31);
        spnBox_D1R = new QSpinBox(grpBox_opera);
        spnBox_D1R->setObjectName(QString::fromUtf8("spnBox_D1R"));
        spnBox_D1R->setGeometry(QRect(60, 90, 41, 22));
        spnBox_D1R->setMaximum(31);
        spnBox_SL = new QSpinBox(grpBox_opera);
        spnBox_SL->setObjectName(QString::fromUtf8("spnBox_SL"));
        spnBox_SL->setGeometry(QRect(110, 90, 41, 22));
        spnBox_SL->setMaximum(15);
        spnBox_D2R = new QSpinBox(grpBox_opera);
        spnBox_D2R->setObjectName(QString::fromUtf8("spnBox_D2R"));
        spnBox_D2R->setGeometry(QRect(160, 90, 41, 22));
        spnBox_D2R->setMaximum(31);
        spnBox_RR = new QSpinBox(grpBox_opera);
        spnBox_RR->setObjectName(QString::fromUtf8("spnBox_RR"));
        spnBox_RR->setGeometry(QRect(210, 90, 41, 22));
        spnBox_RR->setMaximum(15);
        lbl_AR = new QLabel(grpBox_opera);
        lbl_AR->setObjectName(QString::fromUtf8("lbl_AR"));
        lbl_AR->setGeometry(QRect(20, 70, 20, 20));
        lbl_D1R = new QLabel(grpBox_opera);
        lbl_D1R->setObjectName(QString::fromUtf8("lbl_D1R"));
        lbl_D1R->setGeometry(QRect(70, 70, 20, 20));
        lbl_SL = new QLabel(grpBox_opera);
        lbl_SL->setObjectName(QString::fromUtf8("lbl_SL"));
        lbl_SL->setGeometry(QRect(120, 70, 20, 20));
        lbl_D2R = new QLabel(grpBox_opera);
        lbl_D2R->setObjectName(QString::fromUtf8("lbl_D2R"));
        lbl_D2R->setGeometry(QRect(170, 70, 20, 20));
        lbl_RR = new QLabel(grpBox_opera);
        lbl_RR->setObjectName(QString::fromUtf8("lbl_RR"));
        lbl_RR->setGeometry(QRect(220, 70, 20, 20));
        lbl_ARvel = new QLabel(grpBox_opera);
        lbl_ARvel->setObjectName(QString::fromUtf8("lbl_ARvel"));
        lbl_ARvel->setGeometry(QRect(60, 20, 41, 20));
        spnBox_velAR = new QSpinBox(grpBox_opera);
        spnBox_velAR->setObjectName(QString::fromUtf8("spnBox_velAR"));
        spnBox_velAR->setGeometry(QRect(60, 40, 41, 22));
        spnBox_velAR->setMaximum(3);
        spnBox_vellvl = new QSpinBox(grpBox_opera);
        spnBox_vellvl->setObjectName(QString::fromUtf8("spnBox_vellvl"));
        spnBox_vellvl->setGeometry(QRect(10, 40, 41, 22));
        spnBox_vellvl->setMaximum(31);
        lbl_lvlAR = new QLabel(grpBox_opera);
        lbl_lvlAR->setObjectName(QString::fromUtf8("lbl_lvlAR"));
        lbl_lvlAR->setGeometry(QRect(10, 20, 41, 20));
        lbl_detune = new QLabel(grpBox_opera);
        lbl_detune->setObjectName(QString::fromUtf8("lbl_detune"));
        lbl_detune->setGeometry(QRect(110, 120, 41, 20));
        spnBox_coarse = new QSpinBox(grpBox_opera);
        spnBox_coarse->setObjectName(QString::fromUtf8("spnBox_coarse"));
        spnBox_coarse->setGeometry(QRect(10, 140, 41, 22));
        spnBox_coarse->setMaximum(3);
        lbl_coarse = new QLabel(grpBox_opera);
        lbl_coarse->setObjectName(QString::fromUtf8("lbl_coarse"));
        lbl_coarse->setGeometry(QRect(10, 120, 41, 20));
        spnBox_multiple = new QSpinBox(grpBox_opera);
        spnBox_multiple->setObjectName(QString::fromUtf8("spnBox_multiple"));
        spnBox_multiple->setGeometry(QRect(60, 140, 41, 22));
        spnBox_multiple->setMaximum(15);
        lbl_multiple = new QLabel(grpBox_opera);
        lbl_multiple->setObjectName(QString::fromUtf8("lbl_multiple"));
        lbl_multiple->setGeometry(QRect(69, 120, 31, 20));
        spnBox_fine = new QSpinBox(grpBox_opera);
        spnBox_fine->setObjectName(QString::fromUtf8("spnBox_fine"));
        spnBox_fine->setGeometry(QRect(110, 140, 41, 22));
        spnBox_fine->setMinimum(-4);
        spnBox_fine->setMaximum(3);
        lbl_lvldph = new QLabel(grpBox_opera);
        lbl_lvldph->setObjectName(QString::fromUtf8("lbl_lvldph"));
        lbl_lvldph->setGeometry(QRect(59, 170, 41, 20));
        spnBox_lvldph = new QSpinBox(grpBox_opera);
        spnBox_lvldph->setObjectName(QString::fromUtf8("spnBox_lvldph"));
        spnBox_lvldph->setGeometry(QRect(60, 190, 41, 22));
        spnBox_lvldph->setMaximum(15);
        lbl_lvlcurb = new QLabel(grpBox_opera);
        lbl_lvlcurb->setObjectName(QString::fromUtf8("lbl_lvlcurb"));
        lbl_lvlcurb->setGeometry(QRect(10, 170, 51, 20));
        lbl_rtdph = new QLabel(grpBox_opera);
        lbl_rtdph->setObjectName(QString::fromUtf8("lbl_rtdph"));
        lbl_rtdph->setGeometry(QRect(110, 170, 41, 20));
        spnBox_rtdph = new QSpinBox(grpBox_opera);
        spnBox_rtdph->setObjectName(QString::fromUtf8("spnBox_rtdph"));
        spnBox_rtdph->setGeometry(QRect(110, 190, 41, 22));
        spnBox_rtdph->setMaximum(3);
        spnBox_adjTL = new QSpinBox(grpBox_opera);
        spnBox_adjTL->setObjectName(QString::fromUtf8("spnBox_adjTL"));
        spnBox_adjTL->setGeometry(QRect(160, 190, 41, 22));
        spnBox_adjTL->setMaximum(15);
        lbl_adjTL = new QLabel(grpBox_opera);
        lbl_adjTL->setObjectName(QString::fromUtf8("lbl_adjTL"));
        lbl_adjTL->setGeometry(QRect(160, 170, 41, 20));
        pshBut_carrier = new QPushButton(grpBox_opera);
        pshBut_carrier->setObjectName(QString::fromUtf8("pshBut_carrier"));
        pshBut_carrier->setGeometry(QRect(164, 140, 31, 23));
        pshBut_carrier->setCheckable(true);
        lbl_carrmod = new QLabel(grpBox_opera);
        lbl_carrmod->setObjectName(QString::fromUtf8("lbl_carrmod"));
        lbl_carrmod->setGeometry(QRect(156, 120, 51, 20));
        lbl_volume = new QLabel(grpBox_opera);
        lbl_volume->setObjectName(QString::fromUtf8("lbl_volume"));
        lbl_volume->setGeometry(QRect(214, 120, 41, 20));
        cmbBox_lvlcurb = new QComboBox(grpBox_opera);
        cmbBox_lvlcurb->setObjectName(QString::fromUtf8("cmbBox_lvlcurb"));
        cmbBox_lvlcurb->setGeometry(QRect(10, 190, 41, 22));
        label_env = new QEnveloppe(grpBox_opera);
        label_env->setObjectName(QString::fromUtf8("label_env"));
        label_env->setGeometry(QRect(110, 26, 118, 41));
        label_env->setFrameShape(QFrame::StyledPanel);
        hzSlider_volume = new QSlider(grpBox_opera);
        hzSlider_volume->setObjectName(QString::fromUtf8("hzSlider_volume"));
        hzSlider_volume->setGeometry(QRect(220, 150, 21, 61));
        hzSlider_volume->setMaximum(127);
        hzSlider_volume->setOrientation(Qt::Vertical);

        retranslateUi(QOperateur);

        QMetaObject::connectSlotsByName(QOperateur);
    } // setupUi

    void retranslateUi(QWidget *QOperateur)
    {
        QOperateur->setWindowTitle(QApplication::translate("QOperateur", "Form", 0, QApplication::UnicodeUTF8));
        grpBox_opera->setTitle(QApplication::translate("QOperateur", "Operator", 0, QApplication::UnicodeUTF8));
        lbl_AR->setText(QApplication::translate("QOperateur", "AR", 0, QApplication::UnicodeUTF8));
        lbl_D1R->setText(QApplication::translate("QOperateur", "D1R", 0, QApplication::UnicodeUTF8));
        lbl_SL->setText(QApplication::translate("QOperateur", "SL", 0, QApplication::UnicodeUTF8));
        lbl_D2R->setText(QApplication::translate("QOperateur", "D2R", 0, QApplication::UnicodeUTF8));
        lbl_RR->setText(QApplication::translate("QOperateur", "RR", 0, QApplication::UnicodeUTF8));
        lbl_ARvel->setText(QApplication::translate("QOperateur", "AR. Vel.", 0, QApplication::UnicodeUTF8));
        lbl_lvlAR->setText(QApplication::translate("QOperateur", " Lvl. Vel.", 0, QApplication::UnicodeUTF8));
        lbl_detune->setText(QApplication::translate("QOperateur", "Fine", 0, QApplication::UnicodeUTF8));
        lbl_coarse->setText(QApplication::translate("QOperateur", "Coarse", 0, QApplication::UnicodeUTF8));
        lbl_multiple->setText(QApplication::translate("QOperateur", "Mult.", 0, QApplication::UnicodeUTF8));
        lbl_lvldph->setText(QApplication::translate("QOperateur", "Lvl. Dph.", 0, QApplication::UnicodeUTF8));
        lbl_lvlcurb->setText(QApplication::translate("QOperateur", "Lvl. Curb.", 0, QApplication::UnicodeUTF8));
        lbl_rtdph->setText(QApplication::translate("QOperateur", "Rt. Dph.", 0, QApplication::UnicodeUTF8));
        lbl_adjTL->setText(QApplication::translate("QOperateur", "Adj. TL", 0, QApplication::UnicodeUTF8));
        pshBut_carrier->setText(QApplication::translate("QOperateur", "Car.", 0, QApplication::UnicodeUTF8));
        lbl_carrmod->setText(QApplication::translate("QOperateur", "Car./Mod.", 0, QApplication::UnicodeUTF8));
        lbl_volume->setText(QApplication::translate("QOperateur", "Volume", 0, QApplication::UnicodeUTF8));
        cmbBox_lvlcurb->clear();
        cmbBox_lvlcurb->insertItems(0, QStringList()
         << QApplication::translate("QOperateur", "-Lin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QOperateur", "+Lin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QOperateur", "-Exp", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QOperateur", "+Exp", 0, QApplication::UnicodeUTF8)
        );
        label_env->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QOperateur: public Ui_QOperateur {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QOPERATEUR_H
