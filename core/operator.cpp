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
Operator::Operator(const uchar id)
{
    this->id = id;
    InitialiserSysEx();
}

Operator::~Operator()
{
}

/*****************************************************************************/
bool Operator::Enregistrer(FILE * fichier)
{
    uchar sauv[OPERATOR_NB_PARAM];
//Créé la table de paramêtres
    for (int i=0; i < OPERATOR_NB_PARAM; i++)
        sauv[i] = LireParam(i);
//Sauvegarde la table
    fwrite(sauv, OPERATOR_NB_PARAM, 1, fichier);
    return true;
}

bool Operator::Charger(FILE * fichier, const int version)
{
//Charge la table
    uchar sauv[OPERATOR_NB_PARAM];
    if (fread(sauv, OPERATOR_NB_PARAM, 1, fichier))
        return false;
//Récupère les paramêtres
    for (int i=0; i < OPERATOR_NB_PARAM; i++)
        EcrireParam(i, sauv[i]);
    return true;
}

/*****************************************************************************/
const uchar initTab[OPERATOR_NB_PARAM] = {127, 0, 0, 0, 0, 0, 0, 0, 31, 1, 0, 31, 0, 0, 15, 15};
void Operator::Initialiser()
{
    for (int i=0; i < OPERATOR_NB_PARAM; i++)
        EcrireParam(i, initTab[i]);
}

void Operator::Randomiser()
{
    for (int i=0; i < OPERATOR_NB_PARAM; i++)
        EcrireParam(i, RAND(0, 255));
}

void Operator::Copier(uchar * table, const ulong len)
{
    if (len < OPERATOR_LEN_SYSEX) return;
    memcpy(table, sysEx, OPERATOR_LEN_SYSEX);
}

void Operator::Coller(const uchar * table, const ulong len)
{
    if (len < OPERATOR_LEN_SYSEX) return;
    memcpy(sysEx, table, OPERATOR_LEN_SYSEX);
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
void Operator::InitialiserSysEx()
{
    memset(sysEx, OPERATOR_LEN_SYSEX, 0);
}

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

void Operator::CheckSumSysEx()
{
    uchar sum;
    for(int i = 0; i < OPERATOR_LEN_SYSEX - 1; i ++)
        sum += sysEx[i];
    sysEx[OPERATOR_LEN_SYSEX - 1] = (~sum) + 1;
}

/*****************************************************************************/
void Operator::Envoyer()
{
    for (int i = 0; i < OPERATOR_NB_SYSEX; i++)
        if (modif[i]) {
        }
}
