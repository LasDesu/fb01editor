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

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
//Constructeurs
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
//Objets
    Ui::MainWindow *ui;
//Configuration
    uchar PageSel;
    uchar InstSel;
//Utilitaires
    void InitialiserEditeur();
    void ActiverEditeur(bool Actif = true);
private slots:    
//Sélection des drivers
    void on_cmbBox_MIDIIn_activated(int Index);
    void on_cmbBox_MIDIOut_activated(int Index);
    void on_pshBut_refresh_midi_pressed();
//Menus
    void on_actionQuit_triggered(bool checked = false);
    void on_actionAbout_triggered(bool checked = false);
//Changement de pages
    void on_pshBut_next_pressed();
//Gestion des banques
    void on_pshBut_refresh_bank_pressed()
        {EXPANDEUR::ChargerBanque(0);}
//Configuration globale
    void on_spnBox_syschan_valueChanged(int i)
        {EXPANDEUR::SysChan = i - 1;}
    void on_pshBut_combine_clicked(bool checked)
        {EXPANDEUR::EcrireSysParam(0x08, checked == true ? 0 : 1);}
    void on_cmbBox_reception_activated(int i)
        {EXPANDEUR::EcrireSysParam(0x0D, i);}
    void on_pshBut_memory_clicked(bool checked)
        {EXPANDEUR::EcrireSysParam(0x21, checked == true ? 0 : 1);}
    void on_spnBox_confnum_valueChanged(int i)
        {EXPANDEUR::EcrireSysParam(0x22, i);}
    void on_hzSlider_mastvol_valueChanged(int i)
        {EXPANDEUR::EcrireSysParam(0x24, i);}
    };

#endif // MAINWINDOW_H
