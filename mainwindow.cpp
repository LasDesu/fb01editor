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
    ui->setupUi(this);
    InitialiserEditeur();
}

MainWindow::~MainWindow()
{
    TerminerEditeur();
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

void MainWindow::TerminerEditeur()
{
//Réinitialise le MIDI
    MIDI::DesactiverIn();
    MIDI::DesactiverOut();
}

/*****************************************************************************/
void MainWindow::ActiverEditeur(bool Actif)
{
//Active les onglets
    ui->tab_banks->setEnabled(Actif);
    ui->tab_set->setEnabled(Actif);
    ui->tab_voice->setEnabled(Actif);
    ui->tab_operas->setEnabled(Actif);
//Active les menus
    ui->actionLoad_set->setEnabled(Actif);
    ui->actionLoad_voice->setEnabled(Actif);
    ui->actionSave_set->setEnabled(Actif);
    ui->actionSave_voice->setEnabled(Actif);
}

/*****************************************************************************/
void MainWindow::ChangerPage(int Page)
{
//Change de page
    if (PageSel == 0)
    {//Affiche la page 1
        ui->frame_page_1->show();
        ui->frame_page_2->hide();
    }else
    {//Affiche la page 2
        ui->frame_page_2->show();
        ui->frame_page_1->hide();
    }
//Mémorisation de la page
    PageSel = Page;
}

void MainWindow::ChangerInst(int Inst)
{
//Actualise l'interface
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
//Mémorise l'instrument
    InstSel = Inst;
}

/*****************************************************************************/
void MainWindow::ActualiserSet()
{
//Reçoit la configuration
    if (!EXPANDEUR::ChargerSet()) return;
//Décode les données
    ui->widget_instru_1->Recevoir();
    ui->widget_instru_2->Recevoir();
    ui->widget_instru_3->Recevoir();
    ui->widget_instru_4->Recevoir();
    ui->widget_instru_5->Recevoir();
    ui->widget_instru_6->Recevoir();
    ui->widget_instru_7->Recevoir();
    ui->widget_instru_8->Recevoir();
}

void MainWindow::ActualiserInst()
{
    bool b1, b2, b3, b4;
//Reçoit la configuration
    if (!EXPANDEUR::ChargerVoix(InstSel)) return;
//Décode les données
    ui->widget_voice->Recevoir();
    ui->widget_opera_1->Recevoir();
    ui->widget_opera_2->Recevoir();
    ui->widget_opera_3->Recevoir();
    ui->widget_opera_4->Recevoir();
//Détermine le statut
    EXPANDEUR::LireOps(&b1, &b2, &b3, &b4);
    ui->pshBut_OPon_1->setChecked(b1);
    ui->pshBut_OPon_2->setChecked(b2);
    ui->pshBut_OPon_3->setChecked(b3);
    ui->pshBut_OPon_4->setChecked(b4);
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

/*****************************************************************************/
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
void MainWindow::on_actionLoad_set_triggered(bool checked)
{
//Ouvre le fichier
    QFile * Fichier = ChargerFichier(1, VERSION);
    if (Fichier == NULL) return;
//Charge le set d'instruments
    if (ui->widget_instru_1->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_instru_2->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_instru_3->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_instru_4->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_instru_5->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_instru_6->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_instru_7->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_instru_8->Charger(Fichier, VERSION)) goto BadFile;
//Ferme le fichier
    Fichier->close();
    return;
//Erreur apparue
BadFile :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    Fichier->close();
}


void MainWindow::on_actionSave_set_triggered(bool checked)
{
//Ouvre le fichier
    QFile * Fichier = EnregistrerFichier(1, VERSION);
    if (Fichier == NULL) return;
//Enregistre le set d'instruments
    if (ui->widget_instru_1->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_instru_2->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_instru_3->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_instru_4->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_instru_5->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_instru_6->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_instru_7->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_instru_8->Enregistrer(Fichier)) goto BadFile;
//Ferme le fichier
    Fichier->close();
    return;
//Erreur apparue
BadFile:
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    Fichier->close();
}

/*****************************************************************************/
void MainWindow::on_actionLoad_voice_triggered(bool checked)
{
//Ouvre le fichier
    QFile * Fichier = ChargerFichier(2, VERSION);
    if (Fichier == NULL) return;
//Charge la voix
    if (ui->widget_voice->Charger(Fichier, VERSION))   goto BadFile;
    if (ui->widget_opera_1->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_opera_2->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_opera_3->Charger(Fichier, VERSION)) goto BadFile;
    if (ui->widget_opera_4->Charger(Fichier, VERSION)) goto BadFile;
//Ferme le fichier
    Fichier->close();
    return;
//Erreur apparue
BadFile:
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    Fichier->close();
}

void MainWindow::on_actionSave_voice_triggered(bool checked)
{
//Ouvre le fichier
    QFile * Fichier = EnregistrerFichier(2, VERSION);
    if (Fichier == NULL) return;
//Charge la voix
    if (ui->widget_voice->Enregistrer(Fichier))   goto BadFile;
    if (ui->widget_opera_1->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_opera_2->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_opera_3->Enregistrer(Fichier)) goto BadFile;
    if (ui->widget_opera_4->Enregistrer(Fichier)) goto BadFile;
//Ferme le fichier
    Fichier->close();
    return;
//Erreur apparue
BadFile:
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    Fichier->close();
}

/*****************************************************************************/
char ChargeTitres[3][20] = {"Load a bank :", "Load a set :", "Load a voice :"};
char Exts[3][4]= {"fbb", "fbs", "fbv"};
QFile * MainWindow::ChargerFichier(int Type, short Version)
{
    short Ver;
    char  Text[3];
    QFile * Fichier;
//Ouvre le sélecteur
    QString Ext = "*.";
    Ext.append(Exts[Type]);
    QString Nom = QFileDialog::getOpenFileName(this, ChargeTitres[Type], Ext);
    if (Nom.isEmpty()) return NULL;
//Ouvre le fichier   
    Fichier = new QFile(Nom);
    if (!Fichier->open(QIODevice::ReadOnly)) goto Error;
//Vérifie l'entète
    Fichier->read(Text, 3);
    if (strncmp(Exts[Type], Text, 3)) goto BadFile;
    Fichier->read((char *) &Ver, (sizeof(short)));
    if (Ver > Version) goto NewFile;
//Retourne le pointeur
    return Fichier;
//Traitement des érreurs
Error :
    QMessageBox::warning(this, "FB01 SE :", "Cannot open file !");
    return NULL;
BadFile:
    QMessageBox::warning(this, "FB01 SE :", "Bad file type !");
    Fichier->close();
    delete(Fichier);
    return NULL;
NewFile:
    QMessageBox::warning(this, "FB01 SE :", "New file !");
    Fichier->close();
    delete(Fichier);
    return NULL;
}

char EnregTitres[3][20] = {"Save a bank :", "Save a set :", "Save a voice :"};
QFile * MainWindow::EnregistrerFichier(int Type, short Version)
{
    QFile * Fichier;
//Ouvre le sélecteur
    QString Ext = "*.";
    Ext.append(Exts[Type]);
    QString Nom = QFileDialog::getSaveFileName(this, EnregTitres[Type], Ext);
    if (Nom.isEmpty()) return NULL;
//Ouvre le fichier
    Fichier = new QFile(Nom);
    if (!Fichier->open(QIODevice::WriteOnly)) goto Error;
//Ecrit l'entète
    Fichier->write(Exts[Type], 3);
    Fichier->write((char *) &Version, (sizeof(short)));
//Retourne le pointeur
    return Fichier;
//Traitement des érreurs
Error :
    QMessageBox::warning(this, "FB01 SE :", "Cannot open file !");
    Fichier->close();
    delete(Fichier);
    return NULL;
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
