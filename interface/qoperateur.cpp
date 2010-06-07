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
    attente = false;
}

QOperateur::~QOperateur()
{
    delete m_ui;
}

/*****************************************************************************/
void QOperateur::DefinirOP(Operateur * operateur)
{
    QString num;
    this->operateur = operateur;
    num.setNum(operateur->LireId() + 1, 10);
    this->m_ui->grpBox_opera->setTitle((QString) "Operateur " + num + " :");
}

/*****************************************************************************/
void QOperateur::ActualiserEnveloppe()
{
    m_ui->label_env->DefinirEnveloppe(m_ui->but_AR->value(), m_ui->but_D1R->value(),
                                      m_ui->but_SL->value(), m_ui->but_D2R->value(),
                                      m_ui->but_RR->value());
    m_ui->label_env->repaint();
}

void QOperateur::Actualiser()
{
    attente = true;
    m_ui->hzSlider_volume->setValue(127 - operateur->LireParam(Operateur::OPERATOR_LEVEL));
    m_ui->but_vellvl->setValue(operateur->LireParam(Operateur::OPERATOR_LEVEL_VELOCITY));
    m_ui->but_velAR->setValue(operateur->LireParam(Operateur::OPERATOR_ATTACK_VELOCITY));
    m_ui->but_adjTL->setValue(operateur->LireParam(Operateur::OPERATOR_ADJUST));
    m_ui->cmbBox_lvlcurb->setCurrentIndex(operateur->LireParam(Operateur::OPERATOR_LEVEL_CURB));
    m_ui->but_lvldph->setValue(operateur->LireParam(Operateur::OPERATOR_LEVEL_DEPTH));
    m_ui->but_rtdph->setValue(operateur->LireParam(Operateur::OPERATOR_RATE_DEPTH));
    m_ui->but_fine->setValue(operateur->LireParam(Operateur::OPERATOR_FINE) - 4);
    m_ui->but_coarse->setValue(operateur->LireParam(Operateur::OPERATOR_COARSE));
    m_ui->but_mult->setValue(operateur->LireParam(Operateur::OPERATOR_MULTIPLE));
    m_ui->pshBut_carrier->setChecked(operateur->LireParam(Operateur::OPERATOR_MODULATOR));
    m_ui->but_AR->setValue(operateur->LireParam(Operateur::OPERATOR_ATTACK));
    m_ui->but_D1R->setValue(operateur->LireParam(Operateur::OPERATOR_DECAY1));
    m_ui->but_D2R->setValue(operateur->LireParam(Operateur::OPERATOR_DECAY2));
    m_ui->but_SL->setValue(15 - operateur->LireParam(Operateur::OPERATOR_SUSTAIN));
    m_ui->but_RR->setValue(operateur->LireParam(Operateur::OPERATOR_RELEASE));
    ActualiserEnveloppe();
    attente = false;
}

/*****************************************************************************/
void QOperateur::on_hzSlider_volume_valueChanged(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_LEVEL, 127 - i, true);
}

void QOperateur::on_pshBut_carrier_clicked(bool checked)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_MODULATOR, checked, true);
}

void QOperateur::on_cmbBox_lvlcurb_activated(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_LEVEL_CURB, i, true);
}

void QOperateur::on_but_vellvl_valueChanged(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_LEVEL_VELOCITY, i, true);
}

void QOperateur::on_but_velAR_valueChanged(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_ATTACK_VELOCITY, i, true);
}

void QOperateur::on_but_AR_valueChanged(int i)
{
    if (!attente) {
        operateur->EcrireParam(Operateur::OPERATOR_ATTACK, i, true);
        ActualiserEnveloppe();
    }
}

void QOperateur::on_but_D1R_valueChanged(int i)
{
    if (!attente) {
        operateur->EcrireParam(Operateur::OPERATOR_DECAY1, i, true);
        ActualiserEnveloppe();
    }
}

void QOperateur::on_but_SL_valueChanged(int i)
{
    if (!attente) {
        operateur->EcrireParam(Operateur::OPERATOR_SUSTAIN, 15 - i, true);
        ActualiserEnveloppe();
    }
}

void QOperateur::on_but_D2R_valueChanged(int i)
{
    if (!attente) {
        operateur->EcrireParam(Operateur::OPERATOR_DECAY2, i, true);
        ActualiserEnveloppe();
    }
}

void QOperateur::on_but_RR_valueChanged(int i)
{
    if (!attente) {
        operateur->EcrireParam(Operateur::OPERATOR_RELEASE, i, true);
        ActualiserEnveloppe();
    }
}

void QOperateur::on_but_coarse_valueChanged(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_COARSE, i, true);
}

void QOperateur::on_but_fine_valueChanged(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_FINE, i + 4, true);
}

void QOperateur::on_but_mult_valueChanged(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_MULTIPLE, i, true);
}

void QOperateur::on_but_lvldph_valueChanged(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_LEVEL_DEPTH, i, true);
}

void QOperateur::on_but_rtdph_valueChanged(int i)
{
    if (!attente)
    operateur->EcrireParam(Operateur::OPERATOR_RATE_DEPTH, i, true);
}

void QOperateur::on_but_adjTL_valueChanged(int i)
{
    if (!attente)
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
