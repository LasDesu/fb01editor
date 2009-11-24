#ifndef QOPERATEUR_H
#define QOPERATEUR_H

#include "ui_qoperateur.h"
#include "expandeur.h"

namespace Ui {
    class QOperateur;
}

class QOperateur : public QWidget {
    Q_OBJECT
public:
//Constructeurs
    QOperateur(QWidget *parent = 0);
    ~QOperateur();
//Identifiant de l'opérateur
    void  ChangerID(uchar ID);
    uchar RecupererID();
    void  ChangerInst(uchar Index);
    uchar RecupererInst();
protected:
    void changeEvent(QEvent *e);
private:
//Configuration
    uchar IDSel;
    uchar InstSel;
    Ui::QOperateur *m_ui;
private slots:
//Gestion des évènements
    void on_hzSlider_volume_valueChanged(int i)
        {EXPANDEUR::EcrireOpParam(InstSel, 0, 0x00, 127 - i);}
    void on_spnBox_velocity_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 0, m_ui->cmbBox_kbcurb->currentIndex(), i);}
    void on_spnBox_velmod_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 0, m_ui->pshBut_carrier->isChecked(), i, m_ui->spnBox_DR1->value());}
    void on_spnBox_AR_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 0, m_ui->spnBox_rtdph->value(), i);}
    void on_spnBox_DR1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, 0, m_ui->pshBut_carrier->isChecked(), m_ui->spnBox_velmod->value(), i);}
    void on_spnBox_SL_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 0, 15 - i, m_ui->spnBox_RR->value());}
    void on_spnBox_DR2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 0, m_ui->spnBox_coarse->value(), i);}
    void on_spnBox_RR_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, 0, 15 - m_ui->spnBox_SL->value(), i);}
    void on_pshBut_carrier_clicked(bool checked)
        {EXPANDEUR::ChangerOpx05(InstSel, 0, !checked, m_ui->spnBox_velmod->value(), m_ui->spnBox_DR1->value());}
    void on_spnBox_coarse_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, 0, i, m_ui->spnBox_DR2->value());}
    void on_spnBox_fine_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 0, m_ui->cmbBox_kbcurb->currentIndex(), i, m_ui->spnBox_multiple->value());}
    void on_spnBox_multiple_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, 0, m_ui->cmbBox_kbcurb->currentIndex(), m_ui->spnBox_fine->value(), i);}
    void on_spnBox_kbcurb_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, 0, i, m_ui->spnBox_velocity->value());
         EXPANDEUR::ChangerOpx03(InstSel, 0, i, m_ui->spnBox_fine->value(), m_ui->spnBox_multiple->value());}
    void on_spnBox_lvldph_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 0, i, m_ui->spnBox_adjTL->value());}
    void on_spnBox_rtdph_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, 0, i, m_ui->spnBox_AR->value());}
    void on_spnBox_adjTL_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, 0, m_ui->spnBox_lvldph->value(), i);}
};

#endif // QOPERATEUR_H
