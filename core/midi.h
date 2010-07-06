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

#ifndef MIDI_H
#define MIDI_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../types.h"
#include "../win32.h"
#include "../linux.h"

#include "automation.h"

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
    static char * DriverIn(const int index);
    static char * DriverOut(const int index);
//Activation des drivers
    static void ActiverIn(const int index);
    static void ActiverOut(const int index);
    static void ActiverCtrl(const int index);
    static void DesactiverIn();
    static void DesactiverOut();
    static void DesactiverCtrl();
//Etat des drivers
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
//Relaye les messages courts reçus vers la sortie
    static void ActiverINToOUT(const bool active);
    static void ActiverCTRLToOUT(const bool active);
//Envoi de notes
    static void NoteOn(const uchar note);
    static void NoteOff(const uchar note);
    static void AllNotesOff();
//Debug
    static void BackupTampon(char * Chemin);
private:
//Structures spécifiques
    typedef struct {
        void * desc;
        uint nb;
    }DriversStr;
//Objets de la communication
    static DriversStr ins, outs;
    static uint hndIn, hndOut, hndCtrl;
    static int  indIn, indOut, indCtrl;
//Paramêtres de communication
    static uchar midiChannel;
    static uchar velocity;
    static uchar sysChannel;
//Paramêtres de relai
    static bool relaiIN;
    static bool relaiCTRL;
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
    static void WINAPI CallbackIn(uint hmi, uint msg, uint instance, uint param1, uint param2);
    static void WINAPI CallbackCtrl(uint hmi, uint msg, uint instance, uint param1, uint param2);
#endif
#ifdef LINUX
#endif
};


#endif // MIDI_H
