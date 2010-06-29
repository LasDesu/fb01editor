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

#ifndef BANK_VOICE_H
#define BANK_VOICE_H

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"
#include "edit.h"
#include "midi.h"

class Bank_voice : public Edit {
public :
//Constantes
    #define BANKVOICE_LEN_SYSEX 0x83
//Constructeurs
    Bank_voice(const uchar id, uchar * sysEx);
   ~Bank_voice();
private :

};

#endif // BANK_VOICE_H
