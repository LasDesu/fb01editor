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
    //Configuration
        Ui::MainWindow *ui;
        int PageSel;
        int InstSel;
    //Initialisation
        void InitialiserEditeur();
        void TerminerEditeur();
    //Utilitaires
        void ActiverEditeur(bool Actif);
        void ChangerPage(int Page);
        void ChangerInst(int Inst);
    //Archivage
        QFile * ChargerFichier(int Type, short Version);
        QFile * EnregistrerFichier(int Type, short Version);
    //Actualisation
        void ActualiserSet();
        void ActualiserInst();
    private slots:
    //Sélection des drivers
        void on_cmbBox_MIDIIn_activated(int Index);
        void on_cmbBox_MIDIOut_activated(int Index);
        void on_pshBut_refresh_midi_pressed();
    //Menu fichier
        void on_actionQuit_triggered(bool checked = false);
        void on_actionLoad_voice_triggered(bool checked = false);
        void on_actionSave_voice_triggered(bool checked = false);
        void on_actionLoad_set_triggered(bool checked = false);
        void on_actionSave_set_triggered(bool checked = false);
    //Menu FB01
        void on_actionGet_current_voice_triggered(bool checked = false)
            {ActualiserInst();}
        void on_actionGet_current_set_triggered(bool checked = false)
            {ActualiserSet();}
    //Menu aide
        void on_actionAbout_triggered(bool checked = false);
        void on_actionRead_this_triggered(bool checked = false);
        void on_actionOnline_help_triggered(bool checked = false);
    //Gestion des banques

    //Configuration globale
        void on_spnBox_syschan_valueChanged(int i)
            {EXPANDEUR::SysChan = i - 1;}
        void on_pshBut_combine_clicked(bool checked)
            {EXPANDEUR::EcrireSysParam(0x08, checked);}
        void on_cmbBox_reception_activated(int i)
            {EXPANDEUR::EcrireSysParam(0x0D, (uchar) i);}
        void on_pshBut_memory_clicked(bool checked)
            {EXPANDEUR::EcrireSysParam(0x21, checked);}
        void on_spnBox_confnum_valueChanged(int i)
            {EXPANDEUR::EcrireSysParam(0x22, (uchar) i);}
        void on_hzSlider_mastvol_valueChanged(int i)
            {EXPANDEUR::EcrireSysParam(0x24, (uchar) i);}
    //Edition des instruments
        void on_pshBut_next_pressed()
            {ChangerPage(1 - PageSel); ActualiserSet();}
        void on_pshBut_current_1_clicked(bool checked)
            {ChangerInst(0); ActualiserInst();}
        void on_pshBut_current_2_clicked(bool checked)
            {ChangerInst(1); ActualiserInst();}
        void on_pshBut_current_3_clicked(bool checked)
            {ChangerInst(2); ActualiserInst();}
        void on_pshBut_current_4_clicked(bool checked)
            {ChangerInst(3); ActualiserInst();}
        void on_pshBut_current_5_clicked(bool checked)
            {ChangerInst(4); ActualiserInst();}
        void on_pshBut_current_6_clicked(bool checked)
            {ChangerInst(5); ActualiserInst();}
        void on_pshBut_current_7_clicked(bool checked)
            {ChangerInst(6); ActualiserInst();}
        void on_pshBut_current_8_clicked(bool checked)
            {ChangerInst(7); ActualiserInst();}
    //Edition des opérateurs
        void on_pshBut_OPon_1_clicked(bool checked)
            {EXPANDEUR::EcrireOps(InstSel, checked, ui->pshBut_OPon_2->isChecked(), ui->pshBut_OPon_3->isChecked(), ui->pshBut_OPon_4->isChecked());}
        void on_pshBut_OPon_2_clicked(bool checked)
            {EXPANDEUR::EcrireOps(InstSel, ui->pshBut_OPon_2->isChecked(), checked, ui->pshBut_OPon_3->isChecked(), ui->pshBut_OPon_4->isChecked());}
        void on_pshBut_OPon_3_clicked(bool checked)
            {EXPANDEUR::EcrireOps(InstSel, ui->pshBut_OPon_1->isChecked(), ui->pshBut_OPon_2->isChecked(), checked, ui->pshBut_OPon_4->isChecked());}
        void on_pshBut_OPon_4_clicked(bool checked)
            {EXPANDEUR::EcrireOps(InstSel, ui->pshBut_OPon_1->isChecked(), ui->pshBut_OPon_2->isChecked(), ui->pshBut_OPon_3->isChecked(), checked);}
    };

#endif // MAINWINDOW_H
