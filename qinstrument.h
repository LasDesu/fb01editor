#ifndef QINSTRUMENT_H
#define QINSTRUMENT_H

/*****************************************************************************/
    #include "ui_qinstrument.h"
    #include <QFile>

/*****************************************************************************/
    #include "expandeur.h"

/*****************************************************************************/
    #define LNGINST 15

/*****************************************************************************/
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
        void  ChangerID(const uchar ID);
        uchar RecupererID();
    //Chargement/enregistrement
        bool Enregistrer(QFile * Fichier);
        bool Charger(QFile * Fichier, const int Version);
    //Communication
        void Envoyer();
        void Recevoir();
    //Interface et édition
        void Initialiser();
        void Randomiser();
        void Copier(uchar * Table);
        void Coller(const uchar * Table);
        void Echanger(QInstrument * Inst);
    protected:
    //Interne
        void changeEvent(QEvent *e);
    private:
    //Interface
        Ui::QInstrument *m_ui;
        bool  Attente;
        uchar IDSel;
    //Utilitaires
        void InitialiserNotes(QComboBox * Box);
    private slots:
    //Gestion des évènements
        void on_spnBox_notes_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x00, (uchar) i);}
        void on_spnBox_chan_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x01, (uchar) (i - 1));}
        void on_cmbBox_upper_activated(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x02, (uchar) i);}
        void on_cmbBox_lower_activated(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x03, (uchar) i);}
        void on_spnBox_bank_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x04, (uchar) i);}
        void on_spnBox_voice_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x05, (uchar) i);}
        void on_spnBox_detune_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x06, (uchar) i);}
        void on_cmbBox_trans_activated(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x07, (uchar) i);}
        void on_hzSlider_volume_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x08, (uchar) i);}
        void on_hzSlider_pan_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x09, (uchar) i);}
        void on_pshBut_LFO_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x0A, !checked);}
        void on_pshBut_poly_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x0D, !checked);}
        void on_spnBox_porta_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x0B, (uchar) i);}
        void on_spnBox_pitch_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x0C, (uchar) i);}
        void on_cmbBox_pmdctl_activated(int i)
            {if (!Attente) EXPANDEUR::EcrireInstParam(IDSel, 0x0E, (uchar) i);}
    };

#endif // QINSTRUMENT_H
