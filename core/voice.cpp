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

#include "voice.h"

/*****************************************************************************/
Voice::Voice()
{
    for (int i=0; i < 4; i++)
        operators[i] = new Operator(i);
    InitialiserSysEx();
}

Voice::~Voice()
{
    for (int i=0; i < 4; i++)
        delete operators[i];
}

/*****************************************************************************/
bool Voice::Enregistrer(FILE * fichier)
{
    uchar sauv[VOICE_NB_PARAM];
//Créé la table de paramêtres
    for (int i=0; i < VOICE_NB_PARAM; i++)
        sauv[i] = LireParam(i);
//Sauvegarde des informations
    fwrite(auteur, VOICE_LEN_AUTEUR, 1, fichier);
    fwrite(comment, VOICE_LEN_COMMENT, 1, fichier);
    fwrite(nom, VOICE_LEN_NOM, 1, fichier);
//Sauvegarde la table
    fwrite(sauv, OPERATOR_NB_PARAM, 1, fichier);
    return true;
}

bool Voice::Charger(FILE * fichier, const int version)
{
//Charge la table
    uchar sauv[OPERATOR_NB_PARAM];
    if (fread(sauv, VOICE_NB_PARAM, 1, fichier))
        return false;
//Récupère des informations
    fread(auteur, VOICE_LEN_AUTEUR, 1, fichier);
    fread(comment, VOICE_LEN_COMMENT, 1, fichier);
    fread(nom, VOICE_LEN_NOM, 1, fichier);
//Récupère les paramêtres
    for (int i=0; i < VOICE_NB_PARAM; i++)
        EcrireParam(i, sauv[i]);
    return true;
}

/*****************************************************************************/
bool Voice::EnregistrerSysEx(FILE * fichier)
{
//Exporte le sysex

}

bool Voice::ChargerSysEx(FILE * fichier)
{
}

/*****************************************************************************/
const uchar InitTab[16] = {8, 0, 0, 0, 1, 0, 4, 1, 127, 0, 0, 1, 0, 0, 0, 0};
void Voice::Initialiser()
{
    for (int i=0; i < VOICE_NB_PARAM; i++)
        EcrireParam(i, initTab[i]);
}

void Voice::Randomiser()
{
    for (int i=0; i < VOICE_NB_PARAM; i++)
        EcrireParam(i, RAND(0, 255));
}

void Voice::Copier(uchar * table, ulong len)
{
    if (len < VOICE_LEN_SYSEX) return;
    memcpy(table, sysEx, VOICE_LEN_SYSEX);
}

void Voice::Coller(const uchar * table, ulong len)
{
    if (len < VOICE_LEN_SYSEX) return;
    memcpy(sysEx, table, VOICE_LEN_SYSEX);
}

/*****************************************************************************/
uchar Voice::LireParam(const uchar param)
{
    switch(param) {
    case VOICE_ALGORITHME :
        return LireSysEx(0xC) & 0x7;
    case VOICE_USERCODE :
        return LireSysEx(0x7);
    case VOICE_FEEDBACK :
        return LireSysEx(0xC) & 0x38;
    case VOICE_TRANSPOSE :
        return LireSysEx(0xF);
    case VOICE_POLY :
        return (LireSysEx(0x3A) >> 7) & 0x1;
    case VOICE_PORTAMENTO :
        return LireSysEx(0x3A) & 0x7F;
    case VOICE_PITCHBEND :
        return LireSysEx(0x3B) & 0xF;
    case VOICE_CONTROLLER :
        return (LireSysEx(0x3B) >> 4) & 0x7 ;
    case VOICE_LFO_SPEED :
        return LireSysEx(0x8);
    case VOICE_LFO_WAVE :
        return (LireSysEx(0xE) >> 5) & 0x3;
    case VOICE_LFO_LOAD :
        return (LireSysEx(0x9) >> 7) & 0x1;
    case VOICE_LFO_SYNC :
        return (LireSysEx(0xA) >> 7) & 0x1;
    case VOICE_LFO_AMD :
        return LireSysEx(0x9) & 0x7F;
    case VOICE_LFO_AMS :
        return LireSysEx(0xD) & 0x3;
    case VOICE_LFO_PMD :
        return LireSysEx(0xA) & 0x7F;
    case VOICE_LFO_PMS :
        return (LireSysEx(0xD) >> 4) & 0x7;
    case VOICE_ENABLE_OP4 :
        return (LireSysEx(0xB) >> 3) & 0x1;
    case VOICE_ENABLE_OP3 :
        return (LireSysEx(0xB) >> 4) & 0x1;
    case VOICE_ENABLE_OP2 :
        return (LireSysEx(0xB) >> 5) & 0x1;
    case VOICE_ENABLE_OP1 :
        return (LireSysEx(0xB) >> 6) & 0x1;
    default : return;
    }
}

void Voice::EcrireParam(uchar param, uchar valeur)
{
    uchar byte;
    switch(param) {
    case VOICE_ALGORITHME :
        byte  = LireSysEx(0xC) & 0xF8;
        byte += valeur & 0x7;
        EcrireSysEx(0xC, byte);
    break;
    case VOICE_USERCODE :
        EcrireSysEx(0x7, valeur);
    break;
    case VOICE_FEEDBACK :
        byte  = LireSysEx(0xC) & 0xC7;
        byte += valeur & 0x7;
        EcrireSysEx(0xC, byte);
    break;
    case VOICE_TRANSPOSE :
        EcrireSysEx(0xF, valeur);
    break;
    case VOICE_POLY :
        byte  = LireSysEx(0x3A) & 0x7F;
        byte += (valeur & 0x1) << 7;
        EcrireSysEx(0x3A, byte);
    break;
    case VOICE_PORTAMENTO :
        byte  = LireSysEx(0x3A) & 0x80;
        byte += valeur & 0x7F;
        EcrireSysEx(0x3A, byte);
    break;
    case VOICE_PITCHBEND :
        byte  = LireSysEx(0x3B) & 0xF0;
        byte += valeur & 0xF;
        EcrireSysEx(0x3B, byte);
    break;
    case VOICE_CONTROLLER :
        byte  = LireSysEx(0x3B) & 0x8F;
        byte += (valeur & 0x7) << 4;
        EcrireSysEx(0x3B, byte);
    break;
    case VOICE_LFO_SPEED :
        EcrireSysEx(0x8, valeur);
    break;
    case VOICE_LFO_WAVE :
        byte  = LireSysEx(0xE) & 0x9F;
        byte += (valeur & 0x3) << 5;
        EcrireSysEx(0xE, byte);
    break;
    case VOICE_LFO_LOAD :
        byte  = LireSysEx(0x9) & 0x7F;
        byte += (valeur & 0x1) << 7;
        EcrireSysEx(0x9, byte);
    break;
    case VOICE_LFO_SYNC :
        byte  = LireSysEx(0xA) & 0x7F;
        byte += (valeur & 0x1) << 7;
        EcrireSysEx(0xA, byte);
    break;
    case VOICE_LFO_AMD :
        byte  = LireSysEx(0x9) & 0x80;
        byte += valeur & 0x7F;
        EcrireSysEx(0x9, byte);
    break;
    case VOICE_LFO_AMS :
        byte  = LireSysEx(0xD) & 0xFC;
        byte += valeur & 0x3;
        EcrireSysEx(0xD, byte);
    break;
    case VOICE_LFO_PMD :
        byte  = LireSysEx(0xA) & 0x80;
        byte += valeur & 0x7F;
        EcrireSysEx(0xA, byte);
    break;
    case VOICE_LFO_PMS :
        byte  = LireSysEx(0xD) & 0x8F;
        byte += (valeur & 0x7) << 4;
        EcrireSysEx(0xD, byte);
    break;
    case VOICE_ENABLE_OP4 :
        byte  = LireSysEx(0xB) & 0xF7;
        byte += (valeur & 0x1) << 3;
        EcrireSysEx(0xB, byte);
    case VOICE_ENABLE_OP3 :
        byte  = LireSysEx(0xB) & 0xEF;
        byte += (valeur & 0x1) << 4;
        EcrireSysEx(0xB, byte);
    case VOICE_ENABLE_OP2 :
        byte  = LireSysEx(0xB) & 0xDF;
        byte += (valeur & 0x1) << 5;
        EcrireSysEx(0xB, byte);
    case VOICE_ENABLE_OP1 :
        byte  = LireSysEx(0xB) & 0xBF;
        byte += (valeur & 0x1) << 6;
        EcrireSysEx(0xB, byte);
    default : return;
    }
}

/*****************************************************************************/
void Voice::EnvoyerTout(uchar index)
{
}

void Voice::RecevoirTout(uchar index)
{
}

void Voice::Envoyer(uchar index)
{
}

/*****************************************************************************/
void Voice::InitialiserSysEx()
{
    memset(sysEx, VOICE_LEN_SYSEX, 0);
//Entête de message
    sysEx[0] = 0xF0; sysEx[1] = 0x43;
    sysEx[2] = 0x75; sysEx[3] = 0x00;
    sysEx[4] = 0x08; sysEx[5] = 0x00;
    sysEx[6] = 0x00;
//Taille du message
    sysEx[7] = 0x00; sysEx[8] = 0x00;
//Fin du message
    sysEx[VOICE_LEN_SYSEX - 1] = 0xF7;
}

uchar Operator::LireSysEx(const uchar param)
{
    return (sysEx[param + 9] & 0xF) + (sysEx[param * 2 + 9] << 4);
}

void Operator::EcrireSysEx(const uchar param, const uchar valeur)
{
    sysEx[param * 2 + 9]  = valeur & 0xF;
    sysEx[param * 2 + 10] = valeur >> 4;
    modif[param] = true;
}

void Operator::CheckSumSysEx()
{
    uchar sum;
    for(int i = 7; i < VOICE_LEN_SYSEX - 2; i ++)
        sum += sysEx[i];
    sysEx[OPERATOR_LEN_SYSEX - 2] = (~sum) + 1;
}

