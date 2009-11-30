#include "qvoice.h"

/*****************************************************************************/
QVoice::QVoice(QWidget *parent) : QWidget(parent), m_ui(new Ui::QVoice)
{
    Attente = false;
    m_ui->setupUi(this);
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
void QVoice::Rafraichir()
{
    m_ui->txtEdit_author->repaint();
    m_ui->txtEdit_comment->repaint();
    m_ui->txtEdit_voicename->repaint();
}

/*****************************************************************************/
bool QVoice::Enregistrer(QFile * Fichier)
{
    char Infos[INFOS];
    char Nom[7];
    char Octet;
//Ecrit les informations
    strncpy(Infos, m_ui->txtEdit_author->toPlainText().toAscii().constData(), INFOS);
    Fichier->write(Infos, INFOS);
    strncpy(Infos, m_ui->txtEdit_comment->toPlainText().toAscii().constData(), INFOS);
    Fichier->write(Infos, INFOS);
//Ecrit la configuration globale
    strncpy(Nom, m_ui->txtEdit_voicename->toPlainText().toAscii().constData(), 7);
    Fichier->write(Nom, 7);
    Octet = (char) m_ui->spnBox_algo->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_style->currentIndex();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_feedback->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_trans->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_poly->isChecked();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_porta->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_pitch->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_pmdctl->currentIndex();
    Fichier->write(&Octet, 1);
//Ecrit la configuration du LFO
    Octet = (char) m_ui->spnBox_LFOspeed->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->cmbBox_LFOwave->currentIndex();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_LFOload->isChecked();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->pshBut_LFOsync->isChecked();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_AMD->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_AMS->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_PMD->value();
    Fichier->write(&Octet, 1);
    Octet = (char) m_ui->spnBox_PMS->value();
    Fichier->write(&Octet, 1);
//Vérifie les erreurs
    if (Fichier->error()) return true;
    return false;
}

bool QVoice::Charger(QFile * Fichier, int Version)
{
    char Infos[INFOS];
    char Nom[8];
    char Octet;
//Vérouille l'interface
    Attente = true;
//Lit les informations
    Fichier->read(Infos, INFOS);
    Infos[INFOS-1] = 0;
    m_ui->txtEdit_author->setPlainText((QString) Infos);
    Fichier->read(Infos, INFOS);
    Infos[INFOS-1] = 0;
    m_ui->txtEdit_comment->setPlainText((QString) Infos);
//Lit le nom
    Fichier->read(Nom, 7);
    Nom[7] = 0;
    m_ui->txtEdit_voicename->setPlainText((QString)Nom);
//Lit la configuration globale
    Fichier->read(&Octet, 1);
    m_ui->spnBox_algo->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->cmbBox_style->setCurrentIndex((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_feedback->setValue((int) Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_trans->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->pshBut_poly->setChecked((bool)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_porta->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_pitch->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->cmbBox_pmdctl->setCurrentIndex((int)Octet);
    Fichier->read(&Octet, 1);
//Ecrit la configuration du LFO
    Fichier->read(&Octet, 1);
    m_ui->spnBox_LFOspeed->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->cmbBox_LFOwave->setCurrentIndex((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->pshBut_LFOload->setChecked((bool)Octet);
    Fichier->read(&Octet, 1);
    m_ui->pshBut_LFOsync->setChecked((bool)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_AMD->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_AMS->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_PMD->setValue((int)Octet);
    Fichier->read(&Octet, 1);
    m_ui->spnBox_PMS->setValue((int)Octet);
//Vérifie les erreurs
    if (Fichier->error()) return true;
    Attente = false;
//Envoie les données
    Envoyer();
    return false;
}

/*****************************************************************************/
void QVoice::Envoyer()
{
//Envoie la configuration complète
    EXPANDEUR::EcrireVoiceNom(InstSel, m_ui->txtEdit_voicename->toPlainText().toAscii().constData());
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
    uchar p1, p2;
    bool  b1;
//Vérouille l'interface
    Attente = true;
//Interprète les données
    EXPANDEUR::LireVoiceNom(Nom);
    m_ui->txtEdit_voicename->setPlainText((QString) Nom);
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
//Déverrouile
    Attente = false;
}

/*****************************************************************************/
void QVoice::on_spnBox_algo_valueChanged(int i)
{
//Vérification
    if (MIDI::EnAttente()) return;
//Change d'image
    QPixmap Pix;
    QString Nom = ":/imgs/algo";
    QString Num; Num.setNum(i);
    Nom.append(Num); Nom.append(".bmp");
    Pix.load(Nom);
    m_ui->lbl_algo->setPixmap(Pix);
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
