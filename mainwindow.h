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
        {EXPANDEUR::EcrireOpParam(InstSel, 0, 0x00, 127 - i);}
    void on_hzSlider_volume_2_valueChanged(int i)
        {EXPANDEUR::EcrireOpParam(InstSel, 1, 0x00, 127 - i);}
    void on_hzSlider_volume_3_valueChanged(int i)
        {EXPANDEUR::EcrireOpParam(InstSel, 2, 0x00, 127 - i);}
    void on_hzSlider_volume_4_valueChanged(int i)
        {EXPANDEUR::EcrireOpParam(InstSel, 3, 0x00, 127 - i);}
    void on_spnBox_velocity_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 0, ui->cmbBox_kbcurb_1->currentIndex(), i);}
    void on_spnBox_velocity_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 1, ui->cmbBox_kbcurb_2->currentIndex(), i);}
    void on_spnBox_velocity_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 2, ui->cmbBox_kbcurb_3->currentIndex(), i);}
    void on_spnBox_velocity_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 3, ui->cmbBox_kbcurb_4->currentIndex(), i);}
    void on_spnBox_velmod_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 0, ui->pshBut_carrier_1->isChecked(), i, ui->spnBox_DR1_1->value());}
    void on_spnBox_velmod_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 1, ui->pshBut_carrier_2->isChecked(), i, ui->spnBox_DR1_2->value());}
    void on_spnBox_velmod_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 2, ui->pshBut_carrier_3->isChecked(), i, ui->spnBox_DR1_3->value());}
    void on_spnBox_velmod_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 3, ui->pshBut_carrier_4->isChecked(), i, ui->spnBox_DR1_4->value());}
    void on_spnBox_AR_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 0, ui->spnBox_rtdph_1->value(), i);}
    void on_spnBox_AR_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 1, ui->spnBox_rtdph_2->value(), i);}
    void on_spnBox_AR_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 2, ui->spnBox_rtdph_3->value(), i);}
    void on_spnBox_AR_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 3, ui->spnBox_rtdph_4->value(), i);}
    void on_spnBox_DR1_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 0, ui->pshBut_carrier_1->isChecked(), ui->spnBox_velmod_1->value(), i);}
    void on_spnBox_DR1_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 1, ui->pshBut_carrier_2->isChecked(), ui->spnBox_velmod_2->value(), i);}
    void on_spnBox_DR1_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 2, ui->pshBut_carrier_3->isChecked(), ui->spnBox_velmod_3->value(), i);}
    void on_spnBox_DR1_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 3, ui->pshBut_carrier_4->isChecked(), ui->spnBox_velmod_4->value(), i);}
    void on_spnBox_SL_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 0, 15 - i, ui->spnBox_RR_1->value());}
    void on_spnBox_SL_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 1, 15 - i, ui->spnBox_RR_2->value());}
    void on_spnBox_SL_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 2, 15 - i, ui->spnBox_RR_3->value());}
    void on_spnBox_SL_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 3, 15 - i, ui->spnBox_RR_4->value());}
    void on_spnBox_DR2_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 0, ui->spnBox_coarse_1->value(), i);}
    void on_spnBox_DR2_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 1, ui->spnBox_coarse_2->value(), i);}
    void on_spnBox_DR2_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 2, ui->spnBox_coarse_3->value(), i);}
    void on_spnBox_DR2_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 3, ui->spnBox_coarse_4->value(), i);}
    void on_spnBox_RR_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 0, 15 - ui->spnBox_SL_1->value(), i);}
    void on_spnBox_RR_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 1, 15 - ui->spnBox_SL_2->value(), i);}
    void on_spnBox_RR_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 2, 15 - ui->spnBox_SL_3->value(), i);}
    void on_spnBox_RR_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 3, 15 - ui->spnBox_SL_4->value(), i);}
    void on_pshBut_carrier_1_clicked(bool checked)
        {EXPANDEUR::ChangerOpx05(InstSel, 0, !checked, ui->spnBox_velmod_1->value(), ui->spnBox_DR1_1->value());}
    void on_pshBut_carrier_2_clicked(bool checked)
        {EXPANDEUR::ChangerOpx05(InstSel, 1, !checked, ui->spnBox_velmod_2->value(), ui->spnBox_DR1_2->value());}
    void on_pshBut_carrier_3_clicked(bool checked)
        {EXPANDEUR::ChangerOpx05(InstSel, 2, !checked, ui->spnBox_velmod_3->value(), ui->spnBox_DR1_3->value());}
    void on_pshBut_carrier_4_clicked(bool checked)
        {EXPANDEUR::ChangerOpx05(InstSel, 3, !checked, ui->spnBox_velmod_4->value(), ui->spnBox_DR1_4->value());}
    void on_spnBox_coarse_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 0, i, ui->spnBox_DR2_1->value());}
    void on_spnBox_coarse_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 1, i, ui->spnBox_DR2_2->value());}
    void on_spnBox_coarse_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 2, i, ui->spnBox_DR2_3->value());}
    void on_spnBox_coarse_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 3, i, ui->spnBox_DR2_4->value());}
    void on_spnBox_fine_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 0, ui->cmbBox_kbcurb_1->currentIndex(), i, ui->spnBox_multiple_1->value());}
    void on_spnBox_fine_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 1, ui->cmbBox_kbcurb_2->currentIndex(), i, ui->spnBox_multiple_2->value());}
    void on_spnBox_fine_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 2, ui->cmbBox_kbcurb_3->currentIndex(), i, ui->spnBox_multiple_3->value());}
    void on_spnBox_fine_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 3, ui->cmbBox_kbcurb_4->currentIndex(), i, ui->spnBox_multiple_4->value());}
    void on_spnBox_multiple_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 0, ui->cmbBox_kbcurb_1->currentIndex(), ui->spnBox_fine_1->value(), i);}
    void on_spnBox_multiple_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 1, ui->cmbBox_kbcurb_2->currentIndex(), ui->spnBox_fine_2->value(), i);}
    void on_spnBox_multiple_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 2, ui->cmbBox_kbcurb_3->currentIndex(), ui->spnBox_fine_3->value(), i);}
    void on_spnBox_multiple_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 3, ui->cmbBox_kbcurb_4->currentIndex(), ui->spnBox_fine_4->value(), i);}
    void on_spnBox_kbcurb_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 0, i, ui->spnBox_velocity_1->value());
         EXPANDEUR::ChangerOpx03(InstSel, 0, i, ui->spnBox_fine_1->value(), ui->spnBox_multiple_1->value());}
    void on_spnBox_kbcurb_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 1, i, ui->spnBox_velocity_2->value());
         EXPANDEUR::ChangerOpx03(InstSel, 1, i, ui->spnBox_fine_2->value(), ui->spnBox_multiple_2->value());}
    void on_spnBox_kbcurb_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 2, i, ui->spnBox_velocity_3->value());
         EXPANDEUR::ChangerOpx03(InstSel, 2, i, ui->spnBox_fine_3->value(), ui->spnBox_multiple_3->value());}
    void on_spnBox_kbcurb_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 3, i, ui->spnBox_velocity_4->value());
         EXPANDEUR::ChangerOpx03(InstSel, 3, i, ui->spnBox_fine_4->value(), ui->spnBox_multiple_4->value());}
    void on_spnBox_lvldph_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 0, i, ui->spnBox_adjTL_1->value());}
    void on_spnBox_lvldph_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 1, i, ui->spnBox_adjTL_2->value());}
    void on_spnBox_lvldph_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 2, i, ui->spnBox_adjTL_3->value());}
    void on_spnBox_lvldph_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 3, i, ui->spnBox_adjTL_4->value());}
    void on_spnBox_rtdph_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 0, i, ui->spnBox_AR_1->value());}
   void on_spnBox_rtdph_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 1, i, ui->spnBox_AR_2->value());}
   void on_spnBox_rtdph_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 2, i, ui->spnBox_AR_3->value());}
   void on_spnBox_rtdph_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 3, i, ui->spnBox_AR_4->value());}
   void on_spnBox_adjTL_1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 0, ui->spnBox_lvldph_1->value(), i);}
   void on_spnBox_adjTL_2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 1, ui->spnBox_lvldph_2->value(), i);}
   void on_spnBox_adjTL_3_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 2, ui->spnBox_lvldph_3->value(), i);}
   void on_spnBox_adjTL_4_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 3, ui->spnBox_lvldph_4->value(), i);}
};

#endif // MAINWINDOW_H
