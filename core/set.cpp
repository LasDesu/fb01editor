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
   : Edit(0, (uchar *) malloc(SET_LEN_SYSEX), SET_LEN_SYSEX,
          0, SET_OFF_PARAM, EDIT_OBJ_SET)
{
//Vérifie l'allocation
    if (sysEx == NULL) throw(Memory_ex("Unable to allocate the set sysex !"));
//Initialise la classe
    Initialiser();
    CreerCallbacks();
//Initialise les instruments
    memset(instruments, 0, sizeof(Instrument *) * SET_NB_INSTRU);
    for (int i = 0; i < SET_NB_INSTRU; i++) {
        instruments[i] = new Instrument(i, &sysEx[SET_OFF_INSTRU + INSTRU_LEN_SYSEX * i]);
        if (instruments[i] == NULL) throw Memory_ex("");
    }
    AutoriserEnvoi(true);
}

Set::~Set()
{
//Libère les instruments
    for (int i = 0; i < SET_NB_INSTRU; i++)
        if (instruments[i] != NULL) delete instruments[i];
//Libère le sysex
    if (sysEx != NULL) free(sysEx);
}

/*****************************************************************************/
Instrument * Set::RecupererInstrument(const uint index)
{
    return instruments[index];
}

/*****************************************************************************/
bool Set::Enregistrer(FILE * fichier)
{
//Sauvegarde le nom
    if (fwrite(LireNom(), SET_LEN_NOM, 1, fichier) == 0) return false;
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
    if (fread(nom, SET_LEN_NOM, 1, fichier) == 0) return false;
    EcrireNom(nom);
//Recupère la table
    if (version == VERSION) {
        if (!Edit::Charger(fichier, version))
            return false;
    }
//Charge le set d'instruments
    for (int i = 0; i < SET_NB_INSTRU; i++)
        if (!instruments[i]->Charger(fichier, version))
            return false;
    return true;
}

/*****************************************************************************/
const uchar initTab[SET_NB_PARAM] = {0,};
void Set::Initialiser()
{
    uchar entSet[7] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x01, 0x00};
//Entete du sysEx
    Block::Initialiser(entSet, 7);
    sysEx[7] = 0x00; sysEx[8] = 0x00;
//Paramêtres initiaux
    EcrireNom((char *) "none");
    for (int i = 0; i < SET_NB_PARAM; i++)
        EcrireParam((SET_PARAM) i, initTab[i]);
}

/*****************************************************************************/
uchar Set::LireParam(const SET_PARAM param)
{
    try {
        switch(param) {
        case SET_LFO_SPEED:
            return LireParam1Oct(0x9);
        case SET_LFO_WAVE:
            return LireParam1Oct(0xC) & 0x3;
        case SET_LFO_AMD:
            return LireParam1Oct(0xA);
        case SET_LFO_PMD:
            return LireParam1Oct(0xB);
        case SET_COMBINE_MODE:
            return LireParam1Oct(0x8) & 0x1;
        case SET_RECEPTION_MODE:
            return LireParam1Oct(0xD) & 0x3;
        default: return 0;
        }
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
        return 0;
    }
}

void Set::EcrireParam(const SET_PARAM param, const uchar valeur)
{
    try {
        switch(param) {
        case SET_LFO_SPEED:
            EcrireParam1Oct(0x9, valeur & 0x7F);
        break;
        case SET_LFO_WAVE:
            EcrireParam1Oct(0xC, valeur & 0x3);
        break;
        case SET_LFO_AMD:
            EcrireParam1Oct(0xA, valeur & 0x7F);
        break;
        case SET_LFO_PMD:
            EcrireParam1Oct(0xB, valeur & 0x7F);
        break;
        case SET_COMBINE_MODE:
            EcrireParam1Oct(0x8, valeur & 0x1);
        break;
        case SET_RECEPTION_MODE:
            EcrireParam1Oct(0xD, valeur & 0x3);
        break;
        default: return;
        }
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
    }
}

/*****************************************************************************/
char * Set::LireNom()
{
    static char nom[SET_LEN_NOM + 1];
    try {
        for (uchar i = 0; i < SET_LEN_NOM; i++)
            nom[i] = (char) LireParam1Oct(i);
        nom[SET_LEN_NOM] = 0;
        return nom;
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
        return NULL;
    }
}

void Set::EcrireNom(char * nom)
{
    uchar i;
    try {
        int len = min(strlen(nom), SET_LEN_NOM);
        for (i = 0; i < len; i++)
            EcrireParam1Oct(i, nom[i]);
        for (; i < SET_LEN_NOM; i++)
            EcrireParam1Oct(i, ' ');
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
    }
}

/*****************************************************************************/
void Set::Envoyer(const uint param)
{
    uchar envSet[8] = {0xF0, 0x43, 0x75, 0x00, 0x10, 0x00, 0x00, 0xF7};
//Construit le message
    envSet[3] = MIDI::SysChannel();
//Envoi les changements
    envSet[5] = param & 0x7F;
    envSet[6] = sysEx[param + SET_OFF_PARAM];
//Envoi le message
    MIDI::EnvSysEx(envSet, 8);
}

void Set::EnvoyerTout()
{
    MIDI::EnvSysEx(sysEx, SET_LEN_SYSEX);
}

void Set::RecevoirTout()
{
    uchar recSet[] = {0xF0, 0x43, 0x75, 0x00, 0x20, 0x01, 0x00, 0xF7};
//Prépare la demande
    recSet[3] = MIDI::SysChannel();
//Envoi le message
    MIDI::EnvSysEx(recSet, 8);
//Attend la reception
    MIDI::RecSysEx(sysEx, SET_LEN_SYSEX);
}

/*****************************************************************************/
void Set::CreerCallbacks()
{
    Automation::AjouterCallback(this, SET_LFO_SPEED, "Set LFO Speed");
    Automation::AjouterCallback(this, SET_LFO_WAVE, "Set LFO Waveform");
    Automation::AjouterCallback(this, SET_LFO_AMD, "Set LFO AMD");
    Automation::AjouterCallback(this, SET_LFO_PMD, "Set LFO PMD");
}

void Set::AppelerCallback(const uint index, const uchar valeur)
{
    switch(index) {
    case SET_LFO_SPEED : EcrireParam(SET_LFO_SPEED, valeur); break;
    case SET_LFO_WAVE  : EcrireParam(SET_LFO_WAVE, valeur >> 5); break;
    case SET_LFO_AMD   : EcrireParam(SET_LFO_AMD, valeur); break;
    case SET_LFO_PMD   : EcrireParam(SET_LFO_PMD, valeur); break;
    }
}
