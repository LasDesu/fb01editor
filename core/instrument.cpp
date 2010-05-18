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

#include "instrument.h"

/*****************************************************************************/
Instrument::Instrument(const uchar id, uchar * sysEx, bool * modif)
{
//Initialise les propriétés
    this->id       = id;
    this->nbParam  = INSTRU_NB_PARAM;
    this->lenSysEx = INSTRU_LEN_SYSEX;
    this->nbSysEx  = INSTRU_NB_SYSEX;
//Initialise le sysEx
    this->sysEx = sysEx;
    this->modif = modif;
    InitSysEx();
}

Instrument::~Instrument()
{
}

/*****************************************************************************/
const uchar initTab[INSTRU_NB_PARAM] = {1, 0, 127, 0, 2, 0, 0, 2, 127, 63, 0, 0, 4, 1, 1};
void Instrument::Initialiser()
{
    for (int i=0; i < INSTRU_NB_PARAM; i++)
        EcrireParam(i, initTab[i]);
}

/*****************************************************************************/
uchar Instrument::LireParam(const uchar param)
{
    switch(param) {
    case INSTRU_NB_NOTES :
        return LireSysEx(0) & 0xF;
    case INSTRU_CHANNEL :
        return LireSysEx(1) & 0xF;
    case INSTRU_UPPER :
        return LireSysEx(2) & 0x7F;
    case INSTRU_LOWER :
        return LireSysEx(3) & 0xF;
    case INSTRU_BANK :
        return LireSysEx(4) & 0x7;
    case INSTRU_VOICE :
        return LireSysEx(5) & 0x7F;
    case INSTRU_DETUNE :
        return LireSysEx(6) & 0x7F;
    case INSTRU_TRANS :
        return LireSysEx(7) & 0x7;
    case INSTRU_VOLUME :
        return LireSysEx(8) & 0x7F;
    case INSTRU_PAN :
        return LireSysEx(9) & 0x7F;
    case INSTRU_LFO :
        return LireSysEx(10) & 0x1;
    case INSTRU_PORTAMENTO :
        return LireSysEx(11) & 0x7F;
    case INSTRU_PITCHBEND :
        return LireSysEx(12) & 0xF;
    case INSTRU_POLY :
        return LireSysEx(13) & 0x1;
    case INSTRU_CONROLLER :
        return LireSysEx(14) & 0x7;
    default: return 0;
    }
}

void Instrument::EcrireParam(const uchar param, const uchar valeur)
{
    switch(param) {
    case INSTRU_NB_NOTES :
        EcrireSysEx(0, valeur & 0xF);
    break;
    case INSTRU_CHANNEL :
        EcrireSysEx(1, valeur & 0xF);
    break;
    case INSTRU_UPPER :
        EcrireSysEx(2, valeur & 0x7F);
    break;
    case INSTRU_LOWER :
        EcrireSysEx(3, valeur & 0xF);
    break;
    case INSTRU_BANK :
        EcrireSysEx(4, valeur & 0x7);
    break;
    case INSTRU_VOICE :
        EcrireSysEx(5, valeur & 0x7F);
    break;
    case INSTRU_DETUNE :
        EcrireSysEx(6, valeur & 0x7F);
    break;
    case INSTRU_TRANS :
        EcrireSysEx(7, valeur & 0x7);
    break;
    case INSTRU_VOLUME :
        EcrireSysEx(8, valeur & 0x7F);
    break;
    case INSTRU_PAN :
        EcrireSysEx(9, valeur & 0x7F);
    break;
    case INSTRU_LFO :
        EcrireSysEx(10, valeur & 0x1);
    break;
    case INSTRU_PORTAMENTO :
        EcrireSysEx(11, valeur & 0x7F);
    break;
    case INSTRU_PITCHBEND :
        EcrireSysEx(12, valeur & 0xF);
    break;
    case INSTRU_POLY :
        EcrireSysEx(13, valeur & 0x1);
    break;
    case INSTRU_CONROLLER :
        EcrireSysEx(14, valeur & 0x7);
    break;
    default : return;
    }
}

/*****************************************************************************/
uint Instrument::EnvoyerTout()
{
    return MIDI::MIDI_ERREUR_RIEN;
}

uint Instrument::RecevoirTout()
{
    return MIDI::MIDI_ERREUR_RIEN;
}

/*****************************************************************************/
uint Instrument::Envoyer()
{
    uchar envInstrument[8] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x00, 0x00, 0xF7};
//Construit le message
    envInstrument[3] = MIDI::SysChannel();
    envInstrument[4] = 0x18 + (id & 0x7);
//Envoi les changements
    for (int i=0; i < INSTRU_NB_SYSEX; i++)
        if (modif[i]) {
        //Ajoute le contenu
            envInstrument[5] = i & 0x1F;
            envInstrument[6] = sysEx[i];
        //Envoi le message
            uint res = MIDI::EnvSysEx(envInstrument, 8);
            if (res != MIDI::MIDI_ERREUR_RIEN) return res;
            modif[i] = false;
        }
    return MIDI::MIDI_ERREUR_RIEN;
}

/*****************************************************************************/
uchar Instrument::LireSysEx(const uchar param)
{
    return sysEx[param];
}

void Instrument::EcrireSysEx(const uchar param, const uchar valeur)
{
    sysEx[param] = valeur & 0x7F;
    modif[param] = true;
}

