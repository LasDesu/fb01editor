/********************************************************************************
** Form generated from reading UI file 'qbanks.ui'
**
** Created: Sat 6. Feb 18:11:09 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QBANKS_H
#define UI_QBANKS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QBanks
{
public:
    QPushButton *pshBut_bybank;
    QLabel *label_sort_3;
    QPushButton *pshBut_bystyle;
    QLabel *label_sort_2;
    QLabel *label_sort;
    QPushButton *pshBut_byname;
    QTableWidget *table_bank;
    QPlainTextEdit *txtEdit_voicename;
    QComboBox *cmbBox_voicestyle;
    QLabel *label_bankop;
    QPushButton *pshBut_copy;
    QPushButton *pshBut_exchange;

    void setupUi(QWidget *QBanks)
    {
        if (QBanks->objectName().isEmpty())
            QBanks->setObjectName(QString::fromUtf8("QBanks"));
        QBanks->resize(620, 532);
        pshBut_bybank = new QPushButton(QBanks);
        pshBut_bybank->setObjectName(QString::fromUtf8("pshBut_bybank"));
        pshBut_bybank->setGeometry(QRect(530, 460, 71, 21));
        pshBut_bybank->setCheckable(true);
        label_sort_3 = new QLabel(QBanks);
        label_sort_3->setObjectName(QString::fromUtf8("label_sort_3"));
        label_sort_3->setGeometry(QRect(20, 500, 41, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_sort_3->setFont(font);
        pshBut_bystyle = new QPushButton(QBanks);
        pshBut_bystyle->setObjectName(QString::fromUtf8("pshBut_bystyle"));
        pshBut_bystyle->setGeometry(QRect(450, 460, 71, 21));
        pshBut_bystyle->setCheckable(true);
        label_sort_2 = new QLabel(QBanks);
        label_sort_2->setObjectName(QString::fromUtf8("label_sort_2"));
        label_sort_2->setGeometry(QRect(20, 464, 41, 20));
        label_sort_2->setFont(font);
        label_sort = new QLabel(QBanks);
        label_sort->setObjectName(QString::fromUtf8("label_sort"));
        label_sort->setGeometry(QRect(290, 460, 61, 20));
        label_sort->setFont(font);
        pshBut_byname = new QPushButton(QBanks);
        pshBut_byname->setObjectName(QString::fromUtf8("pshBut_byname"));
        pshBut_byname->setGeometry(QRect(370, 460, 71, 21));
        pshBut_byname->setCheckable(true);
        table_bank = new QTableWidget(QBanks);
        table_bank->setObjectName(QString::fromUtf8("table_bank"));
        table_bank->setGeometry(QRect(10, 10, 601, 441));
        table_bank->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_bank->setSelectionMode(QAbstractItemView::ExtendedSelection);
        table_bank->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_bank->horizontalHeader()->setDefaultSectionSize(150);
        table_bank->horizontalHeader()->setMinimumSectionSize(100);
        table_bank->horizontalHeader()->setStretchLastSection(true);
        txtEdit_voicename = new QPlainTextEdit(QBanks);
        txtEdit_voicename->setObjectName(QString::fromUtf8("txtEdit_voicename"));
        txtEdit_voicename->setGeometry(QRect(80, 460, 121, 31));
        txtEdit_voicename->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_voicename->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtEdit_voicename->setLineWrapMode(QPlainTextEdit::NoWrap);
        txtEdit_voicename->setMaximumBlockCount(7);
        cmbBox_voicestyle = new QComboBox(QBanks);
        cmbBox_voicestyle->setObjectName(QString::fromUtf8("cmbBox_voicestyle"));
        cmbBox_voicestyle->setGeometry(QRect(80, 500, 121, 22));
        label_bankop = new QLabel(QBanks);
        label_bankop->setObjectName(QString::fromUtf8("label_bankop"));
        label_bankop->setGeometry(QRect(290, 490, 61, 20));
        label_bankop->setFont(font);
        pshBut_copy = new QPushButton(QBanks);
        pshBut_copy->setObjectName(QString::fromUtf8("pshBut_copy"));
        pshBut_copy->setGeometry(QRect(370, 490, 71, 21));
        pshBut_exchange = new QPushButton(QBanks);
        pshBut_exchange->setObjectName(QString::fromUtf8("pshBut_exchange"));
        pshBut_exchange->setGeometry(QRect(450, 490, 71, 21));

        retranslateUi(QBanks);

        QMetaObject::connectSlotsByName(QBanks);
    } // setupUi

    void retranslateUi(QWidget *QBanks)
    {
        QBanks->setWindowTitle(QApplication::translate("QBanks", "Form", 0, QApplication::UnicodeUTF8));
        pshBut_bybank->setText(QApplication::translate("QBanks", "Bank", 0, QApplication::UnicodeUTF8));
        label_sort_3->setText(QApplication::translate("QBanks", "Style :", 0, QApplication::UnicodeUTF8));
        pshBut_bystyle->setText(QApplication::translate("QBanks", "Style", 0, QApplication::UnicodeUTF8));
        label_sort_2->setText(QApplication::translate("QBanks", "Name :", 0, QApplication::UnicodeUTF8));
        label_sort->setText(QApplication::translate("QBanks", "Sort by :", 0, QApplication::UnicodeUTF8));
        pshBut_byname->setText(QApplication::translate("QBanks", "Name", 0, QApplication::UnicodeUTF8));
        cmbBox_voicestyle->clear();
        cmbBox_voicestyle->insertItems(0, QStringList()
         << QApplication::translate("QBanks", "Piano", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Keys", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Organ", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Guitar", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Bass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Orch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Brass", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Synth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Pad", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Ethnic", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Bells", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Rythm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "SFX", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QBanks", "Other", 0, QApplication::UnicodeUTF8)
        );
        label_bankop->setText(QApplication::translate("QBanks", "Bank :", 0, QApplication::UnicodeUTF8));
        pshBut_copy->setText(QApplication::translate("QBanks", "Copy", 0, QApplication::UnicodeUTF8));
        pshBut_exchange->setText(QApplication::translate("QBanks", "Exchange", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QBanks: public Ui_QBanks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QBANKS_H
