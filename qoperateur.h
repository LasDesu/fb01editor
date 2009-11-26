#ifndef QOPERATEUR_H
#define QOPERATEUR_H

#include <QFile>
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
//Gestion de l'opérateur
    void  ChangerID(uchar ID);
    uchar RecupererID();
    void  ChangerInst(uchar Inst);
    uchar RecupererInst();
//Chargement/enregistrement
    bool Enregistrer(QFile * File);
    bool Charger(QFile * File);
//Communication
    void Envoyer();
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
        {EXPANDEUR::EcrireOpParam(InstSel, IDSel, 0x00, (uchar) (127 - i));}
    void on_spnBox_velocity_valueChanged(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, IDSel, (uchar) m_ui->cmbBox_kbcurb->currentIndex(), (uchar) i);}
    void on_spnBox_velmod_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, IDSel, (uchar) m_ui->pshBut_carrier->isChecked(), (uchar) i, (uchar) m_ui->spnBox_DR1->value());}
    void on_spnBox_AR_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, IDSel, (uchar) m_ui->spnBox_rtdph->value(), (uchar) i);}
    void on_spnBox_DR1_valueChanged(int i)
        {EXPANDEUR::ChangerOpx05(InstSel, IDSel, (uchar) m_ui->pshBut_carrier->isChecked(), (uchar) m_ui->spnBox_velmod->value(), (uchar) i);}
    void on_spnBox_SL_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, IDSel, (uchar) (15 - i), (uchar) m_ui->spnBox_RR->value());}
    void on_spnBox_DR2_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, IDSel, (uchar) m_ui->spnBox_coarse->value(), (uchar) i);}
    void on_spnBox_RR_valueChanged(int i)
        {EXPANDEUR::ChangerOpx07(InstSel, IDSel, (uchar) (15 - m_ui->spnBox_SL->value()), (uchar) i);}
    void on_pshBut_carrier_clicked(bool checked)
        {EXPANDEUR::ChangerOpx05(InstSel, IDSel, (uchar) !checked, (uchar) m_ui->spnBox_velmod->value(), (uchar) m_ui->spnBox_DR1->value());}
    void on_spnBox_coarse_valueChanged(int i)
        {EXPANDEUR::ChangerOpx06(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_DR2->value());}
    void on_spnBox_fine_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, IDSel, (uchar) m_ui->cmbBox_kbcurb->currentIndex(), (uchar) i, (uchar) m_ui->spnBox_multiple->value());}
    void on_spnBox_multiple_valueChanged(int i)
        {EXPANDEUR::ChangerOpx03(InstSel, IDSel, (uchar) m_ui->cmbBox_kbcurb->currentIndex(), (uchar) m_ui->spnBox_fine->value(), (uchar) i);}
    void on_cmbBox_kbcurb_activated(int i)
        {EXPANDEUR::ChangerOpx01(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_velocity->value());
         EXPANDEUR::ChangerOpx03(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_fine->value(), (uchar) m_ui->spnBox_multiple->value());}
    void on_spnBox_lvldph_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_adjTL->value());}
    void on_spnBox_rtdph_valueChanged(int i)
        {EXPANDEUR::ChangerOpx04(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_AR->value());}
    void on_spnBox_adjTL_valueChanged(int i)
        {EXPANDEUR::ChangerOpx02(InstSel, IDSel, (uchar) m_ui->spnBox_lvldph->value(), (uchar) i);}
};

#endif // QOPERATEUR_H
