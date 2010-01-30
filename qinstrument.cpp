#include "qinstrument.h"

/*****************************************************************************/
QInstrument::QInstrument(QWidget *parent) : QWidget(parent), m_ui(new Ui::QInstrument)
{
    Attente = false;
    m_ui->setupUi(this);
 //Initialise les controles
    ChangerID(0);
    InitialiserNotes(m_ui->cmbBox_upper);
    InitialiserNotes(m_ui->cmbBox_lower);
}

QInstrument::~QInstrument()
{
    delete m_ui;
}

/*****************************************************************************/
void QInstrument::ChangerID(uchar ID)
{
//Prépare le nom
    QString nom = "Instrument ";
    QString num; num.setNum(ID + 1);
    nom.append(num);
//Renomme l'instrument
    m_ui->grpBox_instru->setTitle(nom);
    IDSel = ID;
}

uchar QInstrument::RecupererID()
{
    return IDSel;
}

/*****************************************************************************/
const char Notes[12][3] = {"C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};
void QInstrument::InitialiserNotes(QComboBox * Box)
{
//Construit la liste de notes
    Box->clear();
    for (int n = 0; n < 128; n ++)
    {
    //Créé le nom de la note
        QString Num; Num.setNum(n / 12 - 2);
        QString Item = Notes[n % 12];
        Item.append(" "); Item.append(Num);
    //Ajoute à la liste
        Box->addItem(Item, 0);
    }
}

/*****************************************************************************/
bool QInstrument::Charger(QFile * Fichier, int Version)
{
    uchar Table[16];
//Vérrouille l'interface
    Attente = true;
//Charge les données
    Fichier->read((char *)Table, 15);
    if (Fichier->error()) return true;
    Coller(Table);
//Déverrouille
    Attente = false;
    return false;
}

bool QInstrument::Enregistrer(QFile * Fichier)
{
    uchar Table[16];
//Enregistre les données
    Copier(Table);
    Fichier->write((char *) Table, 15);
//Vérifie les erreurs
    if (Fichier->error()) return true;
    return false;
}

/*****************************************************************************/
void QInstrument::Envoyer()
{
//Envoie la configuration complète
    EXPANDEUR::EcrireInstParam(IDSel, 0x00, (uchar) m_ui->spnBox_notes->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x01, (uchar) (m_ui->spnBox_chan->value() - 1));
    EXPANDEUR::EcrireInstParam(IDSel, 0x02, (uchar) m_ui->cmbBox_upper->currentIndex());
    EXPANDEUR::EcrireInstParam(IDSel, 0x03, (uchar) m_ui->cmbBox_lower->currentIndex());
    EXPANDEUR::EcrireInstParam(IDSel, 0x04, (uchar) m_ui->spnBox_bank->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x05, (uchar) m_ui->spnBox_voice->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x06, (uchar) m_ui->spnBox_detune->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x07, (uchar) m_ui->cmbBox_trans->currentIndex());
    EXPANDEUR::EcrireInstParam(IDSel, 0x08, (uchar) m_ui->hzSlider_volume->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x09, (uchar) m_ui->hzSlider_pan->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0A, (uchar) ! m_ui->pshBut_LFO->isChecked());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0B, (uchar) m_ui->spnBox_porta->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0C, (uchar) m_ui->spnBox_pitch->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0D, (uchar) ! m_ui->pshBut_poly->isChecked());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0E, (uchar) m_ui->cmbBox_pmdctl->currentIndex());
}

void QInstrument::Recevoir()
{
//Vérouille l'interface
    Attente = true;
//Interprète les données
    m_ui->spnBox_notes->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x00));
    m_ui->spnBox_chan->setValue((int) (EXPANDEUR::LireInstParam(IDSel, 0x01) + 1));
    m_ui->cmbBox_upper->setCurrentIndex((int) EXPANDEUR::LireInstParam(IDSel, 0x02));
    m_ui->cmbBox_lower->setCurrentIndex((int) EXPANDEUR::LireInstParam(IDSel, 0x03));
    m_ui->spnBox_bank->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x04));
    m_ui->spnBox_voice->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x05));
    m_ui->spnBox_detune->setValue((int)(char)(EXPANDEUR::LireInstx06(IDSel)));
    m_ui->cmbBox_trans->setCurrentIndex((int) EXPANDEUR::LireInstParam(IDSel, 0x07));
    m_ui->hzSlider_volume->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x08));
    m_ui->hzSlider_pan->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x09));
    m_ui->pshBut_LFO->setChecked(! (bool) EXPANDEUR::LireInstParam(IDSel, 0x0A));
    m_ui->spnBox_porta->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x0B));
    m_ui->spnBox_pitch->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x0C));
    m_ui->pshBut_poly->setChecked(! (bool)EXPANDEUR::LireInstParam(IDSel, 0x0D));
    m_ui->cmbBox_pmdctl->setCurrentIndex(EXPANDEUR::LireInstParam(IDSel, 0x0E));
//Déverrouille
    Attente = false;
}

/*****************************************************************************/
const uchar InitTab[16] = {1, 0, 127, 0, 2, 0, 0, 2, 127, 63, 0, 0, 4, 1, 1, 0};
void QInstrument::Initialiser()
{
    Coller(InitTab);
}

void QInstrument::Randomiser()
{
//Vérrouille l'interface
    Attente = true;
//Initialise aléatoirement
    m_ui->spnBox_notes->setValue(RAND(0, 8));
    m_ui->spnBox_chan->setValue(RAND(0, 15));
    m_ui->cmbBox_upper->setCurrentIndex(RAND(0, 127));
    m_ui->cmbBox_lower->setCurrentIndex(RAND(0, 127));
    m_ui->spnBox_bank->setValue(RAND(0, 6));
    m_ui->spnBox_voice->setValue(RAND(0, 47));
    m_ui->spnBox_detune->setValue(RAND(-64, 63));
    m_ui->cmbBox_trans->setCurrentIndex(RAND(0, 4));
    m_ui->hzSlider_volume->setValue(RAND(0, 127));
    m_ui->hzSlider_pan->setValue(RAND(0, 127));
    m_ui->pshBut_LFO->setChecked(RAND(0, 1));
    m_ui->spnBox_porta->setValue(RAND(0, 127));
    m_ui->spnBox_pitch->setValue(RAND(0, 12));
    m_ui->pshBut_poly->setChecked(RAND(0, 1));
    m_ui->cmbBox_pmdctl->setCurrentIndex(RAND(0, 4));
//Actualise l'interface
    Attente = false;
    Envoyer();
}

/*****************************************************************************/
void QInstrument::Copier(uchar Table[16])
{
//Copie les données
    Table[0]  = (uchar) m_ui->spnBox_notes->value();
    Table[1]  = (uchar) m_ui->spnBox_chan->value();
    Table[2]  = (uchar) m_ui->cmbBox_upper->currentIndex();
    Table[3]  = (uchar) m_ui->cmbBox_lower->currentIndex();
    Table[4]  = (uchar) m_ui->spnBox_bank->value();
    Table[5]  = (uchar) m_ui->spnBox_voice->value();
    Table[6]  = (uchar) m_ui->spnBox_detune->value();
    Table[7]  = (uchar) m_ui->cmbBox_trans->currentIndex();
    Table[8]  = (uchar) m_ui->hzSlider_volume->value();
    Table[9]  = (uchar) m_ui->hzSlider_pan->value();
    Table[10] = (uchar) m_ui->pshBut_LFO->isChecked();
    Table[11] = (uchar) m_ui->spnBox_porta->value();
    Table[12] = (uchar) m_ui->spnBox_pitch->value();
    Table[13] = (uchar) m_ui->pshBut_poly->isChecked();
    Table[14] = (uchar) m_ui->cmbBox_pmdctl->currentIndex();
}

void QInstrument::Coller(const uchar Table[16])
{
//Vérrouille l'interface
    Attente = true;
 //Colle les données
    m_ui->spnBox_notes->setValue((int)Table[0]);
    m_ui->spnBox_chan->setValue((int)Table[1]);
    m_ui->cmbBox_upper->setCurrentIndex((int)Table[2]);
    m_ui->cmbBox_lower->setCurrentIndex((int)Table[3]);
    m_ui->spnBox_bank->setValue((int)Table[4]);
    m_ui->spnBox_voice->setValue((int)Table[5]);
    m_ui->spnBox_detune->setValue((int)Table[6]);
    m_ui->cmbBox_trans->setCurrentIndex((int)Table[7]);
    m_ui->hzSlider_volume->setValue((int)Table[8]);
    m_ui->hzSlider_pan->setValue((int)Table[9]);
    m_ui->pshBut_LFO->setChecked((bool)Table[10]);
    m_ui->spnBox_porta->setValue((int)Table[11]);
    m_ui->spnBox_pitch->setValue((int)Table[12]);
    m_ui->pshBut_poly->setChecked((bool)Table[13]);
    m_ui->cmbBox_pmdctl->setCurrentIndex((int)Table[14]);
 //Actualise l'interface
    Attente = false;
    Envoyer();
 }

/*****************************************************************************/
void QInstrument::changeEvent(QEvent *e)
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
