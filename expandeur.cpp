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

#include "expandeur.h"
#include "midi.h"

uchar EXPANDEUR::SysChan = 0;

/*****************************************************************************/
void EXPANDEUR::ChargerBanque(uchar Banque)
{
    MMSG Msg[2];
    MMSG Rep[815];
//Envoi la commande
    Msg[0].data[0] = 0xF0;
    Msg[0].data[1] = 0x43;
    Msg[0].data[2] = 0x75;
    Msg[0].data[3] = SysChan;
    Msg[1].data[0] = 0x20;
    Msg[1].data[1] = 0x00;
    Msg[1].data[2] = Banque & 0xF;
    Msg[1].data[3] = 0xF7;
//Vérifie la réponse

}

void EXPANDEUR::SauverBanque(uchar Banque)
{
}

/*****************************************************************************/
void EXPANDEUR::ActiverOps(uchar Inst, bool Op1, bool Op2, bool Op3, bool Op4)
{
    uchar Octet = 0;
//Active les opérateurs
    if (Op1) Octet += 0x8;
    if (Op2) Octet += 0x10;
    if (Op3) Octet += 0x20;
    if (Op4) Octet += 0x40;
    EcrireVoiceParam(Inst, 0x0B, Octet);
}

void EXPANDEUR::ChangerNom(uchar Inst, const char * Nom)
{
    uchar Octet[7];
//Recopie la chaine
    memset(Octet, 0, 7);
    strncpy((char *)Octet, Nom, 7);
//Envoie le nom
    for (uchar i = 0; i < 7; i++)
        EcrireVoiceParam(Inst, i, Octet[i]);
}

void EXPANDEUR::ChangerVoicex09(uchar Inst, bool Load, uchar AMD)
{
    uchar Octet = 0;
//Compose le paquet
    if (Load) Octet += 0x80;
    Octet += AMD & 0x7F;
    EcrireVoiceParam(Inst, 0x09, Octet);
}

void EXPANDEUR::ChangerVoicex0A(uchar Inst, bool Sync, uchar PMD)
{
    uchar Octet = 0;
//Compose le paquet
    if (Sync) Octet += 0x80;
    Octet += PMD & 0x7F;
    EcrireVoiceParam(Inst, 0x0A, Octet);
}

void EXPANDEUR::ChangerVoicex0C(uchar Inst, uchar Feedback, uchar Algo)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (Feedback & 0x7) << 3;
    Octet += Algo & 0x7;
    EcrireVoiceParam(Inst, 0x0C, Octet);
}

void EXPANDEUR::ChangerVoicex0D(uchar Inst, uchar PMS, uchar AMS)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (PMS & 0x7) << 4;
    Octet += AMS & 0x3;
    EcrireVoiceParam(Inst, 0x0D, Octet);
}

void EXPANDEUR::ChangerVoicex0E(uchar Inst, uchar Wave)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (Wave & 0x3) << 5;
    EcrireVoiceParam(Inst, 0x0E, Octet);
}

void EXPANDEUR::ChangerVoicex3A(uchar Inst, bool Poly, uchar Porta)
{
    uchar Octet = 0;
//Compose le paquet
    if (Poly) Octet += 0x80;
    Octet += Porta & 0x7F;
    EcrireVoiceParam(Inst, 0x3A, Octet);
}

void EXPANDEUR::ChangerVoicex3B(uchar Inst, uchar Pmdctl, uchar Pitch)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (Pmdctl & 0x7) << 4;
    Octet += Pitch & 0xF;
    EcrireVoiceParam(Inst, 0x3B, Octet);
}

/*****************************************************************************/
void EXPANDEUR::ChangerOpx01(uchar Inst, uchar Op, uchar KeyCurb, uchar Velocity)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (KeyCurb & 0x1) << 7;
    Octet += (Velocity & 0x7) << 4;
    EcrireOpParam(Inst, Op, 0x01, Octet);
}

void EXPANDEUR::ChangerOpx02(uchar Inst, uchar Op, uchar LvlDph, uchar Adjust)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (LvlDph & 0xF) << 4;
    Octet += Adjust & 0xF;
    EcrireOpParam(Inst, Op, 0x02, Octet);
}

void EXPANDEUR::ChangerOpx03(uchar Inst, uchar Op, uchar KeyCurb, uchar Fine, uchar Multiple)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (KeyCurb & 0x2) << 6;
    Octet += (Fine & 0x7) << 4;
    Octet += Multiple & 0xF;
    EcrireOpParam(Inst, Op, 0x03, Octet);
}

void EXPANDEUR::ChangerOpx04(uchar Inst, uchar Op, uchar RateDph, uchar AR)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (RateDph & 0x3) << 6;
    Octet += AR & 0x1F;
    EcrireOpParam(Inst, Op, 0x04, Octet);
}

void EXPANDEUR::ChangerOpx05(uchar Inst, uchar Op, bool Carrier, uchar VeloSens, uchar DR1)
{
    uchar Octet = 0;
//Compose le paquet
    if (Carrier) Octet += 0x80;
    Octet += (VeloSens & 0x3) << 5;
    Octet += DR1 & 0x1F;
    EcrireOpParam(Inst, Op, 0x05, Octet);
}

void EXPANDEUR::ChangerOpx06(uchar Inst, uchar Op, uchar Coarse, uchar DR2)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (Coarse & 0x3) << 6;
    Octet += DR2 & 0x1F;
    EcrireOpParam(Inst, Op, 0x06, Octet);
}

void EXPANDEUR::ChangerOpx07(uchar Inst, uchar Op, uchar SL, uchar RR)
{
    uchar Octet = 0;
//Compose le paquet
    Octet += (SL & 0xF) << 4;
    Octet += RR & 0xF;
    EcrireOpParam(Inst, Op, 0x07, Octet);
}

/*****************************************************************************/
void EXPANDEUR::EcrireInstParam(uchar Inst, uchar Param, uchar Valeur)
{
    MMSG Msg[2];
//Construit le message
    Msg[0].data[0] = 0xF0;
    Msg[0].data[1] = 0x43;
    Msg[0].data[2] = 0x75;
    Msg[0].data[3] = SysChan;
    Msg[1].data[0] = 0x18 + (Inst & 0x7);
    Msg[1].data[1] = Param & 0x1F;
    Msg[1].data[2] = Valeur & 0x7F;
    Msg[1].data[3] = 0xF7;
//Transmet le paramêtre
    MIDI::EnvMsgLng(Msg, 8);
}

void EXPANDEUR::EcrireVoiceParam(uchar Inst, uchar Param, uchar Valeur)
{
    MMSG Msg[3];
//Construit le message
    Msg[0].data[0] = 0xF0;
    Msg[0].data[1] = 0x43;
    Msg[0].data[2] = 0x75;
    Msg[0].data[3] = SysChan;
    Msg[1].data[0] = 0x18 + (Inst & 0x7);
    Msg[1].data[1] = (Param + 0x40) & 0x7F;
    Msg[1].data[2] = Valeur & 0xF;
    Msg[1].data[3] = Valeur >> 4;
    Msg[2].data[0] = 0xF7;
//Transmet le paramêtre
    MIDI::EnvMsgLng(Msg, 9);
}

void EXPANDEUR::EcrireOpParam(uchar Inst, uchar Op, uchar Param, uchar Valeur)
{
//Configure un opérateur
    EcrireVoiceParam(Inst, Param + 0x10 + Op * 0x8, Valeur);
}

void EXPANDEUR::EcrireSysParam(uchar Param, uchar Valeur)
{
    MMSG Msg[2];
//Construit le message
    Msg[0].data[0] = 0xF0;
    Msg[0].data[1] = 0x43;
    Msg[0].data[2] = 0x75;
    Msg[0].data[3] = SysChan;
    Msg[1].data[0] = 0x10;
    Msg[1].data[1] = Param & 0x7F;
    Msg[1].data[2] = Valeur & 0x7F;
    Msg[2].data[3] = 0xF7;
//Transmet le paramêtre
    MIDI::EnvMsgLng(Msg, 8);
}
