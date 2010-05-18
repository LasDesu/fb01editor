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

/*****************************************************************************/
uint   MIDI::hndIn   = 0;
uint   MIDI::hndOut  = 0;
uint   MIDI::hndCtrl = 0;
void * MIDI::ins  = NULL;
void * MIDI::outs = NULL;
int    MIDI::nbIns  = 0;
int    MIDI::nbOuts = 0;
uchar  MIDI::midiChannel = 0;
uchar  MIDI::sysChannel = 0;
uchar  MIDI::tampon[2][MIDI_LEN_TAMPON] = {{0,},};

#ifdef WIN32
    MIDIHDR MIDI::header = {0,};
    bool MIDI::prepare = false;
    bool MIDI::attente = false;
#endif

/*****************************************************************************/
void MIDI::EnumererDrivers()
{
//Libère les drivers
    LibererDrivers();
//Enumére les drivers disponibles
#ifdef WIN32
//Compte les drivers
    nbIns  = midiInGetNumDevs();
    nbOuts = midiOutGetNumDevs();
//Alloue les configurations
    if (nbIns != 0)
        ins = malloc(sizeof(MIDIINCAPS) * nbIns);
    if (nbOuts != 0)
        outs = malloc(sizeof(MIDIOUTCAPS) * nbOuts);
//Récupère les configurations
    for (int i = 0; i < nbIns; i++)
        midiInGetDevCapsA(i, &((MIDIINCAPS *)ins)[i], sizeof(MIDIINCAPS));
    for (int i = 0; i < nbOuts; i++)
        midiOutGetDevCapsA(i, &((MIDIOUTCAPS *)outs)[i], sizeof(MIDIOUTCAPS));
#endif
#ifdef LINUX
#endif
}

void MIDI::LibererDrivers()
{
//Ferme les communications
#ifdef WIN32
    if (hndCtrl != 0) DesactiverCtrl();
    if (hndIn != 0) DesactiverIn();
    if (hndOut != 0) DesactiverOut();
//Libère les configurations
    if (ins != NULL) free(ins);
    if (outs != NULL) free(outs);
//Réinitialise la liste
    nbIns  = 0; ins  = NULL;
    nbOuts = 0; outs = NULL;
#endif
}

/*****************************************************************************/
uint MIDI::NbDriversIn()
{
    return nbIns;
}

uint MIDI::NbDriversOut()
{
    return nbOuts;
}

uint MIDI::NbDriversCtrl()
{
    return nbIns;
}

/*****************************************************************************/
char * MIDI::DriverIn(const int index)
{
#ifdef WIN32
    return ((MIDIINCAPS *)ins)[index].szPname;
#endif
#ifdef LINUX
    return NULL;
#endif
}

char * MIDI::DriverOut(const int index)
{
#ifdef WIN32
    return ((MIDIOUTCAPS *)outs)[index].szPname;
#endif
#ifdef LINUX
    return NULL;
#endif
}

char * MIDI::DriverCtrl(const int index)
{
#ifdef WIN32
    return ((MIDIOUTCAPS *)ins)[index].szPname;
#endif
#ifdef LINUX
    return NULL;
#endif
}

/*****************************************************************************/
uint MIDI::ActiverIn(const int index)
{
//Désactive le driver
    DesactiverIn();
#ifdef WIN32
//Ouvre le port
    uint res = midiInOpen(&hndIn, index, (ulong) Callback, 0, CALLBACK_FUNCTION);
    if (res) return MIDI_ERREUR_OPEN_IN;
#endif
#ifdef LINUX
#endif
    return MIDI_ERREUR_RIEN;
}

void MIDI::DesactiverIn()
{
//Vérifie l'activation
    if (hndIn == 0) return;
#ifdef WIN32
//Arrête l'écoute
    attente = true;
    midiInStop(hndIn);
    midiInReset(hndIn);
//Libère le tampon
    DePreparerTampon();
//Ferme le port
    midiInClose(hndIn);
#endif
#ifdef LINUX
#endif
//Reset le handle
    hndIn = 0;
}

/*****************************************************************************/
uint MIDI::ActiverOut(const int index)
{
//Désactive le port précédent
    DesactiverOut();
#ifdef WIN32
//Ouvre le port
    uint res = midiOutOpen(&hndOut, index, 0, 0, 0);
    if (res) return MIDI_ERREUR_OPEN_OUT;
#endif
#ifdef LINUX
#endif
    return MIDI_ERREUR_RIEN;
}

void MIDI::DesactiverOut()
{
//Vérifie l'activation
    if (hndOut == 0) return;
#ifdef WIN32
//Désactive le controlleur
    DesactiverCtrl();
//Ferme le port
    midiOutReset(hndOut);
    midiOutClose(hndOut);
#endif
#ifdef LINUX
#endif
//Reset le handle
    hndOut = 0;
}

/*****************************************************************************/
uint MIDI::ActiverCtrl(const int index)
{
//Désactive le port précédent
    if (hndOut == 0) return MIDI_ERREUR_NOOUT;
    DesactiverCtrl();
#ifdef WIN32
//Ouvre le port
    uint res = midiInOpen(&hndCtrl, index, 0, 0, CALLBACK_NULL);
    if (res) return MIDI_ERREUR_OPEN_IN;
    res = midiConnect(hndCtrl, hndOut, NULL);
    if (res) return MIDI_ERREUR_CONNECT;
#endif
#ifdef LINUX
#endif
    return MIDI_ERREUR_RIEN;
}

void MIDI::DesactiverCtrl()
{
//Vérifie l'activation
    if (hndCtrl == 0) return;
#ifdef WIN32
//Ferme le port
    midiDisconnect(hndCtrl, hndOut, NULL);
    midiInReset(hndCtrl);
    midiInClose(hndCtrl);
#endif
#ifdef LINUX
#endif
//Reset le handle
    hndCtrl = 0;
}

/*****************************************************************************/
bool MIDI::InOk()
{
    return hndIn != 0;
}

bool MIDI::OutOk()
{
    return hndOut != 0;
}

bool MIDI::CtrlOk()
{
    return hndCtrl != 0;
}

/*****************************************************************************/
uint MIDI::EnvSysEx(uchar * sysEx, const int taille)
{
//Vérifie l'ouverture
    if (hndIn == 0) return MIDI_ERREUR_NOIN;
    if (hndOut == 0) return MIDI_ERREUR_NOOUT;
#ifdef WIN32
//Créé l'entête
    MIDIHDR head;
    memset(&head, 0, sizeof(MIDIHDR));
    head.dwBufferLength = taille;
    head.lpData = (char *) sysEx;
//Prépare le message
    uint res = midiOutPrepareHeader(hndOut, &head, sizeof(MIDIHDR));
    if (res) return MIDI_ERREUR_PREPARE;
//Prepare la reception
    if (PreparerTampon() != MIDI_ERREUR_RIEN) {
        midiOutUnprepareHeader(hndOut, &head, sizeof(MIDIHDR));
        return MIDI_ERREUR_PREPARE;
    }
    attente = true;
    midiInStart(hndIn);
//Envoie le message
    res = midiOutLongMsg(hndOut, &head, sizeof(MIDIHDR));
    midiOutUnprepareHeader(hndOut, &head, sizeof(MIDIHDR));
    if (res) {
        attente = false;
        midiInStop(hndIn);
        return MIDI_ERREUR_SEND;
    }
#endif
#ifdef LINUX
#endif
    return MIDI_ERREUR_RIEN;
}

uint MIDI::RecSysEx(uchar * sysEx, const int taille)
{
    ulong cmpt = 0;
//Attend un message
    if (taille > MIDI_LEN_TAMPON) return MIDI_ERREUR_PREPARE;
    while (cmpt > MIDI_ATTENTE_MESSAGE) {
    //Recoit un nouveau message
        if (!attente) {
        //Recopie le message
            midiInStop(hndIn);
            DePreparerTampon();
            memcpy(tampon[1], sysEx, taille);
            return MIDI_ERREUR_RIEN;
        }
    //Attend le message
        sleep(MIDI_ATTENTE);
        cmpt ++;
    }
    return MIDI_ERREUR_TIMEOUT;
}

/*****************************************************************************/
void MIDI::ChoisirMidiChannel(const uchar channel)
{
    midiChannel = channel;
}

uchar MIDI::MidiChannel()
{
    return midiChannel;
}

void MIDI::ChoisirSysChannel(const uchar channel)
{
    sysChannel = channel;
}

uchar MIDI::SysChannel()
{
    return sysChannel;
}

/*****************************************************************************/
void MIDI::Note(const uchar note, const uchar velo)
{
    uchar msg[3];
//Active une note
    if (!hndOut) return;
    msg[0] = 0x90 + (midiChannel & 0xF);
    msg[1] = note & 0x7F;
    msg[2] = velo & 0x7F;
//Envoie la note
    EnvSysEx(msg, 3);
}

/*****************************************************************************/
#ifdef WIN32
uint MIDI::PreparerTampon()
{
//Initialise le tampon
    if (prepare) return MIDI_ERREUR_RIEN;
    memset(tampon[0], 0, MIDI_LEN_TAMPON);
    memset(&header, 0, sizeof(MIDIHDR));
//Configure l'entête
    header.dwBufferLength = MIDI_LEN_TAMPON;
    header.lpData = (char *) tampon;
//Prépare le tampon
    uint res = midiInPrepareHeader(hndIn, &header, sizeof(MIDIHDR));
    if (res) return MIDI_ERREUR_PREPARE;
//Ajoute à la liste
    res = midiInAddBuffer(hndIn, &header, sizeof(MIDIHDR));
    if (res) {
        midiInUnprepareHeader(hndIn, &header, sizeof(MIDIHDR));
        return MIDI_ERREUR_PREPARE;
    }
 //Reset les drapeaux
    attente = false;
    prepare = true;
    return MIDI_ERREUR_RIEN;
}
#endif

#ifdef WIN32
void MIDI::DePreparerTampon()
{
//Déprépare le tampon
    if (!prepare) return;
    midiInUnprepareHeader(hndIn, &header, sizeof(MIDIHDR));
//Reset les drapeaux
    attente = false;
    prepare = false;
}
#endif

/*****************************************************************************/
void MIDI::BackupTampon(char * chemin)
{
    FILE * fichier;
    fichier = fopen(chemin, "wb+");
    if (fichier == NULL) return;
    fwrite(tampon[1], MIDI_LEN_TAMPON, 1, fichier);
    fclose(fichier);
}

/*****************************************************************************/
#ifdef WIN32
void WINAPI MIDI::Callback (uint hmi, uint msg, uint instance, uint param1, uint param2)
{
    if (msg == MM_MIM_LONGDATA && attente) {
    //Recopie du message
        memcpy(tampon[0], tampon[1], MIDI_LEN_TAMPON);
        attente = false;
    }
}
#endif
