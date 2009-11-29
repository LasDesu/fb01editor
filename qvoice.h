#ifndef QVOICE_H
#define QVOICE_H

#include <QFile>
#include "ui_qvoice.h"
#include "expandeur.h"

//Constantes
    #define INFOS 129

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
        bool Enregistrer(QFile * Fichier);
        bool Charger(QFile * Fichier, int Version);
    //Communication
        void Envoyer();
        void Recevoir();
    protected:
        void changeEvent(QEvent *e);
    private:
    //Configuration
        uchar InstSel;
        bool  Attente;
    //Interface
        Ui::QVoice *m_ui;
    private slots:
    //Gestion des évènements
        void on_txtEdit_voicename_textChanged()
            {if (!Attente) EXPANDEUR::EcrireVoiceNom(InstSel, m_ui->txtEdit_voicename->toPlainText().toAscii().constData());}
        void on_cmbBox_style_activated(int i)
            {if (!Attente) EXPANDEUR::EcrireVoiceParam(InstSel, 0x07, (uchar) i);}
        void on_spnBox_feedback_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex0C(InstSel, (uchar) i, (uchar) (m_ui->spnBox_algo->value() - 1));}
        void on_spnBox_trans_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoiceParam(InstSel, 0x0F, (uchar) i);}
        void on_pshBut_poly_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireVoicex3A(InstSel, !checked, (uchar) m_ui->spnBox_porta->value());}
        void on_spnBox_porta_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex3A(InstSel, m_ui->pshBut_poly->isChecked(), (uchar) i);}
        void on_spnBox_pitch_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex3B(InstSel, (uchar) m_ui->cmbBox_pmdctl->currentIndex(), (uchar) i);}
        void on_cmbBox_pmdctl_activated(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex3B(InstSel, (uchar) i, (uchar) m_ui->spnBox_pitch->value());}
        void on_spnBox_LFOspeed_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoiceParam(InstSel, 0x08, (uchar) i);}
        void on_cmbBox_LFOwave_activated(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex0E(InstSel, (uchar) i);}
        void on_pshBut_LFOload_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireVoicex09(InstSel, !checked, (uchar) m_ui->spnBox_AMD->value());}
        void on_pshBut_LFOsync_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireVoicex0A(InstSel, !checked, (uchar) m_ui->spnBox_PMD->value());}
        void on_spnBox_AMD_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex09(InstSel, m_ui->pshBut_LFOload->isChecked(), (uchar) i);}
        void on_spnBox_AMS_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex0D(InstSel, m_ui->spnBox_PMS->value(), (uchar) i);}
        void on_spnBox_PMD_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex0A(InstSel, m_ui->pshBut_LFOsync->isChecked(), (uchar) i);}
        void on_spnBox_PMS_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireVoicex0D(InstSel, (uchar) i, (uchar) m_ui->spnBox_AMS->value());}
        void on_spnBox_algo_valueChanged(int i);
    };

#endif // QVOICE_H
