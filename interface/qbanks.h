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

#include <QtGui/QWidget>
#include "../ui_qbanks.h"

#include "../core/midi.h"
#include "../core/bank.h"

namespace Ui {
    class QBanks;
}

/*****************************************************************************/
class QBanks : public QWidget {
    Q_OBJECT
public:
    QBanks(QWidget *parent = 0);
    ~QBanks();
protected:
    void changeEvent(QEvent *e);
private:
    Ui::QBanks * m_ui;
    Bank * bank;
private slots:
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
