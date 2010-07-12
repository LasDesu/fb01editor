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
Bank::Bank(const uchar id)
    : Edit(id, (uchar *) malloc(BANK_LEN_SYSEX), BANK_LEN_SYSEX,
           0, 0, EDIT_OBJ_BANK)
{
//Initialise la classe
    if (sysEx == NULL) throw (Memory_ex("Unable to allocate the bank sysex !"));
    Initialiser();
//Initialise les voices
    memset(voices, 0, sizeof(Bank_voice *) * BANK_NB_VOICES);
    for (int i = 0; i < BANK_NB_VOICES; i ++) {
        voices[i] = new Bank_voice(i, &sysEx[BANK_OFF_VOICES + i * BANKVOICE_LEN_SYSEX]);
        if (voices[i] == NULL) throw Memory_ex("Unable to allocate the voices of banks !");
    }
    AutoriserEnvoi(true);
}

Bank::~Bank()
{
//Libère les voices
    for (int i = 0; i < BANK_NB_VOICES; i ++)
        if (voices[i] != NULL) delete voices[i];
//Libère le sysex
    if (sysEx != NULL) free(sysEx);
}

/*****************************************************************************/
bool Bank::Enregistrer(FILE * fichier)
{
//Sauvegarde le nom
    if (fwrite(LireNom(), BANK_LEN_NOM, 1, fichier) == 0) return false;
//Sauvegarde les voices
    for (int i = 0; i < BANK_NB_VOICES; i++)
        if (!voices[i]->Enregistrer(fichier))
            return false;
    return true;
}

bool Bank::Charger(FILE * fichier, const short version)
{
    char nom[BANK_LEN_NOM];
//Récupère le nom
    if (fread(nom, BANK_LEN_NOM, 1, fichier) == 0) return false;
    EcrireNom(nom);
//Récupère les voices
    for (int i = 0; i < BANK_NB_VOICES; i++)
        if (!voices[i]->Charger(fichier, version))
            return false;
    return true;
}

/*****************************************************************************/
Bank_voice * Bank::RecupererVoice(const uint index)
{
    return voices[index];
}

/*****************************************************************************/
void Bank::EnvoyerTout()
{
    MIDI::EnvSysEx(sysEx, BANK_LEN_SYSEX);
}

void Bank::RecevoirTout()
{
    uchar recBank[] = {0xF0, 0x43, 0x75, 0x00, 0x20, 0x00, 0x00, 0xF7};
//Prépare la demande
    recBank[3] = MIDI::SysChannel();
    recBank[6] = id & 0x7;
//Envoi le message
    MIDI::EnvSysEx(recBank, 8);
//Attend la réception
    MIDI::RecSysEx(sysEx, BANK_LEN_SYSEX);
}

/*****************************************************************************/
void Bank::Initialiser()
{
    uchar entBank[7] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x00, 0x00};
//Entete du sysEx
    Block::Initialiser(entBank, 7);
    sysEx[7] = 0x00; sysEx[8] = 0x40;
    for (uint i = 0; i < 48; i++) {
        sysEx[BANK_OFF_VOICES - 2 + i * BANKVOICE_LEN_SYSEX] = 0x00;
        sysEx[BANK_OFF_VOICES - 1 + i * BANKVOICE_LEN_SYSEX] = 0x40;
    }
//Nom de la bank
    EcrireNom((char *) "none");
}

/*****************************************************************************/
char * Bank::LireNom()
{
    static char nom[BANK_LEN_NOM + 1];
    try {
        for (uchar i = 0; i < BANK_LEN_NOM; i++)
            nom[i] = (char) LireParam2Oct(i);
        nom[BANK_LEN_NOM] = 0;
        return nom;
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
        return NULL;
    }
}

void Bank::EcrireNom(char * nom)
{
    uchar i;
    try {
        int len = min(strlen(nom), BANK_LEN_NOM);
        for (i = 0; i < len; i++)
            EcrireParam1Oct(i, nom[i]);
        for (; i < BANK_LEN_NOM; i++)
            EcrireParam1Oct(i, ' ');
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
    }
}

