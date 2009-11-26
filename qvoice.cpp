#include "qvoice.h"
#include "ui_qvoice.h"

QVoice::QVoice(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::QVoice)
{
    m_ui->setupUi(this);
}

QVoice::~QVoice()
{
    delete m_ui;
}

/*****************************************************************************/
void QVoice::ChangerInst(uchar Inst)
{
    InstSel = Inst;
}

uchar QVoice::RecupererInst()
{
    return InstSel;
}

/*****************************************************************************/
bool QVoice::Enregistrer(QFile * File)
{
    char Nom[7];
    char Octet;
//Ecrit le nom
    memset(Nom, 0, 7);
    strncpy(Nom, m_ui->txtEdit_name->toPlainText().toAscii().constData(), 7);
    File->write(Nom, 7);
//Ecrit la configuration globale
    Octet = (char) m_ui->spnBox_algo->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_style->currentIndex();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_feedback->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_trans->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_poly->isChecked();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_porta->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_pitch->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_pmdctl->currentIndex();
    File->write(&Octet, 1);
//Ecrit la configuration du LFO
    Octet = (char) m_ui->spnBox_LFOspeed->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_LFOwave->currentIndex();
    File->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_load->isChecked();
    File->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_sync->isChecked();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_AMD->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_AMS->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_PMD->value();
    File->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_PMS->value();
    File->write(&Octet, 1);
//Vérifie les erreurs
    if (File->error()) return true;
    return false;
}

bool QVoice::Charger(QFile * File, int Version)
{
    char Nom[7];
    char Octet;
//Lit le nom
    File->read(Nom, 7);
    m_ui->txtEdit_name->setPlainText((QString)Nom);
//Lit la configuration globale
    File->read(&Octet, 1);
    m_ui->spnBox_algo->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->cmbBox_style->setCurrentIndex((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_feedback->setValue((int) Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_trans->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->pshBut_poly->setChecked((bool)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_porta->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_pitch->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->cmbBox_pmdctl->setCurrentIndex((int)Octet);
    File->read(&Octet, 1);
//Ecrit la configuration du LFO
    File->read(&Octet, 1);
    m_ui->spnBox_LFOspeed->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->cmbBox_LFOwave->setCurrentIndex((int)Octet);
    File->read(&Octet, 1);
    m_ui->pshBut_load->setChecked((bool)Octet);
    File->read(&Octet, 1);
    m_ui->pshBut_sync->setChecked((bool)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_AMD->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_AMS->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_PMD->setValue((int)Octet);
    File->read(&Octet, 1);
    m_ui->spnBox_PMS->setValue((int)Octet);
//Vérifie les erreurs
    if (File->error()) return true;
    return false;
}

/*****************************************************************************/
void QVoice::Envoyer()
{
//Envoie la configuration complète
    EXPANDEUR::ChangerNom(InstSel, m_ui->txtEdit_name->toPlainText().toAscii().constData());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x07, (uchar) m_ui->cmbBox_style->currentIndex());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x08, (uchar) m_ui->spnBox_LFOspeed->value());
    EXPANDEUR::ChangerVoicex09(InstSel, m_ui->pshBut_load->isChecked(), (uchar) m_ui->spnBox_AMD->value());
    EXPANDEUR::ChangerVoicex0A(InstSel, m_ui->pshBut_sync->isChecked(), (uchar) m_ui->spnBox_PMD->value());
    EXPANDEUR::ChangerVoicex0C(InstSel, (uchar) m_ui->spnBox_feedback->value(), (uchar) m_ui->spnBox_algo->value());
    EXPANDEUR::ChangerVoicex0D(InstSel, (uchar) m_ui->spnBox_PMS->value(), (uchar) m_ui->spnBox_AMS->value());
    EXPANDEUR::ChangerVoicex0E(InstSel, (uchar) m_ui->cmbBox_LFOwave->currentIndex());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x0F, (uchar) m_ui->spnBox_trans->value());
    EXPANDEUR::ChangerVoicex3A(InstSel, m_ui->pshBut_poly->isChecked(), (uchar) m_ui->spnBox_porta->value());
    EXPANDEUR::ChangerVoicex3B(InstSel, m_ui->cmbBox_pmdctl->currentIndex(), (uchar) m_ui->spnBox_pitch->value());
}

/*****************************************************************************/
void QVoice::on_spnBox_algo_valueChanged(int i)
{
    QString nom = ":/imgs/algo";
    QString num; num.setNum(i);
    QPixmap pix;
//Change d'image
    nom.append(num);
    nom.append(".bmp");
    pix.load(nom);
    m_ui->lbl_algo->setPixmap(pix);
//Envoie le code
    EXPANDEUR::ChangerVoicex0C(InstSel, (uchar) m_ui->spnBox_feedback->value(), (uchar) (i - 1));
}

/*****************************************************************************/
void QVoice::changeEvent(QEvent *e)
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
