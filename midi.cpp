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
#include <QFile>
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
    bool MIDI::Attente = false;
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
    Resultat = midiInOpen(&HndIn, Index, (ulong) Callback, 0, CALLBACK_FUNCTION);
    if (Resultat)
    {
        AfficherErrIn(Resultat);
        return;
    }
//Démarre l'écoute
    PreparerTampon();
    midiInStart(HndIn);
}

void MIDI::DesactiverIn()
{
//Vérifie l'activation
    if (HndIn == 0) return;
//Arrête l'écoute
    Attente = true;
    midiInReset(HndIn);
    midiInStop(HndIn);
    if (Prepare) midiInUnprepareHeader(HndIn, &TampHDR, sizeof(MIDIHDR));
//Réinitialise
    Prepare = false;
    Attente = false;
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
//Affiche l'érreur
    midiInGetErrorTextA(Resultat, Text, 128);
    QMessageBox::critical(NULL, "FB01 SE :", Text);
}

void MIDI::AfficherErrOut(uint Resultat)
{
    char Text[256];
//Affiche l'érreur
    midiOutGetErrorTextA(Resultat, Text, 256);
    QMessageBox::critical(NULL, "FB01 SE :", Text);
}

/*****************************************************************************/
void MIDI::EnvMsgLng(MMSG * Msg, int Taille)
{
    MIDIHDR Header;
    uint    Resultat;
//Vérifie l'ouverture
    if (HndOut == 0) return;
//Initialise l'entête
    memset(&Header, 0, sizeof(MIDIHDR));
    Header.dwBufferLength = Taille;
    Header.lpData = (char *) Msg;
//Prépare le tampon
    Resultat = midiOutPrepareHeader(HndOut, &Header, sizeof(MIDIHDR));
    if (Resultat) AfficherErrOut(Resultat);
//Envoie le message
    Resultat = midiOutLongMsg(HndOut, &Header, sizeof(MIDIHDR));
    if (Resultat) AfficherErrOut(Resultat);
    midiOutUnprepareHeader(HndOut, &Header, sizeof(MIDIHDR));
}

void MIDI::EnvMsg(MMSG * Msg)
{
//Vérifie l'ouverture
    if (HndOut == 0) return;
//Envoie le message
    uint Resultat = midiOutShortMsg(HndOut, Msg->word);
    if(Resultat) AfficherErrOut(Resultat);
}

/*****************************************************************************/
bool MIDI::AttMsg()
{
//Passe en mode réception
    Attente = true;
    QTime Timer;
    Timer.start();
 //Affiche la boite
    QMessageBox MsgBox(NULL);
    MsgBox.setWindowModality(Qt::WindowModal);
    MsgBox.setWindowTitle("FB01 SE:");
    MsgBox.setText("Waiting for device ...");
    MsgBox.show();
 //Attend un sysex
    while(Attente)
    {
    //Gère les évenements
        mainApp->processEvents();
        if (Timer.elapsed() > ATTENTE)
        {
        //Pas de réponse
            Attente = false;
            MsgBox.setText("No answer !");
            MsgBox.done(0);
        //Arrête l'attente
            return false;
        }
    }
//Récupère les données
    memcpy(Donnees, Tampon, TAMPON);
    PreparerTampon();
//Ferme la boite
    MsgBox.setText("Well received !");
    MsgBox.done(0);
    return true;
}

/*****************************************************************************/
bool MIDI::EnAttente()
{
    return Attente;
}

uchar MIDI::LireMsg(int Pos)
{
    if (Pos < TAMPON) return Donnees[Pos];
    return 0;
}

/*****************************************************************************/
void MIDI::PreparerTampon()
{
    uint Resultat;
//Déprépare le tampon
    if (Prepare)
    {
        midiInUnprepareHeader(HndIn, &TampHDR, sizeof(MIDIHDR));
        Prepare = false;
    }
//Initialise  le tampon
    memset(Tampon, 0, TAMPON);
    memset(&TampHDR, 0, sizeof(MIDIHDR));
//Configure l'entête
    TampHDR.dwBufferLength = TAMPON;
    TampHDR.lpData = (char *) Tampon;
//Prépare le tampon
    Resultat = midiInPrepareHeader(HndIn, &TampHDR, sizeof(MIDIHDR));
    if (Resultat)
    {
        AfficherErrIn(Resultat);
        return;
    }
//Ajoute à la liste
    midiInAddBuffer(HndIn, &TampHDR, sizeof(MIDIHDR));
    Prepare = true;
}

/*****************************************************************************/
void WINAPI MIDI::Callback (ulong hmi, uint msg, ulong instance, ulong param1, ulong param2)
{
//Réception de SysEX
    if (msg == MIM_LONGDATA)
    {
        if (Attente) Attente = false;
        else PreparerTampon();
    }
}
