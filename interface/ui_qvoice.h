/********************************************************************************
** Form generated from reading UI file 'qvoice.ui'
**
** Created: Tue 18. May 13:14:31 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QVOICE_H
#define UI_QVOICE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QVoice
{
public:
    QGroupBox *grpBox_global;
    QLabel *lbl_style;
    QComboBox *cmbBox_style;
    QLabel *lbl_name;
    QPlainTextEdit *txtEdit_voicename;
    QSpinBox *spnBox_feedback;
    QLabel *lbl_feedback;
    QSpinBox *spnBox_trans;
    QLabel *lbl_trans;
    QLabel *lbl_porta_2;
    QLabel *lbl_pmdctl_2;
    QLabel *lbl_pitch_2;
    QLabel *lbl_poly_2;
    QSpinBox *spnBox_pitch;
    QPushButton *pshBut_poly;
    QComboBox *cmbBox_pmdctl;
    QSpinBox *spnBox_porta;
    QGroupBox *grpBox_algos;
    QLabel *lbl_algo;
    QSpinBox *spnBox_algo;
    QGroupBox *grpBox_LFO;
    QSpinBox *spnBox_PMD;
    QLabel *lbl_LFOwave;
    QSpinBox *spnBox_AMD;
    QComboBox *cmbBox_LFOwave;
    QLabel *lbl_AMD;
    QLabel *lbl_PMD;
    QSpinBox *spnBox_LFOspeed;
    QLabel *lbl_LFOspeed;
    QSpinBox *spnBox_PMS;
    QSpinBox *spnBox_AMS;
    QLabel *lbl_AMS;
    QLabel *lbl_PMS;
    QLabel *lbl_poly_3;
    QPushButton *pshBut_LFOload;
    QLabel *lbl_poly_4;
    QPushButton *pshBut_LFOsync;
    QGroupBox *groupBox;
    QLabel *lbl_author;
    QPlainTextEdit *txtEdit_author;
    QPlainTextEdit *txtEdit_comment;
    QLabel *lbl_author_2;

    void setupUi(QWidget *QVoice)
    {
        if (QVoice->objectName().isEmpty())
            QVoice->setObjectName(QString::fromUtf8("QVoice"));
        QVoice->resize(574, 274);
        grpBox_global = new QGroupBox(QVoice);
        grpBox_global->setObjectName(QString::fromUtf8("grpBox_global"));
        grpBox_global->setGeometry(QRect(170, 0, 191, 271));
        lbl_style = new QLabel(grpBox_global);
        lbl_style->setObjectName(QString::fromUtf8("lbl_style"));
        lbl_style->setGeometry(QRect(10, 60, 81, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbl_style->setFont(font);
        cmbBox_style = new QComboBox(grpBox_global);
        cmbBox_style->setObjectName(QString::fromUtf8("cmbBox_style"));
        cmbBox_style->setGeometry(QRect(100, 60, 81, 22));
        lbl_name = new QLabel(grpBox_global);
        lbl_name->setObjectName(QString::fromUtf8("lbl_name"));
        lbl_name->setGeometry(QRect(10, 20, 81, 16));
        lbl_name->setFont(font);
        txtEdit_voicename = new QPlainTextEdit(grpBox_global);
        txtEdit_voicename->setObjectName(QString::fromUtf8("txtEdit_voicename"));
        txtEdit_voicename->setGeometry(QRect(100, 20, 81, 31));
        txtEdit_voicename->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_voicename->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_voicename->setLineWrapMode(QPlainTextEdit::NoWrap);
        txtEdit_voicename->setMaximumBlockCount(6);
        spnBox_feedback = new QSpinBox(grpBox_global);
        spnBox_feedback->setObjectName(QString::fromUtf8("spnBox_feedback"));
        spnBox_feedback->setGeometry(QRect(100, 90, 81, 22));
        spnBox_feedback->setMinimum(0);
        spnBox_feedback->setMaximum(7);
        spnBox_feedback->setValue(0);
        lbl_feedback = new QLabel(grpBox_global);
        lbl_feedback->setObjectName(QString::fromUtf8("lbl_feedback"));
        lbl_feedback->setGeometry(QRect(10, 90, 81, 16));
        lbl_feedback->setFont(font);
        spnBox_trans = new QSpinBox(grpBox_global);
        spnBox_trans->setObjectName(QString::fromUtf8("spnBox_trans"));
        spnBox_trans->setGeometry(QRect(100, 120, 81, 22));
        spnBox_trans->setMinimum(-128);
        spnBox_trans->setMaximum(127);
        spnBox_trans->setValue(0);
        lbl_trans = new QLabel(grpBox_global);
        lbl_trans->setObjectName(QString::fromUtf8("lbl_trans"));
        lbl_trans->setGeometry(QRect(10, 120, 81, 16));
        lbl_trans->setFont(font);
        lbl_porta_2 = new QLabel(grpBox_global);
        lbl_porta_2->setObjectName(QString::fromUtf8("lbl_porta_2"));
        lbl_porta_2->setGeometry(QRect(10, 180, 81, 16));
        lbl_porta_2->setFont(font);
        lbl_pmdctl_2 = new QLabel(grpBox_global);
        lbl_pmdctl_2->setObjectName(QString::fromUtf8("lbl_pmdctl_2"));
        lbl_pmdctl_2->setGeometry(QRect(10, 240, 81, 16));
        lbl_pmdctl_2->setFont(font);
        lbl_pitch_2 = new QLabel(grpBox_global);
        lbl_pitch_2->setObjectName(QString::fromUtf8("lbl_pitch_2"));
        lbl_pitch_2->setGeometry(QRect(10, 210, 81, 16));
        lbl_pitch_2->setFont(font);
        lbl_poly_2 = new QLabel(grpBox_global);
        lbl_poly_2->setObjectName(QString::fromUtf8("lbl_poly_2"));
        lbl_poly_2->setGeometry(QRect(10, 150, 81, 16));
        lbl_poly_2->setFont(font);
        spnBox_pitch = new QSpinBox(grpBox_global);
        spnBox_pitch->setObjectName(QString::fromUtf8("spnBox_pitch"));
        spnBox_pitch->setGeometry(QRect(100, 210, 81, 22));
        spnBox_pitch->setMaximum(12);
        pshBut_poly = new QPushButton(grpBox_global);
        pshBut_poly->setObjectName(QString::fromUtf8("pshBut_poly"));
        pshBut_poly->setGeometry(QRect(100, 150, 81, 21));
        pshBut_poly->setCheckable(true);
        cmbBox_pmdctl = new QComboBox(grpBox_global);
        cmbBox_pmdctl->setObjectName(QString::fromUtf8("cmbBox_pmdctl"));
        cmbBox_pmdctl->setGeometry(QRect(100, 240, 81, 22));
        spnBox_porta = new QSpinBox(grpBox_global);
        spnBox_porta->setObjectName(QString::fromUtf8("spnBox_porta"));
        spnBox_porta->setGeometry(QRect(100, 180, 81, 22));
        spnBox_porta->setMaximum(127);
        grpBox_algos = new QGroupBox(QVoice);
        grpBox_algos->setObjectName(QString::fromUtf8("grpBox_algos"));
        grpBox_algos->setGeometry(QRect(0, 0, 151, 101));
        lbl_algo = new QLabel(grpBox_algos);
        lbl_algo->setObjectName(QString::fromUtf8("lbl_algo"));
        lbl_algo->setGeometry(QRect(40, 20, 71, 41));
        lbl_algo->setPixmap(QPixmap(QString::fromUtf8(":/imgs/algo1.bmp")));
        spnBox_algo = new QSpinBox(grpBox_algos);
        spnBox_algo->setObjectName(QString::fromUtf8("spnBox_algo"));
        spnBox_algo->setGeometry(QRect(40, 70, 71, 22));
        spnBox_algo->setMinimum(1);
        spnBox_algo->setMaximum(8);
        spnBox_algo->setValue(1);
        grpBox_LFO = new QGroupBox(QVoice);
        grpBox_LFO->setObjectName(QString::fromUtf8("grpBox_LFO"));
        grpBox_LFO->setGeometry(QRect(380, 0, 191, 271));
        spnBox_PMD = new QSpinBox(grpBox_LFO);
        spnBox_PMD->setObjectName(QString::fromUtf8("spnBox_PMD"));
        spnBox_PMD->setGeometry(QRect(100, 210, 81, 22));
        spnBox_PMD->setMinimum(0);
        spnBox_PMD->setMaximum(127);
        spnBox_PMD->setValue(0);
        lbl_LFOwave = new QLabel(grpBox_LFO);
        lbl_LFOwave->setObjectName(QString::fromUtf8("lbl_LFOwave"));
        lbl_LFOwave->setGeometry(QRect(10, 50, 81, 16));
        lbl_LFOwave->setFont(font);
        spnBox_AMD = new QSpinBox(grpBox_LFO);
        spnBox_AMD->setObjectName(QString::fromUtf8("spnBox_AMD"));
        spnBox_AMD->setGeometry(QRect(100, 150, 81, 22));
        spnBox_AMD->setMinimum(0);
        spnBox_AMD->setMaximum(127);
        spnBox_AMD->setValue(0);
        cmbBox_LFOwave = new QComboBox(grpBox_LFO);
        cmbBox_LFOwave->setObjectName(QString::fromUtf8("cmbBox_LFOwave"));
        cmbBox_LFOwave->setGeometry(QRect(100, 50, 81, 22));
        lbl_AMD = new QLabel(grpBox_LFO);
        lbl_AMD->setObjectName(QString::fromUtf8("lbl_AMD"));
        lbl_AMD->setGeometry(QRect(10, 150, 81, 20));
        lbl_AMD->setFont(font);
        lbl_PMD = new QLabel(grpBox_LFO);
        lbl_PMD->setObjectName(QString::fromUtf8("lbl_PMD"));
        lbl_PMD->setGeometry(QRect(10, 210, 81, 16));
        lbl_PMD->setFont(font);
        spnBox_LFOspeed = new QSpinBox(grpBox_LFO);
        spnBox_LFOspeed->setObjectName(QString::fromUtf8("spnBox_LFOspeed"));
        spnBox_LFOspeed->setGeometry(QRect(100, 20, 81, 22));
        spnBox_LFOspeed->setMinimum(0);
        spnBox_LFOspeed->setMaximum(255);
        spnBox_LFOspeed->setValue(0);
        lbl_LFOspeed = new QLabel(grpBox_LFO);
        lbl_LFOspeed->setObjectName(QString::fromUtf8("lbl_LFOspeed"));
        lbl_LFOspeed->setGeometry(QRect(10, 20, 81, 16));
        lbl_LFOspeed->setFont(font);
        spnBox_PMS = new QSpinBox(grpBox_LFO);
        spnBox_PMS->setObjectName(QString::fromUtf8("spnBox_PMS"));
        spnBox_PMS->setGeometry(QRect(100, 240, 81, 22));
        spnBox_PMS->setMinimum(0);
        spnBox_PMS->setMaximum(7);
        spnBox_PMS->setValue(0);
        spnBox_AMS = new QSpinBox(grpBox_LFO);
        spnBox_AMS->setObjectName(QString::fromUtf8("spnBox_AMS"));
        spnBox_AMS->setGeometry(QRect(100, 180, 81, 22));
        spnBox_AMS->setMinimum(0);
        spnBox_AMS->setMaximum(3);
        spnBox_AMS->setValue(0);
        lbl_AMS = new QLabel(grpBox_LFO);
        lbl_AMS->setObjectName(QString::fromUtf8("lbl_AMS"));
        lbl_AMS->setGeometry(QRect(10, 180, 81, 16));
        lbl_AMS->setFont(font);
        lbl_PMS = new QLabel(grpBox_LFO);
        lbl_PMS->setObjectName(QString::fromUtf8("lbl_PMS"));
        lbl_PMS->setGeometry(QRect(10, 240, 81, 16));
        lbl_PMS->setFont(font);
        lbl_poly_3 = new QLabel(grpBox_LFO);
        lbl_poly_3->setObjectName(QString::fromUtf8("lbl_poly_3"));
        lbl_poly_3->setGeometry(QRect(10, 80, 81, 16));
        lbl_poly_3->setFont(font);
        pshBut_LFOload = new QPushButton(grpBox_LFO);
        pshBut_LFOload->setObjectName(QString::fromUtf8("pshBut_LFOload"));
        pshBut_LFOload->setGeometry(QRect(100, 80, 81, 21));
        pshBut_LFOload->setCheckable(true);
        lbl_poly_4 = new QLabel(grpBox_LFO);
        lbl_poly_4->setObjectName(QString::fromUtf8("lbl_poly_4"));
        lbl_poly_4->setGeometry(QRect(10, 110, 81, 16));
        lbl_poly_4->setFont(font);
        pshBut_LFOsync = new QPushButton(grpBox_LFO);
        pshBut_LFOsync->setObjectName(QString::fromUtf8("pshBut_LFOsync"));
        pshBut_LFOsync->setGeometry(QRect(100, 110, 81, 21));
        pshBut_LFOsync->setCheckable(true);
        groupBox = new QGroupBox(QVoice);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 110, 151, 161));
        lbl_author = new QLabel(groupBox);
        lbl_author->setObjectName(QString::fromUtf8("lbl_author"));
        lbl_author->setGeometry(QRect(10, 20, 46, 14));
        lbl_author->setFont(font);
        txtEdit_author = new QPlainTextEdit(groupBox);
        txtEdit_author->setObjectName(QString::fromUtf8("txtEdit_author"));
        txtEdit_author->setGeometry(QRect(10, 40, 131, 31));
        txtEdit_author->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_author->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_author->setLineWrapMode(QPlainTextEdit::NoWrap);
        txtEdit_comment = new QPlainTextEdit(groupBox);
        txtEdit_comment->setObjectName(QString::fromUtf8("txtEdit_comment"));
        txtEdit_comment->setGeometry(QRect(10, 100, 131, 51));
        txtEdit_comment->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtEdit_comment->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_comment->setLineWrapMode(QPlainTextEdit::NoWrap);
        lbl_author_2 = new QLabel(groupBox);
        lbl_author_2->setObjectName(QString::fromUtf8("lbl_author_2"));
        lbl_author_2->setGeometry(QRect(10, 80, 71, 16));
        lbl_author_2->setFont(font);

        retranslateUi(QVoice);

        QMetaObject::connectSlotsByName(QVoice);
    } // setupUi

    void retranslateUi(QWidget *QVoice)
    {
        QVoice->setWindowTitle(QApplication::translate("QVoice", "Form", 0, QApplication::UnicodeUTF8));
        grpBox_global->setTitle(QApplication::translate("QVoice", "Global", 0, QApplication::UnicodeUTF8));
        lbl_style->setText(QApplication::translate("QVoice", "Style :", 0, QApplication::UnicodeUTF8));
        cmbBox_style->clear();
        cmbBox_style->insertItems(0, QStringList()
         << QApplication::translate("QVoice", "Piano", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Keys", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Organ", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Guitar", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Bass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Orch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Brass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Synth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Pad", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Ethnic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Bells", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Rythm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "SFX", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Other", 0, QApplication::UnicodeUTF8)
        );
        lbl_name->setText(QApplication::translate("QVoice", "Name :", 0, QApplication::UnicodeUTF8));
        txtEdit_voicename->setPlainText(QString());
        lbl_feedback->setText(QApplication::translate("QVoice", "Feedback :", 0, QApplication::UnicodeUTF8));
        lbl_trans->setText(QApplication::translate("QVoice", "Transpose :", 0, QApplication::UnicodeUTF8));
        lbl_porta_2->setText(QApplication::translate("QVoice", "Porta. time :", 0, QApplication::UnicodeUTF8));
        lbl_pmdctl_2->setText(QApplication::translate("QVoice", "PMD Control. :", 0, QApplication::UnicodeUTF8));
        lbl_pitch_2->setText(QApplication::translate("QVoice", "Pitch bender :", 0, QApplication::UnicodeUTF8));
        lbl_poly_2->setText(QApplication::translate("QVoice", "Mono / Poly :", 0, QApplication::UnicodeUTF8));
        pshBut_poly->setText(QApplication::translate("QVoice", "Poly", 0, QApplication::UnicodeUTF8));
        cmbBox_pmdctl->clear();
        cmbBox_pmdctl->insertItems(0, QStringList()
         << QApplication::translate("QVoice", "Not assigned", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "After touch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Mod. wheel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Breath ctl.", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Foot ctl.", 0, QApplication::UnicodeUTF8)
        );
        grpBox_algos->setTitle(QApplication::translate("QVoice", "Algorythm", 0, QApplication::UnicodeUTF8));
        lbl_algo->setText(QString());
        grpBox_LFO->setTitle(QApplication::translate("QVoice", "LFO", 0, QApplication::UnicodeUTF8));
        lbl_LFOwave->setText(QApplication::translate("QVoice", "LFO wave :", 0, QApplication::UnicodeUTF8));
        cmbBox_LFOwave->clear();
        cmbBox_LFOwave->insertItems(0, QStringList()
         << QApplication::translate("QVoice", "Saw", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Square", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "Triangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QVoice", "S&H", 0, QApplication::UnicodeUTF8)
        );
        lbl_AMD->setText(QApplication::translate("QVoice", "AMD :", 0, QApplication::UnicodeUTF8));
        lbl_PMD->setText(QApplication::translate("QVoice", "PMD :", 0, QApplication::UnicodeUTF8));
        lbl_LFOspeed->setText(QApplication::translate("QVoice", "LFO speed :", 0, QApplication::UnicodeUTF8));
        lbl_AMS->setText(QApplication::translate("QVoice", "AMS :", 0, QApplication::UnicodeUTF8));
        lbl_PMS->setText(QApplication::translate("QVoice", "PMS :", 0, QApplication::UnicodeUTF8));
        lbl_poly_3->setText(QApplication::translate("QVoice", "LFO load :", 0, QApplication::UnicodeUTF8));
        pshBut_LFOload->setText(QApplication::translate("QVoice", "Load", 0, QApplication::UnicodeUTF8));
        lbl_poly_4->setText(QApplication::translate("QVoice", "LFO sync :", 0, QApplication::UnicodeUTF8));
        pshBut_LFOsync->setText(QApplication::translate("QVoice", "Sync", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QVoice", "Informations :", 0, QApplication::UnicodeUTF8));
        lbl_author->setText(QApplication::translate("QVoice", "Author :", 0, QApplication::UnicodeUTF8));
        lbl_author_2->setText(QApplication::translate("QVoice", "Comment :", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QVoice: public Ui_QVoice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QVOICE_H
