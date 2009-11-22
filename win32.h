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
//Types de données
    #define WINAPI __stdcall

//Structures MIDI
    typedef struct
    {
        ushort wMid;
        ushort wPid;
        uint   vDriverVersion;
        char   szPname[32];
        ulong  dwSupport;
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
        ulong  dwSupport;
    } MIDIOUTCAPS;

    typedef struct{
        char *lpData;
        ulong dwBufferLength;
        ulong dwBytesRecorded;
        ulong dwUser;
        ulong dwFlags;
        void  *lpNext;
        ulong reserved;
        ulong dwOffset;
        ulong dwReserved[8];
    } MIDIHDR;

//Routines MIDI winmm
    uint WINAPI midiOutGetNumDevs(void);
    uint WINAPI midiInGetNumDevs(void);
    uint WINAPI midiOutOpen(ulong * lphmo, uint uDeviceID, ulong dwCallback, ulong dwCallbackInstance, ulong dwFlags);
    uint WINAPI midiInOpen(ulong * lphmo, uint uDeviceID, ulong dwCallback, ulong dwCallbackInstance, ulong dwFlags);
    uint WINAPI midiOutClose(ulong hmo);
    uint WINAPI midiInClose(ulong hmi);
    uint WINAPI midiOutGetDevCapsA(uint uDeviceID, MIDIOUTCAPS * lpMidiOutCaps, uint cbMidiOutCaps);
    uint WINAPI midiInGetDevCapsA(uint uDeviceID, MIDIINCAPS * lpMidiInCaps, uint cbMidiInCaps);
    uint WINAPI midiOutPrepareHeader(ulong hmo, MIDIHDR * lpMidiOutHdr, uint cbMidiOutHdr);
    uint WINAPI midiInPrepareHeader(ulong hmi, MIDIHDR * lpMidiInHdr, uint cbMidiInHdr);
    uint WINAPI midiOutUnprepareHeader(ulong hmo, MIDIHDR * lpMidiOutHdr, uint cbMidiOutHdr);
    uint WINAPI midiInUnprepareHeader(ulong hmi, MIDIHDR * lpMidiInHdr, uint cbMidiInHdr);
    uint WINAPI midiOutGetErrorTextA(uint wError, char * lpText, uint cchText);
    uint WINAPI midiInGetErrorTextA(uint wError, char * lpText, uint cchText);
    uint WINAPI midiOutReset(ulong hmo);
    uint WINAPI midiInStart(ulong hmi);
    uint WINAPI midiInStop(ulong hmi);
    uint WINAPI midiOutLongMsg(ulong hmo, MIDIHDR * lpMidiOutHdr, uint cbMidiOutHdr);
    uint WINAPI midiOutShortMsg(ulong hmo, ulong dwMsg);
    uint WINAPI midiInAddBuffer(ulong hmi, MIDIHDR * lpMidiInHdr, uint cbMidiInHdr);

}
#endif // WIN32_H
