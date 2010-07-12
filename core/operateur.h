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

#ifndef OPERATOR_H
#define OPERATOR_H

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

class Operateur : public Edit, public Automated {
public :
//Constantes
    #define OPERATOR_NB_PARAM  16
    #define OPERATOR_LEN_SYSEX 0x10
    #define OPERATOR_OFF_PARAM 0x50
//Paramêtres éditables
    typedef enum {
        OPERATOR_VOLUME = 0,
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
    Operateur(const uchar id, uchar * sysEx);
    ~Operateur();
//Association de l'instrument
    void AssocierInstrument(const uint index);
//Edition de l'objet
    void Initialiser();
//Modification des propriétés
    uchar LireParam(const OPERATOR_PARAM param);
    void  EcrireParam(const OPERATOR_PARAM param, const uchar valeur);
//Envoi / Reception de l'objet
    void Envoyer(const uint param);
//Callbacks automation
    void CreerCallbacks();
    void AppelerCallback(const uint index, const uchar valeur);
private :
//Paramêtres globaux
    uchar instru;
};

#endif
