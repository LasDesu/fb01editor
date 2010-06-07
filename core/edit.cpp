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

#include "edit.h"

/*****************************************************************************/
Edit::Edit(const uchar id, const uchar nbParam, const uchar lenSysEx, uchar * sysEx)
    : Block(nbParam, lenSysEx, sysEx)
{
    this->id = id;
}

Edit::~Edit()
{
}

/*****************************************************************************/
uchar Edit::LireId()
{
    return id;
}

void Edit::EcrireId(uchar id)
{
    this->id = id;
}

/*****************************************************************************/
bool Edit::Enregistrer(FILE * fichier)
{
    uchar sauv[nbParam];
    for (int i=0; i < nbParam; i++)
        sauv[i] = LireParam(i);
    fwrite(sauv, nbParam, 1, fichier);
    return true;
}

bool Edit::Charger(FILE * fichier, const short version)
{
    uchar sauv[nbParam];
    if (fread(sauv, nbParam, 1, fichier))
        return false;
    for (int i=0; i < nbParam; i++)
        EcrireParam(i, sauv[i], true);
    return true;
}

/*****************************************************************************/
bool Edit::Exporte(FILE * fichier)
{
    if (sysEx == NULL) return false;
    uint res = fwrite(sysEx, lenSysEx, 1, fichier);
    if (res != lenSysEx) return false;
    return true;
}

bool Edit::Importe(FILE * fichier)
{
    if (sysEx == NULL) return false;
    uint res = fread(sysEx, lenSysEx, 1, fichier);
    if (res != lenSysEx) return false;
    return true;
}

/*****************************************************************************/
void Edit::Initialiser()
{
    for (int i=0; i < nbParam; i++)
        EcrireParam(i, 0, true);
}

void Edit::Randomiser()
{
    for (int i=0; i < nbParam; i++)
        EcrireParam(i, RAND(0, 255), true);
}

void Edit::Copier(uchar * table, const ulong len)
{
    if (len < lenSysEx) return;
    memcpy(table, sysEx, lenSysEx);
}

void Edit::Coller(const uchar * table, const ulong len)
{
    if (len < lenSysEx) return;
    memcpy(sysEx, table, lenSysEx);
    EnvoyerTout();
}
