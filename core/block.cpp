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

#include "block.h"

/*****************************************************************************/
Block::Block(const uchar nbParam, const uchar lenSysEx, uchar * sysEx)
{
    this->nbParam = nbParam;
    this->lenSysEx = lenSysEx;
    this->sysEx = sysEx;
}

Block::~Block()
{
}

/*****************************************************************************/
void Block::InitSysEx()
{
    memset(sysEx, lenSysEx, 0);
}

void Block::CheckSumSysEx()
{
    uchar sum;
    for(uint i = 7; i < lenSysEx - 2; i ++)
        sum += sysEx[i];
    sysEx[lenSysEx - 2] = (~sum) + 1;
}
