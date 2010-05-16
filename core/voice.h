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

#include <stdlib.h>
#include <stdio.h>

#include "../types.h"
#include "operator.h"

class Voice {
public :
//Paramêtres éditables
    #define VOICE_NB_PARAM 20
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
//Chargement / déchargement
    bool Enregistrer(FILE * fichier);
    bool Charger(FILE * fichier, const int version);
    bool EnregistrerSysEx(FILE * fichier);
    bool ChargerSysEx(FILE * fichier);
//Edition de l'opérateur
    void Initialiser();
    void Randomiser();
    void Copier(uchar * table, ulong len);
    void Coller(const uchar * table, ulong len);
//Lien avec interface
    uchar LireParam(uchar param);
    void  EcrireParam(uchar param, uchar valeur);
//Communication MIDI
    void EnvoyerTout();
    void RecevoirTout();
    void Envoyer();
private :
//Messages SysEx
    #define VOICE_LEN_SYSEX 40
    uchar sysEx[VOICE_LEN_SYSEX];
    bool modifs[VOICE_LEN_SYSEX];
//Opérateurs
    #define VOICE_NB_OPS 4
    Operator * operators[VOICE_NB_OPS];
//Gestion des sysExs
    void  InitialiserSysEx();
    uchar LireSysEx(const uchar param);
    void  EcrireSysEx(const uchar param, const uchar valeur);
    void  CalculerCheckSum();
};

#endif
