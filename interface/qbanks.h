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

/*****************************************************************************/
#include "ui_qbanks.h"

/*****************************************************************************/
#include "expandeur.h"

/*****************************************************************************/
#define LNGBANK x

/*****************************************************************************/
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
    void Envoyer(const int Bank);
    void Recevoir();
    //Chargement/enregistrement
    bool Enregistrer(QFile * Fichier, const int Bank);
    bool Charger(QFile * Fichier, const int Version, const int Bank);
    //Affichage
    void Rafraichir();
    void RafraichirItem(const int row, const int column);
    //Interface et édition
    bool Copier(uchar * Table);
    void Coller(const uchar * Table);
    void Echanger();
protected:
    //Interne
    void changeEvent(QEvent *e);
private:
    //Interface
    Ui::QBanks * m_ui;
    bool Attente;
private slots:
    //Gestion des évènements
    void on_table_bank_cellClicked(int row, int column);
    void on_pshBut_bybank_clicked(bool checked);
    void on_pshBut_byname_clicked(bool checked);
    void on_pshBut_bystyle_clicked(bool checked);
    void on_pshBut_copy_clicked(bool checked);
    void on_pshBut_exchange_clicked(bool checked);
    void on_txtEdit_voicename_textChanged();
    void on_cmbBox_voicestyle_activated(int Index);
};

#endif // QBANKS_H
