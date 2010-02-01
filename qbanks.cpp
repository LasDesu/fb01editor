/*
    FB01 : Sound editor
    Copyright Meslin Frédéric 2009
    fredericmeslin@hotmail.com

    This file is part of FB01 SE

    FB01 SE is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FB01 SE is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FB01 SE.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "qbanks.h"

//Application
    extern QApplication * MainApp;

/*****************************************************************************/
QBanks::QBanks(QWidget *parent) : QWidget(parent), m_ui(new Ui::QBanks)
{
    m_ui->setupUi(this);
//Ajoute des noms de colonne
    m_ui->table_bank->setColumnCount(4);
    QTableWidgetItem * ItNom   = new QTableWidgetItem("Name");
    QTableWidgetItem * ItStyle = new QTableWidgetItem("Style");
    QTableWidgetItem * ItBank  = new QTableWidgetItem("Bank");
    QTableWidgetItem * ItVoice = new QTableWidgetItem("Voice");
    m_ui->table_bank->setHorizontalHeaderItem(0, ItNom);
    m_ui->table_bank->setHorizontalHeaderItem(1, ItStyle);
    m_ui->table_bank->setHorizontalHeaderItem(2, ItBank);
    m_ui->table_bank->setHorizontalHeaderItem(3, ItVoice);
//Acune sélection
    BankSel = -1;
    VoiceSel = -1;
//Déverrouille
    Attente = false;
}

QBanks::~QBanks()
{
    delete m_ui;
}

/*****************************************************************************/
void QBanks::Envoyer(int Bank)
{
//Prévient l'utilisateur
    if (QMessageBox::question(MainApp->activeWindow(), "FB01 SE:", "Ready to send ?",
        QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel) return;
//Envoie les données
    EXPANDEUR::EnvoyerBank(Bank);
}

const char BankNoms[8][6]    = {"Ram 1", "Ram 2", "Rom 1", "Rom 2", "Rom 3", "Rom 4", "Rom 5"};
const char BankStyles[14][8] = {"Piano", "Keys", "Organ", "Guitar", "Bass", "Orch", "Brass",
                                "Synth", "Pad", "Ethnic", "Bells", "Rythm", "Sfx", "Other"};
void QBanks::Recevoir()
{
//Vide la liste
    m_ui->table_bank->clearContents();
    m_ui->txtEdit_voicename->setPlainText("");
    m_ui->cmbBox_voicestyle->setCurrentIndex(0);
//Charge chaque bank
    Attente = true;
    int Index = 0;
    for (int Bank = 0; Bank < 7; Bank ++)
        for (int Voice = 0; Voice < 48; Voice ++)
        {
        //Charge le nom
            char Nom[8];
            EXPANDEUR::LireBankNom(Bank, Voice, Nom);
            Nom[7] = 0;
       //Charge le style
            uchar Style = EXPANDEUR::LireBankParam(Bank, Voice, 0x07);
            if (Style > 13) Style = 13;
       //Créé le nouvel item
            QString Pos; Pos.setNum(Voice + 1);
            QTableWidgetItem * ItNom   = new QTableWidgetItem((QString) Nom);
            QTableWidgetItem * ItStyle = new QTableWidgetItem((QString) BankStyles[Style]);
            QTableWidgetItem * ItBank  = new QTableWidgetItem((QString) BankNoms[Bank]);
            QTableWidgetItem * ItVoice = new QTableWidgetItem(Pos);
        //Ajoute les informations
            ItBank->setData(Qt::StatusTipRole, Bank);
            ItStyle->setData(Qt::StatusTipRole, Style);
            ItVoice->setData(Qt::StatusTipRole, Voice + Bank * NBVOICES);
        //Ajoute l'item
            m_ui->table_bank->setRowCount(Index + 1);
            m_ui->table_bank->setItem(Index, 0, ItNom);
            m_ui->table_bank->setItem(Index, 1, ItStyle);
            m_ui->table_bank->setItem(Index, 2, ItBank);
            m_ui->table_bank->setItem(Index, 3, ItVoice);
        //Passe au suivant
            Index ++;
        }
//Sélectionne le premier
    Attente = false;
    m_ui->table_bank->setCurrentItem(m_ui->table_bank->item(0,0));
    on_table_bank_cellClicked(0,0);
}

/*****************************************************************************/
void QBanks::Initialiser(int Bank)
{
}

/*****************************************************************************/
void QBanks::on_pshBut_bybank_clicked(bool checked)
{
    m_ui->table_bank->sortByColumn(2, Qt::AscendingOrder);
    m_ui->table_bank->setSortingEnabled(checked);
    m_ui->pshBut_byname->setChecked(false);
    m_ui->pshBut_bystyle->setChecked(false);
}

void QBanks::on_pshBut_byname_clicked(bool checked)
{
    m_ui->table_bank->sortByColumn(0, Qt::AscendingOrder);
    m_ui->table_bank->setSortingEnabled(checked);
    m_ui->pshBut_bybank->setChecked(false);
    m_ui->pshBut_bystyle->setChecked(false);
}

void QBanks::on_pshBut_bystyle_clicked(bool checked)
{
    m_ui->table_bank->sortByColumn(1, Qt::AscendingOrder);
    m_ui->table_bank->setSortingEnabled(checked);
    m_ui->pshBut_byname->setChecked(false);
    m_ui->pshBut_bybank->setChecked(false);
}

/*****************************************************************************/
void QBanks::on_table_bank_cellClicked(int row, int column)
{
//Limite la sélection
    if (m_ui->table_bank->selectedItems().count() > 8)
    {
        for (int i = 0; i < 4; i++)
            m_ui->table_bank->selectedItems().at(8)->setSelected(false);
        return;
    }
    if (m_ui->table_bank->selectedItems().count() == 0)
    {
        BankSel = -1; VoiceSel = -1;
        return;
    }
//Affiche les informations
    BankSel  = m_ui->table_bank->item(row, 2)->data(Qt::StatusTipRole).toInt();
    VoiceSel = m_ui->table_bank->item(row, 3)->data(Qt::StatusTipRole).toInt();
    m_ui->txtEdit_voicename->setPlainText(m_ui->table_bank->item(row, 0)->text());
    m_ui->cmbBox_voicestyle->setCurrentIndex(m_ui->table_bank->item(row, 0)->data(Qt::StatusTipRole).toInt());
}

/*****************************************************************************/
void QBanks::Copier(uchar * Table)
{
//Vérifie la sélection
    if (Attente) return;
    QList <QTableWidgetItem *> Liste = m_ui->table_bank->selectedItems();
    if (Liste.count() != 8) {
        QMessageBox::information(MainApp->activeWindow(), "FB01 SE:", "Two voices must be selected !");
        return;
    }
    if (Liste.at(7)->data(Qt::StatusTipRole).toInt() > 95) {
        QMessageBox::warning(MainApp->activeWindow(), "FB01 SE:", "Cannot copy to rom !");
        return;
    }
//Copie la voice
    EXPANDEUR::CopierVoice(Liste.at(3)->data(Qt::StatusTipRole).toInt(), Liste.at(7)->data(Qt::StatusTipRole).toInt());
    for (int i = 0; i < 2; i++)
    {
        Liste.at(4+i)->setText(Liste.at(i)->text());
        Liste.at(4+i)->setData(Qt::StatusTipRole, Liste.at(i)->data(Qt::StatusTipRole));
    }
}

void QBanks::Coller(const uchar * Table)
{
}

/*****************************************************************************/
void QBanks::Echanger()
{
//Vérifie la sélection
    if (Attente) return;
    QList <QTableWidgetItem *> Liste = m_ui->table_bank->selectedItems();
    if (Liste.count() != 8) {
        QMessageBox::information(MainApp->activeWindow(), "FB01 SE:", "Two voices must be selected !");
        return;
    }
    if (Liste.at(3)->data(Qt::StatusTipRole).toInt() > 95 || Liste.at(7)->data(Qt::StatusTipRole).toInt() > 95) {
        QMessageBox::warning(MainApp->activeWindow(), "FB01 SE:", "Cannot exchange with rom !");
        return;
    }
//Echange les voices
    EXPANDEUR::EchangerVoice(Liste.at(3)->data(Qt::StatusTipRole).toInt(), Liste.at(7)->data(Qt::StatusTipRole).toInt());
    for (int i = 0; i < 2; i++)
    {
        QString TStr = Liste.at(4+i)->text();
        Liste.at(4+i)->setText(Liste.at(i)->text());
        Liste.at(i)->setText(TStr);
        QVariant TVar = Liste.at(4+i)->data(Qt::StatusTipRole);
        Liste.at(4+i)->setData(Qt::StatusTipRole, Liste.at(i)->data(Qt::StatusTipRole));
        Liste.at(i)->setData(Qt::StatusTipRole, TVar);
    }
}

/*****************************************************************************/
void QBanks::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
