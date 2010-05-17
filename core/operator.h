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
#include "object.h"
#include "midi.h"

class Operator : public Object {
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
    Operator(const uchar instru, const uchar id, uchar * sysEx, bool * modif);
    ~Operator();
//Edition de l'objet
    void Initialiser();
//Modification des propriétés
    virtual uchar LireParam(const uchar param);
    virtual void  EcrireParam(const uchar param, const uchar valeur);
//Envoi / Reception de l'objet
    virtual uint Envoyer();
    virtual uint EnvoyerTout();
    virtual uint RecevoirTout();
private :
//Messages SysEx
    #define OPERATOR_LEN_SYSEX 16
    #define OPERATOR_NB_SYSEX  8
//Paramêtres globaux
    uchar instru;
//Gestion des SysEx
    virtual uchar LireSysEx(const uchar param);
    virtual void  EcrireSysEx(const uchar param, const uchar valeur);
};

#endif
