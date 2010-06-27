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
QApplication * application = NULL;
MainWindow   * mainWindow = NULL;
Editeur      * editeur = NULL;

/*****************************************************************************/
int main(int argc, char *argv[])
{
//Démarre le programme
    try {
    //Créé l'application et l'interface
        if ((application = new QApplication(argc, argv)) == NULL)
            throw Memory_ex("Unable to create the application !");
        if ((mainWindow = new MainWindow()) == NULL)
            throw Memory_ex("Unable to create the window !");
        mainWindow->show();
    //Créé l'éditeur
        try {
            if ((editeur = new Editeur()) == NULL)
                throw Memory_ex("Unable to create the editor !");
        }catch(Memory_ex ex) {
            QMessageBox::critical(mainWindow, "FB01 SE:", ex.Info());
            quit(); return 0;
        }catch(MIDI_ex ex) {
            QMessageBox::critical(mainWindow, "FB01 SE:", ex.Info());
            quit(); return 0;
        }
    //Démarre le programme
        application->exec();
    }catch (Memory_ex ex) {
        QMessageBox::critical(mainWindow, "FB01 SE:", ex.Info());
    }catch (...) {
        QMessageBox::critical(mainWindow, "FB01 SE:", "Unknown exception occured !");
    }
//Libère les ressources
    quit(); return 0;
}

void quit()
{
    if (application != NULL) delete application;
    if (mainWindow != NULL)  delete mainWindow;
    if (editeur != NULL)     delete editeur;
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
    application->quit();
}

/*****************************************************************************/
void Editeur::InitialiserEditeur()
{
//Attribue les classes à l'interface
    AttribuerConfig();
    AttribuerBanks();
    AttribuerInstruments();
    AttribuerVoice();
    AttribuerOperateurs();
//Initialise les sélections
    ChoisirPageSet(0);
    ChoisirBank(0);
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
    mainWindow->ui->widget_config->setEnabled(actifs);
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

void Editeur::ChoisirBank(const int bank)
{
//Sélectionne la bank
    bankSel = bank;
    mainWindow->ui->pshBut_bank_cur_1->setChecked(bankSel == 0);
    mainWindow->ui->pshBut_bank_cur_2->setChecked(bankSel == 1);
    mainWindow->ui->pshBut_bank_cur_3->setChecked(bankSel == 2);
    mainWindow->ui->pshBut_bank_cur_4->setChecked(bankSel == 3);
    mainWindow->ui->pshBut_bank_cur_5->setChecked(bankSel == 4);
    mainWindow->ui->pshBut_bank_cur_6->setChecked(bankSel == 5);
    mainWindow->ui->pshBut_bank_cur_7->setChecked(bankSel == 6);
}

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
bool Editeur::ActualiserSet()
{
//Actualise le set courant
    try {
        set.RecevoirTout();
    }catch (MIDI_ex ex) {
        QMessageBox::information(mainWindow, "FB01 SE:", ex.Info());
        return false;
    }
    mainWindow->ui->widget_config->Actualiser();
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

bool Editeur::ActualiserInstru()
{
//Actualise l'instrument courant
    voice.AssocierInstrument(instruSel);
    try {
        voice.RecevoirTout();
    }catch (MIDI_ex ex) {
        QMessageBox::information(mainWindow, "FB01 SE:", ex.Info());
        return false;
    }
//Actualise la voice et les opérateurs
    mainWindow->ui->widget_voice->Actualiser();
    mainWindow->ui->widget_opera_1->Actualiser();
    mainWindow->ui->widget_opera_2->Actualiser();
    mainWindow->ui->widget_opera_3->Actualiser();
    mainWindow->ui->widget_opera_4->Actualiser();
//Actualise l'état des opérateurs
    mainWindow->ui->pshBut_OPon_1->setChecked(editeur->voice.LireParam(Voice::VOICE_ENABLE_OP1));
    mainWindow->ui->pshBut_OPon_2->setChecked(editeur->voice.LireParam(Voice::VOICE_ENABLE_OP2));
    mainWindow->ui->pshBut_OPon_3->setChecked(editeur->voice.LireParam(Voice::VOICE_ENABLE_OP3));
    mainWindow->ui->pshBut_OPon_4->setChecked(editeur->voice.LireParam(Voice::VOICE_ENABLE_OP4));
    return true;
}

bool Editeur::ActualiserBanks()
{
    return true;
}

/*****************************************************************************/
void Editeur::RafraichirBanks()
{
    mainWindow->ui->widget_bank_1->repaint();
    mainWindow->ui->widget_bank_2->repaint();
    mainWindow->ui->widget_bank_3->repaint();
    mainWindow->ui->widget_bank_4->repaint();
    mainWindow->ui->widget_bank_5->repaint();
    mainWindow->ui->widget_bank_6->repaint();
    mainWindow->ui->widget_bank_7->repaint();
}

/*****************************************************************************/
void Editeur::RafraichirSet()
{
    mainWindow->ui->widget_config->repaint();
    if (pageSel == 0) {
        mainWindow->ui->widget_instru_1->repaint();
        mainWindow->ui->widget_instru_2->repaint();
        mainWindow->ui->widget_instru_3->repaint();
        mainWindow->ui->widget_instru_4->repaint();
    }else{
        mainWindow->ui->widget_instru_5->repaint();
        mainWindow->ui->widget_instru_6->repaint();
        mainWindow->ui->widget_instru_7->repaint();
        mainWindow->ui->widget_instru_8->repaint();
    }
}

void Editeur::RafraichirInstru()
{
    mainWindow->ui->widget_voice->repaint();
}

/*****************************************************************************/
void Editeur::AttribuerConfig()
{
//Attribue la configuration
    mainWindow->ui->widget_config->DefinirConfig(&config);
    mainWindow->ui->widget_config->DefinirSet(&set);
}

void Editeur::AttribuerBanks()
{
//Attribue les banks aux contrôles
    mainWindow->ui->widget_bank_1->DefinirBank(&banks[0]);
    mainWindow->ui->widget_bank_2->DefinirBank(&banks[1]);
    mainWindow->ui->widget_bank_3->DefinirBank(&banks[2]);
    mainWindow->ui->widget_bank_4->DefinirBank(&banks[3]);
    mainWindow->ui->widget_bank_5->DefinirBank(&banks[4]);
    mainWindow->ui->widget_bank_6->DefinirBank(&banks[5]);
    mainWindow->ui->widget_bank_7->DefinirBank(&banks[6]);
}

void Editeur::AttribuerInstruments()
{
//Attribue les instruments aux contrôles
    mainWindow->ui->widget_instru_1->DefinirInstrument(set.RecupererInstrument(0));
    mainWindow->ui->widget_instru_2->DefinirInstrument(set.RecupererInstrument(1));
    mainWindow->ui->widget_instru_3->DefinirInstrument(set.RecupererInstrument(2));
    mainWindow->ui->widget_instru_4->DefinirInstrument(set.RecupererInstrument(3));
    mainWindow->ui->widget_instru_5->DefinirInstrument(set.RecupererInstrument(4));
    mainWindow->ui->widget_instru_6->DefinirInstrument(set.RecupererInstrument(5));
    mainWindow->ui->widget_instru_7->DefinirInstrument(set.RecupererInstrument(6));
    mainWindow->ui->widget_instru_8->DefinirInstrument(set.RecupererInstrument(7));
}

void Editeur::AttribuerVoice()
{
//Attribue la voice au controle
    mainWindow->ui->widget_voice->DefinirVoice(&voice);
}

void Editeur::AttribuerOperateurs()
{
//Attribue les opérateurs aux contrôles
    mainWindow->ui->widget_opera_1->DefinirOP(voice.RecupererOP(0));
    mainWindow->ui->widget_opera_2->DefinirOP(voice.RecupererOP(1));
    mainWindow->ui->widget_opera_3->DefinirOP(voice.RecupererOP(2));
    mainWindow->ui->widget_opera_4->DefinirOP(voice.RecupererOP(3));
}

/*****************************************************************************/
void Editeur::Actualiser()
{
//Vérifie la configuration
    if (!MIDI::InOk() || !MIDI::OutOk()) return;
    ConfigurerMenus(true);
    ConfigurerOnglets(true);
//Récupère les informations
    if (!ActualiserBanks()) return;
    if (!ActualiserSet()) return;
    if (!ActualiserInstru()) return;
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
const char ChargerTitres[4][20] = {"Load a bank :", "Load a set :", "Load a voice :", "Load a sysex file :"};
const char ChargerExts[4][4]= {"fbb", "fbs", "fbv", "syx"};
FILE * Editeur::ChargerFichier(FICHIER_TYPE type, short * version)
{
    FILE * fichier;
    char ext[3];
//Ouvre le sélecteur de fichier
    QString filtre = "*.";
    filtre.append(ChargerExts[type]);
    QString nom = QFileDialog::getOpenFileName(mainWindow, ChargerTitres[type], filtre);
    if (nom.isEmpty()) return NULL;
//Ouvre le fichier
    fichier = fopen(nom.toAscii().data(), "rb");
    if (fichier == NULL) goto Error;
//Vérifie l'entète et la version
    if (type != FICHIER_SYSEX) {
        if (fread(ext, 1, 3, fichier) < 3) goto ErrorReading;
        if (fread(version, 2, 1, fichier) < 1) goto ErrorReading;
        if (strncmp(ChargerExts[type], ext, 3)) goto BadFile;
        if (*version > VERSION) goto TooNewFile;
    }
//Retourne le pointeur
    return fichier;
//Traitement des érreurs
Error :
    QMessageBox::warning(mainWindow, "FB01 SE :", "Unable to open the file !");
    return NULL;
ErrorReading :
    QMessageBox::warning(mainWindow, "FB01 SE :", "Unable to read the file !");
    fclose(fichier);
    return NULL;
BadFile:
    QMessageBox::warning(mainWindow, "FB01 SE :", "Bad file format or corrupted file !");
    fclose(fichier);
    return NULL;
TooNewFile:
    QMessageBox::warning(mainWindow, "FB01 SE :", "New file format, please download the latest version !");
    fclose(fichier);
    return NULL;
}

char EnregTitres[4][20] = {"Save a bank :", "Save a set :", "Save a voice :", "Save a sysex file :"};
FILE * Editeur::EnregistrerFichier(FICHIER_TYPE type)
{
    FILE * fichier;
    short version = VERSION;
//Ouvre le sélecteur
    QString filtre = "*.";
    filtre.append(ChargerExts[type]);
    QString nom = QFileDialog::getSaveFileName(mainWindow, EnregTitres[type], filtre);
    if (nom.isEmpty()) return NULL;
    if (!nom.endsWith(ChargerExts[type], Qt::CaseInsensitive))
        nom.append(filtre.right(filtre.length() - 1));
//Ouvre le fichier
    fichier = fopen(nom.toAscii().data(), "wb+");
    if (fichier == NULL) goto Error;
//Ecrit l'entète
    if (type != FICHIER_SYSEX) {
        if (fwrite(ChargerExts[type], 1, 3, fichier) < 3) goto ErrorWriting;
        if (fwrite(&version, 2, 1, fichier) < 1) goto ErrorWriting;
    }
//Retourne le pointeur
    return fichier;
//Traitement des érreurs
Error :
    QMessageBox::warning(mainWindow, "FB01 SE :", "Unable to open the file !");
    fclose(fichier);
    return NULL;
ErrorWriting :
    QMessageBox::warning(mainWindow, "FB01 SE :", "Unable to write the file !");
    fclose(fichier);
    return NULL;
}

