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

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QTime>
#include "midi.h"

//Application
    extern QApplication * mainApp;

//Nombre de drivers
    int MIDI::NbIns  = 0;
    int MIDI::NbOuts = 0;
//Tampon
    MIDIHDR MIDI::TampHDR;
    uchar MIDI::Tampon[TAMPON];
    uchar MIDI::Donnees[TAMPON];
    bool MIDI::Prepare = false;
    bool MIDI::Recu    = false;
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
    DesactiverIn();
    if (Index == -1) return;
//Active le port in
    Resultat = midiInOpen(&HndIn, Index, 0, 0, 0);
    if (Resultat) AfficherErrIn(Resultat);
//Configure le tampon
    memset(&TampHDR, 0, sizeof(MIDIHDR));
    TampHDR.dwBufferLength = TAMPON;
    TampHDR.lpData = (char *) Tampon;
//Prépare le tampon
    Resultat = midiInPrepareHeader(HndIn, &TampHDR, sizeof(MIDIHDR));
    if (Resultat) AfficherErrIn(Resultat);
    Prepare = true;
    Recu    = false;
//Active le tampon
    midiInAddBuffer(HndIn, &TampHDR, sizeof(MIDIHDR));
    midiInStart(HndIn);
}

void MIDI::DesactiverIn()
{
//Vérifie l'activation
    if (HndIn == 0) return;
//Arrête l'écoute
    midiInStop(HndIn);
    midiInReset(HndIn);

//Ferme le port
    midiInClose(HndIn);
    HndIn = 0;
}

/*****************************************************************************/
void MIDI::ActiverOut(int Index)
{
    uint Resultat;
//Désactive le port
    DesactiverOut();
    if (Index == -1) return;
//Active le port out
    Resultat = midiOutOpen(&HndOut, Index, 0, 0, 0);
    if (Resultat) AfficherErrOut(Resultat);
}

void MIDI::DesactiverOut()
{
//Vérifie l'activation
    if (HndOut == 0) return;
//Ferme le port
    midiOutReset(HndOut);
    midiOutClose(HndOut);
    HndOut = 0;
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

/*****************************************************************************/
void MIDI::AfficherErrIn(uint Resultat)
{
    char Text[128];
    QMessageBox MsgBox;
//Affiche l'érreur
    midiInGetErrorTextA(Resultat, Text, 128);
    MsgBox.setText(Text);
    MsgBox.exec();
}

void MIDI::AfficherErrOut(uint Resultat)
{
    char Text[128];
    QMessageBox MsgBox;
//Affiche l'érreur
    midiOutGetErrorTextA(Resultat, Text, 128);
    MsgBox.setText(Text);
    MsgBox.exec();
}

/*****************************************************************************/
void MIDI::RecMsgLng(int Secs)
{
//Démarre l'attente
    int Millis = Secs * 1000;
    /*
    QTime::start();
    while(QTime::elapsed() < Millis)
    {
        if (Recu == true) goto Suite;
        mainApp->processEvents();
    }
Suite :
*/
}

/*****************************************************************************/
void MIDI::EnvMsgLng(MMSG * Msg, int Taille)
{
    MIDIHDR Header;
    uint    Resultat;
//Initialise l'entête
    memset(&Header, 0, sizeof(MIDIHDR));
    Header.dwBufferLength = Taille;
    Header.lpData = (char *) Msg;
    Resultat = midiOutPrepareHeader(HndOut, &Header, sizeof(MIDIHDR));
    if(Resultat)AfficherErrOut(Resultat);
//Envoie le message
    Resultat = midiOutLongMsg(HndOut, &Header, sizeof(MIDIHDR));
    if(Resultat)AfficherErrOut(Resultat);
    midiOutUnprepareHeader(HndOut, &Header, sizeof(MIDIHDR));
}

void MIDI::EnvMsg(MMSG * Msg)
{
//Envoie le message
    uint Resultat = midiOutShortMsg(HndOut, Msg->word);
    if(Resultat) AfficherErrOut(Resultat);
}

/*****************************************************************************/
void MIDI::Callback(ulong hmi, uint msg, ulong instance, ulong param1, ulong param2)
{
//SysEX
    if (msg == MIM_LONGDATA)
    {
    //Libère le tampon
        midiInUnprepareHeader(HndIn, &TampHDR, sizeof(MIDIHDR));
        Prepare = false;
    //Copie les données
        memcpy(Donnees, Tampon, TAMPON);
        Recu = true;
    //Reprépare le tampon
        if (TampHDR.dwBytesRecorded == 0) return;
        midiInPrepareHeader(HndIn, &TampHDR, sizeof(MIDIHDR));
        midiInAddBuffer(HndIn, &TampHDR, sizeof(MIDIHDR));
        Prepare = true;
    }
}

