#include "qinstrument.h"

/*****************************************************************************/
QInstrument::QInstrument(QWidget *parent) :  QWidget(parent), m_ui(new Ui::QInstrument)
{
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
bool QInstrument::Enregistrer(QFile * File)
{
    char Octet;
//Ecrit chaque donnée
    Octet = (char) m_ui->spnBox_notes->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_chan->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_upper->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_lower->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_bank->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_voice->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_detune->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_trans->currentIndex();
    File->write(&Octet, 1);
    Octet = (char) m_ui->hzSlider_volume->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->hzSlider_pan->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_LFO->isChecked();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_porta->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_pitch->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_poly->isChecked();
    File->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_pmdctl->currentIndex();
    File->write(&Octet, 1);
//Vérifie les erreurs
    if (File->error()) return true;
    return false;
}

bool QInstrument::Charger(QFile * File)
{
    char Octet;
//Lit chaque donnée
    File->read(&Octet, 1);
    m_ui->spnBox_notes->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_chan->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_upper->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_lower->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_bank->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_voice->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_detune->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->cmbBox_trans->setCurrentIndex((int)Octet);
    File->read(&Octet, 1);
    m_ui->hzSlider_volume->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->hzSlider_pan->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->pshBut_LFO->setChecked((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_porta->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_pitch->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->pshBut_poly->setChecked((int)Octet);
    File->read(&Octet, 1);
    m_ui->cmbBox_pmdctl->setCurrentIndex((int)Octet);
    File->read(&Octet, 1);
//Vérifie les erreurs
    if (File->error()) return true;
    return false;
}

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
