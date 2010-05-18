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
Voice::Voice(const uchar instru)
{
//Initialise les propriétés
    this->id = instru;
    this->nbParam  = VOICE_NB_PARAM;
    this->lenSysEx = VOICE_LEN_SYSEX;
    this->nbSysEx  = VOICE_NB_SYSEX;
//Initialise le sysEx
    this->sysEx = (uchar *) malloc(VOICE_LEN_SYSEX);
    this->modif = (bool *)  malloc(VOICE_NB_SYSEX);
    InitSysEx();
//Initialise les opérateurs
    for (int i=0; i < VOICE_NB_OPS; i++)
        operateurs[i] = new Operateur(instru, i, &sysEx[0x29 + 0x10 * i], &modif[0x10 + 0x8 * i]);
}

Voice::~Voice()
{
//Libère les opérateurs
    for (int i=0; i < 4; i++)
        delete operateurs[i];
//Libère le sysex
    free(this->sysEx);
    free(this->modif);
}

/*****************************************************************************/
bool Voice::Enregistrer(FILE * fichier)
{
//Sauvegarde des informations
    fwrite(auteur, VOICE_LEN_AUTEUR, 1, fichier);
    fwrite(comment, VOICE_LEN_COMMENT, 1, fichier);
    fwrite(nom, VOICE_LEN_NOM, 1, fichier);
//Sauvegarde la table
    if (!Block::Enregistrer(fichier)) return false;
//Sauvegarde les opérateurs
    for (int i=0; i < VOICE_NB_OPS; i ++)
        if (!operateurs[i]->Enregistrer(fichier))
            return false;
    return true;
}

bool Voice::Charger(FILE * fichier, const int version)
{
//Récupère des informations
    fread(auteur, VOICE_LEN_AUTEUR, 1, fichier);
    fread(comment, VOICE_LEN_COMMENT, 1, fichier);
    fread(nom, VOICE_LEN_NOM, 1, fichier);
//Récupère la table
    if (!Block::Charger(fichier, version)) return false;
//Récupère les opérateurs
    for (int i=0; i < VOICE_NB_OPS; i ++)
        if (!operateurs[i]->Charger(fichier, version))
            return false;
    return true;
}

/*****************************************************************************/
const uchar initTab[16] = {8, 0, 0, 0, 1, 0, 4, 1, 127, 0, 0, 1, 0, 0, 0, 0};
void Voice::Initialiser()
{
    EcrireNom((char *) "none");
    for (int i=0; i < VOICE_NB_PARAM; i++)
        EcrireParam(i, initTab[i]);
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
    default : return 0;
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
char * Voice::LireNom()
{
    static char nom[VOICE_LEN_NOM + 1];
    for (uchar i = 0; i < VOICE_LEN_NOM; i++)
        nom[i] = (char) LireSysEx(i);
    nom[VOICE_LEN_NOM] = 0;
    return nom;
}

void Voice::EcrireNom(char * nom)
{
    uchar i = 0;
    int len = min(strlen(nom), VOICE_LEN_NOM);
    for (; i < len; i++) EcrireSysEx(i, nom[i]);
    for (; i < VOICE_LEN_NOM; i++) EcrireSysEx(i, ' ');
}

/*****************************************************************************/
uint Voice::EnvoyerTout()
{
    uint res = MIDI::EnvSysEx(sysEx, VOICE_LEN_SYSEX);
    if (res != MIDI::MIDI_ERREUR_RIEN) return res;
    memset(modif, 0, VOICE_NB_SYSEX);
    return MIDI::MIDI_ERREUR_RIEN;
}

uint Voice::RecevoirTout()
{
    uchar recVoice[8] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x00, 0x00, 0xF7};
//Prépare la demande
    recVoice[3] = MIDI::SysChannel();
    recVoice[4] = 0x20 + ((id + 0x8) & 0xF);
//Envoi le message
    uint res = MIDI::EnvSysEx(recVoice, 8);
    if (res != MIDI::MIDI_ERREUR_RIEN) return res;
//Attend la reception
    return MIDI::RecSysEx(sysEx, VOICE_LEN_SYSEX);
}

/*****************************************************************************/
uint Voice::Envoyer()
{
    uchar envVoice[9] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7};
//Construit le message
    envVoice[3] = MIDI::SysChannel();
    envVoice[4] = 0x18 + (id & 0x7);
//Envoi les changements
    for (int i=0; i < VOICE_NB_SYSEX; i++)
        if (modif[i]) {
        //Ajoute le contenu
            envVoice[5] = (i + 0x40) & 0x7F;
            envVoice[6] = sysEx[i*2];
            envVoice[7] = sysEx[i*2+1];
        //Envoi le message
            uint res = MIDI::EnvSysEx(envVoice, 9);
            if (res != MIDI::MIDI_ERREUR_RIEN) return res;
            modif[i] = false;
        }
    return MIDI::MIDI_ERREUR_RIEN;
}

/*****************************************************************************/
void Voice::InitSysEx()
{
//Entête de message
    Block::InitSysEx();
    sysEx[0] = 0xF0; sysEx[1] = 0x43;
    sysEx[2] = 0x75; sysEx[3] = 0x00;
    sysEx[4] = 0x08; sysEx[5] = 0x00;
    sysEx[6] = 0x00;
//Taille du message
    sysEx[7] = 0x00; sysEx[8] = 0x00;
//Fin du message
    sysEx[VOICE_LEN_SYSEX - 1] = 0xF7;
}

/*****************************************************************************/
uchar Voice::LireSysEx(const uchar param)
{
    return (sysEx[param + 0x9] & 0xF) + (sysEx[param * 2 + 0x9] << 4);
}

void Voice::EcrireSysEx(const uchar param, const uchar valeur)
{
    sysEx[param * 2 + 0x9] = valeur & 0xF;
    sysEx[param * 2 + 0xA] = valeur >> 4;
    modif[param] = true;
}

