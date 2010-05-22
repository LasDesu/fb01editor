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

#include "../ui_mainwindow.h"
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QInputDialog>
#include <QtGui/QFileDialog>
#include <QList>

#include "../editeur.h"
#include "../core/midi.h"
#include "qbank.h"
#include "qinstrument.h"
#include "qvoice.h"
#include "qoperateur.h"

namespace Ui
{
    class MainWindow;
}

/*****************************************************************************/
class MainWindow : public QMainWindow{
    Q_OBJECT
    friend class Editeur;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
public slots:
    void on_cmbBox_MIDICtrl_activated(int index);
    void on_cmbBox_MIDIIn_activated(int index);
    void on_cmbBox_MIDIOut_activated(int index);
    void on_pshBut_refresh_midi_clicked(bool checked);

    void on_actionQuit_triggered(bool checked = false);
    void on_actionLoad_voice_triggered(bool checked = false);
    void on_actionSave_voice_triggered(bool checked = false);
    void on_actionLoad_set_triggered(bool checked = false);
    void on_actionSave_set_triggered(bool checked = false);
    void on_actionLoad_bank_triggered(bool checked = false);
    void on_actionSave_bank_triggered(bool checked = false);

    void on_actionInitialize_triggered(bool checked = false);
    void on_actionRandomize_triggered(bool checked = false);
    void on_actionCopy_triggered(bool checked = false);
    void on_actionPaste_triggered(bool checked = false);
    void on_actionExchange_triggered(bool checked = false);

    void on_actionSend_current_config_triggered(bool checked = false);
    void on_actionGet_current_config_triggered(bool checked = false);
    void on_actionSend_current_set_triggered(bool checked = false);
    void on_actionGet_current_set_triggered(bool checked = false);
    void on_actionSend_current_voice_triggered(bool checked = false);
    void on_actionGet_current_voice_triggered(bool checked = false);

    void on_actionAbout_triggered(bool checked = false);
    void on_actionRead_this_triggered(bool checked = false);
    void on_actionOnline_help_triggered(bool checked = false);

    void on_spnBox_syschan_valueChanged(int i);
    void on_spnBox_kybchan_valueChanged(int i);
    void on_pshBut_combine_clicked(bool checked);
    void on_cmbBox_reception_activated(int i);
    void on_pshBut_memory_clicked(bool checked);
    void on_spnBox_confnum_valueChanged(int i);
    void on_hzSlider_mastvol_valueChanged(int i);

    void on_pshBut_next_pressed();
    void on_pshBut_inst_cur_1_clicked(bool checked);
    void on_pshBut_inst_cur_2_clicked(bool checked);
    void on_pshBut_inst_cur_3_clicked(bool checked);
    void on_pshBut_inst_cur_4_clicked(bool checked);
    void on_pshBut_inst_cur_5_clicked(bool checked);
    void on_pshBut_inst_cur_6_clicked(bool checked);
    void on_pshBut_inst_cur_7_clicked(bool checked);
    void on_pshBut_inst_cur_8_clicked(bool checked);
    void on_txtEdit_setname_textChanged();

    void on_pshBut_op_cur_1_clicked(bool checked);
    void on_pshBut_op_cur_2_clicked(bool checked);
    void on_pshBut_op_cur_3_clicked(bool checked);
    void on_pshBut_op_cur_4_clicked(bool checked);
    void on_pshBut_OPon_1_clicked(bool checked);
    void on_pshBut_OPon_2_clicked(bool checked);
    void on_pshBut_OPon_3_clicked(bool checked);
    void on_pshBut_OPon_4_clicked(bool checked);
};

#endif // MAINWINDOW_H
