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

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include "mainwindow.h"
#include "midi.h"

extern QApplication * mainApp;

/*****************************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
//Initialise l'interface
    ui->setupUi(this);
    InitialiserEditeur();
//Initialise les données

}

MainWindow::~MainWindow()
{
//Réinitialise le MIDI
    MIDI::DesactiverIn();
    MIDI::DesactiverOut();
    delete ui;
}

/*****************************************************************************/
void MainWindow::InitialiserEditeur()
{
//Désactive les controles
    ActiverEditeur(false);
    on_pshBut_refresh_midi_pressed();
//Initialise la page 1
    ui->widget_instru_1->ChangerID(0);
    ui->widget_instru_2->ChangerID(1);
    ui->widget_instru_3->ChangerID(2);
    ui->widget_instru_4->ChangerID(3);
//Initialise la page 2
    ui->widget_instru_5->ChangerID(4);
    ui->widget_instru_6->ChangerID(5);
    ui->widget_instru_7->ChangerID(6);
    ui->widget_instru_8->ChangerID(7);
//Initialise les opérateurs
    ui->widget_opera_1->ChangerID(0);
    ui->widget_opera_2->ChangerID(1);
    ui->widget_opera_3->ChangerID(2);
    ui->widget_opera_4->ChangerID(3);
//Coniguration par défaut
    ChangerPage(0);
    ChangerInst(0);
}

void MainWindow::ActiverEditeur(bool Actif)
{
//Active ou désactive
    ui->tab_banks->setEnabled(Actif);
    ui->tab_instruments->setEnabled(Actif);
    ui->tab_voice->setEnabled(Actif);
    ui->tab_operas->setEnabled(Actif);
}

/*****************************************************************************/
void MainWindow::ChangerPage(int Page)
{
//Change de page
    PageSel = Page;
    if (PageSel == 0)
    {//Affiche la page 1
        ui->frame_page_1->show();
        ui->frame_page_2->hide();
    }else
    {//Affiche la page 2
        ui->frame_page_2->show();
        ui->frame_page_1->hide();
    }
}

void MainWindow::ChangerInst(int Inst)
{
//Active l'instrument
    ui->pshBut_current_1->setChecked(Inst == 0);
    ui->pshBut_current_2->setChecked(Inst == 1);
    ui->pshBut_current_3->setChecked(Inst == 2);
    ui->pshBut_current_4->setChecked(Inst == 3);
    ui->pshBut_current_5->setChecked(Inst == 4);
    ui->pshBut_current_6->setChecked(Inst == 5);
    ui->pshBut_current_7->setChecked(Inst == 6);
    ui->pshBut_current_8->setChecked(Inst == 7);
//Sélectionne l'instrument
    ui->widget_opera_1->ChangerInst(Inst);
    ui->widget_opera_2->ChangerInst(Inst);
    ui->widget_opera_3->ChangerInst(Inst);
    ui->widget_opera_4->ChangerInst(Inst);
    ui->widget_voice->ChangerInst(Inst);
//Mémorise
    InstSel = Inst;
}

/*****************************************************************************/
void MainWindow::on_cmbBox_MIDIIn_activated(int Index)
{
//Sélectionne le driver
    if (Index != -1) MIDI::ActiverIn(Index);
    if (ui->cmbBox_MIDIOut->currentIndex() != -1)
        ActiverEditeur(true);
}

void MainWindow::on_cmbBox_MIDIOut_activated(int Index)
{
//Sélectionne le driver
    if (Index != -1) MIDI::ActiverOut(Index);
    if (ui->cmbBox_MIDIIn->currentIndex() != -1)
        ActiverEditeur(true);
}

void MainWindow::on_pshBut_refresh_midi_pressed()
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
void MainWindow::on_actionLoad_inst_triggered(bool checked)
{
    int  Version;
    char Text[3];
//Ouvre le sélecteur
    QString Nom =
    QFileDialog::getOpenFileName(this, "Load an instrument set", "", "*.fbi");
//Ouvre le fichier
    if (Nom.isEmpty()) return;
    QFile Fichier(Nom);
    if (!Fichier.open(QIODevice::ReadOnly)) goto Error;
//Lit l'entete

//Charge le set d'instruments
    if (ui->widget_instru_1->Charger(&Fichier, Version)) goto Error;
    if (ui->widget_instru_2->Charger(&Fichier, Version)) goto Error;
    if (ui->widget_instru_3->Charger(&Fichier, Version)) goto Error;
    if (ui->widget_instru_4->Charger(&Fichier, Version)) goto Error;
    if (ui->widget_instru_5->Charger(&Fichier, Version)) goto Error;
    if (ui->widget_instru_6->Charger(&Fichier, Version)) goto Error;
    if (ui->widget_instru_7->Charger(&Fichier, Version)) goto Error;
    if (ui->widget_instru_8->Charger(&Fichier, Version)) goto Error;
//Actualise l'instrument
    ui->widget_instru_1->Envoyer();
    ui->widget_instru_2->Envoyer();
    ui->widget_instru_3->Envoyer();
    ui->widget_instru_4->Envoyer();
    ui->widget_instru_5->Envoyer();
    ui->widget_instru_6->Envoyer();
    ui->widget_instru_7->Envoyer();
    ui->widget_instru_8->Envoyer();
//Ferme le fichier
    Fichier.close();
    return;
//Erreur apparue
Error :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
}

void MainWindow::on_actionSave_inst_triggered(bool checked)
{
//Ouvre le sélecteur
    QString Nom =
    QFileDialog::getOpenFileName(this, "Save an instrument set", "", "*.fbi");
//Ouvre le fichier
    if (Nom.isEmpty()) return;
    QFile Fichier(Nom);
    if (!Fichier.open(QIODevice::WriteOnly)) goto Error;
//Enregistre le set d'instruments
    if (ui->widget_instru_1->Enregistrer(&Fichier)) goto Error;
    if (ui->widget_instru_2->Enregistrer(&Fichier)) goto Error;
    if (ui->widget_instru_3->Enregistrer(&Fichier)) goto Error;
    if (ui->widget_instru_4->Enregistrer(&Fichier)) goto Error;
    if (ui->widget_instru_5->Enregistrer(&Fichier)) goto Error;
    if (ui->widget_instru_6->Enregistrer(&Fichier)) goto Error;
    if (ui->widget_instru_7->Enregistrer(&Fichier)) goto Error;
    if (ui->widget_instru_8->Enregistrer(&Fichier)) goto Error;
//Ferme le fichier
    Fichier.close();
    return;
//Erreur apparue
Error :
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
}

/*****************************************************************************/
void MainWindow::on_actionLoad_voice_triggered(bool checked)
{
}
void MainWindow::on_actionSave_voice_triggered(bool checked)
{
}

/*****************************************************************************/
void MainWindow::on_actionQuit_triggered(bool checked)
{
    mainApp->quit();
}

/*****************************************************************************/
void MainWindow::on_actionAbout_triggered(bool checked)
{
    QString Text;
//Informations sur le logiciel
    Text.append("FB01 Sound Editor :\nCopyright Meslin Frederic 2009\nfredericmeslin@hotmail.com\n\n");
    Text.append("A free computer editor for the Yamaha FB01 sound module\n");
    Text.append("This program is under a GPL license, please read the COPYING file.\n\n");
    Text.append("Main website : http://sourceforge.net/projects/fb01editor/\n");
    QMessageBox::information(this, "FB01 SE :", Text);
}

void MainWindow::on_actionRead_this_triggered(bool checked)
{
    QString Text;
//Informations supplémentaires
    Text.append("First thank you for using this program.\n\n");
    Text.append("If you want to improve or get involved in the project,\n");
    Text.append("go and visit the FB01SE website.\n\n");
    Text.append("You can also share your presets on the internet\n");
    Text.append("and participate in the creation of a common patch\n");
    Text.append("bank for all the FB01 users.\n");
    QMessageBox::information(this, "FB01 SE :", Text);
}

void MainWindow::on_actionOnline_help_triggered(bool checked)
{
}

/*****************************************************************************/
