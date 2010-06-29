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

#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../types.h"
#include "../win32.h"
#include "../linux.h"

#include "../excep/memory_ex.h"
#include "../excep/automation_ex.h"

#include "automated.h"

class Automation
{
public:
//Constantes
    #define AUTO_NB_CCS  128
    #define AUTO_NB_CBS  4
    #define AUTO_MAX_CBS 100
    #define AUTO_LEN_NOM 41
//Structure de données
    typedef struct {
        Automated * automated;
        uint index;
        char nom[AUTO_LEN_NOM];
    }CallBackStr;
//Enregistrement des automations
    static void AjouterCallback(Automated * automated, const uint index, const char * nom);
//Gestion de la liste
    static uint   NbCallbacks();
    static char * NomCallback(const uint index);
//Association des callbacks
    static void AssocierCC(const uchar CC, const uint index);
    static void DissocierCC(const uchar CC, const uint index);
//Vérification des associations
    static bool CallbackAssociee(const uint index, const uchar CC);
    static bool CCAssocie(const uchar CC);
//Réaction aux CCs
    static void  ReagirCC(const uchar CC, const uchar valeur);
    static uchar DernierCC();
    static uchar DerniereValeur();
private :
//Liste des CC et callbacks
    static uint CCs[AUTO_NB_CCS][AUTO_NB_CBS];
    static CallBackStr callbacks[AUTO_MAX_CBS];
    static uint nbCallbacks;
//Statistiques évenements CC
    static uchar dernierCC;
    static uchar derniereValeur;
};

#endif // AUTOMATION_H
