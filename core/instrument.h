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

#ifndef INSTRUMENT_H
#define INTRUMENT_H

#include <stdlib.h>
#include <stdio.h>

#include "../types.h"
/*

class Instrument {
public :
//Constantes
//Chargement / déchargement
    bool Enregistrer(FILE * fichier);
    bool Charger(FILE * fichier, const int version);
    bool EnregistrerSysEx(FILE * fichier);
    bool ChargerSysEx(FILE * fichier);
//Edition de l'opérateur
    void Initialiser();
    void Randomiser();
    void Copier(uchar * table, ulong len);
    void Coller(const uchar * table, ulong len);
//Lien avec interface
    uchar LireParam(uchar param);
    void  EcrireParam(uchar param, uchar valeur);
//Communication MIDI
    void EnvoyerTout(uchar index);
    void RecevoirTout(uchar index);
    void Envoyer(uchar index);
private :
//Messages SysEx
    uchar sysEx[];
    bool  modifs[];
};

*/
#endif
