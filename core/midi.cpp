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

#include "midi.h"

/*****************************************************************************/
uint MIDI::hndIn   = 0;
uint MIDI::hndOut  = 0;
uint MIDI::hndCtrl = 0;
int MIDI::indIn    = -1;
int MIDI::indOut   = -1;
int MIDI::indCtrl  = -1;

MIDI::DriversStr MIDI::ins = {NULL, 0};
MIDI::DriversStr MIDI::outs = {NULL, 0};

/*****************************************************************************/
uchar MIDI::midiChannel = 0;
uchar MIDI::velocity    = 127;
uchar MIDI::sysChannel  = 0;

bool  MIDI::relaiIN = true;
bool  MIDI::relaiCTRL = true;
uchar MIDI::tampon[2][MIDI_LEN_TAMPON];

/*****************************************************************************/
#ifdef WIN32
    MIDIHDR MIDI::header = {0,};
    bool MIDI::prepare = false;
    bool MIDI::attente = false;
#endif

/*****************************************************************************/
void MIDI::EnumererDrivers()
{
//Libère les anciens drivers
    LibererDrivers();
//Enumére les drivers disponibles
#ifdef WIN32
//Compte les drivers
    ins.nb  = midiInGetNumDevs();
    outs.nb = midiOutGetNumDevs();
//Alloue les configurations
    if (ins.nb != 0) {
        ins.desc = malloc(sizeof(MIDIINCAPS) * ins.nb);
        if (ins.desc == NULL) {
            ins.nb = 0;
            throw Memory_ex("Unable to allocate driver list for MIDI IN !");
        }
    }
    if (outs.nb != 0) {
        outs.desc = malloc(sizeof(MIDIOUTCAPS) * outs.nb);
        if (outs.desc == NULL) {
            outs.nb = 0;
            throw Memory_ex("Unable to allocate driver list for MIDI OUT !");
        }
    }
//Récupère les configurations
    for (uint i = 0; i < ins.nb; i++)
        if (midiInGetDevCapsA(i, &((MIDIINCAPS *)ins.desc)[i], sizeof(MIDIINCAPS)) != MMSYSERR_NOERROR)
            throw MIDI_ex("Unable to get device caps for MIDI IN !");

    for (uint i = 0; i < outs.nb; i++)
        if (midiOutGetDevCapsA(i, &((MIDIOUTCAPS *)outs.desc)[i], sizeof(MIDIOUTCAPS)) != MMSYSERR_NOERROR)
            throw MIDI_ex("Unable to get device caps for MIDI OUT !");
#endif
#ifdef LINUX

#endif
}

void MIDI::LibererDrivers()
{
//Ferme les communications
#ifdef WIN32
    if (hndCtrl != 0) DesactiverCtrl();
    if (hndIn   != 0) DesactiverIn();
    if (hndOut  != 0) DesactiverOut();
//Libère les configurations
    if (ins.desc  != NULL) free(ins.desc);
    if (outs.desc != NULL) free(outs.desc);
    ins.nb = 0; outs.nb = 0;
//Réinitialise le gestionnaire
    hndIn = 0; hndOut = 0; hndCtrl = 0;
    indIn = -1; indOut = -1; indCtrl = -1;
#endif
}

/*****************************************************************************/
uint MIDI::NbDriversIn()
{
    return ins.nb;
}

uint MIDI::NbDriversOut()
{
    return outs.nb;
}

/*****************************************************************************/
char * MIDI::DriverIn(const int index)
{
#ifdef WIN32
    return ((MIDIINCAPS *)ins.desc)[index].szPname;
#endif
#ifdef LINUX
    return NULL;
#endif
}

char * MIDI::DriverOut(const int index)
{
#ifdef WIN32
    return ((MIDIOUTCAPS *)outs.desc)[index].szPname;
#endif
#ifdef LINUX
    return NULL;
#endif
}

/*****************************************************************************/
void MIDI::ActiverIn(const int index)
{
//Désactive l'ancien driver
    DesactiverIn();
#ifdef WIN32
//Ouvre le port en entrée
    if (index == indCtrl)
        throw MIDI_ex("Cannot select the same driver as MIDI CTRL !");
    if (midiInOpen(&hndIn, index, (ulong) CallbackIn, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to open MIDI IN !");
    if (midiInStart(hndIn) != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to start listenning to MIDI IN !");
#endif
#ifdef LINUX
#endif
//Sauvegarde l'index
    indIn = index;
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
    DePreparerTampon();
//Ferme le port
    midiInClose(hndIn);
#endif
#ifdef LINUX
#endif
//Reset le gestionnaire
    hndIn = 0; indIn = -1;
}

/*****************************************************************************/
void MIDI::ActiverOut(const int index)
{
//Désactive l'ancien driver
    DesactiverOut();
#ifdef WIN32
//Ouvre le port en sortie
    if (midiOutOpen(&hndOut, index, 0, 0, 0) != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to open MIDI OUT !");
#endif
#ifdef LINUX
#endif
//Sauvegarde l'index
    indOut = index;
}

void MIDI::DesactiverOut()
{
//Vérifie l'activation
    if (hndOut == 0) return;
#ifdef WIN32
//Arrête l'émission
    midiOutReset(hndOut);
//Ferme le port
    midiOutClose(hndOut);
#endif
#ifdef LINUX
#endif
//Reset le gestionnaire
    hndOut = 0; indOut = -1;
}

/*****************************************************************************/
void MIDI::ActiverCtrl(const int index)
{
//Désactive l'ancien driver
    DesactiverCtrl();
#ifdef WIN32
//Ouvre le port en entrée
    if (index == indIn)
        throw MIDI_ex("Cannot select the same driver as MIDI IN !");
    if (midiInOpen(&hndCtrl, index, (ulong) CallbackCtrl, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to open MIDI CTRL !");
    if (midiInStart(hndCtrl) != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to start listenning to MIDI CTRL !");
#endif
#ifdef LINUX
#endif
//Sauvegarde l'index
    indCtrl = index;
}

void MIDI::DesactiverCtrl()
{
//Vérifie l'activation
    if (hndCtrl == 0) return;
#ifdef WIN32
//Arrête l'écoute
    midiInStop(hndCtrl);
    midiInReset(hndCtrl);
//Ferme le port
    midiInClose(hndCtrl);
#endif
#ifdef LINUX
#endif
//Reset le gestionnaire
    hndCtrl = 0; indCtrl = -1;
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
    if (hndOut == 0) throw MIDI_ex("No MIDI OUT port openned !");
#ifdef WIN32
//Envoie le message
    if (midiOutShortMsg(hndOut, *(ulong *) msg) != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to send MIDI data !");
#endif
#ifdef LINUX
#endif
//Attente d'émission
    Sleep(MIDI_ATT_MSG);
}

void MIDI::EnvSysEx(uchar * sysEx, const int taille, const bool reponse)
{
    MIDIHDR head;
//Vérifie l'ouverture
    if (hndIn  == 0) throw MIDI_ex("No MIDI IN port openned !");
    if (hndOut == 0) throw MIDI_ex("No MIDI OUT port openned !");
#ifdef WIN32
//Créé l'entête
    memset(&head, 0, sizeof(MIDIHDR));
    head.dwBufferLength = taille;
    head.lpData = (char *) sysEx;
//Prépare le message
    if (midiOutPrepareHeader(hndOut, &head, sizeof(MIDIHDR)) != MMSYSERR_NOERROR)
        throw MIDI_ex("Unable to prepare header !");
//Prépare la réception
    if (reponse) {
        PreparerTampon();
        attente = true;
    }
//Envoie le message
    if (midiOutLongMsg(hndOut, &head, sizeof(MIDIHDR)) != MMSYSERR_NOERROR) {
    //Supprime l'attente de réception
        attente = false;
        midiOutUnprepareHeader(hndOut, &head, sizeof(MIDIHDR));
    //Envoie l'exception
        throw MIDI_ex("Unable to send MIDI data !");
    }
    midiOutUnprepareHeader(hndOut, &head, sizeof(MIDIHDR));
#endif
#ifdef LINUX
#endif
//Attente d'émission
    Sleep(MIDI_ATT_MSG);
}

void MIDI::RecSysEx(uchar * sysEx, const int taille)
{
    ulong cmpt = 0;
//Vérifie l'ouverture
    if (hndIn  == 0) throw MIDI_ex("No MIDI IN port openned !");
    if (!prepare) throw MIDI_ex("No response awaited !");
//Attend un message
    while (cmpt < MIDI_ATTENTE_MESSAGE) {
    //Recoit un nouveau message
        if (!attente) {
        //Recopie le message
            DePreparerTampon();
            memcpy(sysEx, tampon[1], taille);
            return;
        }
    //Attend le message
        sleep(MIDI_ATTENTE);
        cmpt ++;
    }
//Delai d'attente dépassé
    DePreparerTampon();
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
void MIDI::ActiverINToOUT(const bool active)
{
    relaiIN = active;
}

void MIDI::ActiverCTRLToOUT(const bool active)
{
    relaiCTRL = active;
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
        throw MIDI_ex("Unable to add buffer to MIDI IN !");
    }
    prepare = true;
}
#endif

#ifdef WIN32
void MIDI::DePreparerTampon()
{
    if (!prepare) return;
//Déprepare le tampon
    attente = false;
    midiInUnprepareHeader(hndIn, &header, sizeof(MIDIHDR));
    prepare = false;
}
#endif

/*****************************************************************************/
void MIDI::BackupTampon(char * chemin)
{
    FILE * fichier;
//Sauvegarde un backup binaire
    fichier = fopen(chemin, "wb+");
    if (fichier == NULL) return;
    fwrite(tampon[1], MIDI_LEN_TAMPON, 1, fichier);
    fclose(fichier);
}

/*****************************************************************************/
#ifdef WIN32
void WINAPI MIDI::CallbackIn(uint hmi, uint msg, uint instance, uint param1, uint param2)
{
    switch(msg) {
    case MIM_LONGDATA :
    //Récupère le sysEx
        if (!attente) return;
        memcpy(tampon[1], tampon[0], MIDI_LEN_TAMPON);
        attente = false;
    break;
    case MIM_DATA :
    //Relai les autres données
        if (hndOut != 0 && relaiIN) midiOutShortMsg(hndOut, param1);
    break;
    }
}

void WINAPI MIDI::CallbackCtrl(uint hmi, uint msg, uint instance, uint param1, uint param2)
{
    switch(msg) {
    case MIM_DATA :
    //Récupère les CCs
        if ((param1 & 0xF0) == 0xB0) {
            uchar CC = (param1 >> 8) & 0xFF;
            uchar valeur = (param1 >> 16) & 0xFF;
            Automation::ReagirCC(CC, valeur);
        }
    //Relai les autres données
        if (hndOut != 0 && relaiCTRL) midiOutShortMsg(hndOut, param1);
    break;
    }
}

#endif
