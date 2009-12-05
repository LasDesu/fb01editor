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
    InitialiserInterface();
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
//Liste les drivers
    on_pshBut_refresh_midi_clicked(false);
//Initialise les opérateurs
    for (int i = 0; i < 4; i ++)
        Operas[i]->ChangerID(i);
//Initialise les instrus
    for (int i = 0; i < 8; i ++)
        Insts[i]->ChangerID(i);
//Initialise les sélections
    ChangerPage(0);
    ChangerInst(0);
    ChangerOP(0);
//Initialisation diverse
    srand(QTime::currentTime().msec());
    TypeCopie = -1;
    Attente = false;
}

void MainWindow::InitialiserInterface()
{
//Choisit le premier onglet
    ActiverEditeur(false);
    ui->tabWidget->setCurrentIndex(0);
//Organise la table de présets
    ui->table_bank->setRowCount(336);
    ui->table_bank->setColumnCount(4);
//Créé les tables des opérateurs
    Operas[0] = ui->widget_opera_1;
    Operas[1] = ui->widget_opera_2;
    Operas[2] = ui->widget_opera_3;
    Operas[3] = ui->widget_opera_4;
//Créé les tables des instruments
    Insts[0]  = ui->widget_instru_1;
    Insts[1]  = ui->widget_instru_2;
    Insts[2]  = ui->widget_instru_3;
    Insts[3]  = ui->widget_instru_4;
    Insts[4]  = ui->widget_instru_5;
    Insts[5]  = ui->widget_instru_6;
    Insts[6]  = ui->widget_instru_7;
    Insts[7]  = ui->widget_instru_8;
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
//Active le menu fichier
    ui->actionLoad_set->setEnabled(Actif);
    ui->actionLoad_voice->setEnabled(Actif);
    ui->actionSave_set->setEnabled(Actif);
    ui->actionSave_voice->setEnabled(Actif);
//Active le menu FB01
    ui->actionGet_current_config->setEnabled(Actif);
    ui->actionGet_current_set->setEnabled(Actif);
    ui->actionGet_current_voice->setEnabled(Actif);
    ui->actionSend_current_set->setEnabled(Actif);
    ui->actionSend_current_voice->setEnabled(Actif);
//Active le menu édition
    ui->actionInitialize->setEnabled(Actif);
    ui->actionRandomize->setEnabled(Actif);
    ui->actionCopy->setEnabled(Actif);
    ui->actionPaste->setEnabled(Actif);
}

void MainWindow::ActualiserEditeur()
{
//Récupère toutes les informations
    ActualiserConfig();
    ActualiserSet();
    ActualiserVoice();
}

/*****************************************************************************/
void MainWindow::ChangerPage(int Page)
{
//Mémorisation de la page
    PageSel = Page;
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
}

void MainWindow::ChangerInst(int Inst)
{
//Actualise l'interface
    ui->pshBut_inst_cur_1->setChecked(Inst == 0);
    ui->pshBut_inst_cur_2->setChecked(Inst == 1);
    ui->pshBut_inst_cur_3->setChecked(Inst == 2);
    ui->pshBut_inst_cur_4->setChecked(Inst == 3);
    ui->pshBut_inst_cur_5->setChecked(Inst == 4);
    ui->pshBut_inst_cur_6->setChecked(Inst == 5);
    ui->pshBut_inst_cur_7->setChecked(Inst == 6);
    ui->pshBut_inst_cur_8->setChecked(Inst == 7);
//Sélectionne l'instrument
    for (int i = 0; i < 4; i++)
        Operas[i]->ChangerInst(Inst);
//Mémorise l'instrument
    InstSel = Inst;
}

void MainWindow::ChangerOP(int OP)
{
//Actualise l'interface
    ui->pshBut_op_cur_1->setChecked(OP == 0);
    ui->pshBut_op_cur_2->setChecked(OP == 1);
    ui->pshBut_op_cur_3->setChecked(OP == 2);
    ui->pshBut_op_cur_4->setChecked(OP == 3);
//Mémorise l'opérateur
    OPSel = OP;
}

/*****************************************************************************/
void MainWindow::ActualiserConfig()
{
//Reçoit la configuration
    if (!EXPANDEUR::ChargerSet()) return;
    Attente = true;
//Décode les données
    ui->pshBut_combine->setChecked((bool) EXPANDEUR::LireSysParam(0x08));
    ui->cmbBox_reception->setCurrentIndex((int) EXPANDEUR::LireSysParam(0x0D));
    Attente = false;
}

const char BankStyles[14][8] = {"Piano", "Keys", "Organ", "Guitar", "Bass", "Orch", "Brass",
                                "Synth", "Pad", "Ethnic", "Bells", "Rythm", "Sfx", "Other"};
void MainWindow::ActualiserBank()
{
//Vide la liste
    ui->table_bank->clearContents();
//Charge chaque bank
    Attente = true;
    for (int b = 0; b < 8; b++)
    {
    //Reçoit la configuration
        if (!EXPANDEUR::ChargerBank(b)) return;
    //Construit le nom
        QString Bank, NumB;
        if (b < 2) {Bank.append("Ram "); NumB.setNum(b+1);}
        else       {Bank.append("Rom "); NumB.setNum(b-1);}
        Bank.append(NumB);
    //Construit la liste
        for (int v = 0; v < 48; v ++)
        {
        //Charge le nom
            char Nom[8];
            EXPANDEUR::LireBankVoiceNom(v, Nom);
            Nom[7] = 0;
       //Charge le style
            uchar Style = EXPANDEUR::LireBankParam(v, 0x07);
            if (Style > 13) Style = 13;
        //Créé la ligne
            QString NumI; NumI.setNum(v + 1);
            QTableWidgetItem * ItNom   = new QTableWidgetItem((QString) Nom);
            QTableWidgetItem * ItStyle = new QTableWidgetItem((QString) BankStyles[Style]);
            QTableWidgetItem * ItBank  = new QTableWidgetItem(Bank);
            QTableWidgetItem * ItNum  = new QTableWidgetItem(NumI);
        //Ajoute la ligne
            int r = v + b * 48;
            ui->table_bank->setItem(r, 0, ItNom);
            ui->table_bank->setItem(r, 1, ItStyle);
            ui->table_bank->setItem(r, 2, ItBank);
            ui->table_bank->setItem(r, 3, ItNum);
        }
    }
//Déverrouille
    Attente = false;
}

void MainWindow::ActualiserSet()
{
    char Nom[9];
//Reçoit la configuration
    if (!EXPANDEUR::ChargerSet()) return;
    Attente = true;
//Décode les données
    for (int i = 0; i < 8; i++)
        Insts[i]->Recevoir();
//Récupère le nom
    EXPANDEUR::LireSetNom(Nom);
    ui->txtEdit_setname->setPlainText((QString) Nom);
    ui->txtEdit_setname->repaint();
//Dévérouille
    Attente = false;
}

void MainWindow::ActualiserVoice()
{
    bool b1, b2, b3, b4;
//Reçoit la configuration
    if (!EXPANDEUR::ChargerVoice(InstSel)) return;
    Attente = true;
//Décode les données
    ui->widget_voice->Recevoir();
    for (int i = 0; i < 4; i++)
        Operas[i]->Recevoir();
//Rafraichit l'interface
    ui->widget_voice->Rafraichir();
    for (int i = 0; i < 4; i++)
        Operas[i]->Rafraichir();
//Détermine le statut
    EXPANDEUR::LireOps(&b1, &b2, &b3, &b4);
    ui->pshBut_OPon_1->setChecked(b1);
    ui->pshBut_OPon_2->setChecked(b2);
    ui->pshBut_OPon_3->setChecked(b3);
    ui->pshBut_OPon_4->setChecked(b4);
    Attente = false;
}

/*****************************************************************************/
void MainWindow::Envoyer()
{
//Envoie la config globale
    EXPANDEUR::EcrireSysParam(0x08, ui->pshBut_combine->isChecked());
    EXPANDEUR::EcrireSysParam(0x0D, (uchar) ui->cmbBox_reception->currentIndex());
    EXPANDEUR::EcrireSysParam(0x21, ui->pshBut_memory->isChecked());
    EXPANDEUR::EcrireSysParam(0x22, (uchar) ui->spnBox_confnum->value());
    EXPANDEUR::EcrireSysParam(0x24, (uchar) ui->hzSlider_mastvol->value());
}

/*****************************************************************************/
void MainWindow::on_actionLoad_set_triggered(bool checked)
{
    char Nom[9];
//Ouvre le fichier
    QFile * Fichier = ChargerFichier(1, VERSION);
    if (Fichier == NULL) return;
    Attente = true;
//Charge le nom du set
    Fichier->read(Nom, 8);
    Nom[8] = 0;
//Ecrit le nom
    ui->txtEdit_setname->setPlainText((QString) Nom);
//Charge le set d'instruments
    for (int i = 0; i < 8; i++)
        if (Insts[i]->Charger(Fichier, VERSION)) goto BadFile;
//Rafraichit l'affichage
    ui->txtEdit_setname->repaint();
//Ferme le fichier
    Attente = false;
    Fichier->close();
    return;
//Erreur apparue
BadFile :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    Fichier->close();
}

void MainWindow::on_actionSave_set_triggered(bool checked)
{
    char Nom[8];
//Ouvre le fichier
    QFile * Fichier = EnregistrerFichier(1, VERSION);
    if (Fichier == NULL) return;
//Enregistre le nom du set
    strncpy(Nom, ui->txtEdit_setname->toPlainText().toAscii().constData(), 8);
    Fichier->write(Nom, 8);
//Enregistre le set d'instruments
    for (int i = 0; i < 8; i++)
        if (Insts[i]->Enregistrer(Fichier)) goto BadFile;
//Rafraichit l'affichage
    ui->txtEdit_setname->repaint();
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
    Attente = true;
//Charge le voice
    if (ui->widget_voice->Charger(Fichier, VERSION)) goto BadFile;
    for (int i = 0; i < 4; i++)
        if (Operas[i]->Charger(Fichier, VERSION)) goto BadFile;
//Rafraichit l'affichage
    ui->widget_voice->Rafraichir();
    for (int i = 0; i < 4; i++)
        Operas[i]->Rafraichir();
//Ferme le fichier
    Fichier->close();
    Attente = false;
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
//Charge le voice
    if (ui->widget_voice->Enregistrer(Fichier)) goto BadFile;
    for (int i = 0; i < 4; i++)
        if (Operas[i]->Enregistrer(Fichier)) goto BadFile;
//Rafraichit l'affichage
    ui->widget_voice->Rafraichir();
    for (int i = 0; i < 4; i++)
        Operas[i]->Rafraichir();
//Ferme le fichier
    Fichier->close();
    return;
//Erreur apparue
BadFile:
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    Fichier->close();
}

/*****************************************************************************/
const char ChargeTitres[3][20] = {"Load a bank :", "Load a set :", "Load a voice :"};
const char Exts[3][4]= {"fbb", "fbs", "fbv"};
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
void MainWindow::on_actionInitialize_triggered(bool checked)
{
    if (ui->tabWidget->currentIndex() == 4)
    //Opération sur les opérateurs
        Operas[OPSel]->Initialiser();
    else if (ui->tabWidget->currentIndex() == 3)
    //Opération sur la voice
        ui->widget_voice->Initialiser();
    else if (ui->tabWidget->currentIndex() == 2)
    //Opération sur les instruments
        Insts[InstSel]->Initialiser();
}

void MainWindow::on_actionRandomize_triggered(bool checked)
{
    if (ui->tabWidget->currentIndex() == 4)
    //Opération sur les opérateurs
        Operas[OPSel]->Randomiser();
    else if (ui->tabWidget->currentIndex() == 3)
    //Opération sur la voice
        ui->widget_voice->Randomiser();
    else if (ui->tabWidget->currentIndex() == 2)
    //Opération sur les instruments
        Insts[InstSel]->Randomiser();
}

/*****************************************************************************/
void MainWindow::on_actionCopy_triggered(bool checked)
{
    if (ui->tabWidget->currentIndex() == 4)
    {
    //Opération sur les opérateurs
        Operas[OPSel]->Copier(TabCopie);
        TypeCopie = 0;
    }
    else if (ui->tabWidget->currentIndex() == 3)
    {
    //Opération sur la voice
        ui->widget_voice->Copier(TabCopie);
        TypeCopie = 1;
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
    //Opération sur les instruments
        Insts[InstSel]->Copier(TabCopie);
        TypeCopie = 2;
    }
}

void MainWindow::on_actionPaste_triggered(bool checked)
{
    if (ui->tabWidget->currentIndex() == 4)
    {
    //Opération sur les opérateurs
        if (TypeCopie == 0)
            Operas[OPSel]->Coller(TabCopie);
    }
    else if (ui->tabWidget->currentIndex() == 3)
    {
    //Opération sur la voice
        if (TypeCopie == 1)
            ui->widget_voice->Coller(TabCopie);
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
    //Opération sur les instruments
        if (TypeCopie == 2)
            Insts[InstSel]->Coller(TabCopie);
    }
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
    Text.append("Thank you for using this program.\n\n");
    Text.append("If you want to help the author of the project,\n");
    Text.append("you can either donate or make new patchs,\n");
    Text.append("or post bug reports and talk about it in forums.\n");
    QMessageBox::information(this, "FB01 SE :", Text);
}

void MainWindow::on_actionOnline_help_triggered(bool checked)
{
}

/*****************************************************************************/
void MainWindow::on_cmbBox_MIDIIn_activated(int Index)
{
//Sélectionne le driver
    if (Index != -1) MIDI::ActiverIn(Index);
    if (MIDI::EstConfigure())
    {
        ActualiserEditeur();
        ActiverEditeur(true);
    }
}

void MainWindow::on_cmbBox_MIDIOut_activated(int Index)
{
//Sélectionne le driver
    if (Index != -1) MIDI::ActiverOut(Index);
    if (MIDI::EstConfigure())
    {
        ActualiserEditeur();
        ActiverEditeur(true);
    }
}

/*****************************************************************************/
void MainWindow::on_pshBut_refresh_midi_clicked(bool checked)
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
void MainWindow::on_pshBut_bybank_clicked(bool checked)
{
    ui->table_bank->sortByColumn(3, Qt::AscendingOrder);
    ui->table_bank->setSortingEnabled(checked);
    ui->pshBut_byname->setChecked(false);
    ui->pshBut_bystyle->setChecked(false);
}

void MainWindow::on_pshBut_byname_clicked(bool checked)
{
    ui->table_bank->sortByColumn(0, Qt::AscendingOrder);
    ui->table_bank->setSortingEnabled(checked);
    ui->pshBut_bybank->setChecked(false);
    ui->pshBut_bystyle->setChecked(false);
}

void MainWindow::on_pshBut_bystyle_clicked(bool checked)
{
    ui->table_bank->sortByColumn(2, Qt::AscendingOrder);
    ui->table_bank->setSortingEnabled(checked);
    ui->pshBut_byname->setChecked(false);
    ui->pshBut_bybank->setChecked(false);
}
