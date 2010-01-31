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
bool QVoice::Charger(QFile * Fichier, int Version)
{
    uchar Table[16];
    char Infos[INFOS];
    char Nom[8];
//Vérouille l'interface
    Attente = true;
//Lit les informations
    Fichier->read(Infos, INFOS); Infos[INFOS-1] = 0;
    m_ui->txtEdit_author->setPlainText((QString) Infos);
    Fichier->read(Infos, INFOS); Infos[INFOS-1] = 0;
    m_ui->txtEdit_comment->setPlainText((QString) Infos);
    Fichier->read(Nom, 7);  Nom[7] = 0;
    m_ui->txtEdit_voicename->setPlainText((QString)Nom);
//Lit la configuration globale
    Fichier->read((char *) Table, 16);
    if (Fichier->error()) return true;
    Coller(Table);
//Déverrouille
    Attente = false;
    return false;
}

bool QVoice::Enregistrer(QFile * Fichier)
{
    uchar Table[16];
    char Infos[INFOS];
    char Nom[7];
//Ecrit les informations
    strncpy(Infos, m_ui->txtEdit_author->toPlainText().toAscii().constData(), INFOS);
    Fichier->write(Infos, INFOS);
    strncpy(Infos, m_ui->txtEdit_comment->toPlainText().toAscii().constData(), INFOS);
    Fichier->write(Infos, INFOS);
    strncpy(Nom, m_ui->txtEdit_voicename->toPlainText().toAscii().constData(), 7);
    Fichier->write(Nom, 7);
//Ecrit la configuration globale
    Copier(Table);
    Fichier->write((char *) Table, 16);
//Vérifie les erreurs
    if (Fichier->error()) return true;
    return false;
}

/*****************************************************************************/
void QVoice::Envoyer()
{
//Envoie la configuration complète
    EXPANDEUR::EcrireVoiceNom(InstSel, m_ui->txtEdit_voicename->toPlainText().toAscii().constData());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x07, (uchar) m_ui->cmbBox_style->currentIndex());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x08, (uchar) m_ui->spnBox_LFOspeed->value());
    EXPANDEUR::EcrireVoicex09(InstSel, ! m_ui->pshBut_LFOload->isChecked(), (uchar) m_ui->spnBox_AMD->value());
    EXPANDEUR::EcrireVoicex0A(InstSel, ! m_ui->pshBut_LFOsync->isChecked(), (uchar) m_ui->spnBox_PMD->value());
    EXPANDEUR::EcrireVoicex0C(InstSel, (uchar) m_ui->spnBox_feedback->value(), (uchar) (m_ui->spnBox_algo->value() - 1));
    EXPANDEUR::EcrireVoicex0D(InstSel, (uchar) m_ui->spnBox_PMS->value(), (uchar) m_ui->spnBox_AMS->value());
    EXPANDEUR::EcrireVoicex0E(InstSel, (uchar) m_ui->cmbBox_LFOwave->currentIndex());
    EXPANDEUR::EcrireVoiceParam(InstSel, 0x0F, (uchar) m_ui->spnBox_trans->value());
    EXPANDEUR::EcrireVoicex3A(InstSel, ! m_ui->pshBut_poly->isChecked(), (uchar) m_ui->spnBox_porta->value());
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
    m_ui->pshBut_LFOload->setChecked(! b1); m_ui->spnBox_AMD->setValue((int) p1);
    EXPANDEUR::LireVoicex0A(&b1, &p1);
    m_ui->pshBut_LFOsync->setChecked(! b1); m_ui->spnBox_PMD->setValue((int) p1);
    EXPANDEUR::LireVoicex0C(&p1, &p2);
    m_ui->spnBox_feedback->setValue((int) p1); m_ui->spnBox_algo->setValue((int) (p2 + 1));
    EXPANDEUR::LireVoicex0D(&p1, &p2);
    m_ui->spnBox_PMS->setValue((int) p1); m_ui->spnBox_AMS->setValue((int) p2);
    EXPANDEUR::LireVoicex0E(&p1);
    m_ui->cmbBox_LFOwave->setCurrentIndex((int) p1);
    m_ui->spnBox_trans->setValue((int)(char) EXPANDEUR::LireVoiceParam(0x0F));
    EXPANDEUR::LireVoicex3A(&b1, &p1);
    m_ui->pshBut_poly->setChecked(! b1); m_ui->spnBox_porta->setValue((int) p1);
    EXPANDEUR::LireVoicex3B(&p1, &p2);
    m_ui->cmbBox_pmdctl->setCurrentIndex((int) p1); m_ui->spnBox_pitch->setValue((int) p2);
//Déverrouile
    Attente = false;
}

/*****************************************************************************/
QString AlgNoms[] = {":/ALGO1", ":/ALGO2", ":/ALGO3", ":/ALGO4", ":/ALGO5", ":/ALGO6", ":/ALGO7", ":/ALGO8"};
void QVoice::on_spnBox_algo_valueChanged(int i)
{
//Change d'image
    QPixmap Pix;
    Pix.load(AlgNoms[i-1]);
    m_ui->lbl_algo->setPixmap(Pix);
//Envoie le code
    EXPANDEUR::EcrireVoicex0C(InstSel, (uchar) m_ui->spnBox_feedback->value(), (uchar) (i - 1));
}

/*****************************************************************************/
const uchar InitTab[16] = {8, 0, 0, 0, 1, 0, 4, 1, 127, 0, 0, 1, 0, 0, 0, 0};
void QVoice::Initialiser()
{
//Initialise les textes
    Attente = true;
    m_ui->txtEdit_voicename->setPlainText((QString) "Noname");
    m_ui->txtEdit_author->setPlainText((QString) "");
    m_ui->txtEdit_comment->setPlainText((QString) "");
//Initialise les valeurs
    Coller(InitTab);
}

void QVoice::Randomiser()
{
//Vérrouille l'interface
    Attente = true;
//Initialise aléatoirement
    m_ui->spnBox_algo->setValue(RAND(1, 8));
    m_ui->cmbBox_style->setCurrentIndex(RAND(0, 13));
    m_ui->spnBox_feedback->setValue(RAND(0, 7));
    m_ui->spnBox_trans->setValue(RAND(-128, 127));
    m_ui->pshBut_poly->setChecked(RAND(0, 1));
    m_ui->spnBox_porta->setValue(RAND(0, 127));
    m_ui->spnBox_pitch->setValue(RAND(0, 12));
    m_ui->cmbBox_pmdctl->setCurrentIndex(RAND(0, 4));
    m_ui->spnBox_LFOspeed->setValue(RAND(0, 255));
    m_ui->cmbBox_LFOwave->setCurrentIndex(RAND(0, 3));
    m_ui->pshBut_LFOload->setChecked(RAND(0, 1));
    m_ui->pshBut_LFOsync->setChecked(RAND(0, 1));
    m_ui->spnBox_AMD->setValue(RAND(0, 127));
    m_ui->spnBox_AMS->setValue(RAND(0, 3));
    m_ui->spnBox_PMD->setValue(RAND(0, 127));
    m_ui->spnBox_PMS->setValue(RAND(0, 7));
//Actualise l'interface
    Attente = false;
    Rafraichir();
    Envoyer();
}

/*****************************************************************************/
void QVoice::Copier(uchar Table[16])
{
//Copie les données
    Table[0]  = (uchar) m_ui->spnBox_algo->value();
    Table[1]  = (uchar) m_ui->cmbBox_style->currentIndex();
    Table[2]  = (uchar) m_ui->spnBox_feedback->value();
    Table[3]  = (uchar) m_ui->spnBox_trans->value();
    Table[4]  = (uchar) m_ui->pshBut_poly->isChecked();
    Table[5]  = (uchar) m_ui->spnBox_porta->value();
    Table[6]  = (uchar) m_ui->spnBox_pitch->value();
    Table[7]  = (uchar) m_ui->cmbBox_pmdctl->currentIndex();
    Table[8]  = (uchar) m_ui->spnBox_LFOspeed->value();
    Table[9]  = (uchar) m_ui->cmbBox_LFOwave->currentIndex();
    Table[10] = (uchar) m_ui->pshBut_LFOload->isChecked();
    Table[11] = (uchar) m_ui->pshBut_LFOsync->isChecked();
    Table[12] = (uchar) m_ui->spnBox_AMD->value();
    Table[13] = (uchar) m_ui->spnBox_AMS->value();
    Table[14] = (uchar) m_ui->spnBox_PMD->value();
    Table[15] = (uchar) m_ui->spnBox_PMS->value();
}

void QVoice::Coller(const uchar Table[16])
{
//Vérrouille l'interface
    Attente = true;
//Colle les données
    m_ui->spnBox_algo->setValue((int) Table[0]);
    m_ui->cmbBox_style->setCurrentIndex((int) Table[1]);
    m_ui->spnBox_feedback->setValue((int) Table[2]);
    m_ui->spnBox_trans->setValue((int) Table[3]);
    m_ui->pshBut_poly->setChecked((bool) Table[4]);
    m_ui->spnBox_porta->setValue((int) Table[5]);
    m_ui->spnBox_pitch->setValue((int) Table[6]);
    m_ui->cmbBox_pmdctl->setCurrentIndex((int) Table[7]);
    m_ui->spnBox_LFOspeed->setValue((int) Table[8]);
    m_ui->cmbBox_LFOwave->setCurrentIndex((int) Table[9]);
    m_ui->pshBut_LFOload->setChecked((bool) Table[10]);
    m_ui->pshBut_LFOsync->setChecked((bool) Table[11]);
    m_ui->spnBox_AMD->setValue((int) Table[12]);
    m_ui->spnBox_AMS->setValue((int) Table[13]);
    m_ui->spnBox_PMD->setValue((int) Table[14]);
    m_ui->spnBox_PMS->setValue((int) Table[15]);
    Attente = false;
 //Actualise l'interface
    Rafraichir();
    Envoyer();
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
