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

#include "qinstrument.h"

/*****************************************************************************/
QInstrument::QInstrument(QWidget *parent) : QWidget(parent), m_ui(new Ui::QInstrument)
{
    m_ui->setupUi(this);
    InitialiserNotes(m_ui->cmbBox_upper);
    InitialiserNotes(m_ui->cmbBox_lower);
}

QInstrument::~QInstrument()
{
    delete m_ui;
}

/*****************************************************************************/
const char notes[12][3] = {"C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};
void QInstrument::InitialiserNotes(QComboBox * box)
{
    box->clear();
    for (int n = 0; n < 128; n ++)
    {
    //Créé le nom de la note
        QString num; num.setNum(n / 12 - 2);
        QString item = notes[n % 12];
        item.append(" "); item.append(num);
    //Ajoute à la liste
        box->addItem(item, 0);
    }
}

/*****************************************************************************/
void QInstrument::on_spnBox_notes_valueChanged(int i)
{
}

void QInstrument::on_spnBox_chan_valueChanged(int i)
{
}

void QInstrument::on_cmbBox_upper_activated(int i)
{
}

void QInstrument::on_cmbBox_lower_activated(int i)
{
}

void QInstrument::on_spnBox_bank_valueChanged(int i)
{
}

void QInstrument::on_spnBox_voice_valueChanged(int i)
{
}

void QInstrument::on_spnBox_detune_valueChanged(int i)
{
}

void QInstrument::on_cmbBox_trans_activated(int i)
{
}

void QInstrument::on_hzSlider_volume_valueChanged(int i)
{
}

void QInstrument::on_hzSlider_pan_valueChanged(int i)
{
}

void QInstrument::on_pshBut_LFO_clicked(bool checked)
{
}

void QInstrument::on_pshBut_poly_clicked(bool checked)
{
}

void QInstrument::on_spnBox_porta_valueChanged(int i)
{
}

void QInstrument::on_spnBox_pitch_valueChanged(int i)
{
}

void QInstrument::on_cmbBox_pmdctl_activated(int i)
{
}

/*****************************************************************************/
void QInstrument::changeEvent(QEvent *e)
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
