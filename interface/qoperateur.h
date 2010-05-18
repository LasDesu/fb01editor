/*
    FB01 : Sound editor
    Copyright Meslin Frédéric 2009 - 2010
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

#ifndef QOPERATEUR_H
#define QOPERATEUR_H

#include <QtGui/QWidget>

#include "../ui_qoperateur.h"
#include "../core/operateur.h"
#include "../core/midi.h"

namespace Ui {
    class QOperateur;
}

/*****************************************************************************/
class QOperateur : public QWidget {
    Q_OBJECT
public:
    QOperateur(QWidget *parent = 0);
    ~QOperateur();
protected:
    void changeEvent(QEvent *e);
private:
    Ui::QOperateur *m_ui;
    Operateur * operateur;
private slots:
    void on_hzSlider_volume_valueChanged(int i);
    void on_spnBox_vellvl_valueChanged(int i);
    void on_spnBox_velAR_valueChanged(int i);
    void on_spnBox_AR_valueChanged(int i);
    void on_spnBox_D1R_valueChanged(int i);
    void on_spnBox_SL_valueChanged(int i);
    void on_spnBox_D2R_valueChanged(int i);
    void on_spnBox_RR_valueChanged(int i);
    void on_pshBut_carrier_clicked(bool checked);
    void on_spnBox_coarse_valueChanged(int i);
    void on_spnBox_fine_valueChanged(int i);
    void on_spnBox_multiple_valueChanged(int i);
    void on_cmbBox_lvlcurb_activated(int i);
    void on_spnBox_lvldph_valueChanged(int i);
    void on_spnBox_rtdph_valueChanged(int i);
    void on_spnBox_adjTL_valueChanged(int i);
};

#endif // QOPERATEUR_H
