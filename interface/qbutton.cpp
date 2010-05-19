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

#include "qbutton.h"

/*****************************************************************************/
QButton::QButton(QWidget * parent) : QPushButton(parent)
{
//Initialise le controle
    this->valeur = 0;
    this->ancValeur = 0;
    this->click = false;
}

QButton::~QButton()
{
}

/*****************************************************************************/
void QButton::EcrireValeur(int valeur)
{
    static QString text;
    if (valeur >= valMin && valeur <= valMax) {
    //Change la valeur interne
        this->valeur = valeur;
        this->ancValeur = valeur;
        emit valueChanged(valeur);
    //Affiche la nouvelle valeur
        text.setNum(valeur, 10);
        setText(text);
    }
}

int QButton::LireValeur()
{
    return valeur;
}

/*****************************************************************************/
void QButton::mouseMoveEvent(QMouseEvent * event)
{
    static QString text;
    if (!click) return;
//Augmente ou diminue la valeur
    valeur = clickValeur;
    valeur += (sourisY - event->y()) >> 2;
    valeur += (event->x() - sourisX) >> 4;
//Limite la plage
    if(valeur > valMax) valeur = valMax;
    if(valeur < valMin) valeur = valMin;
//Change la valeur du controle
    if (valeur != ancValeur) {
        emit valueChanged(valeur);
        ancValeur = valeur;
        text.setNum(valeur, 10);
        setText(text);
    }
}

/*****************************************************************************/
void QButton::mousePressEvent(QMouseEvent * event)
{
//Récupère les bornes
    QSize size = this->baseSize();
    this->valMin = (char) size.width();
    this->valMax = (char) size.height();
    clickValeur = valeur;
//Sauvegarde la position
    sourisX = event->x();
    sourisY = event->y();
    click = true;
}

void QButton::mouseReleaseEvent(QMouseEvent * event)
{
    click = false;
}

