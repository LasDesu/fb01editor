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

#include "config.h"

/*****************************************************************************/
Config::Config()
    : Edit(0,0,0, NULL)
{
}

Config::~Config()
{
}

/*****************************************************************************/
uchar Config::LireParam(const uchar param)
{
    return 0;
}

void Config::EcrireParam(const uchar param, const uchar valeur, const bool envoi)
{
    return;
}

/*****************************************************************************/
uint Config::EnvoyerTout()
{
    return MIDI::MIDI_ERREUR_RIEN;
}

uint Config::RecevoirTout()
{
    return MIDI::MIDI_ERREUR_RIEN;
}

/*****************************************************************************/
void Config::InitSysEx()
{

}

/*****************************************************************************/
uchar Config::LireSysEx(const uchar param)
{
    return 0;
}

void Config::EcrireSysEx(const uchar param, const uchar valeur, const bool envoi)
{
    return;
}
