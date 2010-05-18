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

#include "qclavier.h"

/*****************************************************************************/
QClavier::QClavier(QWidget * parent, Qt::WindowFlags f) : QLabel(parent, f)
{
    noteJouee = -1;
}

QClavier::~QClavier()
{
    if (noteJouee != -1) MIDI::Note(noteJouee, 0);
}

/*****************************************************************************/
void QClavier::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons()) mousePressEvent(event);
}

/*****************************************************************************/
void QClavier::mousePressEvent(QMouseEvent * event)
{
    int note = TrouverNote(event);
    if (note != noteJouee)
    {
        if (noteJouee != -1) MIDI::Note(noteJouee, 0);
        MIDI::Note(note, 100);
        noteJouee = note;
    }
}

void QClavier::mouseReleaseEvent(QMouseEvent * event)
{
    if (noteJouee != -1) MIDI::Note(noteJouee, 0);
    noteJouee = -1;
}

/*****************************************************************************/
int QClavier::TrouverNote(QMouseEvent * event)
{
    int octave = event->x() / 56;
    int reste  = event->x() % 56;
    int note   = octave * 12;
//Détermine la touche
    if (event->y() < 24)
    {
        if      (reste > 4  && reste < 12) note += 1;
        else if (reste > 12 && reste < 20) note += 3;
        else if (reste > 28 && reste < 36) note += 6;
        else if (reste > 36 && reste < 44) note += 8;
        else if (reste > 44 && reste < 52) note += 10;
        else goto Blanche;
    }else{
    Blanche :
        if      (reste > 8  && reste < 16) note += 2;
        else if (reste > 16 && reste < 24) note += 4;
        else if (reste > 24 && reste < 32) note += 5;
        else if (reste > 32 && reste < 40) note += 7;
        else if (reste > 40 && reste < 48) note += 9;
        else if (reste > 48 && reste < 56) note += 11;
    }
 //Retourne la note
    return (note > 127) ? 127 : note;
}
