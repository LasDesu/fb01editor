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

#include "automation.h"

/*****************************************************************************/
uint Automation::CCs[AUTO_NB_CCS][AUTO_NB_CBS];
Automation::CallBackStr Automation::callbacks[AUTO_MAX_CBS];
uint Automation::nbCallbacks = 0;

uchar Automation::dernierCC = -1;
uchar Automation::derniereValeur = -1;

/*****************************************************************************/
void Automation::AjouterCallback(Automated * automated, const uint index, const char * nom)
{
//Manque de place
    if (nbCallbacks == AUTO_MAX_CBS)
        throw Automation_ex("Too much callbacks registrated !");
//Enregistre la callback
    int len = min(strlen(nom), AUTO_LEN_NOM);
    callbacks[nbCallbacks].automated = automated;
    callbacks[nbCallbacks].index = index;
    strncpy(callbacks[nbCallbacks].nom, nom, len);
 //Passe à la suivante
    nbCallbacks ++;
}

/*****************************************************************************/
uint Automation::NbCallbacks()
{
    return nbCallbacks;
}

char * Automation::NomCallback(const uint index)
{
    return callbacks[index].nom;
}

/*****************************************************************************/
void Automation::AssocierCC(const uchar CC, const uint index)
{
//Vérifie si déjà associée
    for (uint i = 0; i < AUTO_NB_CBS; i ++)
        if (CCs[CC][i] == index + 1) return;
//Associe la callback au CC
    for (uint i = 0; i < AUTO_NB_CBS; i ++)
        if (CCs[CC][i] == 0) {
            CCs[CC][i] = index + 1;
            return;
        }
//Manque de place
    throw Automation_ex("Too much parameters assigned to the same CC !");
}

void Automation::DissocierCC(const uchar CC,  const uint index)
{
//Supprime la callback
    for (uint i = 0; i < AUTO_NB_CBS; i ++)
        if (CCs[CC][i] == index + 1) {
            CCs[CC][i] = 0;
            return;
        }
}

/*****************************************************************************/
bool Automation::CallbackAssociee(const uint index, const uchar CC)
{
//Vérifie si la callback est associée au CC
    for (uint i = 0; i < AUTO_NB_CBS; i ++)
        if (CCs[CC][i] == index + 1) return true;
    return false;
}

bool Automation::CCAssocie(const uchar CC)
{
//Vérifie si le CC contient une callback
    for (uint i = 0; i < AUTO_NB_CBS; i ++)
        if (CCs[CC][i] > 0) return true;
    return false;
}

/*****************************************************************************/
void Automation::ReagirCC(const uchar CC, const uchar valeur)
{
//Execute les callbacks
    for (uint i = 0; i < AUTO_NB_CBS; i ++) {
        int cb = CCs[CC][i] - 1;
        if (cb >= 0) callbacks[cb].automated->AppelerCallback(callbacks[cb].index, valeur);
    }
//Enregistre l'évenement
    dernierCC = CC;
    derniereValeur = valeur;
}

/*****************************************************************************/
uchar Automation::DernierCC()
{
    return dernierCC;
}

uchar Automation::DerniereValeur()
{
    return derniereValeur;
}
