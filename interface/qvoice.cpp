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

#include "qvoice.h"

/*****************************************************************************/
QVoice::QVoice(QWidget *parent) : QWidget(parent), m_ui(new Ui::QVoice)
{
    m_ui->setupUi(this);
    m_ui->but_algo->setValue(1);
}

QVoice::~QVoice()
{
    delete m_ui;
}

/*****************************************************************************/
void QVoice::DefinirVoice(Voice * voice)
{
    this->voice = voice;
}

void QVoice::DefinirAuteur(QString auteur)
{
    m_ui->txtEdit_author->setPlainText(auteur);
}

void QVoice::DefinirComment(QString comment)
{
    m_ui->txtEdit_comment->setPlainText(comment);
}

/*****************************************************************************/
void QVoice::Actualiser()
{
    m_ui->txtEdit_voicename->setPlainText((QString) voice->LireNom());
    m_ui->txtEdit_voicename->repaint();
    m_ui->but_algo->setValue(voice->LireParam(Voice::VOICE_ALGORITHME));
    m_ui->cmbBox_style->setCurrentIndex(voice->LireParam(Voice::VOICE_USERCODE));
    m_ui->cmbBox_LFOwave->setCurrentIndex(voice->LireParam(Voice::VOICE_LFO_WAVE));
    m_ui->spnBox_LFOspeed->setValue(voice->LireParam(Voice::VOICE_LFO_SPEED));
    m_ui->pshBut_LFOload->setChecked(!voice->LireParam(Voice::VOICE_LFO_LOAD));
    m_ui->pshBut_LFOsync->setChecked(!voice->LireParam(Voice::VOICE_LFO_SYNC));
    m_ui->but_feedback->setValue(voice->LireParam(Voice::VOICE_FEEDBACK));
    m_ui->but_AMD->setValue(voice->LireParam(Voice::VOICE_LFO_AMD));
    m_ui->but_PMD->setValue(voice->LireParam(Voice::VOICE_LFO_PMD));
    m_ui->but_PMS->setValue(voice->LireParam(Voice::VOICE_LFO_PMS));
    m_ui->but_AMS->setValue(voice->LireParam(Voice::VOICE_LFO_AMS));
    m_ui->but_trans->setValue(voice->LireParam(Voice::VOICE_TRANSPOSE) - 2);
    m_ui->pshBut_poly->setChecked(!voice->LireParam(Voice::VOICE_POLY));
    m_ui->but_porta->setValue(voice->LireParam(Voice::VOICE_PORTAMENTO));
    m_ui->cmbBox_pmdctl->setCurrentIndex(voice->LireParam(Voice::VOICE_CONTROLLER));
    m_ui->but_pitch->setValue(voice->LireParam(Voice::VOICE_PITCHBEND));
}

/*****************************************************************************/
QString AlgNoms[] = {":/ALGO1", ":/ALGO2", ":/ALGO3", ":/ALGO4", ":/ALGO5", ":/ALGO6", ":/ALGO7", ":/ALGO8"};
void QVoice::on_but_algo_valueChanged(int i)
{
    QPixmap Pix;
//Change l'image
    Pix.load(AlgNoms[i-1]);
    m_ui->lbl_algo->setPixmap(Pix);
//Envoie la donnée
    voice->EcrireParam(Voice::VOICE_ALGORITHME, i - 1, true);
}

/*****************************************************************************/
void QVoice::on_txtEdit_voicename_textChanged()
{
    voice->EcrireNom(m_ui->txtEdit_voicename->toPlainText().toAscii().data(), true);
}

void QVoice::on_cmbBox_style_activated(int i)
{
    voice->EcrireParam(Voice::VOICE_USERCODE, i, true);
}

void QVoice::on_but_feedback_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_FEEDBACK, i, true);
}

void QVoice::on_but_trans_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_TRANSPOSE, i + 2, true);
}

void QVoice::on_pshBut_poly_clicked(bool checked)
{
    voice->EcrireParam(Voice::VOICE_POLY, !checked, true);
}

void QVoice::on_but_porta_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_PORTAMENTO, i, true);
}

void QVoice::on_but_pitch_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_PITCHBEND, i, true);
}

void QVoice::on_cmbBox_pmdctl_activated(int i)
{
    voice->EcrireParam(Voice::VOICE_CONTROLLER, i, true);
}

void QVoice::on_spnBox_LFOspeed_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_LFO_SPEED, i, true);
}

void QVoice::on_cmbBox_LFOwave_activated(int i)
{
    voice->EcrireParam(Voice::VOICE_LFO_WAVE, i, true);
}

void QVoice::on_pshBut_LFOload_clicked(bool checked)
{
    voice->EcrireParam(Voice::VOICE_LFO_LOAD, !checked, true);
}

void QVoice::on_pshBut_LFOsync_clicked(bool checked)
{
    voice->EcrireParam(Voice::VOICE_LFO_SYNC, !checked, true);
}

void QVoice::on_but_AMD_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_LFO_AMD, i, true);
}

void QVoice::on_but_AMS_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_LFO_AMS, i, true);
}

void QVoice::on_but_PMD_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_LFO_PMD, i, true);
}

void QVoice::on_but_PMS_valueChanged(int i)
{
    voice->EcrireParam(Voice::VOICE_LFO_PMS, i, true);
}

/*****************************************************************************/
void QVoice::changeEvent(QEvent *e)
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
