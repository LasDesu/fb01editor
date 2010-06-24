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
    : Edit(0, 0, BANK_LEN_SYSEX, (uchar *) malloc(BANK_LEN_SYSEX))
{
//Initialise la classe
    InitSysEx();
}

Bank::~Bank()
{
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
uchar Bank::LireParam(const uchar param)
{
    return 0;
}

void Bank::EcrireParam(const uchar param, const uchar valeur, const bool envoi)
{
    return;
}

/*****************************************************************************/
uint Bank::EnvoyerTout()
{
    return MIDI::MIDI_ERREUR_RIEN;
}

uint Bank::RecevoirTout()
{
    return MIDI::MIDI_ERREUR_RIEN;
}

/*****************************************************************************/
void Bank::InitSysEx()
{
//Entête de message
    Block::InitSysEx();
    sysEx[0] = 0xF0; sysEx[1] = 0x43;
    sysEx[2] = 0x75; sysEx[3] = 0x00;
    sysEx[4] = 0x00; sysEx[5] = 0x00;
    sysEx[6] = 0x00;
//Taille du paquet entête
    sysEx[7] = 0x00;
    sysEx[8] = 0x40;
//Taille des paquets voices
    //for (int i = 0; i < 48; i++) {
      //  sysEx[i * 0x83 + 0x5F] = 0x00;
      //  sysEx[i * 0x83 + 0x60] = 0x40;
    //}
//Fin du message
    sysEx[BANK_LEN_SYSEX - 1] = 0xF7;
}

/*****************************************************************************/
uchar Bank::LireSysEx(const uchar param)
{
    return 0;
}

void Bank::EcrireSysEx(const uchar param, const uchar valeur, const bool envoi)
{
    return;
}
