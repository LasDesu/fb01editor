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
    #define LNGTAMP 6400
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
        static char * DriverIn(const int Index);
        static char * DriverOut(const int Index);
    //Initialisation
        static void ActiverIn(const int Index);
        static void DesactiverIn();
        static void ActiverOut(const int Index);
        static void DesactiverOut();
        static bool EstConfigure();
    //Envoi de messages
        static void  EnvMsg(uchar * Msg, const int Taille, bool Requete);
        static bool  AttMsg();
        static uchar LireMsg(const int Pos);
        static void  ExtraireMsg(uchar * Temp, const int Taille);
    //Envoi de notes
        static void ChoisirNoteChan(const int Chan);
        static void Note(const uchar Note, const uchar Velo);
    //Debug
        static void BackupTampon(char * Chemin);
    private:
    //Configurations
        static void * Ins, * Outs;
        static int   NbIns, NbOuts;
        static uint  HndIn, HndOut;
        static uchar NoteChan;
    //Tampon de réception
        static uchar Tampon[LNGTAMP];
        static uchar Donnees[LNGTAMP];
        static bool  Attente;
    //Affichage des erreurs
        static void AffErrIn(const uint Resultat);
        static void AffErrOut(const uint Resultat);
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
