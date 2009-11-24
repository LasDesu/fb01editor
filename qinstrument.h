#ifndef QINSTRUMENT_H
#define QINSTRUMENT_H

#include "ui_qinstrument.h"
#include "expandeur.h"

namespace Ui {
    class QInstrument;
}

class QInstrument : public QWidget {
    Q_OBJECT
public:
//Constructeurs
    QInstrument(QWidget *parent = 0);
    ~QInstrument();
//Identifiant de l'instrument
    void  ChangerID(uchar ID);
    uchar RecupererID();
protected:
    void changeEvent(QEvent *e);
private:
//Configuration
    uchar IDSel;
    Ui::QInstrument *m_ui;
private slots:
//Gestion des évènements
    void on_spnBox_notes_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x0, i);}
    void on_spnBox_chan_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x1, i - 1);}
    void on_spnBox_upper_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x2, i);}
    void on_spnBox_lower_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x3, i);}
    void on_spnBox_bank_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x4, i);}
    void on_spnBox_voice_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x5, i);}
    void on_spnBox_detune_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x6, i);}
     void on_cmbBox_trans_activated(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x07, i);}
    void on_hzSlider_volume_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x8, i);}
    void on_hzSlider_pan_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x9, i);}
    void on_pshBut_LFO__clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x0A, checked == true ? 0 : 1);}
    void on_pshBut_poly_clicked(bool checked)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x0D, checked == true ? 0 : 1);}
    void on_spnBox_porta_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x0B, i);}
    void on_spnBox_pitch_valueChanged(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x0C, i);}
    void on_cmbBox_pmdctl_activated(int i)
        {EXPANDEUR::EcrireInstParam(IDSel, 0x0E, i);}
};

#endif // QINSTRUMENT_H
