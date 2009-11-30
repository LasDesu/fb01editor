#include "qinstrument.h"

/*****************************************************************************/
QInstrument::QInstrument(QWidget *parent) :  QWidget(parent), m_ui(new Ui::QInstrument)
{
    Attente = false;
    m_ui->setupUi(this);
    ChangerID(0);
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
bool QInstrument::Enregistrer(QFile * Fichier)
{
    char Octet;
//Ecrit chaque donnée
    Octet = (char) m_ui->spnBox_notes->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_chan->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_upper->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_lower->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_bank->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_voice->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_detune->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_trans->currentIndex();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->hzSlider_volume->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->hzSlider_pan->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_LFO->isChecked();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_porta->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_pitch->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_poly->isChecked();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_pmdctl->currentIndex();
    Fichier->write(&Octet, 1);
//Vérifie les erreurs
    if (Fichier->error()) return true;
    return false;
}

bool QInstrument::Charger(QFile * Fichier, int Version)
{
    char Octet;
//Vérouille l'interface
    Attente = true;
//Lit chaque donnée
    Fichier->read(&Octet, 1);
    m_ui->spnBox_notes->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_chan->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_upper->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_lower->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_bank->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_voice->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_detune->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->cmbBox_trans->setCurrentIndex((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->hzSlider_volume->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->hzSlider_pan->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->pshBut_LFO->setChecked((bool)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_porta->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_pitch->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->pshBut_poly->setChecked((bool)Octet);
    Fichier->read(&Octet, 1);
    m_ui->cmbBox_pmdctl->setCurrentIndex((int)Octet);
//Vérifie les erreurs
    Attente = false;
    if (Fichier->error()) return true;
//Envoie les données
    Envoyer();
    return false;
}

/*****************************************************************************/
void QInstrument::Envoyer()
{
//Envoie la configuration complète
    EXPANDEUR::EcrireInstParam(IDSel, 0x00, (uchar) m_ui->spnBox_notes->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x01, (uchar) (m_ui->spnBox_chan->value() - 1));
    EXPANDEUR::EcrireInstParam(IDSel, 0x02, (uchar) m_ui->spnBox_upper->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x03, (uchar) m_ui->spnBox_lower->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x04, (uchar) m_ui->spnBox_bank->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x05, (uchar) m_ui->spnBox_voice->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x06, (uchar) m_ui->spnBox_detune->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x07, (uchar) m_ui->cmbBox_trans->currentIndex());
    EXPANDEUR::EcrireInstParam(IDSel, 0x08, (uchar) m_ui->hzSlider_volume->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x09, (uchar) m_ui->hzSlider_pan->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0A, (uchar) m_ui->pshBut_LFO->isChecked());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0B, (uchar) m_ui->spnBox_porta->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0C, (uchar) m_ui->spnBox_pitch->value());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0D, (uchar) m_ui->pshBut_poly->isChecked());
    EXPANDEUR::EcrireInstParam(IDSel, 0x0E, (uchar) m_ui->cmbBox_pmdctl->currentIndex());
}

void QInstrument::Recevoir()
{
//Vérouille l'interface
    Attente = true;
//Interprète les données
    m_ui->spnBox_notes->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x00));
    m_ui->spnBox_chan->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x01));
    m_ui->spnBox_upper->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x02));
    m_ui->spnBox_lower->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x03));
    m_ui->spnBox_bank->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x04));
    m_ui->spnBox_voice->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x05));
    m_ui->spnBox_detune->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x06));
    m_ui->cmbBox_trans->setCurrentIndex((int) EXPANDEUR::LireInstParam(IDSel, 0x07));
    m_ui->hzSlider_volume->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x08));
    m_ui->hzSlider_pan->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x09));
    m_ui->pshBut_LFO->setChecked((bool) EXPANDEUR::LireInstParam(IDSel, 0x0A));
    m_ui->spnBox_porta->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x0B));
    m_ui->spnBox_pitch->setValue((int) EXPANDEUR::LireInstParam(IDSel, 0x0C));
    m_ui->pshBut_poly->setChecked(EXPANDEUR::LireInstParam(IDSel, 0x0D));
    m_ui->cmbBox_pmdctl->setCurrentIndex(EXPANDEUR::LireInstParam(IDSel, 0x0E));
//Déverrouille
    Attente = false;
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
