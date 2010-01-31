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

#ifndef WIN32_H
#define WIN32_H

extern "C"
{
//****************************************************************************/
    #define WINAPI __stdcall

//****************************************************************************/
    #define CALLBACK_FUNCTION 0x30000
    #define MIM_LONGDATA      0x3C4

//****************************************************************************/
    typedef struct
    {
        ushort wMid;
        ushort wPid;
        uint   vDriverVersion;
        char   szPname[32];
        uint   dwSupport;
    } MIDIINCAPS;

    typedef struct
    {
        ushort wMid;
        ushort wPid;
        uint   vDriverVersion;
        char   szPname[32];
        ushort wTechnology;
        ushort wVoices;
        ushort wNotes;
        ushort wChannelMask;
        uint   dwSupport;
    } MIDIOUTCAPS;

    typedef struct{
        char *lpData;
        uint dwBufferLength;
        uint dwBytesRecorded;
        uint dwUser;
        uint dwFlags;
        void  *lpNext;
        uint reserved;
        uint dwOffset;
        uint dwReserved[4];
    } MIDIHDR;

//****************************************************************************/
    uint WINAPI midiOutGetNumDevs(void);
    uint WINAPI midiInGetNumDevs(void);
    uint WINAPI midiOutOpen(uint * lphmo, uint uDeviceID, uint dwCallback, uint dwCallbackInstance, uint dwFlags);
    uint WINAPI midiInOpen(uint * lphmo, uint uDeviceID, uint dwCallback, uint dwCallbackInstance, uint dwFlags);
    uint WINAPI midiOutClose(uint hmo);
    uint WINAPI midiInClose(uint hmi);
    uint WINAPI midiOutGetDevCapsA(uint uDeviceID, MIDIOUTCAPS * lpMidiOutCaps, uint cbMidiOutCaps);
    uint WINAPI midiInGetDevCapsA(uint uDeviceID, MIDIINCAPS * lpMidiInCaps, uint cbMidiInCaps);
    uint WINAPI midiOutPrepareHeader(uint hmo, MIDIHDR * lpMidiOutHdr, uint cbMidiOutHdr);
    uint WINAPI midiInPrepareHeader(uint hmi, MIDIHDR * lpMidiInHdr, uint cbMidiInHdr);
    uint WINAPI midiOutUnprepareHeader(uint hmo, MIDIHDR * lpMidiOutHdr, uint cbMidiOutHdr);
    uint WINAPI midiInUnprepareHeader(uint hmi, MIDIHDR * lpMidiInHdr, uint cbMidiInHdr);
    uint WINAPI midiOutGetErrorTextA(uint wError, char * lpText, uint cchText);
    uint WINAPI midiInGetErrorTextA(uint wError, char * lpText, uint cchText);
    uint WINAPI midiInStart(uint hmi);
    uint WINAPI midiInStop(uint hmi);
    uint WINAPI midiOutReset(uint hmo);
    uint WINAPI midiInReset(uint hmi);
    uint WINAPI midiOutLongMsg(uint hmo, MIDIHDR * lpMidiOutHdr, uint cbMidiOutHdr);
    uint WINAPI midiOutShortMsg(uint hmo, uint dwMsg);
    uint WINAPI midiInAddBuffer(uint hmi, MIDIHDR * lpMidiInHdr, uint cbMidiInHdr);
}
#endif // WIN32_H
