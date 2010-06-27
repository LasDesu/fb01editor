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

#include "operateur.h"

/*****************************************************************************/
Operateur::Operateur(const uchar id, uchar * sysEx)
         : Edit(id, sysEx, OPERATOR_LEN_SYSEX, OPERATOR_NB_PARAM, 0)
{
    this->instru = 0;
}

Operateur::~Operateur()
{
}

/*****************************************************************************/
void Operateur::AssocierInstrument(int index)
{
    this->instru = index;
}

/*****************************************************************************/
const uchar initTab[OPERATOR_NB_PARAM] = {127, 0, 0, 0, 0, 0, 0, 0, 31, 1, 0, 31, 0, 0, 15, 15};
void Operateur::Initialiser()
{
    for (int i=0; i < OPERATOR_NB_PARAM; i++)
        EcrireParam(i, initTab[i], true);
}

/*****************************************************************************/
uchar Operateur::LireParam(const uchar param)
{
    try {
        switch(param) {
        case OPERATOR_LEVEL :
            return LireParam2Oct(0x0);
        case OPERATOR_LEVEL_CURB :
            return ((LireParam2Oct(0x1) >> 7) & 0x1)
                  +((LireParam2Oct(0x3) >> 6) & 0x2);
        case OPERATOR_LEVEL_VELOCITY :
            return (LireParam2Oct(0x1) >> 4) & 0x7;
        case OPERATOR_LEVEL_DEPTH :
            return (LireParam2Oct(0x2) >> 4) & 0xF;
        case OPERATOR_ADJUST :
            return LireParam2Oct(0x2) & 0xF;
        case OPERATOR_FINE :
            return (LireParam2Oct(0x3) >> 4) & 0x7;
        case OPERATOR_MULTIPLE :
            return LireParam2Oct(0x3) & 0xF;
        case OPERATOR_RATE_DEPTH :
            return (LireParam2Oct(0x4) >> 6) & 0x3;
        case OPERATOR_ATTACK :
            return LireParam2Oct(0x4) & 0x1F;
        case OPERATOR_MODULATOR :
            return (LireParam2Oct(0x5) >> 7) & 0x1;
        case OPERATOR_ATTACK_VELOCITY :
            return LireParam2Oct(0x5) >> 5 & 0x3;
        case OPERATOR_DECAY1 :
            return LireParam2Oct(0x5) & 0x1F;
        case OPERATOR_COARSE :
            return (LireParam2Oct(0x6) >> 6) & 0x3;
        case OPERATOR_DECAY2 :
            return (LireParam2Oct(0x6) & 0x1F);
        case OPERATOR_SUSTAIN :
            return (LireParam2Oct(0x7) >> 4) & 0xF;
        case OPERATOR_RELEASE :
            return LireParam2Oct(0x7) & 0xF;
        default : return 0;
        }
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
        return 0;
    }
}

void Operateur::EcrireParam(const uchar param, const uchar valeur, const bool envoi)
{
    uchar byte;
    try {
        switch(param) {
        case OPERATOR_LEVEL :
            byte = valeur & 0x7F;
            EcrireParam2Oct(0x0, byte, envoi);
        break;
        case OPERATOR_LEVEL_CURB :
            byte  = LireParam2Oct(0x1) & 0x7F;
            byte += (valeur & 0x1) << 7;
            EcrireParam2Oct(0x1, byte, envoi);
            byte  = LireParam2Oct(3) & 0x7F;
            byte += (valeur & 0x2) << 6;
            EcrireParam2Oct(0x3, byte, envoi);
        break;
        case OPERATOR_LEVEL_VELOCITY :
            byte  = LireParam2Oct(0x1) & 0x8F;
            byte += (valeur & 0x7) << 4;
            EcrireParam2Oct(0x1, byte, envoi);
        break;
        case OPERATOR_LEVEL_DEPTH :
            byte  = LireParam2Oct(2) & 0xF;
            byte += (valeur & 0xF) << 4;
            EcrireParam2Oct(2, byte, envoi);
        break;
        case OPERATOR_ADJUST :
            byte  = LireParam2Oct(0x2) & 0xF0;
            byte += valeur & 0xF;
            EcrireParam2Oct(0x2, byte, envoi);
        break;
        case OPERATOR_FINE :
            byte = LireParam2Oct(0x3) & 0x8F;
            byte += (valeur & 0x7) << 4;
            EcrireParam2Oct(0x3, byte, envoi);
        break;
        case OPERATOR_MULTIPLE :
            byte = LireParam2Oct(0x3) & 0xF0;
            byte += valeur & 0xF;
            EcrireParam2Oct(0x3, byte, envoi);
        break;
        case OPERATOR_RATE_DEPTH :
            byte  = LireParam2Oct(4) & 0x3F;
            byte += (valeur & 0x3) << 6;
            EcrireParam2Oct(4, byte, envoi);
        break;
        case OPERATOR_ATTACK :
            byte = LireParam2Oct(0x4) & 0xE0;
            byte += valeur & 0x1F;
            EcrireParam2Oct(0x4, byte, envoi);
        break;
        case OPERATOR_MODULATOR :
            byte = LireParam2Oct(0x5) & 0x7F;
            byte += (valeur & 0x1) << 7;
            EcrireParam2Oct(0x5, byte, envoi);
        break;
        case OPERATOR_ATTACK_VELOCITY :
            byte  = LireParam2Oct(0x5) & 0x9F;
            byte += (valeur & 0x3) << 5;
            EcrireParam2Oct(0x5, byte, envoi);
        break;
        case OPERATOR_DECAY1 :
            byte = LireParam2Oct(0x5) & 0xE0;
            byte += valeur & 0x1F;
            EcrireParam2Oct(0x5, byte, envoi);
        break;
        case OPERATOR_COARSE :
            byte = LireParam2Oct(0x6) & 0x3F;
            byte += (valeur & 0x3) << 6;
            EcrireParam2Oct(0x6, byte, envoi);
        break;
        case OPERATOR_DECAY2 :
            byte = LireParam2Oct(0x6) & 0xE0;
            byte += valeur & 0x1F;
            EcrireParam2Oct(0x6, byte, envoi);
        break;
        case OPERATOR_SUSTAIN :
            byte = LireParam2Oct(0x7) & 0xF;
            byte += (valeur & 0xF) << 4;
            EcrireParam2Oct(0x7, byte, envoi);
        break;
        case OPERATOR_RELEASE :
            byte = LireParam2Oct(0x7) & 0xF0;
            byte += valeur & 0xF;
            EcrireParam2Oct(0x7, byte, envoi);
        break;
        default : return;
        }
    }catch(MIDI_ex ex) {
        QMessageBox::information(NULL, "FB01 SE:", ex.Info());
    }
}

/*****************************************************************************/
void Operateur::Envoyer(const uint param)
{
    uchar envOperateur[9] = {0xF0, 0x43, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7};
//Construit le message
    envOperateur[3] = MIDI::SysChannel();
    envOperateur[4] = 0x18 + (instru & 0x7);
//Envoi les changements
    envOperateur[5] = (param + (3 - id) * 0x8 + 0x50) & 0x7F;
    envOperateur[6] = sysEx[param * 2] & 0xF;
    envOperateur[7] = sysEx[param * 2 + 1] >> 4;
//Envoi le message
    MIDI::EnvSysEx(envOperateur, 9);
}
