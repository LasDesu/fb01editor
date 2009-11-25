#include "qoperateur.h"

/*****************************************************************************/
QOperateur::QOperateur(QWidget *parent) : QWidget(parent), m_ui(new Ui::QOperateur)
{
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
bool QOperateur::Enregistrer(QFile * File)
{
    char Octet;
//Ecrit chaque donnée
    Octet = (char) m_ui->hzSlider_volume->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_kbcurb->currentIndex();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_velocity->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_lvldph->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_adjTL->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_fine->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_multiple->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_rtdph->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_AR->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_carrier->isChecked();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_velmod->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_DR1->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_coarse->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_DR2->value();
    File->write(&Octet, 1);
    Octet = (uchar) m_ui->spnBox_SL->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_RR->value();
    File->write(&Octet, 1);
//Vérifie les erreurs
    if (File->error()) return true;
    return false;
}

bool QOperateur::Charger(QFile * File)
{
    char Octet;
//Lit chaque donnée
    File->read(&Octet, 1);
    m_ui->hzSlider_volume->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->cmbBox_kbcurb->setCurrentIndex((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_velocity->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_lvldph->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_adjTL->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_fine->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_multiple->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_rtdph->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_AR->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->pshBut_carrier->isChecked();
    File->read(&Octet, 1);
    m_ui->spnBox_velmod->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_DR1->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_coarse->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_DR2->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_SL->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_RR->setValue((int)Octet);
//Vérifie les erreurs
    if (File->error()) return true;
    return false;
}

/*****************************************************************************/
void QOperateur::Envoyer()
{
//Envoie la configuration complète
    EXPANDEUR::EcrireOpParam(InstSel, IDSel, 0x00, (uchar) (127 - m_ui->hzSlider_volume->value()));
    EXPANDEUR::ChangerOpx01(InstSel, IDSel, (uchar) m_ui->cmbBox_kbcurb->currentIndex(), (uchar) m_ui->spnBox_velocity->value());
    EXPANDEUR::ChangerOpx02(InstSel, IDSel, (uchar) m_ui->spnBox_lvldph->value(), (uchar) m_ui->spnBox_adjTL->value());
    EXPANDEUR::ChangerOpx03(InstSel, IDSel, (uchar) m_ui->cmbBox_kbcurb->currentIndex(), (uchar) m_ui->spnBox_fine->value(), (uchar) m_ui->spnBox_multiple->value());
    EXPANDEUR::ChangerOpx04(InstSel, IDSel, (uchar) m_ui->spnBox_rtdph->value(), (uchar) m_ui->spnBox_AR->value());
    EXPANDEUR::ChangerOpx05(InstSel, IDSel, (uchar) m_ui->pshBut_carrier->isChecked(), (uchar) m_ui->spnBox_velmod->value(), (uchar) m_ui->spnBox_DR1->value());
    EXPANDEUR::ChangerOpx06(InstSel, IDSel, (uchar) m_ui->spnBox_coarse->value(), (uchar) m_ui->spnBox_DR2->value());
    EXPANDEUR::ChangerOpx07(InstSel, IDSel, (uchar) (15 - m_ui->spnBox_SL->value()), (uchar) m_ui->spnBox_RR->value());
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
