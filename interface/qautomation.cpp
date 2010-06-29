/*
    FB01 : Sound editor
    Copyright Meslin Frédéric 2009 - 2010
    fredericmeslin@hotmail.com

    This file is part of FB01 SE

    FB01 SE is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FB01 SE is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FB01 SE.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "qautomation.h"

/*****************************************************************************/
QAutomation::QAutomation(QWidget *parent) : QWidget(parent), m_ui(new Ui::QAutomation)
{
    m_ui->setupUi(this);
}

QAutomation::~QAutomation()
{
    delete m_ui;
}

/*****************************************************************************/
void QAutomation::Actualiser()
{
    QString num;
//Ajoute tous les CCs
    m_ui->listWidget_CCs->clear();
    for (uint i = 0; i < AUTO_NB_CCS; i ++) {
        num.setNum(i, 10);
        QListWidgetItem * item = new QListWidgetItem("CC#" + num);
        m_ui->listWidget_CCs->addItem(item);
    }
//Ajoute toutes les callbacks
    m_ui->listWidget_FMs->clear();
    m_ui->listWidget_FMs->addItem(new QListWidgetItem("Nothing"));
    for (uint i = 0; i < Automation::NbCallbacks(); i ++) {
        num.setNum(i, 10);
        QListWidgetItem * item = new QListWidgetItem(Automation::NomCallback(i));
        m_ui->listWidget_FMs->addItem(item);
    }
}

void QAutomation::Rafraichir()
{
    QString num;
//Rafraichit l'interface
    num.setNum(Automation::DernierCC());
    m_ui->lbl_lastCC->setText("Last CC received: " + num);
    m_ui->lbl_lastCC->repaint();
    num.setNum(Automation::DerniereValeur());
    m_ui->lbl_lastValue->setText("Last value received: " + num);
    m_ui->lbl_lastValue->repaint();
}

/*****************************************************************************/
void QAutomation::on_listWidget_CCs_itemClicked(QListWidgetItem * item)
{
    int CC = m_ui->listWidget_CCs->row(item);
//Affiche les callbacks associées
    for (int i = 1; i < m_ui->listWidget_FMs->count(); i++)
        m_ui->listWidget_FMs->item(i)->setSelected(Automation::CallbackAssociee(i - 1, CC));
//Aucune sélection
    m_ui->listWidget_FMs->item(0)->setSelected(!Automation::CCAssocie(CC));
    m_ui->listWidget_FMs->repaint();
}

void QAutomation::on_listWidget_FMs_itemClicked(QListWidgetItem * item)
{
    int i  = m_ui->listWidget_FMs->row(item);
    int CC = m_ui->listWidget_CCs->currentRow();
//Gère l'association des callbacks
    if (i != 0) {
        if (item->isSelected()) {
            try {
                Automation::AssocierCC(CC, i - 1);
            }catch (Automation_ex ex) {
                item->setSelected(false);
            }
        }else Automation::DissocierCC(CC, i - 1);
    }
//Actualise la liste
    m_ui->listWidget_FMs->item(0)->setSelected(!Automation::CCAssocie(CC));
    m_ui->listWidget_FMs->repaint();
}

/*****************************************************************************/
void QAutomation::changeEvent(QEvent *e)
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
