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
    set = new Set();
    voice = new Voice(0);
    for (int i=0; i < EDITEUR_NB_BANK; i++)
        bank[i] = new Bank();
//Initialise les sélections
    ChangerPage(0);
    ChangerInstru(0);
    ChangerOP(0);
//Initialisations diverses
    //srand(QTime::currentTime().msec());
}

void Editeur::InitialiserInterface()
{
//Liste les drivers
    mainWindow->on_pshBut_refresh_midi_clicked(false);
//Choisit le premier onglet
    mainWindow->ui->tabWidget->setCurrentIndex(0);
//Désactive l'interface
    ConfigurerMenus(false);
    ConfigurerOnglets(false);
}

void Editeur::TerminerEditeur()
{
//Réinitialise le MIDI
    MIDI::DesactiverCtrl();
    MIDI::DesactiverIn();
    MIDI::DesactiverOut();
    MIDI::LibererDrivers();
}

void Editeur::TerminerInterface()
{
}

/*****************************************************************************/
void Editeur::ConfigurerOnglets(const bool actifs)
{
//Active ou désactive les onglets
    mainWindow->ui->tab_banks->setEnabled(actifs);
    mainWindow->ui->tab_set->setEnabled(actifs);
    mainWindow->ui->tab_operas->setEnabled(actifs);
    mainWindow->ui->tab_voice->setEnabled(actifs);
//Active le cadre
    mainWindow->ui->grpBox_config->setEnabled(actifs);
}

void Editeur::ConfigurerMenus(const bool actifs)
{
//Menu fichier
    mainWindow->ui->actionLoad_bank->setEnabled(actifs);
    mainWindow->ui->actionSave_bank->setEnabled(actifs);
    mainWindow->ui->actionLoad_set->setEnabled(actifs);
    mainWindow->ui->actionSave_set->setEnabled(actifs);
    mainWindow->ui->actionLoad_voice->setEnabled(actifs);
    mainWindow->ui->actionSave_voice->setEnabled(actifs);
    mainWindow->ui->actionImport_bank->setEnabled(actifs);
    mainWindow->ui->actionImport_set->setEnabled(actifs);
    mainWindow->ui->actionImport_voice->setEnabled(actifs);
    mainWindow->ui->actionExport_bank->setEnabled(actifs);
    mainWindow->ui->actionExport_set->setEnabled(actifs);
    mainWindow->ui->actionExport_voice->setEnabled(actifs);
//Menu édition
    mainWindow->ui->actionInitialize->setEnabled(actifs);
    mainWindow->ui->actionRandomize->setEnabled(actifs);
    mainWindow->ui->actionCopy->setEnabled(actifs);
    mainWindow->ui->actionPaste->setEnabled(actifs);
    mainWindow->ui->actionExchange->setEnabled(actifs);
//Menu FB01
    mainWindow->ui->actionGet_current_config->setEnabled(actifs);
    mainWindow->ui->actionGet_bank->setEnabled(actifs);
    mainWindow->ui->actionGet_current_set->setEnabled(actifs);
    mainWindow->ui->actionGet_current_voice->setEnabled(actifs);
    mainWindow->ui->actionSend_current_config->setEnabled(actifs);
    mainWindow->ui->actionSend_bank->setEnabled(actifs);
    mainWindow->ui->actionSend_current_set->setEnabled(actifs);
    mainWindow->ui->actionSend_current_voice->setEnabled(actifs);
}

/*****************************************************************************/
void Editeur::ChangerPage(const int page)
{
//Sélectionne la page
    pageSel = page;
    if (pageSel == 0)
    {
        mainWindow->ui->frame_page_1->show();
        mainWindow->ui->frame_page_2->hide();
    }else{
        mainWindow->ui->frame_page_2->show();
        mainWindow->ui->frame_page_1->hide();
    }
}

void Editeur::ChangerInstru(const int instru)
{
//Sélectionne l'instrument
    instruSel = instru;
    mainWindow->ui->pshBut_inst_cur_1->setChecked(instruSel == 0);
    mainWindow->ui->pshBut_inst_cur_2->setChecked(instruSel == 1);
    mainWindow->ui->pshBut_inst_cur_3->setChecked(instruSel == 2);
    mainWindow->ui->pshBut_inst_cur_4->setChecked(instruSel == 3);
    mainWindow->ui->pshBut_inst_cur_5->setChecked(instruSel == 4);
    mainWindow->ui->pshBut_inst_cur_6->setChecked(instruSel == 5);
    mainWindow->ui->pshBut_inst_cur_7->setChecked(instruSel == 6);
    mainWindow->ui->pshBut_inst_cur_8->setChecked(instruSel == 7);
//Charge le nouvelle instrument

}

void Editeur::ChangerOP(const int OP)
{
//Sélectionne l'opérateur
    OPSel = OP;
    mainWindow->ui->pshBut_op_cur_1->setChecked(OP == 0);
    mainWindow->ui->pshBut_op_cur_2->setChecked(OP == 1);
    mainWindow->ui->pshBut_op_cur_3->setChecked(OP == 2);
    mainWindow->ui->pshBut_op_cur_4->setChecked(OP == 3);
}

/*****************************************************************************/
void Editeur::ActualiserEditeur()
{
//Vérifie la configuration
    if (!MIDI::InOk() || !MIDI::OutOk()) return;
    ConfigurerMenus(true);
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
    ConfigurerOnglets(0);
    mainWindow->ui->cmbBox_MIDIIn->setCurrentIndex(0);
    mainWindow->ui->cmbBox_MIDIOut->setCurrentIndex(0);
    mainWindow->ui->cmbBox_MIDICtrl->setCurrentIndex(0);
}

/*****************************************************************************/
bool Editeur::ActualiserConfig()
{
    /*
//Reçoit la configuration
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
    */
    return true;
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
    */
    return true;
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
    */
    return true;
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
    */
    return true;
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

