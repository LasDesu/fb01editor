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

#ifndef BANK_H
#define BANK_H

#include <QMessageBox>

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"
#include "../excep/memory_ex.h"
#include "../excep/midi_ex.h"

#include "midi.h"
#include "edit.h"
#include "bank_voice.h"

class Bank : public Edit {
public :
//Paramêtres éditables
    #define BANK_LEN_NOM    8
    #define BANK_LEN_SYSEX  0x18DB
    #define BANK_NB_VOICES  48
    #define BANK_OFF_NOM    0x9
    #define BANK_OFF_VOICES 0x4C
//Constructeurs
    Bank(const uchar id);
    ~Bank();
//Récupèration des voices
    Bank_voice * RecupererVoice(const uint index);
//Modification des parametres
    char * LireNom();
    void   EcrireNom(char * nom);
//Chargement / déchargement
    bool Enregistrer(FILE * fichier);
    bool Charger(FILE * fichier, const short version);
//Edition de l'objet
    void Initialiser();
//Envoi / Reception de l'objet
    void EnvoyerTout();
    void RecevoirTout();
private :
//Voices de la bank
    Bank_voice * voices[BANK_NB_VOICES];
};

#endif
