#ifndef QVOICE_H
#define QVOICE_H

#include <QFile>
#include "ui_qvoice.h"
#include "expandeur.h"

namespace Ui {
    class QVoice;
}

class QVoice : public QWidget {
    Q_OBJECT
public:
//Constructeurs
    QVoice(QWidget *parent = 0);
    ~QVoice();
//Gestion de la configuration
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
    uchar InstSel;
    Ui::QVoice *m_ui;
private slots:
//Gestion des évènements
    void on_txtEdit_name_textChanged()
        {EXPANDEUR::ChangerNom(InstSel, m_ui->txtEdit_name->toPlainText().toAscii().data());}
    void on_cmbBox_style_activated(int i)
        {EXPANDEUR::EcrireVoiceParam(InstSel, 0x07, (uchar) i);}
    void on_spnBox_feedback_valueChanged(int i)
        {EXPANDEUR::ChangerVoicex0C(InstSel, (uchar) i, (uchar) m_ui->spnBox_algo->value());}
    void on_spnBox_trans_valueChanged(int i)
        {EXPANDEUR::EcrireVoiceParam(InstSel, 0x0F, (uchar) i);}
    void on_pshBut_poly_clicked(bool checked)
        {EXPANDEUR::ChangerVoicex3A(InstSel, (uchar) !checked, (uchar) m_ui->spnBox_porta->value());}
    void on_spnBox_porta_valueChanged(int i)
        {EXPANDEUR::ChangerVoicex3A(InstSel, (uchar) m_ui->pshBut_poly->isChecked(), (uchar) i);}
    void on_spnBox_pitch_valueChanged(int i)
        {EXPANDEUR::ChangerVoicex3B(InstSel, (uchar) m_ui->cmbBox_pmdctl->currentIndex(), (uchar) i);}
    void on_cmbBox_pmdctl_valueChanged(int i)
        {EXPANDEUR::ChangerVoicex3B(InstSel, (uchar) i, (uchar) m_ui->spnBox_pitch->value());}
    void on_spnBox_LFOspeed_valueChanged(int i)
        {EXPANDEUR::EcrireVoiceParam(InstSel, 0x08, (uchar) i);}
    void on_cmbBox_LFOwave_activated(int i)
        {EXPANDEUR::ChangerVoicex0E(InstSel, (uchar) i);}
    void on_pshBut_LFOload_clicked(bool checked)
        {EXPANDEUR::ChangerVoicex09(InstSel, (uchar) !checked, (uchar) m_ui->spnBox_AMD->value());}
    void on_pshBut_LFOsync_clicked(bool checked)
        {EXPANDEUR::ChangerVoicex0A(InstSel, (uchar) !checked, (uchar) m_ui->spnBox_PMD->value());}
    void on_spnBox_AMD_valueChanged(int i)
        {EXPANDEUR::ChangerVoicex09(InstSel, (uchar) m_ui->pshBut_load->isChecked(), (uchar) i);}
    void on_spnBox_AMS_valueChanged(int i)
        {EXPANDEUR::ChangerVoicex0D(InstSel, (uchar) m_ui->spnBox_PMS->value(), (uchar) i);}
    void on_spnBox_PMD_valueChanged(int i)
        {EXPANDEUR::ChangerVoicex0A(InstSel, (uchar) m_ui->pshBut_load->isChecked(), (uchar) i);}
    void on_spnBox_PMS_valueChanged(int i)
        {EXPANDEUR::ChangerVoicex0D(InstSel, (uchar) i, (uchar) m_ui->spnBox_AMS->value());}
    void on_spnBox_algo_valueChanged(int i);
};

#endif // QVOICE_H
