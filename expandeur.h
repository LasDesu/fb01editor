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

    class EXPANDEUR
    {
    private:
    //Etats de configuration
        static uchar SysChan;
    public:
    //Configuration
        static bool Detecter();
        static void DefinirSysChan(uchar Chan);
    //Communication
        static void EcrireInstParam(uchar Inst, uchar Param, uchar Valeur);
        static void EcrireVoiceParam(uchar Inst, uchar Param, uchar Valeur);
        static void EcrireOpParam(uchar Inst, uchar Op, uchar Param, uchar Valeur);
        static void EcrireSysParam(uchar Param, uchar Valeur);
    //Paramêtres
        static void ActiverOps(uchar Inst, bool Op1, bool Op2, bool Op3, bool Op4);
    };

#endif // EXPANDEUR_H
