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

#ifndef QCLAVIER_H
#define QCLAVIER_H

/*****************************************************************************/
#include <QtGui/QLabel>
#include <QtGui/QMouseEvent>

#include "../types.h"
#include "../core/midi.h"

/*****************************************************************************/
class QClavier : public QLabel
{
public:
    QClavier(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~QClavier();
private:
//Note en cours
    int noteJouee;
//Détermine la note
    int TrouverNote(QMouseEvent * event);
//Réimplémentation de la souris
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
};

#endif // QCLAVIER_H
