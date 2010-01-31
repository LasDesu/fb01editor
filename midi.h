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

#ifndef MIDI_H
#define MIDI_H

//****************************************************************************/
    #include <QtGui/QApplication>
    #include <QtGui/QMessageBox>
    #include <QTime>
    #include <QFile>
    #include <string.h>

//****************************************************************************/
    #include "types.h"
    #ifdef WIN32
        #include "win32.h"
    #endif
    #ifdef LINUX
        #include "linux.h"
    #endif

//****************************************************************************/
    #define TAMPON   6400
    #define ATTENTE 10000

//****************************************************************************/
    class MIDI
    {
    public:
    //Enumération
        static void Lister();
        static void DeLister();
        static int  NbDriversIn();
        static int  NbDriversOut();
        static char * DriverIn(int Index);
        static char * DriverOut(int Index);
    //Initialisation
        static void ActiverIn(int Index);
        static void DesactiverIn();
        static void ActiverOut(int Index);
        static void DesactiverOut();
        static bool EstConfigure();
    //Envoi de messages
        static void  EnvMsg(uchar * Msg, int Taille, bool Requete);
        static bool  AttMsg();
        static uchar LireMsg(int Pos);
        static void  ExtraireMsg(uchar * Temp, int Taille);
    //Envoi de notes
        static void ChoisirNoteChan(int Chan);
        static void Note(uchar Note, uchar Velo);
    //Debug
        static void BackupTampon(char * Chemin);
    private:
    //Configurations
        static void * Ins, * Outs;
        static int   NbIns, NbOuts;
        static uint  HndIn, HndOut;
        static uchar NoteChan;
    //Tampon de réception
        static uchar Tampon[TAMPON];
        static uchar Donnees[TAMPON];
        static bool  Attente;
    //Affichage des erreurs
        static void AffErrIn(uint Resultat);
        static void AffErrOut(uint Resultat);
        static void AffAttente(bool Active);
    //Fonctions spécifiques
        #ifdef WIN32
        //Statut des tampons
            static MIDIHDR Header;
            static bool Prepare;
        //Gestion des tampon
            static void PreparerTampon();
            static void DePreparerTampon();
            static void WINAPI Callback (uint hmi, uint msg, uint instance, uint param1, uint param2);
            static void TraiterSysEx();
        #endif
        #ifdef LINUX
        #endif
    };

#endif // MIDI_H
