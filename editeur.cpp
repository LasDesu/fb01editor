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

#include "editeur.h"

QApplication * application;
Editeur      * editeur;

/*****************************************************************************/
int main(int argc, char *argv[])
{
//Créé l'éditeur
    application = new QApplication(argc, argv);
    editeur = new Editeur();
//Démarre le programme
    int res = application->exec();
//Libère les ressources
    delete editeur;
    delete application;
    return res;
}

/*****************************************************************************/
Editeur::Editeur()
{
//Créé la fenêtre
    mainWindow = new MainWindow();
    mainWindow->show();
//Initialise l'éditeur
    InitialiserInterface();
    InitialiserEditeur();
}

Editeur::~Editeur()
{
//Termine l'éditeur
    TerminerEditeur();
    TerminerInterface();
//Libère la fenêtre
    delete mainWindow;
}

/*****************************************************************************/
void Editeur::InitialiserEditeur()
{
//Créé les objets de l'éditeur
    bank  = new Bank();
    set   = new Set();
    voice = new Voice();
//Initialise les sélections
    ChangerPage(0);
    ChangerInst(0);
    ChangerOP(0);
//Initialisations diverses
    srand(QTime::currentTime().msec());
}

void Editeur::InitialiserInterface()
{
    //Liste les drivers
        mainWindow->on_pshBut_refresh_midi_clicked(false);

    /*
//Choisit le premier onglet
    ui->tabWidget->setCurrentIndex(0);
//Créé les tables des opérateurs
    operas[0] = ui->widget_opera_1->;
    operas[1] = ui->widget_opera_2;
    operas[2] = ui->widget_opera_3;
    operas[3] = ui->widget_opera_4;
//Créé les tables des instruments
    instrus[0]  = ui->widget_instru_1;
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
    */
}

void Editeur::TerminerEditeur()
{
    /*
//Réinitialise le MIDI
    MIDI::DesactiverIn();
    MIDI::DesactiverOut();
//Désalloue la liste
    MIDI::DeLister();
//Libère l'espace de copie
    if (TypeCopie != -1) free(Copie);
    */
}

void Editeur::TerminerInterface()
{
}

/*****************************************************************************/
void Editeur::ConfigurerOnglets(const bool Actifs)
{
    /*
//Active ou désactive les onglets
    ui->tab_banks->setEnabled(Actifs);
    ui->tab_set->setEnabled(Actifs);
    ui->tab_operas->setEnabled(Actifs);
    ui->tab_voice->setEnabled(Actifs);
//Active le cadre
    ui->grpBox_config->setEnabled(Actifs);
    */
}

const bool MenuActifs[6][19] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0},
                                {1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,0,0,0,0},
                                {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0},
                                {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1}};
void Editeur::ConfigurerMenus(const int Onglet)
{
    /*
//Menu fichier
    ui->actionLoad_bank->setEnabled(MenuActifs[Onglet][0]);
    ui->actionSave_bank->setEnabled(MenuActifs[Onglet][1]);
    ui->actionLoad_set->setEnabled(MenuActifs[Onglet][2]);
    ui->actionSave_set->setEnabled(MenuActifs[Onglet][3]);
    ui->actionLoad_voice->setEnabled(MenuActifs[Onglet][4]);
    ui->actionSave_voice->setEnabled(MenuActifs[Onglet][5]);
//Menu édition
    ui->actionInitialize->setEnabled(MenuActifs[Onglet][6]);
    ui->actionRandomize->setEnabled(MenuActifs[Onglet][7]);
    ui->actionCopy->setEnabled(MenuActifs[Onglet][8]);
    ui->actionPaste->setEnabled(MenuActifs[Onglet][9]);
    ui->actionExchange->setEnabled(MenuActifs[Onglet][10]);
//Menu configuration
    ui->actionSend_current_config->setEnabled(MenuActifs[Onglet][11]);
    ui->actionGet_current_config->setEnabled(MenuActifs[Onglet][12]);
    ui->actionGet_all_banks->setEnabled(MenuActifs[Onglet][13]);
    ui->menuSend_bank->setEnabled(MenuActifs[Onglet][14]);
    ui->actionSend_current_set->setEnabled(MenuActifs[Onglet][15]);
    ui->actionGet_current_set->setEnabled(MenuActifs[Onglet][16]);
    ui->actionSend_current_voice->setEnabled(MenuActifs[Onglet][17]);
    ui->actionGet_current_voice->setEnabled(MenuActifs[Onglet][18]);
    */
}

/*****************************************************************************/
void Editeur::ChangerPage(const int Page)
{
    /*
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
    */
}

void Editeur::ChangerInst(const int Inst)
{
    /*
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
    */
}

void Editeur::ChangerOP(const int OP)
{
    /*
//Actualise l'interface
    ui->pshBut_op_cur_1->setChecked(OP == 0);
    ui->pshBut_op_cur_2->setChecked(OP == 1);
    ui->pshBut_op_cur_3->setChecked(OP == 2);
    ui->pshBut_op_cur_4->setChecked(OP == 3);
//Mémorise l'opérateur
    OPSel = OP;
    */
}

/*****************************************************************************/
void Editeur::ActualiserEditeur()
{
    /*
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
    */
}

/*****************************************************************************/
bool Editeur::ActualiserConfig()
{
    /*
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
    */
}

bool Editeur::ActualiserBank()
{
    /*
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
    */
}

bool Editeur::ActualiserSet()
{
    /*
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
    */
}

bool Editeur::ActualiserVoice()
{
    /*
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
    */
}

/*****************************************************************************/
/*

void Editeur::Envoyer()
{
//Vérrouille
    Attente = true;
//Envoie la config globale
    EXPANDEUR::EcrireSysParam(0x08, ui->pshBut_combine->isChecked());
    EXPANDEUR::EcrireSysParam(0x0D, (uchar) ui->cmbBox_reception->currentIndex());
    EXPANDEUR::EcrireSysParam(0x21, ui->pshBut_memory->isChecked());
    EXPANDEUR::EcrireSysParam(0x22, (uchar) ui->spnBox_confnum->value()-1);
    EXPANDEUR::EcrireSysParam(0x24, (uchar) ui->hzSlider_mastvol->value());
//Déverrouille
    Attente = false;
}
    */

/*****************************************************************************/
const char ChargeTitres[3][20] = {"Load a bank :", "Load a set :", "Load a voice :"};
const char Exts[3][4]= {"fbb", "fbs", "fbv"};
FILE * Editeur::ChargerFichier(const int Type, const short Version)
{
    /*
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
    */
}

char EnregTitres[3][20] = {"Save a bank :", "Save a set :", "Save a voice :"};
FILE * Editeur::EnregistrerFichier(const int Type, const short Version)
{
    /*
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
    */
}

