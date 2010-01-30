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

#ifndef QBANKS_H
#define QBANKS_H

//Inclusions générales
    #include "ui_qbanks.h"

//Inclusions spécifiques
    #include "expandeur.h"

namespace Ui {
    class QBanks;
}


class QBanks : public QWidget {
    Q_OBJECT
public:
//Constructeurs
    QBanks(QWidget *parent = 0);
    ~QBanks();
//Communication
    void Envoyer(int Bank);
    void Recevoir();
//Interface et édition
    void Initialiser(int Bank);
protected:
//Interne
    void changeEvent(QEvent *e);
private:
//Interface
    Ui::QBanks * m_ui;
    bool Attente;
//Sélection
    int BankSel;
    int VoiceSel;
private slots:
//Gestion des évènements
    void on_table_bank_cellClicked(int row, int column);
    void on_pshBut_bybank_clicked(bool checked);
    void on_pshBut_byname_clicked(bool checked);
    void on_pshBut_bystyle_clicked(bool checked);
    void on_pshBut_duplicate_clicked(bool checked);
    void on_pshBut_exchange_clicked(bool checked);
    void on_txtEdit_voicename_textChanged()
        {if (!Attente && BankSel != -1){
            EXPANDEUR::EcrireBankNom(BankSel, VoiceSel, m_ui->txtEdit_voicename->toPlainText().toAscii().constData());
            m_ui->table_bank->selectedItems().at(0)->setText(m_ui->txtEdit_voicename->toPlainText().left(8));}
        }
    void on_cmbBox_voicestyle_activated(int Index)
        {if (!Attente && BankSel != -1){
            EXPANDEUR::EcrireBankParam(BankSel, VoiceSel, 0x07, Index);
            m_ui->table_bank->selectedItems().at(1)->setText(m_ui->cmbBox_voicestyle->currentText());}
        }

};

#endif // QBANKS_H
