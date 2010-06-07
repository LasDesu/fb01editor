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

#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"
#include "edit.h"
#include "instrument.h"
#include "midi.h"

class Set : public Edit {
public :
//Paramêtres éditables
    #define SET_NB_PARAM 0
    #define SET_LEN_NOM 8
    typedef enum {
        SET_LFO_SPEED = 0,
        SET_LFO_WAVE,
        SET_LFO_AMD,
        SET_LFO_PMD,
        SET_COMBINE_MODE,
        SET_RECEPTION_MODE
    }SET_PARAM;
//Constructeurs
    Set();
    ~Set();
//Récupération des objets
    Instrument * RecupererInstrument(int index);
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
    uint EnvoyerTout();
    uint RecevoirTout();
private :
//Instruments du set
    #define SET_NB_INSTRU 8
    Instrument * instruments[SET_NB_INSTRU];
//Gestion des messages sysExs
    #define SET_LEN_SYSEX 171
    void  InitSysEx();
    uchar LireSysEx(const uchar param);
    void  EcrireSysEx(const uchar param, const uchar valeur, const bool envoi);
};

#endif
