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

void QOperateur::ChangerInst(uchar Index)
{
    InstSel = Index;
}

uchar QOperateur::RecupererInst()
{
    return InstSel;
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
