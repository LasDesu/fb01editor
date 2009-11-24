/*
    FB01 : Sound editor
    Copyright Meslin Frédéric 2009
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

#include "qalgo.h"

/*****************************************************************************/
QAlgo::QAlgo(QWidget * parent, Qt::WindowFlags f) : QLabel(parent, f)
{
    ChangerAlgo(0);
}

QAlgo::~QAlgo()
{
}

/*****************************************************************************/
void QAlgo::ChangerAlgo(uchar Algo)
{
//Change l'image
    QString chemin = ":/imgs/algo";
    QString num; num.setNum(Algo+1);
    chemin.append(num);
    chemin.append((QString)".bmp");
    setPixmap(QPixmap(chemin));
//Change l'algorythme
    AlgoSel = Algo;
}

uchar QAlgo::RecupererAlgo()
{
    return AlgoSel;
}

/*****************************************************************************/
void QAlgo::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
    //Incrémente
        if(AlgoSel < 7) ChangerAlgo(AlgoSel + 1);
        else ChangerAlgo(0);
    }else if (event->button() == Qt::RightButton)
    {
    //Décrémente
        if(AlgoSel > 0) ChangerAlgo(AlgoSel - 1);
        else ChangerAlgo(7);
    }
}
