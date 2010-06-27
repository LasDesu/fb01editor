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

#ifndef EDITEUR_H
#define EDITEUR_H

#include <QApplication>
#include "interface/mainwindow.h"

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "excep/memory_ex.h"
#include "excep/midi_ex.h"

#include "core/midi.h"
#include "core/voice.h"
#include "core/operateur.h"
#include "core/set.h"
#include "core/instrument.h"
#include "core/bank.h"
#include "core/bank_voice.h"
#include "core/config.h"


//****************************************************************************/
int main(int argc, char *argv[]);
void quit();

//****************************************************************************/
class Editeur {
    friend class MainWindow;
public :
//Constantes
    #define EDITEUR_NB_BANK 4
    typedef enum {
        FICHIER_VOICE = 0,
        FICHIER_SET,
        FICHIER_BANK,
        FICHIER_SYSEX
    }FICHIER_TYPE;
//Constructeurs
    Editeur();
    ~Editeur();
//Chargement et déchargement
    FILE * ChargerFichier(FICHIER_TYPE type, short * version);
    FILE * EnregistrerFichier(FICHIER_TYPE type);
//Actualisation de l'éditeur
    void Actualiser();
    void Reinitialiser();
//Attribution des objets
    void AttribuerConfig();
    void AttribuerBanks();
    void AttribuerInstruments();
    void AttribuerVoice();
    void AttribuerOperateurs();
//Configuration de l'interface
    void ConfigurerOnglets(const bool actifs);
    void ConfigurerMenus(const bool actifs);
//Sélection des objets sélectionné
    void ChoisirPageSet(const int page);
    void ChoisirBank(const int bank);
    void ChoisirInstru(const int instru);
    void ChoisirOP(const int OP);
//Actualisation des contenus
    bool ActualiserBanks();
    bool ActualiserSet();
    bool ActualiserInstru();
//Rafraichissement de l'affichage
    void RafraichirBanks();
    void RafraichirSet();
    void RafraichirInstru();
private :
//Objets de l'éditeur
    Bank   banks[EDITEUR_NB_BANK];
    Set    set;
    Voice  voice;
    Config config;
//Sélection d'édition
    int pageSel;
    int instruSel;
    int OPSel;
    int bankSel;
//Initialisation de l'éditeur
    void InitialiserEditeur();
    void InitialiserInterface();
    void TerminerEditeur();
    void TerminerInterface();    
};

#endif
