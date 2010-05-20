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
//Initialise la liste des notes
    InitialiserNotes(m_ui->cmbBox_upper);
    InitialiserNotes(m_ui->cmbBox_lower);
//Initialise certains boutons
    m_ui->but_channel->setValue(1);
    m_ui->but_bank->setValue(1);
    m_ui->but_voice->setValue(1);
}

QInstrument::~QInstrument()
{
    delete m_ui;
}

/*****************************************************************************/
void QInstrument::Actualiser()
{
    m_ui->but_notes->setValue(instrument->LireParam(Instrument::INSTRU_NB_NOTES));
    m_ui->but_channel->setValue(instrument->LireParam(Instrument::INSTRU_CHANNEL) + 1);
    m_ui->cmbBox_upper->setCurrentIndex(instrument->LireParam(Instrument::INSTRU_UPPER));
    m_ui->cmbBox_lower->setCurrentIndex(instrument->LireParam(Instrument::INSTRU_LOWER));
    m_ui->but_bank->setValue(instrument->LireParam(Instrument::INSTRU_BANK) + 1);
    m_ui->but_voice->setValue(instrument->LireParam(Instrument::INSTRU_VOICE) + 1);
    m_ui->but_detune->setValue(instrument->LireParam(Instrument::INSTRU_DETUNE));
    m_ui->but_trans->setValue(instrument->LireParam(Instrument::INSTRU_TRANS) - 2);
    m_ui->hzSlider_volume->setValue(instrument->LireParam(Instrument::INSTRU_VOLUME));
    m_ui->hzSlider_pan->setValue(instrument->LireParam(Instrument::INSTRU_PAN));
    m_ui->pshBut_LFO->setChecked(!instrument->LireParam(Instrument::INSTRU_LFO));
    m_ui->but_porta->setValue(instrument->LireParam(Instrument::INSTRU_PORTAMENTO));
    m_ui->but_pitch->setValue(instrument->LireParam(Instrument::INSTRU_PITCHBEND));
    m_ui->pshBut_poly->setChecked(!instrument->LireParam(Instrument::INSTRU_POLY));
    m_ui->cmbBox_pmdctl->setCurrentIndex(instrument->LireParam(Instrument::INSTRU_CONROLLER));
}

/*****************************************************************************/
void QInstrument::DefinirInstrument(Instrument * instrument)
{
    this->instrument = instrument;
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
void QInstrument::on_but_notes_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_NB_NOTES, i, true);
}

void QInstrument::on_but_channel_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_CHANNEL, i - 1, true);
}

void QInstrument::on_cmbBox_upper_activated(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_UPPER, i, true);
}

void QInstrument::on_cmbBox_lower_activated(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_LOWER, i, true);
}

void QInstrument::on_but_bank_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_BANK, i - 1, true);
}

void QInstrument::on_but_voice_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_VOICE, i - 1, true);
}

void QInstrument::on_but_detune_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_DETUNE, i, true);
}

void QInstrument::on_but_trans_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_TRANS, i + 2, true);
}

void QInstrument::on_hzSlider_volume_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_VOLUME, i, true);
}

void QInstrument::on_hzSlider_pan_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_PAN, i, true);
}

void QInstrument::on_pshBut_LFO_clicked(bool checked)
{
    instrument->EcrireParam(Instrument::INSTRU_LFO, !checked, true);
}

void QInstrument::on_pshBut_poly_clicked(bool checked)
{
    instrument->EcrireParam(Instrument::INSTRU_POLY, !checked, true);
}

void QInstrument::on_but_porta_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_PORTAMENTO, i, true);
}

void QInstrument::on_but_pitch_valueChanged(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_PITCHBEND, i, true);
}

void QInstrument::on_cmbBox_pmdctl_activated(int i)
{
    instrument->EcrireParam(Instrument::INSTRU_CONROLLER, i, true);
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
