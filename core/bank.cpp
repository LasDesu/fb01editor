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

#include "bank.h"

/*****************************************************************************/
Bank::Bank()
    : Edit(0, (uchar *) malloc(BANK_LEN_SYSEX), BANK_LEN_SYSEX, 0, 0)
{
//Initialise la classe
    Initialiser();
//Initialise les voices
    memset(voices, 0, sizeof(Bank_voice *) * BANK_NB_VOICES);
    for (int i = 0; i < BANK_NB_VOICES; i ++) {
        voices[i] = new Bank_voice(i, &sysEx[0x4A + i * 0x83]);
        if (voices[i] == NULL) throw Memory_ex("Unable to allocate the voices of banks !");
    }
}

Bank::~Bank()
{
//Libère les voices
    for (int i = 0; i < BANK_NB_VOICES; i ++)
        if (voices[i] != NULL) delete voices[i];
//Libère le sysex
    free(sysEx);
}

/*****************************************************************************/
bool Bank::Enregistrer(FILE * fichier)
{
//Sauvegarde les données
    return true;
}

bool Bank::Charger(FILE * fichier, const short version)
{
//Recupère les données
    if (version == VERSION) {

    }else{
    //Compatibilité editeur 1.0
    }
    return true;
}

/*****************************************************************************/
void Bank::EnvoyerTout()
{
}

void Bank::RecevoirTout()
{
}

/*****************************************************************************/
void Bank::Initialiser()
{
    uchar entBank[7] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x00, 0x00};
//Entête de message
    Block::Initialiser(entBank, 7);
    sysEx[7] = 0x00; sysEx[8] = 0x40;
//Taille des paquets voices
    //for (int i = 0; i < 48; i++) {
      //  sysEx[i * 0x83 + 0x5F] = 0x00;
      //  sysEx[i * 0x83 + 0x60] = 0x40;
    //}
}

