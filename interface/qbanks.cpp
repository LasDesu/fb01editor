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
}

QBanks::~QBanks()
{
    delete m_ui;
}
/*****************************************************************************/
void QBanks::DefinirBank(Bank * bank)
{
    this->bank = bank;
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
void QBanks::on_pshBut_copy_clicked(bool checked)
{
    /*
    bool ok;
    uchar Tampon[LNGBULK];
//Sélectionne les banks
    if (Attente) return;
    if (!EXPANDEUR::BanksValide()) return;
    int BankSrc = QInputDialog::getInt(MainApp->activeWindow(), "FB01 SE :", "Select the source bank :", 3, 1, 4, 1, &ok);
    if (!ok) return;
    int BankDst = QInputDialog::getInt(MainApp->activeWindow(), "FB01 SE :", "Select the destination bank :", 1, 1, 2, 1, &ok);
    if (!ok) return;
    if (BankSrc == BankDst) return;
//Copie une bank sur une autre
    Attente = true;
    EXPANDEUR::CopierBank(BankSrc-1, Tampon);
    EXPANDEUR::CollerBank(BankDst-1, Tampon);
 //Déverrouille et rafraichit
    Attente = false;
    Rafraichir();
    */
}

void QBanks::on_pshBut_exchange_clicked(bool checked)
{
    /*
    uchar Tampon1[LNGBULK];
    uchar Tampon2[LNGBULK];
//Echange les banks
    if (Attente) return;
    if (!EXPANDEUR::BanksValide()) return;
    Attente = true;
    EXPANDEUR::CopierBank(0, Tampon1);
    EXPANDEUR::CopierBank(1, Tampon2);
    EXPANDEUR::CollerBank(0, Tampon2);
    EXPANDEUR::CollerBank(1, Tampon1);
//Déverrouille et rafraichit
    Attente = false;
    Rafraichir();
    */
}

/*****************************************************************************/
void QBanks::on_table_bank_cellClicked(int row, int column)
{
    /*
//Limite la sélection
    QList <QTableWidgetItem *> Liste = m_ui->table_bank->selectedItems();
    if (Liste.count() > 8)
    {
        for (int i=0; i < 4; i++)
            Liste.at(8+i)->setSelected(false);
        m_ui->table_bank->setCurrentItem(Liste.at(0));
        return;
    }
//Affiche les informations
    Attente = true;
    m_ui->txtEdit_voicename->setPlainText(m_ui->table_bank->item(row, 0)->text());
    m_ui->cmbBox_voicestyle->setCurrentIndex(m_ui->table_bank->item(row, 1)->data(Qt::StatusTipRole).toInt());
    Attente = false;
    */
}

void QBanks::on_txtEdit_voicename_textChanged()
{
    /*
    if (Attente) return;
    if (m_ui->table_bank->item(0,0) == NULL) return;
//Change le nom de la voice
    uchar Bank  = m_ui->table_bank->selectedItems().at(0)->row() / NBVOICES;
    uchar Voice = m_ui->table_bank->selectedItems().at(0)->row() % NBVOICES;
    EXPANDEUR::EcrireBankNom(Bank, Voice, m_ui->txtEdit_voicename->toPlainText().toAscii().constData());
    m_ui->table_bank->selectedItems().at(0)->setText(m_ui->txtEdit_voicename->toPlainText().left(8));
    */
}

void QBanks::on_cmbBox_voicestyle_activated(int Index)
{
    /*
    if (Attente) return;
    if (m_ui->table_bank->item(0,0) == NULL) return;
//Change le style de la voice
    uchar Bank  = m_ui->table_bank->selectedItems().at(0)->row() / NBVOICES;
    uchar Voice = m_ui->table_bank->selectedItems().at(0)->row() % NBVOICES;
    EXPANDEUR::EcrireBankParam(Bank, Voice, 0x07, Index);
    m_ui->table_bank->selectedItems().at(1)->setText(m_ui->cmbBox_voicestyle->currentText());
    m_ui->table_bank->selectedItems().at(1)->setData(Qt::StatusTipRole, Index);
    */
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
