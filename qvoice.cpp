#include "qvoice.h"
#include "ui_qvoice.h"

QVoice::QVoice(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::QVoice)
{
//Initialise
    m_ui->setupUi(this);
    Attente = false;
    ChangerInst(0);
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
    Octet = (char) m_ui->pshBut_LFOload->isChecked();
    File->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_LFOsync->isChecked();
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
    m_ui->pshBut_LFOload->setChecked((bool)Octet);
    File->read(&Octet, 1);
    m_ui->pshBut_LFOsync->setChecked((bool)Octet);
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
    EXPANDEUR::EcrireNom(InstSel, m_ui->txtEdit_name->toPlainText().toAscii().constData());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x07, (uchar) m_ui->cmbBox_style->currentIndex());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x08, (uchar) m_ui->spnBox_LFOspeed->value());
    EXPANDEUR::EcrireVoicex09(InstSel, m_ui->pshBut_LFOload->isChecked(), (uchar) m_ui->spnBox_AMD->value());
    EXPANDEUR::EcrireVoicex0A(InstSel, m_ui->pshBut_LFOsync->isChecked(), (uchar) m_ui->spnBox_PMD->value());
    EXPANDEUR::EcrireVoicex0C(InstSel, (uchar) m_ui->spnBox_feedback->value(), (uchar) m_ui->spnBox_algo->value());
    EXPANDEUR::EcrireVoicex0D(InstSel, (uchar) m_ui->spnBox_PMS->value(), (uchar) m_ui->spnBox_AMS->value());
    EXPANDEUR::EcrireVoicex0E(InstSel, (uchar) m_ui->cmbBox_LFOwave->currentIndex());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x0F, (uchar) m_ui->spnBox_trans->value());
    EXPANDEUR::EcrireVoicex3A(InstSel, m_ui->pshBut_poly->isChecked(), (uchar) m_ui->spnBox_porta->value());
    EXPANDEUR::EcrireVoicex3B(InstSel, m_ui->cmbBox_pmdctl->currentIndex(), (uchar) m_ui->spnBox_pitch->value());
}

void QVoice::Recevoir()
{
    char  Nom[8];
    bool  b1;
    uchar p1, p2;
//Reçoit la configuration de l'expandeur
    if (!EXPANDEUR::ChargerVoix(InstSel)) return;
    Attente = true;
//Récupère les données
    EXPANDEUR::LireNom(Nom);
    m_ui->txtEdit_name->setPlainText((QString) Nom);
    m_ui->cmbBox_style->setCurrentIndex((int)EXPANDEUR::LireVoiceParam(0x07));
    m_ui->spnBox_LFOspeed->setValue((int)EXPANDEUR::LireVoiceParam(0x08));
    EXPANDEUR::LireVoicex09(&b1, &p1);
    m_ui->pshBut_LFOload->setChecked(b1); m_ui->spnBox_AMD->setValue((int) p1);
    EXPANDEUR::LireVoicex0A(&b1, &p1);
    m_ui->pshBut_LFOsync->setChecked(b1); m_ui->spnBox_PMD->setValue((int) p1);
    EXPANDEUR::LireVoicex0C(&p1, &p2);
    m_ui->spnBox_feedback->setValue((int) p1); m_ui->spnBox_algo->setValue((int) (p2 + 1));
    EXPANDEUR::LireVoicex0D(&p1, &p2);
    m_ui->spnBox_PMS->setValue((int) p1); m_ui->spnBox_AMS->setValue((int) p2);
    EXPANDEUR::LireVoicex0E(&p1);
    m_ui->cmbBox_LFOwave->setCurrentIndex((int) p1);
    m_ui->spnBox_trans->setValue(EXPANDEUR::LireVoiceParam(0x0F));
    EXPANDEUR::LireVoicex3A(&b1, &p1);
    m_ui->pshBut_poly->setChecked(b1); m_ui->spnBox_porta->setValue((int) p1);
    EXPANDEUR::LireVoicex3B(&p1, &p2);
    m_ui->cmbBox_pmdctl->setCurrentIndex((int) p1); m_ui->spnBox_pitch->setValue((int) p2);
//Fin de la reception
    Attente = false;
}

/*****************************************************************************/
void QVoice::on_spnBox_algo_valueChanged(int i)
{
//Vérification
    if (MIDI::EnAttente()) return;
//Change d'image
    QPixmap pix;
    QString nom = ":/imgs/algo";
    QString num; num.setNum(i);
    nom.append(num);
    nom.append(".bmp");
    pix.load(nom);
    m_ui->lbl_algo->setPixmap(pix);
//Envoie le code
    EXPANDEUR::EcrireVoicex0C(InstSel, (uchar) m_ui->spnBox_feedback->value(), (uchar) (i - 1));
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
