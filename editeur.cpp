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

//Objets principaux
QApplication * application;
MainWindow   * mainWindow = NULL;
Editeur      * editeur = NULL;

/*****************************************************************************/
int main(int argc, char *argv[])
{
//Créé l'éditeur
    application = new QApplication(argc, argv);
    mainWindow  = new MainWindow();
    mainWindow->show();
    editeur = new Editeur();
//Démarre le programme
    int res = application->exec();
//Libère les ressources
    delete editeur;
    delete mainWindow;
    delete application;
    return res;
}

/*****************************************************************************/
Editeur::Editeur()
{
//Initialise l'éditeur
    InitialiserInterface();
    InitialiserEditeur();
}

Editeur::~Editeur()
{
//Termine l'éditeur
    TerminerEditeur();
    TerminerInterface();
}

/*****************************************************************************/
void Editeur::InitialiserEditeur()
{
//Créé les objets de l'éditeur
    set = new Set();
    voice = new Voice();
    for (int i=0; i < EDITEUR_NB_BANK; i++)
        banks[i] = new Bank();
//Attribue les classes à l'interface
    AttribuerInstruments();
    AttribuerVoice();
    AttribuerOperateurs();
//Initialise les sélections
    ChoisirPageSet(0);
    ChoisirInstru(0);
    ChoisirOP(0);
//Initialisations diverses
    //srand(QTime::currentTime().msec());
}

void Editeur::InitialiserInterface()
{
//Liste les drivers
    mainWindow->on_pshBut_refresh_midi_clicked(false);
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
//Active ou désactive le cadre de config
    mainWindow->ui->grpBox_config->setEnabled(actifs);
//Sélectionne l'onglet de configuration
    if (!actifs)
        mainWindow->ui->tabWidget->setCurrentIndex(0);
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
void Editeur::ChoisirPageSet(const int page)
{
//Sélectionne la page
    pageSel = page;
    if (pageSel == 0) {
        mainWindow->ui->frame_page_1->show();
        mainWindow->ui->frame_page_2->hide();
    }else{
        mainWindow->ui->frame_page_2->show();
        mainWindow->ui->frame_page_1->hide();
    }
}

bool Editeur::ActualiserSet()
{
//Charge le set d'instruments
    if (!set->RecevoirTout()) return false;
//Change le nom du set
    mainWindow->ui->txtEdit_setname->setPlainText((QString) set->LireNom());
    mainWindow->ui->txtEdit_setname->repaint();
//Actualise les instruments
    if (pageSel == 0) {
        mainWindow->ui->widget_instru_1->Actualiser();
        mainWindow->ui->widget_instru_2->Actualiser();
        mainWindow->ui->widget_instru_3->Actualiser();
        mainWindow->ui->widget_instru_4->Actualiser();
    }else{
        mainWindow->ui->widget_instru_5->Actualiser();
        mainWindow->ui->widget_instru_6->Actualiser();
        mainWindow->ui->widget_instru_7->Actualiser();
        mainWindow->ui->widget_instru_8->Actualiser();
    }
    return true;
}

/*****************************************************************************/
void Editeur::ChoisirInstru(const int instru)
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
}

bool Editeur::ActualiserInstru()
{
//Charge l'instrument sélectionné
    voice->AssocierInstrument(instruSel);
    if (!voice->RecevoirTout()) return false;
//Actualise la voice et les opérateurs
    mainWindow->ui->widget_voice->Actualiser();
    mainWindow->ui->widget_opera_1->Actualiser();
    mainWindow->ui->widget_opera_2->Actualiser();
    mainWindow->ui->widget_opera_3->Actualiser();
    mainWindow->ui->widget_opera_4->Actualiser();
    return true;
}

void Editeur::ChoisirOP(const int OP)
{
//Sélectionne l'opérateur
    OPSel = OP;
    mainWindow->ui->pshBut_op_cur_1->setChecked(OPSel == 0);
    mainWindow->ui->pshBut_op_cur_2->setChecked(OPSel == 1);
    mainWindow->ui->pshBut_op_cur_3->setChecked(OPSel == 2);
    mainWindow->ui->pshBut_op_cur_4->setChecked(OPSel == 3);
}

/*****************************************************************************/
bool Editeur::ActualiserConfig()
{
    return true;
}
bool Editeur::ActualiserBanks()
{
    return true;
}


/*****************************************************************************/
void Editeur::AttribuerInstruments()
{
//Attribue les instruments aux contrôles
    mainWindow->ui->widget_instru_1->DefinirInstrument(set->RecupererInstrument(0));
    mainWindow->ui->widget_instru_2->DefinirInstrument(set->RecupererInstrument(1));
    mainWindow->ui->widget_instru_3->DefinirInstrument(set->RecupererInstrument(2));
    mainWindow->ui->widget_instru_4->DefinirInstrument(set->RecupererInstrument(3));
    mainWindow->ui->widget_instru_5->DefinirInstrument(set->RecupererInstrument(4));
    mainWindow->ui->widget_instru_6->DefinirInstrument(set->RecupererInstrument(5));
    mainWindow->ui->widget_instru_7->DefinirInstrument(set->RecupererInstrument(6));
    mainWindow->ui->widget_instru_8->DefinirInstrument(set->RecupererInstrument(7));
}

void Editeur::AttribuerVoice()
{
//Attribue la voice au controle
    mainWindow->ui->widget_voice->DefinirVoice(voice);
}

void Editeur::AttribuerOperateurs()
{
//Attribue les opérateurs aux contrôles
    mainWindow->ui->widget_opera_1->DefinirOP(voice->RecupererOP(0));
    mainWindow->ui->widget_opera_2->DefinirOP(voice->RecupererOP(1));
    mainWindow->ui->widget_opera_3->DefinirOP(voice->RecupererOP(2));
    mainWindow->ui->widget_opera_4->DefinirOP(voice->RecupererOP(3));
}


/*****************************************************************************/
void Editeur::ErreurMIDI()
{
    QMessageBox::information(mainWindow,"FB01 Editor :", "Error in MIDI communication,\nplease check your cables and devices !");
    Reinitialiser();
}

void Editeur::ErreurConnection()
{
    QMessageBox::information(mainWindow,"FB01 Editor :", "Error when connecting to the MIDI driver,\nplease check your interfaces and refresh the drivers list !");
}

/*****************************************************************************/
void Editeur::Actualiser()
{
//Vérifie la configuration
    if (!MIDI::InOk() || !MIDI::OutOk()) return;
    ConfigurerMenus(true);
    ConfigurerOnglets(true);
//Récupère les informations
    if (!ActualiserConfig()) {
        Reinitialiser();
        return;
    }
    if (!ActualiserSet()) {
        ErreurMIDI();
        return;
    }
    if (!ActualiserInstru()) {
        ErreurMIDI();
        return;
    }
}

void Editeur::Reinitialiser()
{
//Déselectionne les drivers
    mainWindow->ui->cmbBox_MIDIIn->setCurrentIndex(0);
    mainWindow->ui->cmbBox_MIDIOut->setCurrentIndex(0);
    mainWindow->ui->cmbBox_MIDICtrl->setCurrentIndex(0);
    MIDI::DesactiverIn();
    MIDI::DesactiverOut();
//Vérrouille l'interface
    ConfigurerMenus(0);
    ConfigurerOnglets(0);
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

