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

#include "qclavier.h"

/*****************************************************************************/
QClavier::QClavier(QWidget * parent, Qt::WindowFlags f) : QLabel(parent, f)
{
//Aucune note
    NoteJouee = -1;
}

QClavier::~QClavier()
{
//Arrête la note
    if (NoteJouee != -1)
        MIDI::Note(NoteJouee, 0);
}

/*****************************************************************************/
void QClavier::mouseMoveEvent(QMouseEvent * event)
{
//Pression sur une touche
    if (event->buttons())
        mousePressEvent(event);
}

/*****************************************************************************/
void QClavier::mousePressEvent(QMouseEvent * event)
{
//Produit la note
    int Note = TrouverNote(event);
    if (Note != NoteJouee)
    {
    //Arrête la note
        if (NoteJouee != -1)
            MIDI::Note(NoteJouee, 0);
    //Joue la nouvelle
        MIDI::Note(Note, 100);
        NoteJouee = Note;
    }
}

void QClavier::mouseReleaseEvent(QMouseEvent * event)
{
//Arrête la note
    if (NoteJouee != -1)
        MIDI::Note(NoteJouee, 0);
    NoteJouee = -1;
}

/*****************************************************************************/
int QClavier::TrouverNote(QMouseEvent * event)
{
    int Octave = event->x() / 56;
    int Reste  = event->x() % 56;
    int Note   = Octave * 12;
//Détermine la touche
    if (event->y() < 24)
    {
        if      (Reste > 4  && Reste < 12) Note += 1;
        else if (Reste > 12 && Reste < 20) Note += 3;
        else if (Reste > 28 && Reste < 36) Note += 6;
        else if (Reste > 36 && Reste < 44) Note += 8;
        else if (Reste > 44 && Reste < 52) Note += 10;
        else goto Blanche;
    }else{
    Blanche :
        if      (Reste > 8  && Reste < 16) Note += 2;
        else if (Reste > 16 && Reste < 24) Note += 4;
        else if (Reste > 24 && Reste < 32) Note += 5;
        else if (Reste > 32 && Reste < 40) Note += 7;
        else if (Reste > 40 && Reste < 48) Note += 9;
        else if (Reste > 48 && Reste < 56) Note += 11;
    }
 //Retourne la note
    return (Note > 127) ? 127 : Note;
}
