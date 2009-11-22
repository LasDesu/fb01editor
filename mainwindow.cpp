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

#include <QMessageBox>
#include "mainwindow.h"
#include "midi.h"

/*****************************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
//Initialise l'interface
    ui->setupUi(this);
    ActiverEditeur(false);
    InitInstrus();
//Initialise les données
    on_pshBut_refresh_pressed();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*****************************************************************************/
void MainWindow::ActiverEditeur(bool Actif)
{
//Active ou désactive
    ui->tab_banks->setEnabled(Actif);
    ui->tab_instruments->setEnabled(Actif);
    ui->tab_voiceops->setEnabled(Actif);
}

void MainWindow::on_cmbBox_MIDIIn_activated(int Index)
{
    if (Index != -1) MIDI::ActiverIn(Index);
    if (ui->cmbBox_MIDIOut->currentIndex() != -1)
        ActiverEditeur();
}

void MainWindow::on_cmbBox_MIDIOut_activated(int Index)
{
    if (Index != -1) MIDI::ActiverOut(Index);
    if (ui->cmbBox_MIDIIn->currentIndex() != -1)
        ActiverEditeur();
}

/*****************************************************************************/
void MainWindow::on_pshBut_next_pressed()
{
    QString Num;
//Sauvegarde les instrus
    SauverInstrus(Instrus[PageSel]);
//Change de page
    PageSel = 1 - PageSel;
//Charge les instrus
    ChargerInstrus(Instrus[PageSel]);
//Actualise l'interface
    Num.setNum(PageSel * 4 + 1);
    ui->grpBox_inst_1->setTitle(QString("Instrument ").append(Num));
    Num.setNum(PageSel * 4 + 2);
    ui->grpBox_inst_2->setTitle(QString("Instrument ").append(Num));
    Num.setNum(PageSel * 4 + 3);
    ui->grpBox_inst_3->setTitle(QString("Instrument ").append(Num));
    Num.setNum(PageSel * 4 + 4);
    ui->grpBox_inst_4->setTitle(QString("Instrument ").append(Num));
}

/*****************************************************************************/
void MainWindow::on_pshBut_refresh_pressed()
{
//Efface les items
    ui->cmbBox_MIDIIn->clear();
    ui->cmbBox_MIDIOut->clear();
//Ajoute les périphériques
    MIDI::Lister();
    int Ins = MIDI::NbDriversIn();
    for (int i = 0; i < Ins; i++)
        ui->cmbBox_MIDIIn->addItem(MIDI::DriverIn(i), i);
    int Outs = MIDI::NbDriversOut();
    for (int i = 0; i < Outs; i++)
        ui->cmbBox_MIDIOut->addItem(MIDI::DriverOut(i), i);
//Désactive les onglets
    ActiverEditeur(false);
}

/*****************************************************************************/
void MainWindow::on_actionQuit_triggered(bool checked)
{
   // delete ui;
}

void MainWindow::on_actionAbout_triggered(bool checked)
{
    QMessageBox msgBox;
    msgBox.setText("FB01 Editor :\nMeslin Frederic 2009\nfredericmeslin@hotmail.com\n\nA free computer editor for the Yamaha FB01 sound module");
    msgBox.exec();
}

/*****************************************************************************/

void MainWindow::InitInstrus()
{
//Initialise les instrus
    for (int i = 0; i < 59; i ++)
        Instrus[0][i]= 0;
    for (int i = 0; i < 59; i ++)
        Instrus[1][i]= 0;
//Charge les instruments
    PageSel  = 0;
    InstSel  = 0;
    ChargerInstrus(Instrus[0]);
}


void MainWindow::ChargerInstrus(uchar Table[])
{
//Sauvegarde les instruments
    ui->spnBox_notes_1->setValue((int) Table[0]);
    ui->spnBox_notes_2->setValue((int) Table[1]);
    ui->spnBox_notes_3->setValue((int) Table[2]);
    ui->spnBox_notes_4->setValue((int) Table[3]);
    ui->spnBox_chan_1->setValue((int) Table[4]);
    ui->spnBox_chan_2->setValue((int) Table[5]);
    ui->spnBox_chan_3->setValue((int) Table[6]);
    ui->spnBox_chan_4->setValue((int) Table[7]);
    ui->spnBox_upper_1->setValue((int) Table[8]);
    ui->spnBox_upper_2->setValue((int) Table[9]);
    ui->spnBox_upper_3->setValue((int) Table[10]);
    ui->spnBox_upper_4->setValue((int) Table[11]);
    ui->spnBox_lower_1->setValue((int) Table[12]);
    ui->spnBox_lower_2->setValue((int) Table[13]);
    ui->spnBox_lower_3->setValue((int) Table[14]);
    ui->spnBox_lower_4->setValue((int) Table[15]);
    ui->spnBox_bank_1->setValue((int) Table[16]);
    ui->spnBox_bank_2->setValue((int) Table[17]);
    ui->spnBox_bank_3->setValue((int) Table[18]);
    ui->spnBox_bank_4->setValue((int) Table[19]);
    ui->spnBox_voice_1->setValue((int) Table[20]);
    ui->spnBox_voice_2->setValue((int) Table[21]);
    ui->spnBox_voice_3->setValue((int) Table[22]);
    ui->spnBox_voice_4->setValue((int) Table[23]);
    ui->spnBox_detune_1->setValue((int) Table[24]);
    ui->spnBox_detune_2->setValue((int) Table[25]);
    ui->spnBox_detune_3->setValue((int) Table[26]);
    ui->spnBox_detune_4->setValue((int) Table[27]);
    ui->cmbBox_trans_1->setCurrentIndex((int) Table[28]);
    ui->cmbBox_trans_2->setCurrentIndex((int) Table[29]);
    ui->cmbBox_trans_3->setCurrentIndex((int) Table[30]);
    ui->cmbBox_trans_4->setCurrentIndex((int) Table[31]);
    ui->hzSlider_level_1->setValue((int) Table[32]);
    ui->hzSlider_level_2->setValue((int) Table[33]);
    ui->hzSlider_level_3->setValue((int) Table[34]);
    ui->hzSlider_level_4->setValue((int) Table[35]);
    ui->hzSlider_pan_1->setValue((int) Table[36]);
    ui->hzSlider_pan_2->setValue((int) Table[37]);
    ui->hzSlider_pan_3->setValue((int) Table[38]);
    ui->hzSlider_pan_4->setValue((int) Table[39]);
    ui->pshBut_LFO_1->setChecked((bool) Table[40]);
    ui->pshBut_LFO_2->setChecked((bool) Table[41]);
    ui->pshBut_LFO_3->setChecked((bool) Table[42]);
    ui->pshBut_LFO_4->setChecked((bool) Table[43]);
    ui->spnBox_porta_1->setValue((int) Table[44]);
    ui->spnBox_porta_2->setValue((int) Table[45]);
    ui->spnBox_porta_3->setValue((int) Table[46]);
    ui->spnBox_porta_4->setValue((int) Table[47]);
    ui->spnBox_pitch_1->setValue((int) Table[48]);
    ui->spnBox_pitch_2->setValue((int) Table[49]);
    ui->spnBox_pitch_3->setValue((int) Table[50]);
    ui->spnBox_pitch_4->setValue((int) Table[51]);
    ui->pshBut_poly_1->setChecked((bool) Table[52]);
    ui->pshBut_poly_2->setChecked((bool) Table[53]);
    ui->pshBut_poly_3->setChecked((bool) Table[54]);
    ui->pshBut_poly_4->setChecked((bool) Table[55]);
    ui->cmbBox_pmdctl_1->setCurrentIndex((int) Table[56]);
    ui->cmbBox_pmdctl_2->setCurrentIndex((int) Table[57]);
    ui->cmbBox_pmdctl_3->setCurrentIndex((int) Table[58]);
    ui->cmbBox_pmdctl_4->setCurrentIndex((int) Table[59]);
}

void MainWindow::SauverInstrus(uchar Table[])
{
//Sauvegarde les instruments
    Table[0]  = (uchar) ui->spnBox_notes_1->value();
    Table[1]  = (uchar) ui->spnBox_notes_2->value();
    Table[2]  = (uchar) ui->spnBox_notes_3->value();
    Table[3]  = (uchar) ui->spnBox_notes_4->value();
    Table[4]  = (uchar) ui->spnBox_chan_1->value();
    Table[5]  = (uchar) ui->spnBox_chan_2->value();
    Table[6]  = (uchar) ui->spnBox_chan_3->value();
    Table[7]  = (uchar) ui->spnBox_chan_4->value();
    Table[8]  = (uchar) ui->spnBox_upper_1->value();
    Table[9]  = (uchar) ui->spnBox_upper_2->value();
    Table[10] = (uchar) ui->spnBox_upper_3->value();
    Table[11] = (uchar) ui->spnBox_upper_4->value();
    Table[12] = (uchar) ui->spnBox_lower_1->value();
    Table[13] = (uchar) ui->spnBox_lower_2->value();
    Table[14] = (uchar) ui->spnBox_lower_3->value();
    Table[15] = (uchar) ui->spnBox_lower_4->value();
    Table[16] = (uchar) ui->spnBox_bank_1->value();
    Table[17] = (uchar) ui->spnBox_bank_2->value();
    Table[18] = (uchar) ui->spnBox_bank_3->value();
    Table[19] = (uchar) ui->spnBox_bank_4->value();
    Table[20] = (uchar) ui->spnBox_voice_1->value();
    Table[21] = (uchar) ui->spnBox_voice_2->value();
    Table[22] = (uchar) ui->spnBox_voice_3->value();
    Table[23] = (uchar) ui->spnBox_voice_4->value();
    Table[24] = (uchar) ui->spnBox_detune_1->value();
    Table[25] = (uchar) ui->spnBox_detune_2->value();
    Table[26] = (uchar) ui->spnBox_detune_3->value();
    Table[27] = (uchar) ui->spnBox_detune_4->value();
    Table[28] = (uchar) ui->cmbBox_trans_1->currentIndex();
    Table[29] = (uchar) ui->cmbBox_trans_2->currentIndex();
    Table[30] = (uchar) ui->cmbBox_trans_3->currentIndex();
    Table[31] = (uchar) ui->cmbBox_trans_4->currentIndex();
    Table[32] = (uchar) ui->hzSlider_level_1->value();
    Table[33] = (uchar) ui->hzSlider_level_2->value();
    Table[34] = (uchar) ui->hzSlider_level_3->value();
    Table[35] = (uchar) ui->hzSlider_level_4->value();
    Table[36] = (uchar) ui->hzSlider_pan_1->value();
    Table[37] = (uchar) ui->hzSlider_pan_2->value();
    Table[38] = (uchar) ui->hzSlider_pan_3->value();
    Table[39] = (uchar) ui->hzSlider_pan_4->value();
    Table[40] = (uchar) ui->pshBut_LFO_1->isChecked() ? 1 : 0;
    Table[41] = (uchar) ui->pshBut_LFO_2->isChecked() ? 1 : 0;
    Table[42] = (uchar) ui->pshBut_LFO_3->isChecked() ? 1 : 0;
    Table[43] = (uchar) ui->pshBut_LFO_4->isChecked() ? 1 : 0;
    Table[44] = (uchar) ui->spnBox_porta_1->value();
    Table[45] = (uchar) ui->spnBox_porta_2->value();
    Table[46] = (uchar) ui->spnBox_porta_3->value();
    Table[47] = (uchar) ui->spnBox_porta_4->value();
    Table[48] = (uchar) ui->spnBox_pitch_1->value();
    Table[49] = (uchar) ui->spnBox_pitch_2->value();
    Table[50] = (uchar) ui->spnBox_pitch_3->value();
    Table[51] = (uchar) ui->spnBox_pitch_4->value();
    Table[52] = ui->pshBut_poly_1->isChecked() ? 1 : 0;
    Table[53] = ui->pshBut_poly_2->isChecked() ? 1 : 0;
    Table[54] = ui->pshBut_poly_3->isChecked() ? 1 : 0;
    Table[55] = ui->pshBut_poly_4->isChecked() ? 1 : 0;
    Table[56] = ui->cmbBox_pmdctl_1->currentIndex();
    Table[57] = ui->cmbBox_pmdctl_2->currentIndex();
    Table[58] = ui->cmbBox_pmdctl_3->currentIndex();
    Table[59] = ui->cmbBox_pmdctl_4->currentIndex();
}
