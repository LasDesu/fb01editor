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

#include "midi.h"

//Application
    extern QApplication * mainApp;

//Espace tampon
    uchar MIDI::Tampon[TAMPON];
    uchar MIDI::Donnees[TAMPON];

#ifdef WIN32
    MIDIHDR MIDI::Header;
    bool MIDI::Prepare = false;
    bool MIDI::Attente = false;
#endif

//Handles
    ulong MIDI::HndIn  = 0;
    ulong MIDI::HndOut = 0;

//Configuration
    void * MIDI::Ins  = NULL;
    void * MIDI::Outs = NULL;
    int    MIDI::NbIns  = 0;
    int    MIDI::NbOuts = 0;
    uchar  MIDI::NoteChan = 0;

/*****************************************************************************/
void MIDI::Lister()
{
//Efface les configs précédentes
    DeLister();
#ifdef WIN32
//Compte les drivers
    NbIns  = midiInGetNumDevs();
    NbOuts = midiOutGetNumDevs();
//Alloue les configurations
    if (NbIns != 0)
        Ins = malloc(sizeof(MIDIINCAPS) * NbIns);
    if (NbOuts != 0)
        Outs = malloc(sizeof(MIDIOUTCAPS) * NbOuts);
//Récupère les configurations
    for (int i = 0; i < NbIns; i++)
        midiInGetDevCapsA(i, &((MIDIINCAPS *)Ins)[i], sizeof(MIDIINCAPS));
    for (int i = 0; i < NbOuts; i++)
        midiOutGetDevCapsA(i, &((MIDIOUTCAPS *)Outs)[i], sizeof(MIDIOUTCAPS));
#endif
#ifdef LINUX
#endif
}

void MIDI::DeLister()
{
#ifdef WIN32
//Libère la liste
    if (Ins != NULL)  free(Ins);
    if (Outs != NULL) free(Outs);
#endif
//Réinitialise
    NbIns  = 0; Ins  = NULL;
    NbOuts = 0; Outs = NULL;
}

/*****************************************************************************/
int MIDI::NbDriversIn()
{
    return NbIns;
}

int MIDI::NbDriversOut()
{
    return NbOuts;
}

char * MIDI::DriverIn(int Index)
{
#ifdef WIN32
    return ((MIDIINCAPS *)Ins)[Index].szPname;
#endif
#ifdef LINUX
#endif
}

char * MIDI::DriverOut(int Index)
{
#ifdef WIN32
    return ((MIDIOUTCAPS *)Outs)[Index].szPname;
#endif
#ifdef LINUX
#endif
}

/*****************************************************************************/
void MIDI::ActiverIn(int Index)
{
    uint Resultat;
//Désactive le port précédent
    DesactiverIn();
#ifdef WIN32
//Ouvre le port
    Resultat = midiInOpen(&HndIn, Index, (ulong) Callback, 0, CALLBACK_FUNCTION);
    if (Resultat) {AffErrIn(Resultat); return;}
//Démarre l'écoute
    PreparerTampon();
    midiInStart(HndIn);
#endif
#ifdef LINUX
#endif
}

void MIDI::DesactiverIn()
{
//Vérifie l'activation
    if (HndIn == 0) return;
#ifdef WIN32
//Arrête l'écoute
    Attente = true;
    midiInReset(HndIn);
    midiInStop(HndIn);
    DePreparerTampon();
//Ferme le port
    midiInClose(HndIn);
#endif
#ifdef LINUX
#endif
    HndIn = 0;
}

/*****************************************************************************/
void MIDI::ActiverOut(int Index)
{
    uint Resultat;
//Désactive le port précédent
    DesactiverOut();
#ifdef WIN32
//Ouvre le port
    Resultat = midiOutOpen(&HndOut, Index, 0, 0, 0);
    if (Resultat) AffErrOut(Resultat);
#endif
#ifdef LINUX
#endif
}

void MIDI::DesactiverOut()
{
//Vérifie l'activation
    if (HndOut == 0) return;
#ifdef WIN32
//Ferme le port
    midiOutReset(HndOut);
    midiOutClose(HndOut);
#endif
#ifdef LINUX
#endif
    HndOut = 0;
}

/*****************************************************************************/
bool MIDI::EstConfigure()
{
    return (HndIn != 0 && HndOut != 0);
}

/*****************************************************************************/
void MIDI::AffAttente(bool Active)
{
    static QMessageBox * MsgBox;
    if (Active)
    {
    //Affiche la boite
        MsgBox = new QMessageBox(QMessageBox::Information, "FB01 SE:", "Waiting for device ...",
                                 0, mainApp->activeWindow());
        MsgBox->show();
        MsgBox->repaint();
    }else{
    //Supprime la boite
        MsgBox->done(0);
        delete MsgBox;
    }
}

/*****************************************************************************/
void MIDI::AffErrIn(uint Resultat)
{
    char Text[256];
//Récupère l'information
#ifdef WIN32
    midiInGetErrorTextA(Resultat, Text, 256);
#endif
#ifdef LINUX
#endif
//Affiche l'érreur
    QMessageBox::critical(mainApp->activeWindow(), "FB01 SE:", Text);
}

void MIDI::AffErrOut(uint Resultat)
{
    char Text[256];
//Récupère l'information
#ifdef WIN32
    midiOutGetErrorTextA(Resultat, Text, 256);
#endif
#ifdef LINUX
#endif
//Affiche l'érreur
    QMessageBox::critical(mainApp->activeWindow(), "FB01 SE:", Text);
}

/*****************************************************************************/
void MIDI::EnvMsgLng(MMSG * Msg, int Taille, bool Requete)
{
    uint Resultat;
//Vérifie l'ouverture
    if (HndOut == 0) return;
#ifdef WIN32
//Initialise l'entête
    MIDIHDR Head;
    memset(&Head, 0, sizeof(MIDIHDR));
    Head.dwBufferLength = Taille;
    Head.lpData = (char *) Msg;
//Prépare le message
    Resultat = midiOutPrepareHeader(HndOut, &Head, sizeof(MIDIHDR));
    if (Resultat) AffErrOut(Resultat);
//Envoie le message
    if (Requete) Attente = true;
    else Attente = false;
    Resultat = midiOutLongMsg(HndOut, &Head, sizeof(MIDIHDR));
    if (Resultat) AffErrOut(Resultat);
    midiOutUnprepareHeader(HndOut, &Head, sizeof(MIDIHDR));
#endif
#ifdef LINUX
#endif
}

void MIDI::EnvMsg(MMSG * Msg)
{
//Vérifie l'ouverture
    if (HndOut == 0) return;
#ifdef WIN32
//Envoie le message
    uint Resultat = midiOutShortMsg(HndOut, Msg->word);
    if(Resultat) AffErrOut(Resultat);
#endif
#ifdef LINUX
#endif
}

/*****************************************************************************/
void MIDI::ChoisirNoteChan(int Chan)
{
    NoteChan = Chan;
}

void MIDI::Note(uchar Note, uchar Velo)
{
    MMSG Msg;
//Active une note
    if (!HndOut) return;
    Msg.data[0] = 0x90 + (NoteChan & 0xF);
    Msg.data[1] = Note & 0x7F;
    Msg.data[2] = Velo & 0x7F;
    Msg.data[3] = 0;
//Envoie la note
    EnvMsg(&Msg);
}

/*****************************************************************************/
bool MIDI::AttMsg()
{
    QTime Timer;
//Démarre l'attente
    AffAttente(true);
    Timer.start();
#ifdef WIN32
//Attend le message    
    while(Attente)
    {
    //Gère les évenements
        mainApp->processEvents();
        if (Timer.elapsed() > ATTENTE)
        {
        //Affiche une erreur
            QMessageBox::critical(mainApp->activeWindow(), "FB01 SE:", "No device responded !");
        //Termine l'attente
            Attente = false;
            AffAttente(false);
            return false;
        }
    }
//Récupère les données
    memcpy(Donnees, Tampon, TAMPON);
    PreparerTampon();
#endif
//Termine l'attente
    AffAttente(false);
    return true;
}

/*****************************************************************************/
void MIDI::CopierMsg(MMSG * Temp, int Taille)
{
    Taille = (TAMPON < Taille) ? TAMPON : Taille;
    if (Temp != NULL) memcpy(Temp, Donnees, Taille);
}

uchar MIDI::LireMsg(int Pos)
{
    if (Pos < TAMPON)
        return Donnees[Pos];
    return 0;
}

bool MIDI::Recoit()
{
    return Attente;
}

/*****************************************************************************/
#ifdef WIN32
void MIDI::PreparerTampon()
{
    uint Resultat;
//Initialise  le tampon
    DePreparerTampon();
    memset(Tampon, 0, TAMPON);
    memset(&Header, 0, sizeof(MIDIHDR));
//Configure l'entête
    Header.dwBufferLength = TAMPON;
    Header.lpData = (char *) Tampon;
//Prépare le tampon
    Resultat = midiInPrepareHeader(HndIn, &Header, sizeof(MIDIHDR));
    if (Resultat) {AffErrIn(Resultat); return;}
//Ajoute à la liste
    midiInAddBuffer(HndIn, &Header, sizeof(MIDIHDR));
    Attente = false;
    Prepare = true;
}
#endif

#ifdef WIN32
void MIDI::DePreparerTampon()
{
    uint Resultat;
//Déprépare le tampon
    if (!Prepare) return;
    Resultat = midiInUnprepareHeader(HndIn, &Header, sizeof(MIDIHDR));
//Réinitialise
    Attente = false;
    Prepare = false;
    if (Resultat) AffErrIn(Resultat);
}
#endif

/*****************************************************************************/
void MIDI::BackupTampon(char * Chemin)
{
//Effectue un backup
    QFile Fichier((QString)Chemin);
    Fichier.open(QIODevice::WriteOnly);
    Fichier.write((char *) Donnees, TAMPON);
    Fichier.close();
}

/*****************************************************************************/
#ifdef WIN32
void WINAPI MIDI::Callback (ulong hmi, uint msg, ulong instance, ulong param1, ulong param2)
{
    if (msg == MIM_LONGDATA)
    {
    //Réception du sysex
        if (Attente) Attente = false;
        else TraiterSysEx();
    }
}

void MIDI::TraiterSysEx()
{
//Traite un sysex inattendu
    PreparerTampon();
}
#endif
