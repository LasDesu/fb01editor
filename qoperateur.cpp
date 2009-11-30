#include "qoperateur.h"

/*****************************************************************************/
QOperateur::QOperateur(QWidget *parent) : QWidget(parent), m_ui(new Ui::QOperateur)
{
    Attente = false;
    m_ui->setupUi(this);
    ChangerID(0);
    ChangerInst(0);
}

QOperateur::~QOperateur()
{
    delete m_ui;
}

/*****************************************************************************/
void QOperateur::ChangerID(uchar ID)
{
//Prépare le nom
    QString nom = "Operator ";
    QString num; num.setNum(ID + 1);
    nom.append(num);
//Renomme l'instrument
    m_ui->grpBox_opera->setTitle(nom);
    IDSel = ID;
}

uchar QOperateur::RecupererID()
{
    return IDSel;
}

/*****************************************************************************/
void QOperateur::ChangerInst(uchar Inst)
{
    InstSel = Inst;
}

uchar QOperateur::RecupererInst()
{
    return InstSel;
}

/*****************************************************************************/
void QOperateur::Rafraichir()
{
    m_ui->label_env->DefinirEnveloppe(m_ui->spnBox_AR->value(), m_ui->spnBox_DR1->value(), m_ui->spnBox_SL->value(),m_ui->spnBox_DR2->value(), m_ui->spnBox_RR->value());
    m_ui->label_env->repaint();
}

/*****************************************************************************/
bool QOperateur::Enregistrer(QFile * Fichier)
{
    char Octet;
//Ecrit chaque donnée
    Octet = (char) m_ui->hzSlider_volume->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_kbcurb->currentIndex();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_velocity->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_lvldph->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_adjTL->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_fine->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_multiple->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_rtdph->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_AR->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_carrier->isChecked();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_velmod->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_DR1->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_coarse->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_DR2->value();
    Fichier->write(&Octet, 1);
    Octet = (uchar) m_ui->spnBox_SL->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_RR->value();
    Fichier->write(&Octet, 1);
//Vérifie les erreurs
    if (Fichier->error()) return true;
    return false;
}

bool QOperateur::Charger(QFile * Fichier, int Version)
{
    char Octet;
//Vérouille l'interface
    Attente = true;
//Lit chaque donnée
    Fichier->read(&Octet, 1);
    m_ui->hzSlider_volume->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->cmbBox_kbcurb->setCurrentIndex((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_velocity->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_lvldph->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_adjTL->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_fine->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_multiple->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_rtdph->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_AR->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->pshBut_carrier->setChecked((bool)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_velmod->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_DR1->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_coarse->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_DR2->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_SL->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_RR->setValue((int)Octet);
//Vérifie les erreurs
    Attente = false;
    if (Fichier->error()) return true;
//Envoie les données
    Envoyer();
    return false;
}

/*****************************************************************************/
void QOperateur::Envoyer()
{
//Envoie la configuration complète
    EXPANDEUR::EcrireOpParam(InstSel, IDSel, 0x00, (uchar) (127 - m_ui->hzSlider_volume->value()));
    EXPANDEUR::EcrireOpx01(InstSel, IDSel, (uchar) m_ui->cmbBox_kbcurb->currentIndex(), (uchar) m_ui->spnBox_velocity->value());
    EXPANDEUR::EcrireOpx02(InstSel, IDSel, (uchar) m_ui->spnBox_lvldph->value(), (uchar) m_ui->spnBox_adjTL->value());
    EXPANDEUR::EcrireOpx03(InstSel, IDSel, (uchar) m_ui->cmbBox_kbcurb->currentIndex(), (uchar) m_ui->spnBox_fine->value(), (uchar) m_ui->spnBox_multiple->value());
    EXPANDEUR::EcrireOpx04(InstSel, IDSel, (uchar) m_ui->spnBox_rtdph->value(), (uchar) m_ui->spnBox_AR->value());
    EXPANDEUR::EcrireOpx05(InstSel, IDSel, (uchar) m_ui->pshBut_carrier->isChecked(), (uchar) m_ui->spnBox_velmod->value(), (uchar) m_ui->spnBox_DR1->value());
    EXPANDEUR::EcrireOpx06(InstSel, IDSel, (uchar) m_ui->spnBox_coarse->value(), (uchar) m_ui->spnBox_DR2->value());
    EXPANDEUR::EcrireOpx07(InstSel, IDSel, (uchar) (15 - m_ui->spnBox_SL->value()), (uchar) m_ui->spnBox_RR->value());
}

void QOperateur::Recevoir()
{
    uchar st1, st2;
    uchar p1, p2;
    bool  b1;
//Vérouille l'interface
    Attente = true;
//Interprète les données
    m_ui->hzSlider_volume->setValue((int) (127 - EXPANDEUR::LireOpParam(IDSel, 0x00)));
    EXPANDEUR::LireOpx01(IDSel, &st1, &p2);
    m_ui->spnBox_velocity->setValue((int) p2);
    EXPANDEUR::LireOpx02(IDSel, &p1, &p2);
    m_ui->spnBox_lvldph->setValue((int) p1); m_ui->spnBox_adjTL->setValue((int) p2);
    EXPANDEUR::LireOpx03(IDSel, &st2, &p1, &p2);
    m_ui->cmbBox_kbcurb->setCurrentIndex((int)st1 + st2);
    m_ui->spnBox_fine->setValue((int) p1);
    m_ui->spnBox_multiple->setValue((int) p2);
    EXPANDEUR::LireOpx04(IDSel, &p1, &p2);
    m_ui->spnBox_rtdph->setValue((int) p1);
    m_ui->spnBox_AR->setValue((int) p2);
    EXPANDEUR::LireOpx05(IDSel, &b1, &p1, &p2);
    m_ui->pshBut_carrier->setChecked(b1);
    m_ui->spnBox_velmod->setValue((int) p1);
    m_ui->spnBox_DR1->setValue((int) p2);
    EXPANDEUR::LireOpx06(IDSel, &p1, &p2);
    m_ui->spnBox_coarse->setValue((int) p1); m_ui->spnBox_DR2->setValue((int) p2);
    EXPANDEUR::LireOpx07(IDSel, &p1, &p2);
    m_ui->spnBox_SL->setValue((int) (15 - p1)); m_ui->spnBox_RR->setValue((int) p2);
 //Déverouille
    Attente = false;
}

/*****************************************************************************/
void QOperateur::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
