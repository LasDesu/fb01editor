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
#include "editeur.h"

extern QApplication * MainApp;
extern Editeur * editeur;

/*****************************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->but_kybchan->setValue(1);
    ui->but_kybvelo->setValue(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*****************************************************************************/
void MainWindow::on_actionLoad_bank_triggered(bool checked)
{
    short version;
//Ouvre le fichier
    FILE * fichier = editeur->ChargerFichier(Editeur::FICHIER_BANK, &version);
    if (fichier == NULL) return;
//Charge la bank
    if (!editeur->banks[editeur->bankSel].Charger(fichier, version)) goto ErrorReading;
    editeur->RafraichirBanks();
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorReading :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    fclose(fichier);
}

void MainWindow::on_actionSave_bank_triggered(bool checked)
{
//Ouvre le fichier
    FILE * fichier = editeur->EnregistrerFichier(Editeur::FICHIER_BANK);
    if (fichier == NULL) return;
//Sauvegarde la bank
    if (!editeur->banks[editeur->bankSel].Enregistrer(fichier)) goto ErrorWriting;
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorWriting :
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    fclose(fichier);
}

/*****************************************************************************/
void MainWindow::on_actionLoad_set_triggered(bool checked)
{
    short version;
//Ouvre le fichier
    FILE * fichier = editeur->ChargerFichier(Editeur::FICHIER_SET, &version);
    if (fichier == NULL) return;
//Charge les propriétés du set
    if (!editeur->set.Charger(fichier, version)) goto ErrorReading;
    editeur->RafraichirSet();
//Ferme le fichier
    fclose(fichier);
    return;
//Traitement des érreurs
ErrorReading :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    fclose(fichier);
}

void MainWindow::on_actionSave_set_triggered(bool checked)
{
//Ouvre le fichier
    FILE * fichier = editeur->EnregistrerFichier(Editeur::FICHIER_SET);
    if (fichier == NULL) return;
//Enregistre les propriétés du set
    if (!editeur->set.Enregistrer(fichier)) goto ErrorWriting;
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorWriting :
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    fclose(fichier);
}

/*****************************************************************************/
void MainWindow::on_actionLoad_voice_triggered(bool checked)
{
    short version;
//Ouvre le fichier
    FILE * fichier = editeur->ChargerFichier(Editeur::FICHIER_VOICE, &version);
    if (fichier == NULL) return;
//Charge la voice
    if (!editeur->voice.Charger(fichier, version)) goto ErrorReading;
    editeur->RafraichirInstru();
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorReading :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    fclose(fichier);
}

void MainWindow::on_actionSave_voice_triggered(bool checked)
{
//Ouvre le fichier
    FILE * fichier = editeur->EnregistrerFichier(Editeur::FICHIER_VOICE);
    if (fichier == NULL) return;
//Charge la voice
    if (!editeur->voice.Enregistrer(fichier)) goto ErrorWriting;
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorWriting :
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    fclose(fichier);
}

/*****************************************************************************/
void MainWindow::on_actionImport_bank_triggered(bool checked)
{
/*
//Ouvre le fichier
    FILE * fichier = editeur->ChargerFichier(Editeur::FICHIER_SYSEX, NULL);
    if (fichier == NULL) return;
//Importe la bank
    if (editeur->banks[editeur->BankSel].Importe(fichier)) goto ErrorReading;
    editeur->RafraichirInstru();
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorReading :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    fclose(fichier);
*/
}

void MainWindow::on_actionExport_bank_triggered(bool checked)
{
/*
//Ouvre le fichier
    FILE * fichier = editeur->EnregistrerFichier(Editeur::FICHIER_SYSEX);
    if (fichier == NULL) return;
//Exporte la bank
    if (!editeur->banks[editeur->BankSel].Exporte(fichier)) goto ErrorWriting;
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorWriting :
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    fclose(fichier);
*/
}

void MainWindow::on_actionImport_set_triggered(bool checked)
{
//Ouvre le fichier
    FILE * fichier = editeur->ChargerFichier(Editeur::FICHIER_SYSEX, NULL);
    if (fichier == NULL) return;
//Importe le set
    if (editeur->set.Importe(fichier)) goto ErrorReading;
    editeur->RafraichirSet();
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorReading :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    fclose(fichier);
}

void MainWindow::on_actionExport_set_triggered(bool checked)
{
//Ouvre le fichier
    FILE * fichier = editeur->EnregistrerFichier(Editeur::FICHIER_SYSEX);
    if (fichier == NULL) return;
//Exporte le set
    if (!editeur->set.Exporte(fichier)) goto ErrorWriting;
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorWriting :
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    fclose(fichier);
}

void MainWindow::on_actionImport_voice_triggered(bool checked)
{
//Ouvre le fichier
    FILE * fichier = editeur->ChargerFichier(Editeur::FICHIER_SYSEX, NULL);
    if (fichier == NULL) return;
//Importe la voice
    if (editeur->voice.Importe(fichier)) goto ErrorReading;
    editeur->RafraichirInstru();
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorReading :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    fclose(fichier);
}

void MainWindow::on_actionExport_voice_triggered(bool checked)
{
//Ouvre le fichier
    FILE * fichier = editeur->EnregistrerFichier(Editeur::FICHIER_SYSEX);
    if (fichier == NULL) return;
//Exporte la voice
    if (!editeur->voice.Exporte(fichier)) goto ErrorWriting;
//Ferme le fichier
    fclose(fichier);
    return;
//Erreur apparue
ErrorWriting :
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    fclose(fichier);
}

/*****************************************************************************/
void MainWindow::on_actionInitialize_triggered(bool checked)
{
    switch(ui->tabWidget->currentIndex()) {
    case ONGLET_SET :
        editeur->set.RecupererInstrument(editeur->instruSel)->Initialiser();
        editeur->RafraichirSet();
        break;
    case ONGLET_VOICE :
        editeur->voice.Initialiser();
        editeur->RafraichirInstru();
        break;
    case ONGLET_OPERATEURS :
        editeur->voice.RecupererOP(editeur->OPSel)->Initialiser();
        editeur->RafraichirInstru();
        break;
    }
}

void MainWindow::on_actionRandomize_triggered(bool checked)
{
    switch(ui->tabWidget->currentIndex()) {
    case ONGLET_SET :
        editeur->set.RecupererInstrument(editeur->instruSel)->Randomiser();
        editeur->RafraichirSet();
        break;
    case ONGLET_VOICE :
        editeur->voice.Randomiser();
        editeur->RafraichirInstru();
        break;
    case ONGLET_OPERATEURS :
        editeur->voice.RecupererOP(editeur->OPSel)->Randomiser();
        editeur->RafraichirInstru();
        break;
    }
}

/*****************************************************************************/
void MainWindow::on_actionCopy_triggered(bool checked)
{
    switch(ui->tabWidget->currentIndex()) {
    case ONGLET_BANK :
        //editeur->banks[editeur->BankSel].Copier();
        break;
    case ONGLET_SET :
        //editeur->set.RecupererInstrument(editeur->instruSel)->Copier();
        break;
    case ONGLET_VOICE :
        //editeur->voice.Copier();
        break;
    case ONGLET_OPERATEURS :
        //editeur->voice.RecupererOP(editeur->OPSel)->Copier();
        break;
    }
}

void MainWindow::on_actionPaste_triggered(bool checked)
{
    switch(ui->tabWidget->currentIndex()) {
    case ONGLET_BANK :
        //editeur->banks[editeur->BankSel].Coller();
        editeur->RafraichirBanks();
        break;
    case ONGLET_SET :
        //editeur->set.RecupererInstrument(editeur->instruSel)->Coller();
        editeur->RafraichirSet();
        break;
    case ONGLET_VOICE :
        //editeur->voice.Coller();
        editeur->RafraichirInstru();
        break;
    case ONGLET_OPERATEURS :
        //editeur->voice.RecupererOP(editeur->OPSel)->Coller();
        editeur->RafraichirInstru();
        break;
    }
}

/*****************************************************************************/
void MainWindow::on_actionExchange_triggered(bool checked)
{
    /*
    bool ok;
    int Inst, OP;
    if (Attente) return;
    switch (ui->tabWidget->currentIndex())
    {
    case 1 : ui->widget_banks->Echanger(); break;
    case 2 :
        Inst = QInputDialog::getInt(this, "FB01 SE :", "With which instrument would you like to exchange ?", InstSel+1, 1, 8, 1, &ok);
        if (!ok || Inst == InstSel+1) return;
        Insts[InstSel]->Echanger(Insts[Inst-1]);
        break;
    case 4 :
        OP = QInputDialog::getInt(this, "FB01 SE :", "With which operator would you like to exchange ?", OPSel+1, 1, 4, 1, &ok);
        if (!ok || OP == OPSel+1) return;
        Operas[OPSel]->Echanger(Operas[OP-1]);
        break;
    default : break;
    }
    */
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
    Text.append("FB01 Sound Editor : V1.0 (06/02/10)\nCopyright Meslin Frederic 2010\nfredericmeslin@hotmail.com\n\n");
    Text.append("A free computer editor for the Yamaha FB01 sound module\n");
    Text.append("This program is under a GPL license, please read the COPYING file.\n\n");
    Text.append("Main website : http://sourceforge.net/projects/fb01editor/\n");
    QMessageBox::information(this, "FB01 SE :", Text);
}

void MainWindow::on_actionRead_this_triggered(bool checked)
{
    QString Text;
//Informations supplémentaires
    Text.append("--- Thank you for using this program. ---\n");
    Text.append("Please visit the FB01 website for updates, bug reports and tricks.\n\n");
    Text.append("If you want to help the project author, you can either donate\n");
    Text.append("or get involved into the developpment of the editor, by posting\n");
    Text.append("bug reports or directly contacting me by email or on sourceforge.\n");
    QMessageBox::information(this, "FB01 SE :", Text);
}

void MainWindow::on_actionOnline_help_triggered(bool checked)
{
    QString Text;
//Informations supplémentaires
    Text.append("Please look for the :\n\n");
    Text.append("help.pdf file (ENGLISH)\n");
    Text.append("aide.pdf file (FRANCAIS)\n\n");
    Text.append("in the directory of the editor.\n");
    QMessageBox::information(this, "FB01 SE :", Text);
}

/*****************************************************************************/
void MainWindow::on_cmbBox_MIDICtrl_activated(int index)
{
    if (index < 1) {
    //Déselectionne le driver
        MIDI::DesactiverCtrl();
    }else{
    //Sélectionne le driver
        if (MIDI::ActiverCtrl(index - 1)) {
            ui->cmbBox_MIDICtrl->setCurrentIndex(0);
            editeur->ErreurConnection();
            return;
        }
        editeur->Actualiser();
    }
}

void MainWindow::on_cmbBox_MIDIIn_activated(int index)
{
    if (index < 1) {
    //Déselectionne le driver
        MIDI::DesactiverIn();
        editeur->ConfigurerOnglets(false);
        editeur->ConfigurerMenus(false);
    }else{
    //Sélectionne le driver
        if (MIDI::ActiverIn(index - 1)) {
            ui->cmbBox_MIDIIn->setCurrentIndex(0);
            editeur->ErreurConnection();
            return;
        }
        editeur->Actualiser();
    }
}

void MainWindow::on_cmbBox_MIDIOut_activated(int index)
{
    if (index < 1)
    {
    //Déselectionne le driver
        MIDI::DesactiverOut();
        ui->cmbBox_MIDICtrl->setCurrentIndex(0);
        editeur->ConfigurerOnglets(false);
        editeur->ConfigurerMenus(false);
    }else{
    //Sélectionne le driver
        if (MIDI::ActiverOut(index - 1)) {
            ui->cmbBox_MIDIOut->setCurrentIndex(0);
            editeur->ErreurConnection();
            return;
        }
        editeur->Actualiser();
    }
}

/*****************************************************************************/
void MainWindow::on_pshBut_refresh_midi_clicked(bool checked)
{
//Efface les items
    ui->cmbBox_MIDICtrl->clear();
    ui->cmbBox_MIDIIn->clear();
    ui->cmbBox_MIDIOut->clear();
//Liste les périphériques
    MIDI::EnumererDrivers();
    int nbIns = MIDI::NbDriversIn();
    int nbOuts = MIDI::NbDriversOut();
    ui->cmbBox_MIDICtrl->addItem((QString) "No driver selected", 0);
    ui->cmbBox_MIDIIn->addItem((QString) "No driver selected", 0);
    ui->cmbBox_MIDIOut->addItem((QString) "No driver selected", 0);
//Ajoute les périphériques
    for (int i = 0; i < nbIns; i++) {
        ui->cmbBox_MIDICtrl->addItem((QString)MIDI::DriverIn(i), i+1);
        ui->cmbBox_MIDIIn->addItem((QString)MIDI::DriverIn(i), i+1);
    }
    for (int i = 0; i < nbOuts; i++)
        ui->cmbBox_MIDIOut->addItem((QString)MIDI::DriverOut(i), i+1);
//Sélectionne le driver nul
    ui->cmbBox_MIDICtrl->setCurrentIndex(0);
    ui->cmbBox_MIDIIn->setCurrentIndex(0);
    ui->cmbBox_MIDIOut->setCurrentIndex(0);
}

/*****************************************************************************/
void MainWindow::on_but_kybchan_valueChanged(int i)
{
    MIDI::ChoisirMidiChannel(i-1);
}

void MainWindow::on_but_kybvelo_valueChanged(int i)
{
    MIDI::ChoisirVelocity(i);
}

/*****************************************************************************/
void MainWindow::on_actionSend_current_config_triggered(bool checked)
{
    editeur->config.EnvoyerTout();
}

/*****************************************************************************/
void MainWindow::on_actionSend_current_set_triggered(bool checked)
{
    editeur->set.EnvoyerTout();
}

void MainWindow::on_actionGet_current_set_triggered(bool checked)
{
    editeur->ActualiserSet();
    editeur->RafraichirSet();
}

/*****************************************************************************/
void MainWindow::on_actionSend_current_voice_triggered(bool checked)
{
    editeur->voice.EnvoyerTout();
}

void MainWindow::on_actionGet_current_voice_triggered(bool checked)
{
    editeur->ActualiserInstru();
    editeur->RafraichirInstru();
}

/*****************************************************************************/
void MainWindow::on_pshBut_bank_cur_1_clicked(bool checked)
{
    editeur->ChoisirBank(0);
}

void MainWindow::on_pshBut_bank_cur_2_clicked(bool checked)
{
    editeur->ChoisirBank(1);
}

void MainWindow::on_pshBut_bank_cur_3_clicked(bool checked)
{
    editeur->ChoisirBank(2);
}

void MainWindow::on_pshBut_bank_cur_4_clicked(bool checked)
{
    editeur->ChoisirBank(3);
}

void MainWindow::on_pshBut_bank_cur_5_clicked(bool checked)
{
    editeur->ChoisirBank(4);
}

void MainWindow::on_pshBut_bank_cur_6_clicked(bool checked)
{
    editeur->ChoisirBank(5);
}

void MainWindow::on_pshBut_bank_cur_7_clicked(bool checked)
{
    editeur->ChoisirBank(6);
}

/*****************************************************************************/
void MainWindow::on_pshBut_inst_cur_1_clicked(bool checked)
{
    editeur->ChoisirInstru(0);
    if(!editeur->ActualiserInstru())
        editeur->ErreurMIDI();
}

void MainWindow::on_pshBut_inst_cur_2_clicked(bool checked)
{
    editeur->ChoisirInstru(1);
    if(!editeur->ActualiserInstru())
        editeur->ErreurMIDI();
}

void MainWindow::on_pshBut_inst_cur_3_clicked(bool checked)
{
    editeur->ChoisirInstru(2);
    if(!editeur->ActualiserInstru())
        editeur->ErreurMIDI();
}

void MainWindow::on_pshBut_inst_cur_4_clicked(bool checked)
{
    editeur->ChoisirInstru(3);
    if(!editeur->ActualiserInstru())
        editeur->ErreurMIDI();
}

void MainWindow::on_pshBut_inst_cur_5_clicked(bool checked)
{
    editeur->ChoisirInstru(4);
    if(!editeur->ActualiserInstru())
        editeur->ErreurMIDI();
}

void MainWindow::on_pshBut_inst_cur_6_clicked(bool checked)
{
    editeur->ChoisirInstru(5);
    if(!editeur->ActualiserInstru())
        editeur->ErreurMIDI();
}

void MainWindow::on_pshBut_inst_cur_7_clicked(bool checked)
{
    editeur->ChoisirInstru(6);
    if(!editeur->ActualiserInstru())
        editeur->ErreurMIDI();
}

void MainWindow::on_pshBut_inst_cur_8_clicked(bool checked)
{
    editeur->ChoisirInstru(7);
    if(!editeur->ActualiserInstru())
        editeur->ErreurMIDI();
}

/*****************************************************************************/
void MainWindow::on_pshBut_op_cur_1_clicked(bool checked)
{
    editeur->ChoisirOP(0);
}

void MainWindow::on_pshBut_op_cur_2_clicked(bool checked)
{
    editeur->ChoisirOP(1);
}

void MainWindow::on_pshBut_op_cur_3_clicked(bool checked)
{
    editeur->ChoisirOP(2);
}

void MainWindow::on_pshBut_op_cur_4_clicked(bool checked)
{
    editeur->ChoisirOP(3);
}

/*****************************************************************************/
void MainWindow::on_pshBut_OPon_1_clicked(bool checked)
{
    editeur->voice.EcrireParam(Voice::VOICE_ENABLE_OP1, checked, true);
}

void MainWindow::on_pshBut_OPon_2_clicked(bool checked)
{
    editeur->voice.EcrireParam(Voice::VOICE_ENABLE_OP2, checked, true);
}

void MainWindow::on_pshBut_OPon_3_clicked(bool checked)
{
    editeur->voice.EcrireParam(Voice::VOICE_ENABLE_OP3, checked, true);
}

void MainWindow::on_pshBut_OPon_4_clicked(bool checked)
{
    editeur->voice.EcrireParam(Voice::VOICE_ENABLE_OP4, checked, true);
}

/*****************************************************************************/
void MainWindow::on_pshBut_next_pressed()
{
    editeur->ChoisirPageSet(1 - editeur->pageSel);
}

