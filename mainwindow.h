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
    uchar Instrus[2][59];
//Configuration
    uchar PageSel;
    uchar InstSel;
//Utilitaires
    void InitInstrus();
    void ChargerInstrus(uchar Table[]);
    void SauverInstrus(uchar Table[]);
    void ActiverEditeur(bool Actif = true);
private slots:    
//Sélection des drivers
    void on_cmbBox_MIDIIn_activated(int Index);
    void on_cmbBox_MIDIOut_activated(int Index);
    void on_pshBut_refresh_pressed();
//Menus
    void on_actionQuit_triggered(bool checked = false);
    void on_actionAbout_triggered(bool checked = false);
//Changement de pages
    void on_pshBut_next_pressed();
//Configuration globale
    void on_spnBox_syschan_valueChanged(int i)
        {EXPANDEUR::DefinirSysChan(i - 1);}
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
//Configuration des instruments
    void on_spnBox_notes_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x0, i);}
    void on_spnBox_notes_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x0, i);}
    void on_spnBox_notes_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x0, i);}
    void on_spnBox_notes_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x0, i);}
    void on_spnBox_chan_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x1, i - 1);}
    void on_spnBox_chan_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x1, i - 1);}
    void on_spnBox_chan_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x1, i - 1);}
    void on_spnBox_chan_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x1, i - 1);}
    void on_spnBox_upper_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x2, i);}
    void on_spnBox_upper_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x2, i);}
    void on_spnBox_upper_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x2, i);}
    void on_spnBox_upper_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x2, i);}
    void on_spnBox_lower_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x3, i);}
    void on_spnBox_lower_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x3, i);}
    void on_spnBox_lower_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x3, i);}
    void on_spnBox_lower_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x3, i);}
    void on_spnBox_bank_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x4, i);}
    void on_spnBox_bank_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x4, i);}
    void on_spnBox_bank_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x4, i);}
    void on_spnBox_bank_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x4, i);}
    void on_spnBox_voice_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x5, i);}
    void on_spnBox_voice_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x5, i);}
    void on_spnBox_voice_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x5, i);}
    void on_spnBox_voice_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x5, i);}
    void on_spnBox_det_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x6, i);}
    void on_spnBox_det_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x6, i);}
    void on_spnBox_det_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x6, i);}
    void on_spnBox_det_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x6, i);}
     void on_cmbBox_trans_1_activated(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x07, i);}
    void on_cmbBox_trans_2_activated(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x07, i);}
    void on_cmbBox_trans_3_activated(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x07, i);}
    void on_cmbBox_trans_4_activated(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x07, i);}
    void on_hzSlider_level_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x8, i);}
    void on_hzSlider_level_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x8, i);}
    void on_hzSlider_level_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x8, i);}
    void on_hzSlider_level_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x8, i);}
    void on_hzSlider_pan_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x9, i);}
    void on_hzSlider_pan_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x9, i);}
    void on_hzSlider_pan_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x9, i);}
    void on_hzSlider_pan_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x9, i);}
    void on_pshBut_LFO_1_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x0A, checked == true ? 0 : 1);}
    void on_pshBut_LFO_2_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x0A, checked == true ? 0 : 1);}
    void on_pshBut_LFO_3_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x0A, checked == true ? 0 : 1);}
    void on_pshBut_LFO_4_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x0A, checked == true ? 0 : 1);}
    void on_pshBut_poly_1_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x0D, checked == true ? 0 : 1);}
    void on_pshBut_poly_2_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x0D, checked == true ? 0 : 1);}
    void on_pshBut_poly_3_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x0D, checked == true ? 0 : 1);}
    void on_pshBut_poly_4_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x0D, checked == true ? 0 : 1);}
    void on_spnBox_porta_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x0B, i);}
    void on_spnBox_porta_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x0B, i);}
    void on_spnBox_porta_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x0B, i);}
    void on_spnBox_porta_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x0B, i);}
    void on_spnBox_pitch_1_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x0C, i);}
    void on_spnBox_pitch_2_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x0C, i);}
    void on_spnBox_pitch_3_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x0C, i);}
    void on_spnBox_pitch_4_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x0C, i);}
    void on_cmbBox_pmdctl_1_activated(int i)
        {EXPANDEUR::EcrireInstParam(PageSel * 4, 0x0E, i);}
    void on_cmbBox_pmdctl_2_activated(int i)
        {EXPANDEUR::EcrireInstParam(1 + PageSel * 4, 0x0E, i);}
    void on_cmbBox_pmdctl_3_activated(int i)
        {EXPANDEUR::EcrireInstParam(2 + PageSel * 4, 0x0E, i);}
    void on_cmbBox_pmdctl_4_activated(int i)
        {EXPANDEUR::EcrireInstParam(3 + PageSel * 4, 0x0E, i);}
//Configuration des voix
    void on_pshBut_enable_1_clicked(bool checked)
        {EXPANDEUR::ActiverOps(InstSel, checked, ui->pshBut_enable_2->isChecked(), ui->pshBut_enable_3->isChecked(), ui->pshBut_enable_4->isChecked());}
    void on_pshBut_enable_2_clicked(bool checked)
        {EXPANDEUR::ActiverOps(InstSel, ui->pshBut_enable_1->isChecked(), checked, ui->pshBut_enable_3->isChecked(), ui->pshBut_enable_4->isChecked());}
    void on_pshBut_enable_3_clicked(bool checked)
        {EXPANDEUR::ActiverOps(InstSel, ui->pshBut_enable_1->isChecked(), ui->pshBut_enable_2->isChecked(), checked, ui->pshBut_enable_4->isChecked());}
    void on_pshBut_enable_4_clicked(bool checked)
        {EXPANDEUR::ActiverOps(InstSel, ui->pshBut_enable_1->isChecked(), ui->pshBut_enable_2->isChecked(), ui->pshBut_enable_3->isChecked(), checked);}
    void on_hzSlider_volume_1_valueChanged(int i)
        {EXPANDEUR::EcrireOpParam(InstSel, 0, 0x00, i);}
    void on_hzSlider_volume_2_valueChanged(int i)
        {EXPANDEUR::EcrireOpParam(InstSel, 1, 0x00, i);}
    void on_hzSlider_volume_3_valueChanged(int i)
        {EXPANDEUR::EcrireOpParam(InstSel, 2, 0x00, i);}
    void on_hzSlider_volume_4_valueChanged(int i)
        {EXPANDEUR::EcrireOpParam(InstSel, 3, 0x00, i);}
};

#endif // MAINWINDOW_H
