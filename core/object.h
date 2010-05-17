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

#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"

class Object {
public :
//Constructeurs
    Object();
    ~Object();
//Chargement / déchargement de l'objet
    bool Enregistrer(FILE * fichier);
    bool Charger(FILE * fichier, const int version);
//Importation exportation de l'objet
    bool Exporte(FILE * fichier);
    bool Importe(FILE * fichier);
//Edition de l'objet
    void Initialiser();
    void Randomiser();
    void Copier(uchar * table, const ulong len);
    void Coller(const uchar * table, const ulong len);
//Modification des propriétés
    virtual uchar LireParam(const uchar param);
    virtual void  EcrireParam(const uchar param, const uchar valeur);
//Envoi / Reception de l'objet
    virtual uint Envoyer();
    virtual uint EnvoyerTout();
    virtual uint RecevoirTout();
protected :
//Messages SysEx
    uint lenSysEx;
    uint nbSysEx;
    uchar * sysEx;
    bool  * modif;
//Paramêtres globaux
    uchar id;
    uchar nbParam;
//Gestion des SysEx
    void InitSysEx();
    void CheckSumSysEx();
    virtual uchar LireSysEx(const uchar param);
    virtual void  EcrireSysEx(const uchar param, const uchar valeur);

};

#endif
