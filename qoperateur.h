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

#ifndef QOPERATEUR_H
#define QOPERATEUR_H

/*****************************************************************************/
    #include "ui_qoperateur.h"
    #include <QFile>

/*****************************************************************************/
    #include "expandeur.h"

/*****************************************************************************/
    #define LNGOP 16

/*****************************************************************************/
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
        void  ChangerID(const uchar ID);
        uchar RecupererID();
        void  ChangerInst(const uchar Inst);
        uchar RecupererInst();
    //Chargement/enregistrement
        bool Enregistrer(QFile * Fichier);
        bool Charger(QFile * Fichier, const int Version);
    //Interface et édition
        void Initialiser();
        void Randomiser();
        void Copier(uchar * Table);
        void Coller(const uchar * Table);
        void Echanger(QOperateur * Op);
        void Rafraichir();
    //Communication
        void Envoyer();
        void Recevoir();
    protected:
    //Interne
        void changeEvent(QEvent *e);
    private:
    //Interface
        Ui::QOperateur *m_ui;
        bool  Attente;
        uchar IDSel;
        uchar InstSel;
    private slots:
    //Gestion des évènements
        void on_hzSlider_volume_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpParam(InstSel, IDSel, 0x00, (uchar) (127 - i));}
        void on_spnBox_vellvl_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpx01(InstSel, IDSel, (uchar) m_ui->cmbBox_lvlcurb->currentIndex(), (uchar) i);}
        void on_spnBox_velAR_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpx05(InstSel, IDSel, m_ui->pshBut_carrier->isChecked(), (uchar) i, (uchar) m_ui->spnBox_D1R->value());}
        void on_spnBox_AR_valueChanged(int i)
            {if (!Attente){
                EXPANDEUR::EcrireOpx04(InstSel, IDSel, (uchar) m_ui->spnBox_rtdph->value(), (uchar) i);
                Rafraichir();}}
        void on_spnBox_D1R_valueChanged(int i)
            {if (!Attente){
                EXPANDEUR::EcrireOpx05(InstSel, IDSel, m_ui->pshBut_carrier->isChecked(), (uchar) m_ui->spnBox_velAR->value(), (uchar) i);
                Rafraichir();}}
        void on_spnBox_SL_valueChanged(int i)
            {if (!Attente){
                EXPANDEUR::EcrireOpx07(InstSel, IDSel, (uchar) (15 - i), (uchar) m_ui->spnBox_RR->value());
                Rafraichir();}}
        void on_spnBox_D2R_valueChanged(int i)
            {if (!Attente){
                EXPANDEUR::EcrireOpx06(InstSel, IDSel, (uchar) m_ui->spnBox_coarse->value(), (uchar) i);
                Rafraichir();}}
        void on_spnBox_RR_valueChanged(int i)
            {if (!Attente){
                EXPANDEUR::EcrireOpx07(InstSel, IDSel, (uchar) (15 - m_ui->spnBox_SL->value()), (uchar) i);
                Rafraichir();}}
        void on_pshBut_carrier_clicked(bool checked)
            {if (!Attente) EXPANDEUR::EcrireOpx05(InstSel, IDSel, !checked, (uchar) m_ui->spnBox_velAR->value(), (uchar) m_ui->spnBox_D1R->value());}
        void on_spnBox_coarse_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpx06(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_D2R->value());}
        void on_spnBox_fine_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpx03(InstSel, IDSel, (uchar) m_ui->cmbBox_lvlcurb->currentIndex(), (uchar) (i + 4), (uchar) m_ui->spnBox_multiple->value());}
        void on_spnBox_multiple_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpx03(InstSel, IDSel, (uchar) m_ui->cmbBox_lvlcurb->currentIndex(), (uchar) (m_ui->spnBox_fine->value() + 4), (uchar) i);}
        void on_cmbBox_lvlcurb_activated(int i)
            {if (!Attente) {
                EXPANDEUR::EcrireOpx01(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_vellvl->value());
                EXPANDEUR::EcrireOpx03(InstSel, IDSel, (uchar) i, (uchar) (m_ui->spnBox_fine->value() + 4), (uchar) m_ui->spnBox_multiple->value());}}
        void on_spnBox_lvldph_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpx02(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_adjTL->value());}
        void on_spnBox_rtdph_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpx04(InstSel, IDSel, (uchar) i, (uchar) m_ui->spnBox_AR->value());}
        void on_spnBox_adjTL_valueChanged(int i)
            {if (!Attente) EXPANDEUR::EcrireOpx02(InstSel, IDSel, (uchar) m_ui->spnBox_lvldph->value(), (uchar) i);}
    };

#endif // QOPERATEUR_H
