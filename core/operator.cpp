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

#include "operator.h"

/*****************************************************************************/
Operator::Operator(const uchar instru, const uchar id, uchar * sysEx, bool * modif)
{
//Initialise les propriétés
    this->instru  = instru;
    this->id       = id;
    this->nbParam  = OPERATOR_NB_PARAM;
    this->lenSysEx = OPERATOR_LEN_SYSEX;
    this->nbSysEx  = OPERATOR_NB_SYSEX;
//Initialise le sysEx
    this->sysEx = sysEx;
    this->modif = modif;
    InitSysEx();
}

Operator::~Operator()
{
}

/*****************************************************************************/
const uchar initTab[OPERATOR_NB_PARAM] = {127, 0, 0, 0, 0, 0, 0, 0, 31, 1, 0, 31, 0, 0, 15, 15};
void Operator::Initialiser()
{
    for (int i=0; i < OPERATOR_NB_PARAM; i++)
        EcrireParam(i, initTab[i]);
}

/*****************************************************************************/
uchar Operator::LireParam(const uchar param)
{
    switch(param) {
    case OPERATOR_LEVEL :
        return LireSysEx(0x1) & 0x7F;
    case OPERATOR_LEVEL_CURB :
        return ((LireSysEx(0x1) >> 7) & 0x1)
              +((LireSysEx(0x3) >> 6) & 0x2);
    case OPERATOR_LEVEL_VELOCITY :
        return (LireSysEx(0x1) >> 4) & 0x7;
    case OPERATOR_LEVEL_DEPTH :
        return (LireSysEx(0x2) >> 4) & 0xF;
    case OPERATOR_ADJUST :
        return LireSysEx(0x2) & 0xF;
    case OPERATOR_FINE :
        return (LireSysEx(0x3) >> 4) & 0x7;
    case OPERATOR_MULTIPLE :
        return LireSysEx(0x3) & 0xF;
    case OPERATOR_RATE_DEPTH :
        return (LireSysEx(0x4) >> 6) & 0x3;
    case OPERATOR_ATTACK :
        return LireSysEx(0x4) & 0x1F;
    case OPERATOR_MODULATOR :
        return (LireSysEx(0x5) >> 7) & 0x1;
    case OPERATOR_ATTACK_VELOCITY :
        return LireSysEx(0x5) >> 5 & 0x3;
    case OPERATOR_DECAY1 :
        return LireSysEx(0x5) & 0x1F;
    case OPERATOR_COARSE :
        return (LireSysEx(0x6) >> 6) & 0x3;
    case OPERATOR_DECAY2 :
        return (LireSysEx(0x6) & 0x1F);
    case OPERATOR_SUSTAIN :
        return (LireSysEx(0x7) >> 4) & 0xF;
    case OPERATOR_RELEASE :
        return LireSysEx(0x7) & 0xF;
    default : return 0;
    }
}

void Operator::EcrireParam(const uchar param, const uchar valeur)
{
    uchar byte;
    switch(param) {
    case OPERATOR_LEVEL :
        byte = valeur & 0x7F;
        EcrireSysEx(0x0, byte);
    break;
    case OPERATOR_LEVEL_CURB :
        byte  = LireSysEx(0x1) & 0x7F;
        byte += (valeur & 0x1) << 7;
        EcrireSysEx(0x1, byte);
        byte  = LireSysEx(3) & 0x7F;
        byte += (valeur & 0x2) << 6;
        EcrireSysEx(0x3, byte);
    break;
    case OPERATOR_LEVEL_VELOCITY :
        byte  = LireSysEx(0x1) & 0x8F;
        byte += (valeur & 0x7) << 4;
        EcrireSysEx(0x1, byte);
    break;
    case OPERATOR_LEVEL_DEPTH :
        byte  = LireSysEx(2) & 0xF;
        byte += (valeur & 0xF) << 4;
        EcrireSysEx(2, byte);
    break;
    case OPERATOR_ADJUST :
        byte  = LireSysEx(0x2) & 0xF0;
        byte += valeur & 0xF;
        EcrireSysEx(0x2, byte);
    break;
    case OPERATOR_FINE :
        byte = LireSysEx(0x3) & 0x8F;
        byte += (valeur & 0x7) << 4;
        EcrireSysEx(0x3, byte);
    break;
    case OPERATOR_MULTIPLE :
        byte = LireSysEx(0x3) & 0xF0;
        byte += valeur & 0xF;
        EcrireSysEx(0x3, byte);
    break;
    case OPERATOR_RATE_DEPTH :
        byte  = LireSysEx(4) & 0x3F;
        byte += (valeur & 0x3) << 6;
        EcrireSysEx(4, byte);
    break;
    case OPERATOR_ATTACK :
        byte = LireSysEx(0x4) & 0xE0;
        byte += valeur & 0x1F;
        EcrireSysEx(0x4, byte);
    break;
    case OPERATOR_MODULATOR :
        byte = LireSysEx(0x5) & 0x7F;
        byte += (valeur & 0x1) << 7;
        EcrireSysEx(0x5, byte);
    break;
    case OPERATOR_ATTACK_VELOCITY :
        byte  = LireSysEx(0x5) & 0x9F;
        byte += (valeur & 0x3) << 5;
        EcrireSysEx(0x5, byte);
    break;
    case OPERATOR_DECAY1 :
        byte = LireSysEx(0x5) & 0xE0;
        byte += valeur & 0x1F;
        EcrireSysEx(0x5, byte);
    break;
    case OPERATOR_COARSE :
        byte = LireSysEx(0x6) & 0x3F;
        byte += (valeur & 0x3) << 6;
        EcrireSysEx(0x6, byte);
    break;
    case OPERATOR_DECAY2 :
        byte = LireSysEx(0x6) & 0xE0;
        byte += valeur & 0x1F;
        EcrireSysEx(0x6, byte);
    break;
    case OPERATOR_SUSTAIN :
        byte = LireSysEx(0x7) & 0xF;
        byte += (valeur & 0xF) << 4;
        EcrireSysEx(0x7, byte);
    break;
    case OPERATOR_RELEASE :
        byte = LireSysEx(0x7) & 0xF0;
        byte += valeur & 0xF;
        EcrireSysEx(0x7, byte);
    break;
    default : return;
    }
}

/*****************************************************************************/
uint Operator::EnvoyerTout()
{
    return MIDI::MIDI_ERREUR_RIEN;
}

uint Operator::RecevoirTout()
{
    return MIDI::MIDI_ERREUR_RIEN;
}

/*****************************************************************************/
uint Operator::Envoyer()
{
    uchar envOperateur[9] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7};
//Construit le message
    envOperateur[3] = MIDI::SysChannel();
    envOperateur[4] = 0x18 + (instru & 0x7);
//Envoi les changements
    for (int i=0; i < OPERATOR_NB_SYSEX; i++)
        if (modif[i]) {
        //Ajoute le contenu
            envOperateur[5] = (i + id * 0x8 + 0x50) & 0x7F;
            envOperateur[6] = sysEx[i*2];
            envOperateur[7] = sysEx[i*2+1];
        //Envoi le message
            uint res = MIDI::EnvSysEx(envOperateur, 9);
            if (res != MIDI::MIDI_ERREUR_RIEN) return res;
            modif[i] = false;
        }
    return MIDI::MIDI_ERREUR_RIEN;
}

/*****************************************************************************/
uchar Operator::LireSysEx(const uchar param)
{
    return (sysEx[param] & 0xF) + (sysEx[param * 2] << 4);
}

void Operator::EcrireSysEx(const uchar param, const uchar valeur)
{
    sysEx[param * 2] = valeur & 0xF;
    sysEx[param * 2 + 1] = valeur >> 4;
    modif[param] = true;
}

