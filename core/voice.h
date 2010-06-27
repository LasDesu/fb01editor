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

#ifndef VOICE_H
#define VOICE_H

#include <QMessageBox>

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"
#include "../excep/memory_ex.h"

#include "edit.h"
#include "operateur.h"
#include "midi.h"

class Voice : public Edit {
public :
//Constantes
    #define VOICE_LEN_SYSEX 139
    #define VOICE_NB_PARAM  20
    #define VOICE_OFF_PARAM 0x9
    #define VOICE_NB_OPS 4
    #define VOICE_LEN_AUTEUR 129
    #define VOICE_LEN_COMMENT 129
    #define VOICE_LEN_NOM 7
//Paramêtres éditables
    typedef enum {
        VOICE_ALGORITHME = 0,
        VOICE_USERCODE,
        VOICE_FEEDBACK,
        VOICE_TRANSPOSE,
        VOICE_POLY,
        VOICE_PORTAMENTO,
        VOICE_PITCHBEND,
        VOICE_CONTROLLER,
        VOICE_LFO_SPEED,
        VOICE_LFO_WAVE,
        VOICE_LFO_LOAD,
        VOICE_LFO_SYNC,
        VOICE_LFO_AMD,
        VOICE_LFO_AMS,
        VOICE_LFO_PMD,
        VOICE_LFO_PMS,
        VOICE_ENABLE_OP1,
        VOICE_ENABLE_OP2,
        VOICE_ENABLE_OP3,
        VOICE_ENABLE_OP4,
    }VOICE_PARAM;
//Constructeurs
    Voice();
    ~Voice();
//Récupération des objets
    Operateur * RecupererOP(int index);
//Association de l'instrument
    void AssocierInstrument(int index);
//Chargement / déchargement
    bool Enregistrer(FILE * fichier);
    bool Charger(FILE * fichier, const short version);
//Edition de l'objet
    void Initialiser();
//Modification des propriétés
    uchar  LireParam(const uchar param);
    void   EcrireParam(const uchar param, const uchar valeur, const bool envoi);
    char * LireNom();
    void   EcrireNom(char * nom, const bool envoi);
//Envoi / Reception de l'objet
    void Envoyer(const uint param);
    void EnvoyerTout();
    void RecevoirTout();
private :
//Opérateurs intégrés
    Operateur * operateurs[VOICE_NB_OPS];
//Paramêtres spéciaux
    char auteur[VOICE_LEN_AUTEUR];
    char comment[VOICE_LEN_COMMENT];
    char nom[VOICE_LEN_NOM];
};

#endif
