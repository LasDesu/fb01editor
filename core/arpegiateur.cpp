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

#include "arpegiateur.h"

/*****************************************************************************/
bool Arpegiateur::Initialiser()
{
    return true;
}

void Arpegiateur::Terminer()
{

}

/*****************************************************************************/
void Arpegiateur::ActiverArpegiateur(const bool actif)
{

}

void Arpegiateur::DefinirTempo(const int bpm)
{

}

void Arpegiateur::DefinirNbPas(const int nbPas)
{

}

void Arpegiateur::ActiverSynchroNote(const bool active)
{

}

void Arpegiateur::ActiverSynchroTempo(const bool active)
{

}

void Arpegiateur::ActiverVerrou(const bool verrou)
{

}

/*****************************************************************************/
void Arpegiateur::ChoisirHauteurPas(const int index, const int hauteur)
{

}

void Arpegiateur::ChoisirEtatPas(const int index, const bool etat)
{

}

/*****************************************************************************/
void Arpegiateur::ReagirNote(const uchar valeur)
{

}

void Arpegiateur::ReagirTempo()
{

}

/*****************************************************************************/
bool Arpegiateur::Enregistrer(FILE * fichier)
{
    return true;
}

bool Arpegiateur::Charger(FILE * fichier, const short version)
{
    return true;
}
