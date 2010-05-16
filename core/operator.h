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

#ifndef OPERATOR_H
#define OPERATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"

class Operator {
public :
//Paramêtres éditables
    #define OPERATOR_NB_PARAM 16
    typedef enum {
        OPERATOR_LEVEL = 0,
        OPERATOR_LEVEL_CURB,
        OPERATOR_LEVEL_VELOCITY,
        OPERATOR_LEVEL_DEPTH,
        OPERATOR_ADJUST,
        OPERATOR_FINE,
        OPERATOR_MULTIPLE,
        OPERATOR_RATE_DEPTH,
        OPERATOR_ATTACK,
        OPERATOR_MODULATOR,
        OPERATOR_ATTACK_VELOCITY,
        OPERATOR_DECAY1,
        OPERATOR_COARSE,
        OPERATOR_DECAY2,
        OPERATOR_SUSTAIN,
        OPERATOR_RELEASE
    }OPERATOR_PARAM;
//Constructeurs
    Operator(const uchar id);
    ~Operator();
//Chargement / déchargement
    bool Enregistrer(FILE * fichier);
    bool Charger(FILE * fichier, const int version);
//Edition de l'opérateur
    void Initialiser();
    void Randomiser();
    void Copier(uchar * table, const ulong len);
    void Coller(const uchar * table, const ulong len);
//Lien avec interface
    uchar LireParam(const uchar param);
    void EcrireParam(const uchar param, const uchar valeur);
//Communication MIDI
    void Envoyer();
private :
//Messages SysEx
    #define OPERATOR_LEN_SYSEX 17
    #define OPERATOR_NB_SYSEX  8
    uchar sysEx[OPERATOR_LEN_SYSEX];
    bool  modif[OPERATOR_NB_SYSEX];
//Association opérateur
    uchar id;
//Gestion des SysEx
    void  InitialiserSysEx();
    uchar LireSysEx(const uchar param);
    void  EcrireSysEx(const uchar param, const uchar valeur);
    void  CheckSumSysEx();
};

#endif
