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
    clavierDispo = CLAVIER_AUCUNE;
    ChoisirClavier(CLAVIER_QWERTY);
	grabKeyboard();
}

QClavier::~QClavier()
{
    Reinitialiser();
}

/*****************************************************************************/
const int dispoQWERTY[CLAVIER_NB_TOUCHES] = {
	Qt::Key_Q, Qt::Key_2, Qt::Key_W, Qt::Key_3, Qt::Key_E, Qt::Key_R,
	Qt::Key_5, Qt::Key_T, Qt::Key_6, Qt::Key_Y, Qt::Key_7, Qt::Key_U,
	Qt::Key_Z, Qt::Key_S, Qt::Key_X, Qt::Key_D, Qt::Key_C, Qt::Key_V,
	Qt::Key_G, Qt::Key_B, Qt::Key_H, Qt::Key_N, Qt::Key_J, Qt::Key_M
};
const int dispoAZERTY[CLAVIER_NB_TOUCHES] = {
	Qt::Key_A, Qt::Key_2, Qt::Key_Z, Qt::Key_3, Qt::Key_E, Qt::Key_R,
	Qt::Key_5, Qt::Key_T, Qt::Key_6, Qt::Key_Y, Qt::Key_7, Qt::Key_U,
	Qt::Key_W, Qt::Key_S, Qt::Key_X, Qt::Key_D, Qt::Key_C, Qt::Key_V,
	Qt::Key_G, Qt::Key_B, Qt::Key_H, Qt::Key_N, Qt::Key_J, Qt::Key_Comma
};
void QClavier::ChoisirClavier(const CLAVIER_DISPO dispo)
{
//Réinitialise le clavier
    if (clavierDispo == dispo) return;
    Reinitialiser();
//Choisie la disposition des touches
    switch (dispo) {
        case CLAVIER_AUCUNE: return;
		case CLAVIER_QWERTY: touch_table = dispoQWERTY; break;
		case CLAVIER_AZERTY: touch_table = dispoAZERTY; break;
        default : return;
	}
}

/*****************************************************************************/
void QClavier::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons()) mousePressEvent(event);
}

void QClavier::processKey( QKeyEvent *event, bool pressed )
{
	int note;

	for ( uint i = 0; i < CLAVIER_NB_TOUCHES; i ++ ) {
		if ( event->key() == touch_table[i] ) {
			note = TrouverNoteClavier( i,
				event->modifiers() & Qt::ShiftModifier,
				 event->modifiers() & Qt::ControlModifier );
			try {
				if ( pressed )
					MIDI::NoteOn( note );
				else
					MIDI::NoteOff( note );
				touches[i] = pressed;
			} catch ( MIDI_ex ex ) {
				return;
			}
		}
	}
}

void QClavier::keyPressEvent(QKeyEvent *event)
{
	QClavier::processKey( event, true );
}

void QClavier::keyReleaseEvent(QKeyEvent *event)
{
	QClavier::processKey( event, false );
}

/*****************************************************************************/
void QClavier::mousePressEvent(QMouseEvent * event)
{
    int note = TrouverNoteSouris(event->x(), event->y());
    if (note != noteSouris) {
        try {
            MIDI::NoteOff(noteSouris);
            MIDI::NoteOn(note);
            noteSouris = note;
        }catch (MIDI_ex ex) { return; }
    }
}

void QClavier::mouseReleaseEvent(QMouseEvent * event)
{
    if (noteSouris != -1) {
        try {
            MIDI::NoteOff(noteSouris);
            noteSouris = -1;
        }catch (MIDI_ex ex) { return; }
    }
}

/*****************************************************************************/
int QClavier::TrouverNoteSouris(const int x, const int y)
{
//Détermine l'octave
    int octave   = x / 56;
    int position = x % 56;
    int note     = octave * 12;
//Détermine la touche du piano
    if (y < 24)
    {
        if      (position > 4  && position < 12) note += 1;
        else if (position > 12 && position < 20) note += 3;
        else if (position > 28 && position < 36) note += 6;
        else if (position > 36 && position < 44) note += 8;
        else if (position > 44 && position < 52) note += 10;
        else goto Blanche;
    }else{
    Blanche :
        if      (position > 8  && position < 16) note += 2;
        else if (position > 16 && position < 24) note += 4;
        else if (position > 24 && position < 32) note += 5;
        else if (position > 32 && position < 40) note += 7;
        else if (position > 40 && position < 48) note += 9;
        else if (position > 48 && position < 56) note += 11;
    }
 //Retourne la note
    return min(note, 127);
}

int QClavier::TrouverNoteClavier(const int index, const bool shift, const bool control)
{
    if (shift) return min(index + 12 + G_REF, 127);
    if (control) return max(0, index - 12 + G_REF);
    return index + G_REF;
}

/*****************************************************************************/
void QClavier::Reinitialiser()
{
//Réinitialise les commandes
    for (uint i = 0; i < CLAVIER_NB_TOUCHES; i++)
		touches[i] = false;
    noteSouris = -1;
//Arrête toute note jouée
    try {
        MIDI::AllNotesOff();
    }catch (MIDI_ex ex) { return; }
}
