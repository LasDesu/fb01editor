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

#ifndef EXPANDEUR_H
#define EXPANDEUR_H

    #include "types.h"

    #define BANQUES 7
    #define VOIX 48

    class EXPANDEUR
    {
    private:
    //Banques
        static uchar Banques[BANQUES][VOIX];
    public:
    //Configuration
        static uchar SysChan;
    //Chargement/déchargement
        static void ChargerBanque(uchar Banque);
        static void SauverBanque(uchar Banque);
    //Communication
        static void EcrireInstParam(uchar Inst, uchar Param, uchar Valeur);
        static void EcrireVoiceParam(uchar Inst, uchar Param, uchar Valeur);
        static void EcrireOpParam(uchar Inst, uchar Op, uchar Param, uchar Valeur);
        static void EcrireSysParam(uchar Param, uchar Valeur);
    //Paramètres composés voies
        static void ActiverOps(uchar Inst, bool Op1, bool Op2, bool Op3, bool Op4);
        static void ChangerNom(uchar Inst, char * Nom);
        static void ChangerVoicex09(uchar Inst, uchar Load, uchar AMD);
        static void ChangerVoicex0A(uchar Inst, uchar Sync, uchar PMD);
        static void ChangerVoicex0C(uchar Inst, uchar Feedback, uchar Algo);
        static void ChangerVoicex0D(uchar Inst, uchar PMS, uchar AMS);
        static void ChangerVoicex0E(uchar Inst, uchar Wave);
        static void ChangerVoicex3A(uchar Inst, uchar Poly, uchar Porta);
        static void ChangerVoicex3B(uchar Inst, uchar Pmdctl, uchar Pitch);
    //Paramètres composés opérateurs
        static void ChangerOpx01(uchar Inst, uchar Op, uchar KeyCurb, uchar Velocity);
        static void ChangerOpx02(uchar Inst, uchar Op, uchar LvlDph, uchar Adjust);
        static void ChangerOpx03(uchar Inst, uchar Op, uchar KeyCurb, uchar Fine, uchar Multiple);
        static void ChangerOpx04(uchar Inst, uchar Op, uchar RateDph, uchar AR);
        static void ChangerOpx05(uchar Inst, uchar Op, bool Carrier, uchar VeloSens, uchar DR1);
        static void ChangerOpx06(uchar Inst, uchar Op, uchar Coarse, uchar DR2);
        static void ChangerOpx07(uchar Inst, uchar Op, uchar SL, uchar RR);
    };

#endif // EXPANDEUR_H
