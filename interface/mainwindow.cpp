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
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*****************************************************************************/
void MainWindow::on_actionLoad_bank_triggered(bool checked)
{
/*
    bool ok;
//Ouvre le fichier
    QFile * Fichier = ChargerFichier(0, VERSION);
    if (Fichier == NULL) return;
    Attente = true;
//Charge la bank
    int Bank = QInputDialog::getInt(this, "FB01 SE :", "Which bank would you like to load ?", 1, 1, 2, 1, &ok);
    if (!ok) return;
    if (ui->widget_banks->Charger(Fichier, VERSION, Bank - 1)) goto BadFile;
//Rafraichit l'affichage
    ui->widget_banks->Rafraichir();
//Ferme le fichier
    Attente = false;
    Fichier->close();
    return;
//Erreur apparue
BadFile :
    QMessageBox::warning(this, "FB01 SE :", "Error reading file !");
    Fichier->close();
    */
}

void MainWindow::on_actionSave_bank_triggered(bool checked)
{
   /*
    bool ok;
//Ouvre le fichier
    QFile * Fichier = EnregistrerFichier(0, VERSION);
    if (Fichier == NULL) return;
//Sauve la bank
    int Bank = QInputDialog::getInt(this, "FB01 SE :", "Which bank would you like to save ?", 1, 1, 2, 1, &ok);
    if (!ok) return;
    if (ui->widget_banks->Enregistrer(Fichier, Bank - 1)) goto BadFile;
//Ferme le fichier
    Fichier->close();
    return;
//Erreur apparue
BadFile :
    QMessageBox::warning(this, "FB01 SE :", "Error writing file !");
    Fichier->close();
    */
}

/*****************************************************************************/
void MainWindow::on_actionLoad_set_triggered(bool checked)
{
    /*
//Ouvre le fichier
    QFile * Fichier = ChargerFichier(1, VERSION);
    if (Fichier == NULL) return;
    Attente = true;
//Charge le nom du set
    char Nom[9];
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
    */
}

void MainWindow::on_actionSave_set_triggered(bool checked)
{
    /*
//Ouvre le fichier
    QFile * Fichier = EnregistrerFichier(1, VERSION);
    if (Fichier == NULL) return;
//Enregistre le nom du set
    char Nom[8];
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
    */
}

/*****************************************************************************/
void MainWindow::on_actionLoad_voice_triggered(bool checked)
{
    /*
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
    */
}

void MainWindow::on_actionSave_voice_triggered(bool checked)
{
    /*
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
    */
}

void MainWindow::on_actionInitialize_triggered(bool checked)
{
    /*
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
        */
}

void MainWindow::on_actionRandomize_triggered(bool checked)
{
    /*
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
        */
}

/*****************************************************************************/
void MainWindow::on_actionCopy_triggered(bool checked)
{
    /*
    if (Attente) return;
    if (Copie) free(Copie);
//Copie le contenu
    switch (ui->tabWidget->currentIndex())
    {
    case 1 :
        Copie = (uchar *) malloc(LNGBLK);
        if(ui->widget_banks->Copier(Copie))
        {
        //Libère l'espace
            TypeCopie = 0;
            free(Copie);
            return;
        }
        TypeCopie = 1;
    break;
    case 2 :
        Copie = (uchar *) malloc(LNGINST);
        Insts[InstSel]->Copier(Copie);
        TypeCopie = 2;
    break;
    case 3 :
        Copie = (uchar *) malloc(LNGVOICE);
        ui->widget_voice->Copier(Copie);
        TypeCopie = 3;
    break;
    case 4 :
        Copie = (uchar *) malloc(LNGOP);
        Operas[OPSel]->Copier(Copie);
        TypeCopie = 4;
    break;
    default : break;
    }
    */
}

void MainWindow::on_actionPaste_triggered(bool checked)
{
    /*
    if (Attente) return;
    if (TypeCopie != ui->tabWidget->currentIndex()) return;
//Colle le contenu
    switch (ui->tabWidget->currentIndex())
    {
    case 1 : ui->widget_banks->Coller(Copie); break;
    case 2 : Insts[InstSel]->Coller(Copie); break;
    case 3 : ui->widget_voice->Coller(Copie); break;
    case 4 : Operas[OPSel]->Coller(Copie); break;
    default : break;
    }
    */
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
    Text.append("Thank you for using this program.\n");
    Text.append("Please visit the FB01 website for updates, bug reports and tricks.\n\n");
    Text.append("If you want to help the project author, you can either donate\n");
    Text.append("or get involved into the developpment of the editor, by posting\n");
    Text.append("bug reports or directly contacting me on sourceforge.\n");
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
void MainWindow::on_cmbBox_MIDIIn_activated(int Index)
{
    /*
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
    */
}

void MainWindow::on_cmbBox_MIDIOut_activated(int Index)
{
    /*
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
    */
}

/*****************************************************************************/
void MainWindow::on_pshBut_refresh_midi_clicked(bool checked)
{
    /*
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
    */
}

/*****************************************************************************/
void MainWindow::on_actionSend_current_config_triggered(bool checked)
{
}

void MainWindow::on_actionGet_current_config_triggered(bool checked)
{
}

void MainWindow::on_actionSend_current_set_triggered(bool checked)
{
}

void MainWindow::on_actionGet_current_set_triggered(bool checked)
{
}

void MainWindow::on_actionSend_current_voice_triggered(bool checked)
{
}

void MainWindow::on_actionGet_current_voice_triggered(bool checked)
{
}

/*****************************************************************************/
void MainWindow::on_actionRam_1_triggered(bool checked)
{
}

void MainWindow::on_actionRam_2_triggered(bool checked)
{
}

void MainWindow::on_actionGet_all_banks_triggered(bool checked)
{
}

/*****************************************************************************/
void MainWindow::on_spnBox_syschan_valueChanged(int i)
{
}

void MainWindow::on_spnBox_kybchan_valueChanged(int i)
{
}

void MainWindow::on_pshBut_combine_clicked(bool checked)
{
}

void MainWindow::on_cmbBox_reception_activated(int i)
{
}

void MainWindow::on_pshBut_memory_clicked(bool checked)
{
}

void MainWindow::on_spnBox_confnum_valueChanged(int i)
{
}

void MainWindow::on_hzSlider_mastvol_valueChanged(int i)
{
}

/*****************************************************************************/
void MainWindow::on_pshBut_inst_cur_1_clicked(bool checked)
{
}

void MainWindow::on_pshBut_inst_cur_2_clicked(bool checked)
{
}

void MainWindow::on_pshBut_inst_cur_3_clicked(bool checked)
{
}

void MainWindow::on_pshBut_inst_cur_4_clicked(bool checked)
{
}

void MainWindow::on_pshBut_inst_cur_5_clicked(bool checked)
{
}

void MainWindow::on_pshBut_inst_cur_6_clicked(bool checked)
{
}

void MainWindow::on_pshBut_inst_cur_7_clicked(bool checked)
{
}

void MainWindow::on_pshBut_inst_cur_8_clicked(bool checked)
{
}

void MainWindow::on_txtEdit_setname_textChanged()
{
}

/*****************************************************************************/
void MainWindow::on_pshBut_op_cur_1_clicked(bool checked)
{
}

void MainWindow::on_pshBut_op_cur_2_clicked(bool checked)
{
}

void MainWindow::on_pshBut_op_cur_3_clicked(bool checked)
{
}

void MainWindow::on_pshBut_op_cur_4_clicked(bool checked)
{
}

void MainWindow::on_pshBut_OPon_1_clicked(bool checked)
{
}

void MainWindow::on_pshBut_OPon_2_clicked(bool checked)
{
}

void MainWindow::on_pshBut_OPon_3_clicked(bool checked)
{
}

void MainWindow::on_pshBut_OPon_4_clicked(bool checked)
{
}

/*****************************************************************************/
void MainWindow::on_pshBut_next_pressed()
{
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
}
