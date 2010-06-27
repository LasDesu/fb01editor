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
uchar  MIDI::velocity = 127;
uchar  MIDI::sysChannel = 0;
uchar  MIDI::tampon[2][MIDI_LEN_TAMPON] = {{0,},};

/*****************************************************************************/
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
    if (nbIns != 0) {
        ins = malloc(sizeof(MIDIINCAPS) * nbIns);
        if (ins == NULL) throw Memory_ex("Unable to allocate driver list for MIDI in !");
    }
    if (nbOuts != 0) {
        outs = malloc(sizeof(MIDIOUTCAPS) * nbOuts);
        if (outs == NULL) throw Memory_ex("Unable to allocate driver list for MIDI out !");
    }
//Récupère les configurations
    for (int i = 0; i < nbIns; i++)
        if (midiInGetDevCapsA(i, &((MIDIINCAPS *)ins)[i], sizeof(MIDIINCAPS))
            != MMSYSERR_NOERROR)
            throw MIDI_ex("Unable to get device caps for MIDI in !");

    for (int i = 0; i < nbOuts; i++)
        if (midiOutGetDevCapsA(i, &((MIDIOUTCAPS *)outs)[i], sizeof(MIDIOUTCAPS))
            != MMSYSERR_NOERROR)
            throw MIDI_ex("Unable to get device caps for MIDI out !");
#endif
#ifdef LINUX

#endif
}

void MIDI::LibererDrivers()
{
//Ferme les communications
#ifdef WIN32
    if (hndCtrl != 0) DesactiverCtrl();
    if (hndIn != 0)   DesactiverIn();
    if (hndOut != 0)  DesactiverOut();
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
void MIDI::ActiverIn(const int index)
{
//Désactive le driver
    DesactiverIn();
#ifdef WIN32
//Ouvre le port en entrée
    if (midiInOpen(&hndIn, index, (ulong) Callback, 0, CALLBACK_FUNCTION)
        != MMSYSERR_NOERROR) throw MIDI_ex("Unable to open MIDI in !");
#endif
#ifdef LINUX
#endif
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
void MIDI::ActiverOut(const int index)
{
//Désactive le port précédent
    DesactiverOut();
#ifdef WIN32
//Ouvre le port en sortie
    if (midiOutOpen(&hndOut, index, 0, 0, 0)
        != MMSYSERR_NOERROR) throw MIDI_ex("Unable to open MIDI out !");
#endif
#ifdef LINUX
#endif
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
void MIDI::ActiverCtrl(const int index)
{
//Désactive le port précédent
    if (!hndOut) throw MIDI_ex("No openned MIDI out port !");
    DesactiverCtrl();
#ifdef WIN32
//Ouvre le port
    if (midiInOpen(&hndCtrl, index, 0, 0, CALLBACK_NULL)
        != MMSYSERR_NOERROR) throw MIDI_ex("Unable to open MIDI ctrl !");
    if (midiConnect(hndCtrl, hndOut, NULL)
        != MMSYSERR_NOERROR) throw MIDI_ex("Unable to connect MIDI ctrl to MIDI out");
#endif
#ifdef LINUX
#endif
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
void MIDI::EnvMsg(uchar * msg)
{
//Vérifie l'ouverture
    if (hndOut == 0) throw MIDI_ex("No openned MIDI out port !");
#ifdef WIN32
//Envoie le message
    if (midiOutShortMsg(hndOut, *(ulong *) msg) != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to send MIDI data !");
#endif
#ifdef LINUX
#endif
}

void MIDI::EnvSysEx(uchar * sysEx, const int taille)
{
//Vérifie l'ouverture
    if (hndIn == 0)  throw MIDI_ex("No openned MIDI in port !");
    if (hndOut == 0) throw MIDI_ex("No openned MIDI out port !");
#ifdef WIN32
//Créé l'entête
    MIDIHDR head;
    memset(&head, 0, sizeof(MIDIHDR));
    head.dwBufferLength = taille;
    head.lpData = (char *) sysEx;
//Prépare le message
    if (midiOutPrepareHeader(hndOut, &head, sizeof(MIDIHDR))
        != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to prepare header !");
//Prépare la réception
    PreparerTampon();
    attente = true;
    midiInStart(hndIn);
//Envoie le message
    if (midiOutLongMsg(hndOut, &head, sizeof(MIDIHDR))
        != MMSYSERR_NOERROR) {
    //Supprime l'attente de réception
        attente = false;
        midiInStop(hndIn);
        midiOutUnprepareHeader(hndOut, &head, sizeof(MIDIHDR));
    //Envoie l'exception
        throw MIDI_ex("Unable to send MIDI data !");
    }
    midiOutUnprepareHeader(hndOut, &head, sizeof(MIDIHDR));
#endif
#ifdef LINUX
#endif
}

void MIDI::RecSysEx(uchar * sysEx, const int taille)
{
    ulong cmpt = 0;
//Attend un message
    while (cmpt < MIDI_ATTENTE_MESSAGE) {
    //Recoit un nouveau message
        if (!attente) {
        //Recopie le message
            midiInStop(hndIn);
            DePreparerTampon();
            memcpy(sysEx, tampon[1], taille);
            return;
        }
    //Attend le message
        sleep(MIDI_ATTENTE);
        cmpt ++;
    }
    throw MIDI_ex("No MIDI data received !");
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

void MIDI::ChoisirVelocity(const uchar velo)
{
    velocity = velo;
}

uchar MIDI::Velocity()
{
    return velocity;
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
void MIDI::NoteOn(const uchar note)
{
    uchar msg[4];
//Active une note
    msg[0] = 0x90 + (midiChannel & 0xF);
    msg[1] = note & 0x7F;
    msg[2] = velocity & 0x7F;
    msg[3] = 0;
//Envoie la note
    EnvMsg(msg);
}

void MIDI::NoteOff(const uchar note)
{
    uchar msg[4];
//Active une note
    msg[0] = 0x90 + (midiChannel & 0xF);
    msg[1] = note & 0x7F;
    msg[2] = 0;
    msg[3] = 0;
//Envoie la note
    EnvMsg(msg);
}

void MIDI::AllNotesOff()
{
    uchar msg[4];
//Désactive toutes les notes
    msg[0] = 0xB0 + (midiChannel & 0xF);
    msg[1] = 0x7B;
    msg[2] = 0;
    msg[3] = 0;
//Envoie la commande
    EnvMsg(msg);
}

/*****************************************************************************/
#ifdef WIN32
void MIDI::PreparerTampon()
{
//Initialise le tampon
    if (prepare) return;
    attente = false;
    memset(tampon[0], 0, MIDI_LEN_TAMPON);
    memset(&header, 0, sizeof(MIDIHDR));
//Configure l'entête
    header.dwBufferLength = MIDI_LEN_TAMPON;
    header.lpData = (char *) tampon;
//Prépare le tampon
    if (midiInPrepareHeader(hndIn, &header, sizeof(MIDIHDR))
        != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to prepare header !");
//Ajoute à la liste
    if (midiInAddBuffer(hndIn, &header, sizeof(MIDIHDR))
        != MMSYSERR_NOERROR) {
        midiInUnprepareHeader(hndIn, &header, sizeof(MIDIHDR));
        throw MIDI_ex("Unable to assign buffer to MIDI in !");
    }
    prepare = true;
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
        memcpy(tampon[1], tampon[0], MIDI_LEN_TAMPON);
        attente = false;
    }
}
#endif
