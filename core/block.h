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

#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>
#include <strings.h>

#include "../types.h"

class Block {
public :
//Constructeurs
    Block(const uchar nbParam, const uchar lenSysEx, uchar * sysEx);
    ~Block();
//Modification des propriétés
    virtual uchar LireParam(const uchar param) = 0;
    virtual void  EcrireParam(const uchar param, const uchar valeur, const bool envoi) = 0;
//Envoi / Reception de l'objet
    virtual uint EnvoyerTout() = 0;
    virtual uint RecevoirTout() = 0;
protected :
//Paramêtres sysEx
    uchar * sysEx;
    uint lenSysEx;
    uchar nbParam;
//Utilitaires SysEx
    virtual void InitSysEx();
    virtual void CheckSumSysEx();
//Ecriture et lecture
    virtual uchar LireSysEx(const uchar param) = 0;
    virtual void  EcrireSysEx(const uchar param, const uchar valeur, const bool envoi) = 0;
};

#endif
