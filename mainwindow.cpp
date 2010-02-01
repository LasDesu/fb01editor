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

#include "mainwindow.h"

extern QApplication * MainApp;

/*****************************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//Initialisation
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
//Initialise les instruments
    for (int i = 0; i < 8; i ++)
        Insts[i]->ChangerID(i);
//Initialise les sélections
    ChangerPage(0);
    ChangerInst(0);
    ChangerOP(0);
//Initialisations diverses
    srand(QTime::currentTime().msec());
    Copie = NULL;
    TypeCopie = -1;
//Déverrouille
    Attente = false;
}

void MainWindow::InitialiserInterface()
{
//Choisit le premier onglet
    ui->tabWidget->setCurrentIndex(0);
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
//Désactive l'interface
    ConfigurerMenus(0);
    ConfigurerOnglets(false);
}

void MainWindow::TerminerEditeur()
{
//Réinitialise le MIDI
    MIDI::DesactiverIn();
    MIDI::DesactiverOut();
//Désalloue la liste
    MIDI::DeLister();
//Libère l'espace de copie
    if (TypeCopie != -1) free(Copie);
}

/*****************************************************************************/
void MainWindow::ConfigurerOnglets(const bool Actifs)
{
//Active ou désactive les onglets
    ui->tab_banks->setEnabled(Actifs);
    ui->tab_set->setEnabled(Actifs);
    ui->tab_operas->setEnabled(Actifs);
    ui->tab_voice->setEnabled(Actifs);
//Active le cadre
    ui->grpBox_config->setEnabled(Actifs);
}

const bool MenuActifs[6][17] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0},
                                {1,1,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0},
                                {1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0},
                                {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
                                {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1}};
void MainWindow::ConfigurerMenus(const int Onglet)
{
//Menu fichier
    ui->actionLoad_set->setEnabled(MenuActifs[Onglet][0]);
    ui->actionSave_set->setEnabled(MenuActifs[Onglet][1]);
    ui->actionLoad_voice->setEnabled(MenuActifs[Onglet][2]);
    ui->actionSave_voice->setEnabled(MenuActifs[Onglet][3]);
//Menu édition
    ui->actionInitialize->setEnabled(MenuActifs[Onglet][4]);
    ui->actionRandomize->setEnabled(MenuActifs[Onglet][5]);
    ui->actionCopy->setEnabled(MenuActifs[Onglet][6]);
    ui->actionPaste->setEnabled(MenuActifs[Onglet][7]);
    ui->actionExchange->setEnabled(MenuActifs[Onglet][8]);
//Menu configuration
    ui->actionSend_current_config->setEnabled(MenuActifs[Onglet][9]);
    ui->actionGet_current_config->setEnabled(MenuActifs[Onglet][10]);
    ui->actionGet_all_banks->setEnabled(MenuActifs[Onglet][11]);
    ui->menuSend_bank->setEnabled(MenuActifs[Onglet][12]);
    ui->actionSend_current_set->setEnabled(MenuActifs[Onglet][13]);
    ui->actionGet_current_set->setEnabled(MenuActifs[Onglet][14]);
    ui->actionSend_current_voice->setEnabled(MenuActifs[Onglet][15]);
    ui->actionGet_current_voice->setEnabled(MenuActifs[Onglet][16]);
}

/*****************************************************************************/
void MainWindow::ChangerPage(const int Page)
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

void MainWindow::ChangerInst(const int Inst)
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

void MainWindow::ChangerOP(const int OP)
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
void MainWindow::ActualiserEditeur()
{
//Vérifie la configuration
    if (!MIDI::EstConfigure()) return;
    ConfigurerMenus(ui->tabWidget->currentIndex() + 1);
    ConfigurerOnglets(true);
//Récupère les informations
    if (!ActualiserConfig()) goto Erreur;
    if (!ActualiserSet())    goto Erreur;
    if (!ActualiserVoice())  goto Erreur;
    return;
Erreur:
//Réset les drivers
    MIDI::DesactiverIn();
    MIDI::DesactiverOut();
//Vérrouille l'éditeur
    ConfigurerMenus(0);
    ConfigurerOnglets(false);
    ui->cmbBox_MIDIIn->setCurrentIndex(0);
    ui->cmbBox_MIDIOut->setCurrentIndex(0);

}
/*****************************************************************************/
bool MainWindow::ActualiserConfig()
{
//Reçoit la configuration
    Attente = true;
    if (!EXPANDEUR::RecevoirSet())
    {
        Attente = false;
        return false;
    }
//Décode les données
    ui->pshBut_combine->setChecked((bool) EXPANDEUR::LireSysParam(0x08));
    ui->cmbBox_reception->setCurrentIndex((int) EXPANDEUR::LireSysParam(0x0D));
//Déverrouille
    Attente = false;
    return true;
}

bool MainWindow::ActualiserBank()
{
//Recoit les banks
    Attente = true;
    for (int i = 0; i < 7; i++)
        if (!EXPANDEUR::RecevoirBank(i))
        {
            Attente = false;
            return false;
        }
//Décode les données
    ui->widget_banks->Recevoir();
//Déverrouille
    Attente = false;
    return true;
}

bool MainWindow::ActualiserSet()
{
    char Nom[9];
//Reçoit la configuration
    Attente = true;
    if (!EXPANDEUR::RecevoirSet())
    {
        Attente = false;
        return false;
    }
//Décode les données
    for (int i = 0; i < 8; i++)
        Insts[i]->Recevoir();
//Récupère le nom
    EXPANDEUR::LireSetNom(Nom);
    ui->txtEdit_setname->setPlainText((QString) Nom);
    ui->txtEdit_setname->repaint();
//Déverrouille
    Attente = false;
    return true;
}

bool MainWindow::ActualiserVoice()
{
    bool b1, b2, b3, b4;
//Reçoit la configuration
    Attente = true;
    if (!EXPANDEUR::RecevoirVoice(InstSel))
    {
        Attente = false;
        return false;
    }
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
//Déverrouille
    Attente = false;
    return true;
}

/*****************************************************************************/
void MainWindow::Envoyer()
{
//Vérrouille
    Attente = true;
//Envoie la config globale
    EXPANDEUR::EcrireSysParam(0x08, ui->pshBut_combine->isChecked());
    EXPANDEUR::EcrireSysParam(0x0D, (uchar) ui->cmbBox_reception->currentIndex());
    EXPANDEUR::EcrireSysParam(0x21, ui->pshBut_memory->isChecked());
    EXPANDEUR::EcrireSysParam(0x22, (uchar) ui->spnBox_confnum->value());
    EXPANDEUR::EcrireSysParam(0x24, (uchar) ui->hzSlider_mastvol->value());
//Déverrouille
    Attente = false;
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
QFile * MainWindow::ChargerFichier(const int Type, const short Version)
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
QFile * MainWindow::EnregistrerFichier(const int Type, const short Version)
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
    if (Attente) return;
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
    if (Attente) return;
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
    if (Attente) return;
    if (Copie) free(Copie);
    if (ui->tabWidget->currentIndex() == 4)
    {
        Copie = (uchar *) malloc(LNGOP);
        Operas[OPSel]->Copier(Copie);
        TypeCopie = 0;
    }
    else if (ui->tabWidget->currentIndex() == 3)
    {
        Copie = (uchar *) malloc(LNGVOICE);
        ui->widget_voice->Copier(Copie);
        TypeCopie = 1;
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
        Copie = (uchar *) malloc(LNGINST);
        Insts[InstSel]->Copier(Copie);
        TypeCopie = 2;
    }
}

void MainWindow::on_actionPaste_triggered(bool checked)
{
    if (Attente) return;
    if (ui->tabWidget->currentIndex() == 4)
    {
        if (TypeCopie == 0) Operas[OPSel]->Coller(Copie);
    }
    else if (ui->tabWidget->currentIndex() == 3)
    {
        if (TypeCopie == 1) ui->widget_voice->Coller(Copie);
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
        if (TypeCopie == 2) Insts[InstSel]->Coller(Copie);
    }
}

/*****************************************************************************/
void MainWindow::on_actionExchange_triggered(bool checked)
{
}

/*****************************************************************************/
void MainWindow::on_actionQuit_triggered(bool checked)
{
    MainApp->quit();
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
//Change de driver
    if (Attente) return;
    if (Index < 1)
    {
    //Déselectionne le driver
        MIDI::DesactiverIn();
        ConfigurerOnglets(false);
        ConfigurerMenus(0);
    }else{
    //Sélectionne le driver
        MIDI::ActiverIn(Index - 1);
        ActualiserEditeur();
    }
}

void MainWindow::on_cmbBox_MIDIOut_activated(int Index)
{
//Change le driver
    if (Attente) return;
    if (Index < 1)
    {
    //Déselectionne le driver
        MIDI::DesactiverOut();
        ConfigurerOnglets(false);
        ConfigurerMenus(0);
    }else{
    //Sélectionne le driver
        MIDI::ActiverOut(Index - 1);
        ActualiserEditeur();
    }
}

/*****************************************************************************/
void MainWindow::on_pshBut_refresh_midi_clicked(bool checked)
{
//Efface les items
    ui->cmbBox_MIDIIn->clear();
    ui->cmbBox_MIDIOut->clear();
//Liste les périphériques
    MIDI::Lister();
    int Ins = MIDI::NbDriversIn();
    int Outs = MIDI::NbDriversOut();
    ui->cmbBox_MIDIIn->addItem((QString) "No driver selected", 0);
    ui->cmbBox_MIDIOut->addItem((QString) "No driver selected", 0);
//Ajoute les périphériques
    for (int i = 0; i < Ins; i++)
        ui->cmbBox_MIDIIn->addItem((QString)MIDI::DriverIn(i), i+1);
    for (int i = 0; i < Outs; i++)
        ui->cmbBox_MIDIOut->addItem((QString)MIDI::DriverOut(i), i+1);
//Sélectionne le driver nul
    ui->cmbBox_MIDIIn->setCurrentIndex(0);
    ui->cmbBox_MIDIOut->setCurrentIndex(0);
//Désactive l'éditeur
    ConfigurerOnglets(false);
    ConfigurerMenus(0);
}

