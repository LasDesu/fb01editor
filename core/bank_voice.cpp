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

#include "bank_voice.h"

/*****************************************************************************/
Bank_voice::Bank_voice(const uchar id, uchar * sysEx)
    : Edit(id, sysEx, BANKVOICE_LEN_SYSEX, 0, 0, EDIT_OBJ_BANK_VOICE)
{

}

Bank_voice::~Bank_voice()
{

}

/*****************************************************************************/
char * Bank_voice::LireNom()
{
    static char nom[BANKVOICE_LEN_NOM + 1];
    try {
        for (uchar i = 0; i < BANKVOICE_LEN_NOM; i++)
            nom[i] = (char) LireParam2Oct(i);
        nom[BANKVOICE_LEN_NOM] = 0;
        return nom;
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
        return NULL;
    }
}

uchar Bank_voice::LireStyle()
{
    try {
        return LireParam2Oct(BANKVOICE_PARAM_STYLE);
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
        return NULL;
    }
}
