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

#include "instrument.h"

/*****************************************************************************/
Instrument::Instrument(const uchar id, uchar * sysEx)
          : Edit(id, sysEx, INSTRU_LEN_SYSEX, INSTRU_NB_PARAM, 0)
{
    CreerCallbacks();
}

Instrument::~Instrument()
{
}

/*****************************************************************************/
const uchar initTab[INSTRU_NB_PARAM] = {1, 0, 127, 0, 2, 0, 0, 2, 127, 63, 0, 0, 4, 1, 1};
void Instrument::Initialiser()
{
    for (int i = 0; i < INSTRU_NB_PARAM; i++)
        EcrireParam((INSTRU_PARAM) i, initTab[i], true);
}

/*****************************************************************************/
uchar Instrument::LireParam(const INSTRU_PARAM param)
{
    uchar temp;
    try {
        switch(param) {
        case INSTRU_NB_NOTES :
            return LireParam1Oct(0) & 0xF;
        case INSTRU_CHANNEL :
            return LireParam1Oct(1) & 0xF;
        case INSTRU_UPPER :
            return LireParam1Oct(2);
        case INSTRU_LOWER :
            return LireParam1Oct(3) & 0xF;
        case INSTRU_BANK :
            return LireParam1Oct(4) & 0x7;
        case INSTRU_VOICE :
            return LireParam1Oct(5);
        case INSTRU_DETUNE :
            temp = LireParam1Oct(6);
            if (temp > 63) temp += 0x80;
            return temp;
        case INSTRU_TRANS :
            return LireParam1Oct(7) & 0x7;
        case INSTRU_VOLUME :
            return LireParam1Oct(8);
        case INSTRU_PAN :
            return LireParam1Oct(9);
        case INSTRU_LFO :
            return LireParam1Oct(10) & 0x1;
        case INSTRU_PORTAMENTO :
            temp = LireParam1Oct(11);
            return temp;
        case INSTRU_PITCHBEND :
            return LireParam1Oct(12) & 0xF;
        case INSTRU_POLY :
            return LireParam1Oct(13) & 0x1;
        case INSTRU_CONROLLER :
            return LireParam1Oct(14) & 0x7;
        default: return 0;
        }
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
        return 0;
    }
}

void Instrument::EcrireParam(const INSTRU_PARAM param, const uchar valeur, const bool envoi)
{
    try {
        switch(param) {
        case INSTRU_NB_NOTES :
            EcrireParam1Oct(0, valeur & 0xF, envoi);
        break;
        case INSTRU_CHANNEL :
            EcrireParam1Oct(1, valeur & 0xF, envoi);
        break;
        case INSTRU_UPPER :
            EcrireParam1Oct(2, valeur & 0xF, envoi);
        break;
        case INSTRU_LOWER :
            EcrireParam1Oct(3, valeur & 0xF, envoi);
        break;
        case INSTRU_BANK :
            EcrireParam1Oct(4, valeur & 0x7, envoi);
        break;
        case INSTRU_VOICE :
            EcrireParam1Oct(5, valeur, envoi);
        break;
        case INSTRU_DETUNE :
            EcrireParam1Oct(6, valeur, envoi);
        break;
        case INSTRU_TRANS :
            EcrireParam1Oct(7, valeur & 0x7, envoi);
        break;
        case INSTRU_VOLUME :
            EcrireParam1Oct(8, valeur, envoi);
        break;
        case INSTRU_PAN :
            EcrireParam1Oct(9, valeur, envoi);
        break;
        case INSTRU_LFO :
            EcrireParam1Oct(10, valeur & 0x1, envoi);
        break;
        case INSTRU_PORTAMENTO :
            EcrireParam1Oct(11, valeur, envoi);
        break;
        case INSTRU_PITCHBEND :
            EcrireParam1Oct(12, valeur & 0xF, envoi);
        break;
        case INSTRU_POLY :
            EcrireParam1Oct(13, valeur & 0x1, envoi);
        break;
        case INSTRU_CONROLLER :
            EcrireParam1Oct(14, valeur & 0x7, envoi);
        break;
        default : return;
        }
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
    }
}

/*****************************************************************************/
void Instrument::Envoyer(const uint param)
{
    uchar envInstrument[8] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x00, 0x00, 0xF7};
//Construit le message
    envInstrument[3] = MIDI::SysChannel();
    envInstrument[4] = 0x18 + (id & 0x7);
//Envoi les changements
    envInstrument[5] = param & 0x1F;
    envInstrument[6] = sysEx[param] & 0x7F;
//Envoi le message
    MIDI::EnvSysEx(envInstrument, 8);
}

/*****************************************************************************/
void Instrument::CreerCallbacks()
{
    char base[AUTO_LEN_NOM], text[AUTO_LEN_NOM];
    char num;
//Créé le nom de base
    num = '1' + id;
    strcpy(base, "Instrument ");
    strncat(base, &num, 1);
//Enregistre les callbacks
    strcpy(text, base); strcat(text, " volume");
    Automation::AjouterCallback(this,INSTRU_VOLUME, text);
    strcpy(text, base); strcat(text, " pan");
    Automation::AjouterCallback(this, INSTRU_PAN, text);
    strcpy(text, base); strcat(text, " transpose");
    Automation::AjouterCallback(this, INSTRU_TRANS, text);
    strcpy(text, base); strcat(text, " detune");
    Automation::AjouterCallback(this, INSTRU_DETUNE, text);
}

void Instrument::AppelerCallback(const uint index, const uchar valeur)
{
    switch(index) {
    case INSTRU_VOLUME : EcrireParam(INSTRU_VOLUME, valeur, true); break;
    case INSTRU_PAN : EcrireParam(INSTRU_PAN, valeur, true); break;
    case INSTRU_TRANS : EcrireParam(INSTRU_TRANS, valeur >> 4, true); break;
    case INSTRU_DETUNE : EcrireParam(INSTRU_DETUNE, valeur, true); break;
    }
}
