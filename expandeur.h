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
    #include "midi.h"

    #define BANQUES 7
    #define VOIX    48

    class EXPANDEUR
    {
    private:

    public:
    //Configuration
        static uchar SysChan;
    //Chargement/déchargement
        static bool ChargerBanque(uchar Banque);
        static bool ChargerSet();
        static bool ChargerVoix(uchar Inst);
    //Communication
        static void  EcrireInstParam(uchar Inst, uchar Param, uchar Valeur);
        static void  EcrireVoiceParam(uchar Inst, uchar Param, uchar Valeur);
        static uchar LireVoiceParam(uchar Param);
        static void  EcrireOpParam(uchar Inst, uchar Op, uchar Param, uchar Valeur);
        static uchar LireOpParam(uchar Op, uchar Param);
        static void  EcrireSysParam(uchar Param, uchar Valeur);
        static bool  Attente();
    //Paramètres composés voies
        static void EcrireOps(uchar Inst, bool Op1, bool Op2, bool Op3, bool Op4);
        static void LireOps(bool * Op1, bool * Op2, bool * Op3, bool * Op4);
        static void EcrireNom(uchar Inst, const char * Nom);
        static void LireNom(char * Nom);
        static void EcrireVoicex09(uchar Inst, bool Load, uchar AMD);
        static void LireVoicex09(bool * Load, uchar * AMD);
        static void EcrireVoicex0A(uchar Inst, bool Sync, uchar PMD);
        static void LireVoicex0A(bool * Sync, uchar * PMD);
        static void EcrireVoicex0C(uchar Inst, uchar Feedback, uchar Algo);
        static void LireVoicex0C(uchar * Feedback, uchar * Algo);
        static void EcrireVoicex0D(uchar Inst, uchar PMS, uchar AMS);
        static void LireVoicex0D(uchar * PMS, uchar * AMS);
        static void EcrireVoicex0E(uchar Inst, uchar Wave);
        static void LireVoicex0E(uchar * Wave);
        static void EcrireVoicex3A(uchar Inst, bool Poly, uchar Porta);
        static void LireVoicex3A(bool * Poly, uchar * Porta);
        static void EcrireVoicex3B(uchar Inst, uchar Pmdctl, uchar Pitch);
        static void LireVoicex3B(uchar * Pmdctl, uchar * Pitch);
    //Paramètres composés opérateurs
        static void EcrireOpx01(uchar Inst, uchar Op, uchar KeyCurb, uchar Velocity);
        static void EcrireOpx02(uchar Inst, uchar Op, uchar LvlDph, uchar Adjust);
        static void EcrireOpx03(uchar Inst, uchar Op, uchar KeyCurb, uchar Fine, uchar Multiple);
        static void EcrireOpx04(uchar Inst, uchar Op, uchar RateDph, uchar AR);
        static void EcrireOpx05(uchar Inst, uchar Op, bool Carrier, uchar VeloSens, uchar DR1);
        static void EcrireOpx06(uchar Inst, uchar Op, uchar Coarse, uchar DR2);
        static void EcrireOpx07(uchar Inst, uchar Op, uchar SL, uchar RR);
    };

#endif // EXPANDEUR_H
