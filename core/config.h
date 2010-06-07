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

#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"
#include "edit.h"
#include "midi.h"

/*****************************************************************************/
class Config : public Edit {
public :
//Paramêtres éditables
    #define CONFIG_NB_PARAM 4
    typedef enum {
        CONFIG_SYSCHANNEL = 0,
        CONFIG_MEMORY_PROTECT,
        CONFIG_CONFIG_NUMBER,
        CONFIG_DETUNE,
        CONFIG_MASTER_VOLUME
    }CONFIG_PARAM;
//Constructeurs
    Config();
    ~Config();
//Modification des propriétés
    uchar LireParam(const uchar param);
    void  EcrireParam(const uchar param, const uchar valeur, const bool envoi);
//Envoi / Reception de l'objet
    uint EnvoyerTout();
    uint RecevoirTout();
private :
//Ecriture et lecture
    #define CONFIG_LEN_SYSEX 0
    uchar LireSysEx(const uchar param);
    void  EcrireSysEx(const uchar param, const uchar valeur, const bool envoi);
};

#endif
