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

#include "qconfig.h"

/*****************************************************************************/
QConfig::QConfig(QWidget *parent) : QWidget(parent), m_ui(new Ui::QConfig)
{
    m_ui->setupUi(this);
    attente = true;
    m_ui->but_syschan->setValue(1);
    m_ui->but_setnum->setValue(1);
    attente = false;
}

QConfig::~QConfig()
{
    delete m_ui;
}

/*****************************************************************************/
void QConfig::DefinirConfig(Config * config)
{
    this->config = config;
}

void QConfig::DefinirSet(Set * set)
{
    this->set = set;
}

/*****************************************************************************/
void QConfig::Rafraichir()
{
    attente = true;
//Rafraichit l'affichage
    m_ui->txtEdit_name->setPlainText((QString) set->LireNom());
    m_ui->pshBut_combine->setChecked(set->LireParam(Set::SET_COMBINE_MODE));
    m_ui->cmbBox_reception->setCurrentIndex(set->LireParam(Set::SET_RECEPTION_MODE));
    m_ui->spnBox_LFOspeed->setValue(set->LireParam(Set::SET_LFO_SPEED));
    m_ui->cmbBox_LFOwave->setCurrentIndex(set->LireParam(Set::SET_LFO_WAVE));
    m_ui->but_AMD->setValue(set->LireParam(Set::SET_LFO_AMD));
    m_ui->but_PMD->setValue(set->LireParam(Set::SET_LFO_PMD));
//Repeind certains contrôles
    m_ui->txtEdit_name->repaint();
    attente = false;
}

/*****************************************************************************/
void QConfig::on_but_syschan_valueChanged(int i)
{
    if (!attente)
        config->EcrireParam(Config::CONFIG_SYSCHANNEL, i - 1, true);
}

void QConfig::on_pshBut_memory_clicked(bool checked)
{
    if (!attente)
        config->EcrireParam(Config::CONFIG_MEMORY_PROTECT, checked, true);
}

void QConfig::on_but_setnum_valueChanged(int i)
{
    if (!attente)
        config->EcrireParam(Config::CONFIG_CONFIG_NUMBER, i - 1, true);
}

void QConfig::on_but_mastdetune_valueChanged(int i)
{
    if (!attente)
        config->EcrireParam(Config::CONFIG_DETUNE, i, true);
}

void QConfig::on_hzSlider_mastvol_valueChanged(int i)
{
    if (!attente)
        config->EcrireParam(Config::CONFIG_MASTER_VOLUME, i, true);
}

/*****************************************************************************/
void QConfig::on_txtEdit_name_textChanged()
{
    if (!attente)
        set->EcrireNom(m_ui->txtEdit_name->toPlainText().toAscii().data(), true);
}

void QConfig::on_pshBut_combine_clicked(bool checked)
{
    if (!attente)
        set->EcrireParam(Set::SET_COMBINE_MODE, checked, true);
}

void QConfig::on_cmbBox_reception_activated(int i)
{
    if (!attente)
        set->EcrireParam(Set::SET_RECEPTION_MODE, i, true);
}

void QConfig::on_spnBox_LFOspeed_valueChanged(int i)
{
    if (!attente)
        set->EcrireParam(Set::SET_LFO_SPEED, i, true);
}

void QConfig::on_cmbBox_LFOwave_activated(int i)
{
    if (!attente)
        set->EcrireParam(Set::SET_LFO_WAVE, i, true);
}

void QConfig::on_but_AMD_valueChanged(int i)
{
    if (!attente)
        set->EcrireParam(Set::SET_LFO_AMD, i, true);
}

void QConfig::on_but_PMD_valueChanged(int i)
{
    if (!attente)
        set->EcrireParam(Set::SET_LFO_PMD, i, true);
}

/*****************************************************************************/
void QConfig::changeEvent(QEvent *e)
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
