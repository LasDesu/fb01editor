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

#include "periph.h"

/*****************************************************************************/
bool Periph::ToucheASCII(const char code)
{
#ifdef WIN32
    short key = VkKeyScan(code);
    if (key == 0xFFFF) return false;
    return (GetAsyncKeyState(key & 0xFF) & 0x8000) > 0;
#endif
}

/*****************************************************************************/
bool Periph::ToucheShift()
{
#ifdef WIN32
    return (GetAsyncKeyState(VK_SHIFT) & 0x8000) > 0;
#endif
}

bool Periph::ToucheCtrl()
{
#ifdef WIN32
    return (GetAsyncKeyState(VK_CONTROL) & 0x8000) > 0;
#endif
}

bool Periph::ToucheAlt()
{
#ifdef WIN32
    return (GetAsyncKeyState(VK_MENU) & 0x8000) > 0;
#endif
}
/*****************************************************************************/
