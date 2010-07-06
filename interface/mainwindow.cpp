/*
    FB01 : Sound editor
    Copyright Meslin Frédéric 2009 - 2010
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

extern QApplication * application;
extern Editeur * editeur;

/*****************************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
//Initialise l'interface
    ui->setupUi(this);
    ui->but_kybchan->setValue(1);
    ui->but_kybvelo->setValue(100);
//Initialise certaines valeurs par défaut
    MIDI::ActiverINToOUT(true);
    MIDI::ActiverCTRLToOUT(true);
    MIDI::ChoisirSysChannel(0);
//Lance de timer d'actualisation
    timer = startTimer(EDITEUR_INTER_ACTU);
}

MainWindow::~MainWindow()
{
    if (timer != 0) killTimer(timer);
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
    if (!editeur->banks[editeur->bankSel]->Charger(fichier, version)) goto ErrorReading;
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
    if (!editeur->banks[editeur->bankSel]->Enregistrer(fichier)) goto ErrorWriting;
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
    editeur->RafraichirVoice();
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
    editeur->RafraichirVoice();
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
    editeur->RafraichirVoice();
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
        editeur->RafraichirVoice();
        break;
    case ONGLET_OPERATEURS :
        editeur->voice.RecupererOP(editeur->OPSel)->Initialiser();
        editeur->RafraichirVoice();
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
        editeur->RafraichirVoice();
        break;
    case ONGLET_OPERATEURS :
        editeur->voice.RecupererOP(editeur->OPSel)->Randomiser();
        editeur->RafraichirVoice();
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
        editeur->RafraichirVoice();
        break;
    case ONGLET_OPERATEURS :
        //editeur->voice.RecupererOP(editeur->OPSel)->Coller();
        editeur->RafraichirVoice();
        break;
    }
}

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
void MainWindow::on_actionSend_current_config_triggered(bool checked)
{
    try {
        editeur->config.EnvoyerTout();
    }catch(MIDI_ex ex) {
        QMessageBox::information(this, "FB01 SE:", ex.Info());
    }
}

/*****************************************************************************/
void MainWindow::on_actionSend_current_bank_triggered(bool checked)
{

}

void MainWindow::on_actionGet_current_bank_triggered(bool checked)
{

}

/*****************************************************************************/
void MainWindow::on_actionSend_current_set_triggered(bool checked)
{
    try {
        editeur->set.EnvoyerTout();
    }catch(MIDI_ex ex) {
        QMessageBox::information(this, "FB01 SE:", ex.Info());
    }
}

void MainWindow::on_actionGet_current_set_triggered(bool checked)
{
    editeur->ActualiserSet();
    editeur->RafraichirSet();
}

/*****************************************************************************/
void MainWindow::on_actionSend_current_voice_triggered(bool checked)
{
    try {
        editeur->voice.EnvoyerTout();
    }catch(MIDI_ex ex) {
        QMessageBox::information(this, "FB01 SE:", ex.Info());
    }
}

void MainWindow::on_actionGet_current_voice_triggered(bool checked)
{
    editeur->ActualiserVoice();
    editeur->RafraichirVoice();
}

/*****************************************************************************/
void MainWindow::on_actionQuit_triggered(bool checked)
{
    application->quit();
}

/*****************************************************************************/
void MainWindow::on_actionAbout_FB01SE_triggered(bool checked)
{
    QString text;
//Informations sur le logiciel
    text.append("FB01 Sound Editor : V1.0 (06/02/10)\nCopyright Meslin Frederic 2010\nfredericmeslin@hotmail.com\n\n");
    text.append("A free computer editor for the Yamaha FB01 sound module\n");
    text.append("This program is under a GPL license, please read the COPYING file.\n\n");
    text.append("Main website : http://sourceforge.net/projects/fb01editor/\n");
    QMessageBox::information(this, "FB01 SE :", text);
}

void MainWindow::on_actionAbout_Qt_triggered(bool checked)
{
    QString Text;
//Informations sur la bibliothèque Qt
    QMessageBox::aboutQt(this, "FB01 SE:");
}

/*****************************************************************************/
void MainWindow::on_actionRead_this_triggered(bool checked)
{
    QString text;
//Informations supplémentaires
    text.append("--- Thank you for using this program. ---\n");
    text.append("Please visit the FB01 website for updates, bug reports and tricks.\n\n");
    text.append("If you want to help the project author, you can either donate\n");
    text.append("or get involved into the developpment of the editor, by posting\n");
    text.append("bug reports or directly contacting me by email or on sourceforge.\n");
    QMessageBox::information(this, "FB01 SE :", text);
}

void MainWindow::on_actionUser_manual_triggered(bool checked)
{
    QString text;
//Informations supplémentaires
    text.append("Please look for the :\n\n");
    text.append("help.pdf file (ENGLISH)\n");
    text.append("aide.pdf file (FRANCAIS)\n\n");
    text.append("in the directory of the editor.\n");
    QMessageBox::information(this, "FB01 SE :", text);
}

/*****************************************************************************/
void MainWindow::on_cmbBox_MIDICtrl_activated(int index)
{
    if (index < 1) {
    //Déselectionne le driver
        MIDI::DesactiverCtrl();
    }else{
    //Sélectionne le driver
        try {
            MIDI::ActiverCtrl(index - 1);
        }catch (MIDI_ex ex) {
        //Désélectionne le driver
            ui->cmbBox_MIDICtrl->setCurrentIndex(0);
            QMessageBox::information(this, "FB01 SE:", ex.Info());
            return;
        }
    //Actualise l'éditeur
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
        try {
            MIDI::ActiverIn(index - 1);
        }catch (MIDI_ex ex){
            ui->cmbBox_MIDIIn->setCurrentIndex(0);
            QMessageBox::information(this, "FB01 SE:", ex.Info());
            return;
        }
    //Actualise l'éditeur
        editeur->Actualiser();
    }
}

void MainWindow::on_cmbBox_MIDIOut_activated(int index)
{
    if (index < 1)
    {
    //Déselectionne le driver
        MIDI::DesactiverOut();
        editeur->ConfigurerOnglets(false);
        editeur->ConfigurerMenus(false);
    }else{
    //Sélectionne le driver
        try {
            MIDI::ActiverOut(index - 1);
        }catch (MIDI_ex ex) {
        //Désélectionne le driver
            ui->cmbBox_MIDIOut->setCurrentIndex(0);
            QMessageBox::information(this, "FB01 SE:", ex.Info());
            return;
        }
    //Actualise l'éditeur
        editeur->Actualiser();
    }
}

void MainWindow::on_pshBut_refresh_midi_clicked(bool checked)
{
//Initialise la liste des drivers
    ui->cmbBox_MIDICtrl->clear();
    ui->cmbBox_MIDIIn->clear();
    ui->cmbBox_MIDIOut->clear();
    ui->cmbBox_MIDICtrl->addItem((QString) "No driver selected", 0);
    ui->cmbBox_MIDIIn->addItem((QString) "No driver selected", 0);
    ui->cmbBox_MIDIOut->addItem((QString) "No driver selected", 0);
    ui->cmbBox_MIDICtrl->setCurrentIndex(0);
    ui->cmbBox_MIDIIn->setCurrentIndex(0);
    ui->cmbBox_MIDIOut->setCurrentIndex(0);
//Enumère les drivers
    try {
        MIDI::EnumererDrivers();
    }catch (MIDI_ex ex) {
        QMessageBox::information(this, "FB01 SE:", ex.Info());
        return;
    }
//Ajoute les périphériques
    int nbIns  = MIDI::NbDriversIn();
    int nbOuts = MIDI::NbDriversOut();
    for (int i = 0; i < nbIns; i++) {
        ui->cmbBox_MIDICtrl->addItem((QString)MIDI::DriverIn(i), i+1);
        ui->cmbBox_MIDIIn->addItem((QString)MIDI::DriverIn(i), i+1);
    }
    for (int i = 0; i < nbOuts; i++)
        ui->cmbBox_MIDIOut->addItem((QString)MIDI::DriverOut(i), i+1);
}

/*****************************************************************************/
void MainWindow::on_pshBut_INToOUT_clicked(bool checked)
{
    MIDI::ActiverINToOUT(checked);
}

void MainWindow::on_pshBut_CTRLToOUT_clicked(bool checked)
{
    MIDI::ActiverCTRLToOUT(checked);
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

void MainWindow::on_pshBut_kybQWERTY_clicked(bool checked)
{
//Active la prise en charge du clavier
    if (checked) {
        ui->lbl_clavier->ChoisirClavier(QClavier::CLAVIER_QWERTY);
        ui->lbl_clavier->ActiverClavier(true);
        ui->pshBut_kybAZERTY->setChecked(false);
    }else ui->lbl_clavier->ActiverClavier(false);
}

void MainWindow::on_pshBut_kybAZERTY_clicked(bool checked)
{
//Active la prise en charge du clavier
    if (checked) {
        ui->lbl_clavier->ChoisirClavier(QClavier::CLAVIER_AZERTY);
        ui->lbl_clavier->ActiverClavier(true);
        ui->pshBut_kybQWERTY->setChecked(false);
    }else ui->lbl_clavier->ActiverClavier(false);
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
    editeur->ActualiserVoice();
}

void MainWindow::on_pshBut_inst_cur_2_clicked(bool checked)
{
    editeur->ChoisirInstru(1);
    editeur->ActualiserVoice();
}

void MainWindow::on_pshBut_inst_cur_3_clicked(bool checked)
{
    editeur->ChoisirInstru(2);
    editeur->ActualiserVoice();
}

void MainWindow::on_pshBut_inst_cur_4_clicked(bool checked)
{
    editeur->ChoisirInstru(3);
    editeur->ActualiserVoice();
}

void MainWindow::on_pshBut_inst_cur_5_clicked(bool checked)
{
    editeur->ChoisirInstru(4);
    editeur->ActualiserVoice();
}

void MainWindow::on_pshBut_inst_cur_6_clicked(bool checked)
{
    editeur->ChoisirInstru(5);
    editeur->ActualiserVoice();
}

void MainWindow::on_pshBut_inst_cur_7_clicked(bool checked)
{
    editeur->ChoisirInstru(6);
    editeur->ActualiserVoice();
}

void MainWindow::on_pshBut_inst_cur_8_clicked(bool checked)
{
    editeur->ChoisirInstru(7);
    editeur->ActualiserVoice();
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
void MainWindow::on_pshBut_nextSet_pressed()
{
    editeur->ChoisirPageSet(1 - editeur->pageSetSel);
}

void MainWindow::on_pshBut_nextBank_pressed()
{
    editeur->ChoisirPageSet(1 - editeur->pageBankSel);
}

/*****************************************************************************/
void MainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    editeur->Rafraichir();
}
