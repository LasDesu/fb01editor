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
void QOperateur::ChangerInst(const uchar Inst)
{
    InstSel = Inst;
}

uchar QOperateur::RecupererInst()
{
    return InstSel;
}

/*****************************************************************************/
bool QOperateur::Charger(QFile * Fichier, const int Version)
{
    uchar Table[16];
//Vérrouille l'interface
    Attente = true;
//Charge les données
    Fichier->read((char *) Table, LNGOP);
    if (Fichier->error()) return true;
    Coller(Table);
//Déverrouille
    Attente = false;
    return false;
}

bool QOperateur::Enregistrer(QFile * Fichier)
{
    uchar Table[16];
//Enregistre les données
    Copier(Table);
    Fichier->write((char *) Table, LNGOP);
//Vérifie les erreurs
    if (Fichier->error()) return true;
    return false;
}

/*****************************************************************************/
void QOperateur::Rafraichir()
{
    m_ui->label_env->DefinirEnveloppe(m_ui->spnBox_AR->value(), m_ui->spnBox_D1R->value(), m_ui->spnBox_SL->value(),m_ui->spnBox_D2R->value(), m_ui->spnBox_RR->value());
    m_ui->label_env->repaint();
}

/*****************************************************************************/
void QOperateur::Envoyer()
{
//Envoie la configuration complète
    EXPANDEUR::EcrireOpParam(InstSel, IDSel, 0x00, (uchar) (127 - m_ui->hzSlider_volume->value()));
    EXPANDEUR::EcrireOpx01(InstSel, IDSel, (uchar) m_ui->cmbBox_lvlcurb->currentIndex(), (uchar) m_ui->spnBox_vellvl->value());
    EXPANDEUR::EcrireOpx02(InstSel, IDSel, (uchar) m_ui->spnBox_lvldph->value(), (uchar) m_ui->spnBox_adjTL->value());
    EXPANDEUR::EcrireOpx03(InstSel, IDSel, (uchar) m_ui->cmbBox_lvlcurb->currentIndex(), (uchar) (m_ui->spnBox_fine->value() + 4), (uchar) m_ui->spnBox_multiple->value());
    EXPANDEUR::EcrireOpx04(InstSel, IDSel, (uchar) m_ui->spnBox_rtdph->value(), (uchar) m_ui->spnBox_AR->value());
    EXPANDEUR::EcrireOpx05(InstSel, IDSel, (uchar) m_ui->pshBut_carrier->isChecked(), (uchar) m_ui->spnBox_velAR->value(), (uchar) m_ui->spnBox_D1R->value());
    EXPANDEUR::EcrireOpx06(InstSel, IDSel, (uchar) m_ui->spnBox_coarse->value(), (uchar) m_ui->spnBox_D2R->value());
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
    m_ui->spnBox_vellvl->setValue((int) p2);
    EXPANDEUR::LireOpx02(IDSel, &p1, &p2);
    m_ui->spnBox_lvldph->setValue((int) p1); m_ui->spnBox_adjTL->setValue((int) p2);
    EXPANDEUR::LireOpx03(IDSel, &st2, &p1, &p2);
    m_ui->cmbBox_lvlcurb->setCurrentIndex((int)st1 + st2);
    m_ui->spnBox_fine->setValue((int) (p1 - 4));
    m_ui->spnBox_multiple->setValue((int) p2);
    EXPANDEUR::LireOpx04(IDSel, &p1, &p2);
    m_ui->spnBox_rtdph->setValue((int) p1);
    m_ui->spnBox_AR->setValue((int) p2);
    EXPANDEUR::LireOpx05(IDSel, &b1, &p1, &p2);
    m_ui->pshBut_carrier->setChecked(b1);
    m_ui->spnBox_velAR->setValue((int) p1);
    m_ui->spnBox_D1R->setValue((int) p2);
    EXPANDEUR::LireOpx06(IDSel, &p1, &p2);
    m_ui->spnBox_coarse->setValue((int) p1); m_ui->spnBox_D2R->setValue((int) p2);
    EXPANDEUR::LireOpx07(IDSel, &p1, &p2);
    m_ui->spnBox_SL->setValue((int) (15 - p1)); m_ui->spnBox_RR->setValue((int) p2);
 //Déverrouille
    Attente = false;
}

/*****************************************************************************/
const uchar InitTab[LNGOP] = {127, 0, 0, 0, 0, 0, 0, 0, 31, 1, 0, 31, 0, 0, 15, 15};
void QOperateur::Initialiser()
{
    Coller(InitTab);
}

void QOperateur::Randomiser()
{
//Vérrouille l'interface
    Attente = true;
//Initialise avec des données aléatoires
    m_ui->hzSlider_volume->setValue(RAND(95, 127));
    m_ui->cmbBox_lvlcurb->setCurrentIndex(RAND(0, 3));
    m_ui->spnBox_vellvl->setValue(RAND(0, 31));
    m_ui->spnBox_lvldph->setValue(RAND(0, 15));
    m_ui->spnBox_adjTL->setValue(RAND(0, 15));
    m_ui->spnBox_fine->setValue(RAND(-4, 3));
    m_ui->spnBox_multiple->setValue(RAND(0, 15));
    m_ui->spnBox_rtdph->setValue(0);
    m_ui->spnBox_AR->setValue(31);
    m_ui->pshBut_carrier->setChecked((bool) RAND(0, 1));
    m_ui->spnBox_velAR->setValue(RAND(0, 3));
    m_ui->spnBox_D1R->setValue(RAND(0, 31));
    m_ui->spnBox_coarse->setValue(RAND(0, 3));
    m_ui->spnBox_D2R->setValue(RAND(0, 31));
    m_ui->spnBox_SL->setValue(RAND(0, 15));
    m_ui->spnBox_RR->setValue(RAND(0, 15));
//Actualise l'interface
    Rafraichir();
    Envoyer();
//Déverrouille
    Attente = false;
}

/*****************************************************************************/
void QOperateur::Echanger(QOperateur * Op)
{
    uchar Table1[LNGOP];
    uchar Table2[LNGOP];
//Echange les opérateurs
    Op->Copier(Table1);
    this->Copier(Table2);
    this->Coller(Table1);
    Op->Coller(Table2);
}

/*****************************************************************************/
void QOperateur::Copier(uchar * Table)
{
//Copie les données
    Table[0]  = (uchar) m_ui->hzSlider_volume->value();
    Table[1]  = (uchar) m_ui->cmbBox_lvlcurb->currentIndex();
    Table[2]  = (uchar) m_ui->spnBox_vellvl->value();
    Table[3]  = (uchar) m_ui->spnBox_lvldph->value();
    Table[4]  = (uchar) m_ui->spnBox_adjTL->value();
    Table[5]  = (uchar) m_ui->spnBox_fine->value();
    Table[6]  = (uchar) m_ui->spnBox_multiple->value();
    Table[7]  = (uchar) m_ui->spnBox_rtdph->value();
    Table[8]  = (uchar) m_ui->spnBox_AR->value();
    Table[9]  = (uchar) m_ui->pshBut_carrier->isChecked();
    Table[10] = (uchar) m_ui->spnBox_velAR->value();
    Table[11] = (uchar) m_ui->spnBox_D1R->value();
    Table[12] = (uchar) m_ui->spnBox_coarse->value();
    Table[13] = (uchar) m_ui->spnBox_D2R->value();
    Table[14] = (uchar) m_ui->spnBox_SL->value();
    Table[15] = (uchar) m_ui->spnBox_RR->value();
 }

void QOperateur::Coller(const uchar * Table)
{
//Vérrouille l'interface
    Attente = true;
 //Colle les données
    m_ui->hzSlider_volume->setValue((int)Table[0]);
    m_ui->cmbBox_lvlcurb->setCurrentIndex((int)Table[1]);
    m_ui->spnBox_vellvl->setValue((int)Table[2]);
    m_ui->spnBox_lvldph->setValue((int)Table[3]);
    m_ui->spnBox_adjTL->setValue((int)Table[4]);
    m_ui->spnBox_fine->setValue((int)Table[5]);
    m_ui->spnBox_multiple->setValue((int)Table[6]);
    m_ui->spnBox_rtdph->setValue((int)Table[7]);
    m_ui->spnBox_AR->setValue((int)Table[8]);
    m_ui->pshBut_carrier->setChecked((bool)Table[9]);
    m_ui->spnBox_velAR->setValue((int)Table[10]);
    m_ui->spnBox_D1R->setValue((int)Table[11]);
    m_ui->spnBox_coarse->setValue((int)Table[12]);
    m_ui->spnBox_D2R->setValue((int)Table[13]);
    m_ui->spnBox_SL->setValue((int)Table[14]);
    m_ui->spnBox_RR->setValue((int)Table[15]);
 //Actualise l'interface
    Rafraichir();
    Envoyer();
 //Déverrouille
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
