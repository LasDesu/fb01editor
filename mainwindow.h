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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "expandeur.h"

//Constantes
    #define VERSION 1

    namespace Ui
    {
        class MainWindow;
    }

    class MainWindow : public QMainWindow{
        Q_OBJECT
    public:
    //Constructeurs
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
    private:
    //Objets d'interface
        Ui::MainWindow *ui;
        QOperateur  * Operas[4];
        QInstrument * Insts[8];
        bool Attente;
    //Paramêtres d'édition
        uchar TabCopie[16];
        int TypeCopie;
        int PageSel;
        int InstSel;
        int OPSel;
    //Initialisation
        void InitialiserEditeur();
        void InitialiserInterface();
        void TerminerEditeur();
    //Utilitaires
        void ActiverEditeur(bool Actif);
        void ChangerPage(int Page);
        void ChangerInst(int Inst);
        void ChangerOP(int OP);
    //Archivage
        QFile * ChargerFichier(int Type, short Version);
        QFile * EnregistrerFichier(int Type, short Version);
    //Communication
        void Envoyer();
    //Actualisation
        void ActualiserEditeur();
        void ActualiserSet();
        void ActualiserVoice();
        void ActualiserConfig();
        void ActualiserBank();
    private slots:
    //Sélection des drivers
        void on_cmbBox_MIDIIn_activated(int Index);
        void on_cmbBox_MIDIOut_activated(int Index);
        void on_pshBut_refresh_midi_clicked(bool checked);
    //Menu fichier
        void on_actionQuit_triggered(bool checked = false);
        void on_actionLoad_voice_triggered(bool checked = false);
        void on_actionSave_voice_triggered(bool checked = false);
        void on_actionLoad_set_triggered(bool checked = false);
        void on_actionSave_set_triggered(bool checked = false);
    //Menu edit
        void on_actionInitialize_triggered(bool checked = false);
        void on_actionRandomize_triggered(bool checked = false);
        void on_actionCopy_triggered(bool checked = false);
        void on_actionPaste_triggered(bool checked = false);
    //Menu FB01
        void on_actionSend_current_voice_triggered(bool checked = false)
            {ui->widget_voice->Envoyer();
             ui->widget_opera_1->Envoyer(); ui->widget_opera_2->Envoyer();
             ui->widget_opera_3->Envoyer(); ui->widget_opera_4->Envoyer();}
        void on_actionSend_current_set_triggered(bool checked = false)
            {ui->widget_instru_1->Envoyer(); ui->widget_instru_2->Envoyer();
             ui->widget_instru_3->Envoyer(); ui->widget_instru_4->Envoyer();
             ui->widget_instru_5->Envoyer(); ui->widget_instru_6->Envoyer();
             ui->widget_instru_7->Envoyer(); ui->widget_instru_8->Envoyer();}
        void on_actionSend_current_config_triggered(bool checked = false)
            {Envoyer();}
        void on_actionGet_current_voice_triggered(bool checked = false)
            {ActualiserVoice();}
        void on_actionGet_current_set_triggered(bool checked = false)
            {ActualiserSet();}
        void on_actionGet_current_config_triggered(bool checked = false)
            {ActualiserConfig();}
     //Menu aide
        void on_actionAbout_triggered(bool checked = false);
        void on_actionRead_this_triggered(bool checked = false);
        void on_actionOnline_help_triggered(bool checked = false);
    //Gestion des banks
        void on_pshBut_refresh_bank_clicked(bool checked)
            {ActualiserBank();}
        void on_pshBut_bybank_clicked(bool checked);
        void on_pshBut_byname_clicked(bool checked);
        void on_pshBut_bystyle_clicked(bool checked);
    //Configuration globale
        void on_spnBox_syschan_valueChanged(int i)
            {if (!Attente) EXPANDEUR::SysChan = i - 1;}
        void on_pshBut_combine_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireSysParam(0x08, !checked);}
        void on_cmbBox_reception_activated(int i)
            {if (!Attente) EXPANDEUR::EcrireSysParam(0x0D, (uchar) i);}
        void on_pshBut_memory_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireSysParam(0x21, !checked);}
        void on_spnBox_confnum_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireSysParam(0x22, (uchar) i);}
        void on_hzSlider_mastvol_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireSysParam(0x24, (uchar) i);}
    //Edition des instruments
        void on_pshBut_next_pressed()
            {ChangerPage(1 - PageSel); ActualiserSet();}
        void on_pshBut_inst_cur_1_clicked(bool checked)
            {ChangerInst(0); ActualiserVoice();}
        void on_pshBut_inst_cur_2_clicked(bool checked)
            {ChangerInst(1); ActualiserVoice();}
        void on_pshBut_inst_cur_3_clicked(bool checked)
            {ChangerInst(2); ActualiserVoice();}
        void on_pshBut_inst_cur_4_clicked(bool checked)
            {ChangerInst(3); ActualiserVoice();}
        void on_pshBut_inst_cur_5_clicked(bool checked)
            {ChangerInst(4); ActualiserVoice();}
        void on_pshBut_inst_cur_6_clicked(bool checked)
            {ChangerInst(5); ActualiserVoice();}
        void on_pshBut_inst_cur_7_clicked(bool checked)
            {ChangerInst(6); ActualiserVoice();}
        void on_pshBut_inst_cur_8_clicked(bool checked)
            {ChangerInst(7); ActualiserVoice();}
        void on_txtEdit_setname_textChanged()
            {if (!Attente) EXPANDEUR::EcrireSetNom(ui->txtEdit_setname->toPlainText().toAscii().constData());}
    //Edition des opérateurs
        void on_pshBut_op_cur_1_clicked(bool checked)
            {ChangerOP(0);}
        void on_pshBut_op_cur_2_clicked(bool checked)
            {ChangerOP(1);}
        void on_pshBut_op_cur_3_clicked(bool checked)
            {ChangerOP(2);}
        void on_pshBut_op_cur_4_clicked(bool checked)
            {ChangerOP(3);}
        void on_pshBut_OPon_1_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireOps(InstSel, checked, ui->pshBut_OPon_2->isChecked(), ui->pshBut_OPon_3->isChecked(), ui->pshBut_OPon_4->isChecked());}
        void on_pshBut_OPon_2_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireOps(InstSel, ui->pshBut_OPon_1->isChecked(), checked, ui->pshBut_OPon_3->isChecked(), ui->pshBut_OPon_4->isChecked());}
        void on_pshBut_OPon_3_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireOps(InstSel, ui->pshBut_OPon_1->isChecked(), ui->pshBut_OPon_2->isChecked(), checked, ui->pshBut_OPon_4->isChecked());}
        void on_pshBut_OPon_4_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireOps(InstSel, ui->pshBut_OPon_1->isChecked(), ui->pshBut_OPon_2->isChecked(), ui->pshBut_OPon_3->isChecked(), checked);}
    };

#endif // MAINWINDOW_H
