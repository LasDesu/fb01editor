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
