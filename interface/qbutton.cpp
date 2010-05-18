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
    this->valeur = 0;
    this->valMin = 0;
    this->valMax = 127;
    this->click = false;
}

QButton::~QButton()
{
}

/*****************************************************************************/
void QButton::mouseMoveEvent(QMouseEvent * event)
{
    if (!click) return;
//Augmente ou diminue la valeur
    int ancValeur = valeur;
    valeur += event->y() - sourisY;
    valeur += (event->x() - sourisX) / 4;
//Limite la plage
    if(valeur > valMax) valeur = valMax;
    if(valeur < valMin) valeur = valMin;
//Reprend la position
    if(valeur != ancValeur) {
        sourisX = event->x();
        sourisY = event->y();
    }
}

/*****************************************************************************/
void QButton::mousePressEvent(QMouseEvent * event)
{
    click = true;
    sourisX = event->x();
    sourisY = event->y();
}

void QButton::mouseReleaseEvent(QMouseEvent * event)
{
    click = false;
}
