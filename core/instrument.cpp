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

#include "instrument.h"

/*****************************************************************************/
Instrument::Instrument(const uchar id, uchar * sysEx, bool * modif)
{
//Initialise les propriétés
    this->id       = id;
    this->nbParam  = INSTRU_NB_PARAM;
    this->lenSysEx = INSTRU_LEN_SYSEX;
    this->nbSysEx  = INSTRU_NB_SYSEX;
//Initialise le sysEx
    this->sysEx = sysEx;
    this->modif = modif;
    InitSysEx();
}

Instrument::~Instrument()
{
}

/*****************************************************************************/
const uchar initTab[INSTRU_NB_PARAM] = {0,};
void Instrument::Initialiser()
{
    for (int i=0; i < INSTRU_NB_PARAM; i++)
        EcrireParam(i, initTab[i]);
}

/*****************************************************************************/
uchar Instrument::LireParam(const uchar param)
{

}

void Instrument::EcrireParam(const uchar param, const uchar valeur)
{

}

/*****************************************************************************/
uint Instrument::EnvoyerTout()
{
    return 0;
}

uint Instrument::RecevoirTout()
{
    return 0;
}

/*****************************************************************************/
uint Instrument::Envoyer()
{

}

/*****************************************************************************/
void Instrument::InitSysEx()
{
//Entête de message
    Object::InitSysEx();
}

/*****************************************************************************/
uchar Instrument::LireSysEx(const uchar param)
{
    return 0;
}

void Instrument::EcrireSysEx(const uchar param, const uchar valeur)
{
}

