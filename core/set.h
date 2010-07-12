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

#ifndef SET_H
#define SET_H

#include <QMessageBox>

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"
#include "../excep/memory_ex.h"
#include "../excep/midi_ex.h"
#include "../excep/automation_ex.h"

#include "automation.h"
#include "automated.h"
#include "midi.h"
#include "edit.h"
#include "instrument.h"

class Set : public Edit,  public Automated {
public :
//Constantes
    #define SET_NB_PARAM 1
    #define SET_OFF_PARAM 0x9
    #define SET_OFF_INSTRU 0x29
    #define SET_NB_INSTRU 8
    #define SET_LEN_NOM 8
    #define SET_LEN_SYSEX 0xAB
//Paramêtres éditables
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
    Instrument * RecupererInstrument(const uint index);
//Chargement / déchargement
    bool Enregistrer(FILE * fichier);
    bool Charger(FILE * fichier, const short version);
//Edition de l'objet
    void Initialiser();
//Modification des propriétés
    uchar  LireParam(const SET_PARAM param);
    void   EcrireParam(const SET_PARAM param, const uchar valeur);
    char * LireNom();
    void   EcrireNom(char * nom);
//Envoi / Reception de l'objet
    void Envoyer(const uint param);
    void EnvoyerTout();
    void RecevoirTout();
//Callbacks automation
    void CreerCallbacks();
    void AppelerCallback(const uint index, const uchar valeur);
private :
//Instruments du set
    Instrument * instruments[SET_NB_INSTRU];
};

#endif
