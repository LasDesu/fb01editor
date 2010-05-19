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

#include "qoperateur.h"

/*****************************************************************************/
QOperateur::QOperateur(QWidget *parent) : QWidget(parent), m_ui(new Ui::QOperateur)
{
    m_ui->setupUi(this);
}

QOperateur::~QOperateur()
{
    delete m_ui;
}

/*****************************************************************************/
void QOperateur::DefinirOP(Operateur * operateur)
{
    this->operateur = operateur;
}

/*****************************************************************************/
void QOperateur::ActualiserEnveloppe()
{
    m_ui->label_env->DefinirEnveloppe(m_ui->but_AR->LireValeur(), m_ui->but_D1R->LireValeur(),
                                      m_ui->but_SL->LireValeur(), m_ui->but_D2R->LireValeur(),
                                      m_ui->but_RR->LireValeur());
    m_ui->label_env->repaint();
}

/*****************************************************************************/
void QOperateur::on_hzSlider_volume_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_LEVEL, 127 - i, true);
}

void QOperateur::on_pshBut_carrier_clicked(bool checked)
{
    operateur->EcrireParam(Operateur::OPERATOR_MODULATOR, checked, true);
}

void QOperateur::on_cmbBox_lvlcurb_activated(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_LEVEL_CURB, i, true);
}

void QOperateur::on_but_vellvl_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_LEVEL_VELOCITY, i, true);
}

void QOperateur::on_but_velAR_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_ATTACK_VELOCITY, i, true);
}

void QOperateur::on_but_AR_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_ATTACK, i, true);
    ActualiserEnveloppe();
}

void QOperateur::on_but_D1R_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_DECAY1, i, true);
    ActualiserEnveloppe();
}

void QOperateur::on_but_SL_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_SUSTAIN, 15 - i, true);
    ActualiserEnveloppe();
}

void QOperateur::on_but_D2R_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_DECAY2, i, true);
    ActualiserEnveloppe();
}

void QOperateur::on_but_RR_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_RELEASE, i, true);
    ActualiserEnveloppe();
}

void QOperateur::on_but_coarse_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_COARSE, i, true);
}

void QOperateur::on_but_fine_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_FINE, i + 4, true);
}

void QOperateur::on_but_mult_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_MULTIPLE, i, true);
}

void QOperateur::on_but_lvldph_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_LEVEL_DEPTH, i, true);
}

void QOperateur::on_but_rtdph_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_RATE_DEPTH, i, true);
}

void QOperateur::on_but_adjTL_valueChanged(int i)
{
    operateur->EcrireParam(Operateur::OPERATOR_ADJUST, i, true);
}

/*****************************************************************************/
void QOperateur::changeEvent(QEvent *e)
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
