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

    #include "memory.h"
    #include "types.h"
    #include "win32.h"

//Constantes
    #define MAXINS  5
    #define MAXOUTS 5
    #define TAMPON  2048
    #define ATTENTE 8000

//Message midi
    typedef union
    {
        ulong word;
        uchar data[4];
    }MMSG;

    class MIDI
    {
    private:
    //Objets internes
        static int   NbIns, NbOuts;
        static ulong HndIn, HndOut;
        static MIDIINCAPS  Ins[MAXINS];
        static MIDIOUTCAPS Outs[MAXOUTS];
    //Tampon de réception
        static uchar Tampon[TAMPON];
        static uchar Donnees[TAMPON];
        static MIDIHDR TampHDR;
    //Flags de réception
        static bool Prepare;
        static bool Attente;
    //Callback de reception
        static void WINAPI Callback (ulong hmi, uint msg, ulong instance, ulong param1, ulong param2);
    //Utilitaires
        static void AfficherErrIn(uint Resultat);
        static void AfficherErrOut(uint Resultat);
        static void PreparerTampon();
    public:
    //Enumération
        static void Lister();
        static int  NbDriversIn();
        static int  NbDriversOut();
        static char * DriverIn(int Index);
        static char * DriverOut(int Index);
    //Initialisation
        static void ActiverIn(int Index);
        static void DesactiverIn();
        static void ActiverOut(int Index);
        static void DesactiverOut();
    //Communication
        static void  EnvMsgLng(MMSG * Msg, int Taille);
        static void  EnvMsg(MMSG * Msg);
        static bool  AttMsg();
        static uchar LireMsg(int Pos);
        static bool  EnAttente();
    //Messages spécifiques
        static void Note(uchar Chan, uchar Note, uchar Velo);
    };

#endif // MIDI_H
