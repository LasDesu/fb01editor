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

#include "core/midi.h"
#include "core/operateur.h"
#include "core/voice.h"
#include "core/instrument.h"
#include "core/set.h"
#include "core/bank.h"

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "types.h"
#include "win32.h"
#include "linux.h"

//****************************************************************************/
class Editeur {
public :
    Editeur();
    ~Editeur();
//Chargement et déchargement
    FILE * ChargerFichier(const int Type, const short Version);
    FILE * EnregistrerFichier(const int Type, const short Version);
//Actualisation de l'éditeur
    void ActualiserEditeur();
    bool ActualiserSet();
    bool ActualiserVoice();
    bool ActualiserConfig();
    bool ActualiserBank();
//Configuration de l'interface
    void ConfigurerOnglets(const bool actifs);
    void ConfigurerMenus(const bool actifs);
    void ChangerPage(const int page);
    void ChangerInstru(const int instru);
    void ChangerOP(const int OP);
private :
//Objets de l'éditeur
    #define EDITEUR_NB_BANK 4
    Bank  * bank[EDITEUR_NB_BANK];
    Voice * voice;
    Set   * set;
//Fenêtre principale
    MainWindow  * mainWindow;
//Sélection d'édition
    int pageSel, instruSel, OPSel;
//Initialisation de l'éditeur
    void InitialiserEditeur();
    void InitialiserInterface();
    void TerminerEditeur();
    void TerminerInterface();
};

#endif
