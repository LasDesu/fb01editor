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

#include "set.h"

/*****************************************************************************/
Set::Set()
   : Edit(0, 0, SET_LEN_SYSEX, (uchar *) malloc(SET_LEN_SYSEX))
{
//Initialise la classe
    InitSysEx();
    EcrireNom((char *) "none", false);
//Initialise les instruments
    for (int i=0; i < SET_NB_INSTRU; i++)
        instruments[i] = new Instrument(i, &sysEx[0x29 + 0x10 * i]);
}

Set::~Set()
{
//Libère les instruments
    for (int i=0; i < SET_NB_INSTRU; i++)
        delete instruments[i];
//Libère le sysex
    free(this->sysEx);
}

/*****************************************************************************/
Instrument * Set::RecupererInstrument(int index)
{
    return instruments[index];
}

/*****************************************************************************/
bool Set::Enregistrer(FILE * fichier)
{
//Ecrit le nom
    fread(LireNom(), 1, SET_LEN_NOM, fichier);
//Sauvegarde la table
    if(!Edit::Enregistrer(fichier))
        return false;
//Sauvegarde les instruments
    for (int i = 0; i < SET_NB_INSTRU; i++)
        if (!instruments[i]->Enregistrer(fichier))
            return false;
    return true;
}

bool Set::Charger(FILE * fichier, const short version)
{
    char nom[SET_LEN_NOM];
//Récupère le nom
    fread(nom, 1, SET_LEN_NOM, fichier);
    EcrireNom(nom, false);
//Recupère la table
    if (version == VERSION) {
        if(!Edit::Charger(fichier, version))
            return false;
    }
//Charge le set d'instruments
    for (int i = 0; i < SET_NB_INSTRU; i++)
        if (!instruments[i]->Charger(fichier, version))
            return false;
    return true;
}

/*****************************************************************************/
void Set::Initialiser()
{
    EcrireNom((char *)"none", true);
}

/*****************************************************************************/
uchar Set::LireParam(const uchar param)
{
    switch(param) {
    case SET_LFO_SPEED:
        return LireSysEx(0x9);
    case SET_LFO_WAVE:
        return LireSysEx(0xC) & 0x3;
    case SET_LFO_AMD:
        return LireSysEx(0xA);
    case SET_LFO_PMD:
        return LireSysEx(0xB);
    case SET_COMBINE_MODE:
        return LireSysEx(0x8) & 0x1;
    case SET_RECEPTION_MODE:
        return LireSysEx(0xD) & 0x3;
    default: return 0;
    }
}

void Set::EcrireParam(const uchar param, const uchar valeur, const bool envoi)
{
    switch(param) {
    case SET_LFO_SPEED:
        EcrireSysEx(0x9, valeur & 0x7F, true);
    break;
    case SET_LFO_WAVE:
        EcrireSysEx(0xC, valeur & 0x3, true);
    break;
    case SET_LFO_AMD:
        EcrireSysEx(0xA, valeur & 0x7F, true);
    break;
    case SET_LFO_PMD:
        EcrireSysEx(0xB, valeur & 0x7F, true);
    break;
    case SET_COMBINE_MODE:
        EcrireSysEx(0x8, valeur & 0x1, true);
    break;
    case SET_RECEPTION_MODE:
        EcrireSysEx(0xD, valeur & 0x3, true);
    break;
    default: return;
    }
}

/*****************************************************************************/
char * Set::LireNom()
{
    static char nom[SET_LEN_NOM + 1];
    for (uchar i = 0; i < SET_LEN_NOM; i++)
        nom[i] = (char) LireSysEx(i);
    nom[SET_LEN_NOM] = 0;
    return nom;
}

void Set::EcrireNom(char * nom, const bool envoi)
{
    uchar i = 0;
    int len = min(strlen(nom), SET_LEN_NOM);
    for (; i < len; i++) EcrireSysEx(i, nom[i], envoi);
    for (; i < SET_LEN_NOM; i++) EcrireSysEx(i, ' ', envoi);
}

/*****************************************************************************/
uint Set::EnvoyerTout()
{
    uint res = MIDI::EnvSysEx(sysEx, SET_LEN_SYSEX);
    if (res != MIDI::MIDI_ERREUR_RIEN) return res;
    return MIDI::MIDI_ERREUR_RIEN;
}

uint Set::RecevoirTout()
{
    uchar recSet[] = {0xF0, 0x43, 0x75, 0x00, 0x20, 0x01, 0x00, 0xF7};
//Prépare la demande
    recSet[3] = MIDI::SysChannel();
//Envoi le message
    uint res = MIDI::EnvSysEx(recSet, 8);
    if (res != MIDI::MIDI_ERREUR_RIEN) return res;
//Attend la reception
    return MIDI::RecSysEx(sysEx, SET_LEN_SYSEX);
}

/*****************************************************************************/
void Set::InitSysEx()
{
//Entête de message
    Block::InitSysEx();
    sysEx[0] = 0xF0; sysEx[1] = 0x43;
    sysEx[2] = 0x75; sysEx[3] = 0x00;
    sysEx[4] = 0x00; sysEx[5] = 0x01;
    sysEx[6] = 0x00;
//Taille du message
    sysEx[7] = 0x00; sysEx[8] = 0x00;
//Fin du message
    sysEx[SET_LEN_SYSEX - 1] = 0xF7;
}

/*****************************************************************************/
uchar Set::LireSysEx(const uchar param)
{
    return sysEx[param + 0x9];
}

void Set::EcrireSysEx(const uchar param, const uchar valeur, const bool envoi)
{
    uchar envSet[8] = {0xF0, 0x43, 0x75, 0x00, 0x10, 0x00, 0x00, 0xF7};
//Modifie le sysEx
    sysEx[param + 0x9] = valeur & 0x7F;
//Construit le message
    if (!envoi) return;
    envSet[3] = MIDI::SysChannel();
//Envoi les changements
    envSet[5] = param & 0x7F;
    envSet[6] = valeur & 0x7F;
//Envoi le message
    MIDI::EnvSysEx(envSet, 8);
}
