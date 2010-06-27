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

#ifndef EDIT_H
#define EDIT_H

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../types.h"
#include "../excep/memory_ex.h"

#include "block.h"

class Edit : public Block {
public :
//Constructeurs
    Edit(const uchar id, uchar * sysEx, const uint lenSysEx, const uint nbParam, const uint offParam);
    ~Edit();
//Gestion de l'id objet
    uchar LireId();
    void  EcrireId(const uchar id);
//Chargement / déchargement de l'objet
    virtual bool Enregistrer(FILE * fichier);
    virtual bool Charger(FILE * fichier, const short version);
//Importation exportation de l'objet
    virtual bool Exporte(FILE * fichier);
    virtual bool Importe(FILE * fichier);
//Edition de l'objet
    virtual void Initialiser();
    virtual void Randomiser();
    virtual void Copier(uchar * table, const ulong len);
    virtual void Coller(const uchar * table, const ulong len, const bool envoi);
    virtual void Echanger(uchar * table, const ulong len, const bool envoi);
protected :
//Paramètres de l'objet
    uchar id;
};

#endif
