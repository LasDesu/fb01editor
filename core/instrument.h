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

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QMessageBox>

#include <stdlib.h>
#include <stdio.h>

#include "../types.h"
#include "../excep/memory_ex.h"
#include "../excep/midi_ex.h"
#include "../excep/automation_ex.h"

#include "automation.h"
#include "automated.h"
#include "midi.h"
#include "edit.h"


class Instrument : public Edit, public Automated {
public :
//Constantes
    #define INSTRU_NB_PARAM 15
    #define INSTRU_LEN_SYSEX 32
//Paramêtres éditables
typedef enum {
        INSTRU_NB_NOTES = 0,
        INSTRU_CHANNEL,
        INSTRU_UPPER,
        INSTRU_LOWER,
        INSTRU_BANK,
        INSTRU_VOICE,
        INSTRU_DETUNE,
        INSTRU_TRANS,
        INSTRU_VOLUME,
        INSTRU_PAN,
        INSTRU_LFO,
        INSTRU_PORTAMENTO,
        INSTRU_PITCHBEND,
        INSTRU_POLY,
        INSTRU_CONROLLER
    }INSTRU_PARAM;
//Constructeurs
    Instrument(const uchar id, uchar * sysEx);
    ~Instrument();
//Edition de l'objet
    void Initialiser();
//Modification des propriétés
    uchar LireParam(const INSTRU_PARAM param);
    void  EcrireParam(const INSTRU_PARAM param, const uchar valeur, const bool envoi);
//Envoi / Reception de l'objet
    void Envoyer(const uint param);
//Callbacks automation
    void CreerCallbacks();
    void AppelerCallback(const uint index, const uchar valeur);
};

#endif
