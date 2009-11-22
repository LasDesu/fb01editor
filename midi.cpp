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

#include <QMessageBox>
#include "midi.h"

//Initialise
    int MIDI::NbIns  = 0;
    int MIDI::NbOuts = 0;

//Prototypes
    ulong MIDI::HndIn = 0;
    ulong MIDI::HndOut = 0;
    MIDIINCAPS  MIDI::Ins[MAXINS];
    MIDIOUTCAPS MIDI::Outs[MAXOUTS];

/*****************************************************************************/
void MIDI::Lister()
{
//Compte les drivers
    NbIns  = midiInGetNumDevs();
    NbOuts = midiOutGetNumDevs();
    if (NbIns > MAXINS) NbIns = MAXINS;
    if (NbOuts > MAXOUTS) NbOuts = MAXOUTS;
//Récupère les noms
    for (int i = 0; i < NbIns; i++)
        midiInGetDevCapsA(i, &Ins[i], sizeof(MIDIINCAPS));
    for (int i = 0; i < NbOuts; i++)
        midiOutGetDevCapsA(i, &Outs[i], sizeof(MIDIOUTCAPS));
}

/*****************************************************************************/
int MIDI::NbDriversIn()
{
    return NbIns;
}

char * MIDI::DriverIn(int Index)
{
    return Ins[Index].szPname;
}

int MIDI::NbDriversOut()
{
    return NbOuts;
}

char * MIDI::DriverOut(int Index)
{
    return Outs[Index].szPname;
}

/*****************************************************************************/
void MIDI::ActiverIn(int Index)
{
    uint Resultat;
//Désactive le port
    if (HndIn != 0)
    {
        midiInStop(HndIn);
        midiInClose(HndIn);
        HndIn = 0;
    }
    if (Index == -1) return;
//Active le port in
    Resultat = midiInOpen(&HndIn, Index, 0, 0, 0);
    if (Resultat) AfficherErrIn(Resultat);
    midiInStart(HndIn);
}

void MIDI::ActiverOut(int Index)
{
    uint Resultat;
//Initialise
    if (HndOut != 0)
    {
        midiOutClose(HndOut);
        HndOut = 0;
    }
    if (Index == -1) return;
//Active le port in
    Resultat = midiOutOpen(&HndOut, Index, 0, 0, 0);
    if (Resultat) AfficherErrOut(Resultat);
}

/*****************************************************************************/
void MIDI::Note(uchar Chan, uchar Note, uchar Velo)
{
    MMSG Msg;
//Active une note
    if (!HndOut) return;
    Msg.data[0] = 0x90 + (Chan & 0xF);
    Msg.data[1] = Note & 0x7F;
    Msg.data[2] = Velo & 0x7F;
    Msg.data[3] = 0;
    EnvMsg(&Msg);
}

void MIDI::Reset(uchar Chan)
{
    MMSG Msg;
//Arrête les notes
    if (!HndOut) return;
    Msg.data[0] = 0xB0 + (Chan & 0xF);
    Msg.data[1] = 0x7B;
    Msg.data[2] = 0;
    Msg.data[3] = 0;
    EnvMsg(&Msg);
}

/*****************************************************************************/
void MIDI::AfficherErrIn(uint Resultat)
{
    char Text[128];
    QMessageBox msgBox;
//Affiche l'érreur
    midiInGetErrorTextA(Resultat, Text, 128);
    msgBox.setText(Text);
    msgBox.exec();
}

void MIDI::AfficherErrOut(uint Resultat)
{
    char Text[128];
    QMessageBox msgBox;
//Affiche l'érreur
    midiOutGetErrorTextA(Resultat, Text, 128);
    msgBox.setText(Text);
    msgBox.exec();
}

/*****************************************************************************/
void MIDI::EchMsg(MMSG * Msg, int TMsg, MMSG * Rep, int TRep)
{
    MIDIHDR HeadMsg;
    MIDIHDR HeadRep;
    uint    Resultat;
//Initialise les entêtes
    memset(&HeadMsg, 0, sizeof(MIDIHDR));
    HeadMsg.dwBufferLength = TMsg;
    HeadMsg.lpData = (char *) Msg;
    midiOutPrepareHeader(HndOut, &HeadMsg, sizeof(MIDIHDR));
    memset(&HeadRep, 0, sizeof(MIDIHDR));
    HeadRep.dwBufferLength = TRep;
    HeadRep.lpData = (char *) Rep;
    midiInPrepareHeader(HndIn, &HeadRep, sizeof(MIDIHDR));
//Effectue l'échange
    Resultat = midiOutLongMsg(HndOut, &HeadMsg, sizeof(MIDIHDR));
    if(Resultat) AfficherErrOut(Resultat);
    Resultat = midiInAddBuffer(HndIn, &HeadRep, sizeof(MIDIHDR));
    if(Resultat) AfficherErrIn(Resultat);
//Réinitialise
    midiOutUnprepareHeader(HndOut, &HeadMsg, sizeof(MIDIHDR));
    midiInUnprepareHeader(HndIn, &HeadRep, sizeof(MIDIHDR));
}

void MIDI::EnvMsgLng(MMSG * Msg, int Taille)
{
    MIDIHDR Header;
    uint    Resultat;
//Initialise l'entête
    memset(&Header, 0, sizeof(MIDIHDR));
    Header.dwBufferLength = Taille;
    Header.lpData = (char *) Msg;
    midiOutPrepareHeader(HndOut, &Header, sizeof(MIDIHDR));
//Envoie le message
    Resultat = midiOutLongMsg(HndOut, &Header, sizeof(MIDIHDR));
    if(Resultat) AfficherErrOut(Resultat);
    midiOutUnprepareHeader(HndOut, &Header, sizeof(MIDIHDR));
}

void MIDI::EnvMsg(MMSG * Msg)
{
    uint Resultat = midiOutShortMsg(HndOut, Msg->word);
    if(Resultat) AfficherErrOut(Resultat);
}

