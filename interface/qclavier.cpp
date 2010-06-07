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
    noteSouris = -1;
    setFocusPolicy(Qt::StrongFocus);
}

QClavier::~QClavier()
{
    MIDI::AllNotesOff();
}

/*****************************************************************************/
void QClavier::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons()) mousePressEvent(event);
}

/*****************************************************************************/
void QClavier::mousePressEvent(QMouseEvent * event)
{
    int note = TrouverNoteSouris(event);
    if (note != noteSouris) {
        MIDI::NoteOff(noteSouris);
        MIDI::NoteOn(note);
        noteSouris = note;
    }
}

void QClavier::keyPressEvent(QKeyEvent * event)
{
    if (event->isAutoRepeat()) return;
    int note = TrouverNoteClavier(event);
    if (note >= 0) MIDI::NoteOn(note);
}

/*****************************************************************************/
void QClavier::mouseReleaseEvent(QMouseEvent * event)
{
    if (noteSouris != -1)
        MIDI::NoteOff(noteSouris);
    noteSouris = -1;
}

void QClavier::keyReleaseEvent(QKeyEvent * event)
{
    int note = TrouverNoteClavier(event);
    if (note >= 0) MIDI::NoteOff(note);
}

/*****************************************************************************/
int QClavier::TrouverNoteSouris(QMouseEvent * event)
{
//Détermine l'octave
    int octave = event->x() / 56;
    int reste  = event->x() % 56;
    int note   = octave * 12;
//Détermine la touche du piano
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

const int clavierNotes[] = {Qt::Key_Q, Qt::Key_2, Qt::Key_W, Qt::Key_3, Qt::Key_E, Qt::Key_R, Qt::Key_5, Qt::Key_T, Qt::Key_6, Qt::Key_Y, Qt::Key_7, Qt::Key_U,
                            Qt::Key_Z, Qt::Key_S, Qt::Key_X, Qt::Key_D, Qt::Key_C, Qt::Key_V, Qt::Key_G, Qt::Key_B, Qt::Key_H, Qt::Key_N, Qt::Key_J, Qt::Key_M};
const int nbClavierNotes = sizeof(clavierNotes) / sizeof(int);
int QClavier::TrouverNoteClavier(QKeyEvent * event)
{
    for(int i = 0; i < nbClavierNotes; i++)
        if(event->key() == clavierNotes[i]) {
            switch (event->modifiers()) {
                case Qt::ShiftModifier: return i+24+G_REF;
                case Qt::ControlModifier: return i+12+G_REF;
                case Qt::AltModifier: return i-12+G_REF;
                default: return i+G_REF;
            }
        }
    return -1;
}

