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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../types.h"
#include "../win32.h"
#include "../linux.h"

#include "../excep/midi_ex.h"
#include "../excep/memory_ex.h"

class MIDI
{
public:
//Enumération des drivers
    static void EnumererDrivers();
    static void LibererDrivers();
    static uint NbDriversIn();
    static uint NbDriversOut();
    static uint NbDriversCtrl();
    static char * DriverIn(const int index);
    static char * DriverOut(const int index);
    static char * DriverCtrl(const int index);
//Initialisation des drivers
    static void ActiverIn(const int index);
    static void ActiverOut(const int index);
    static void ActiverCtrl(const int index);
    static void DesactiverIn();
    static void DesactiverOut();
    static void DesactiverCtrl();
    static bool InOk();
    static bool OutOk();
    static bool CtrlOk();
//Envoi de messages
    static void EnvMsg(uchar * msg);
    static void EnvSysEx(uchar * sysEx, const int taille);
    static void RecSysEx(uchar * sysEx, const int taille);
//Paramêtres de transmission
    static void  ChoisirMidiChannel(const uchar channel);
    static uchar MidiChannel();
    static void  ChoisirVelocity(const uchar velocity);
    static uchar Velocity();
    static void  ChoisirSysChannel(const uchar channel);
    static uchar SysChannel();
//Envoi de notes
    static void NoteOn(const uchar note);
    static void NoteOff(const uchar note);
    static void AllNotesOff();
//Debug
    static void BackupTampon(char * Chemin);
protected:
//Objets de la communication
    static void * ins, * outs;
    static int   nbIns, nbOuts;
    static uint  hndIn, hndOut, hndCtrl;
//Paramêtres de communication
    static uchar midiChannel;
    static uchar velocity;
    static uchar sysChannel;
//Tampon de réception
    #define MIDI_LEN_TAMPON      0x2000
    #define MIDI_ATTENTE         100
    #define MIDI_ATTENTE_MESSAGE 100
    static uchar tampon[2][MIDI_LEN_TAMPON];
    static bool  attente;
#ifdef WIN32
//Statut des tampons
    static MIDIHDR header;
    static bool prepare;
//Gestion des tampons
    static void PreparerTampon();
    static void DePreparerTampon();
    static void WINAPI Callback (uint hmi, uint msg, uint instance, uint param1, uint param2);
#endif
#ifdef LINUX
#endif
};


#endif // MIDI_H
