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
       : Edit(0,CONFIG_NB_PARAM, 0, NULL)
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
    switch(param) {
    case CONFIG_SYSCHANNEL:
        EcrireSysEx(0x20, valeur & 0xF, true);
        MIDI::ChoisirSysChannel(valeur);
    break;
    case CONFIG_MEMORY_PROTECT:
        EcrireSysEx(0x21, valeur & 0x1, true);
    break;
    case CONFIG_CONFIG_NUMBER:
        EcrireSysEx(0x22, valeur & 0x1F, true);
    break;
    case CONFIG_DETUNE:
        EcrireSysEx(0x23, valeur & 0x7F, true);
    break;
    case CONFIG_MASTER_VOLUME:
        EcrireSysEx(0x24, valeur & 0x7F, true);
    break;
    default: return;
    }
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
uchar Config::LireSysEx(const uchar param)
{
    return 0;
}

void Config::EcrireSysEx(const uchar param, const uchar valeur, const bool envoi)
{
    uchar envConfig[] = {0xF0, 0x43, 0x75, 0x00, 0x10, 0x00, 0x00, 0xF7};
//Construit le message
    envConfig[3] = MIDI::SysChannel();
    envConfig[5] = param & 0x7F;
    envConfig[6] = valeur & 0x7F;
//Transmet le paramêtre
    MIDI::EnvSysEx(envConfig, 8);
    return;
}
