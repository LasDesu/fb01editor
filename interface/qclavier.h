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
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>

#include "../types.h"
#include "../core/midi.h"

#include "../excep/midi_ex.h"

/*****************************************************************************/
class QClavier : public QLabel
{
    Q_OBJECT
public:
    QClavier(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~QClavier();
protected:
//Réimplémentation de la souris
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
//Réimplémentation du clavier
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
private:
//Note en cours
    #define G_REF 36
    int noteSouris;
//Détermine la note
    int TrouverNoteSouris(QMouseEvent * event);
    int TrouverNoteClavier(QKeyEvent * event);
};

#endif // QCLAVIER_H
