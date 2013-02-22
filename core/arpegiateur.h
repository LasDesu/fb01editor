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

#ifndef ARPEGIATEUR_H
#define ARPEGIATEUR_H

#include <stdlib.h>
#include <stdio.h>

#include "../types.h"
#include "../win32.h"
#include "../linux.h"

#include "midi.h"

class Arpegiateur
{
public:
//Initialisation de la classe
    static bool Initialiser();
    static void Terminer();
//Configuration de l'arpégiateur
    static void ActiverArpegiateur(const bool actif);
    static void DefinirTempo(const int bpm);
    static void DefinirNbPas(const int nbPas);
    static void ActiverSynchroNote(const bool active);
    static void ActiverSynchroTempo(const bool active);
    static void ActiverVerrou(const bool verrou);
    static void ChoisirHauteurPas(const int index, const int hauteur);
    static void ChoisirEtatPas(const int index, const bool etat);
//Messages MIDI
    static void ReagirNote(const uchar valeur);
    static void ReagirTempo();
//Chargement / enregistrement
    static bool Enregistrer(FILE * fichier);
    static bool Charger(FILE * fichier, const short version);
private :
};

#endif // ARPEGIATEUR_H
