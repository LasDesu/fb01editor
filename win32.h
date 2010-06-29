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

#ifndef WIN32_H
#define WIN32_H
#ifdef WIN32

extern "C"
{
    #define WINAPI __stdcall

    #define CALLBACK_NULL     0
    #define CALLBACK_FUNCTION 0x30000

    #define MMSYSERR_NOERROR   0
    #define MMSYSERR_ERROR     1
    #define MMSYSERR_ALLOCATED 4

    #define MIM_OPEN      0x3C1
    #define MIM_CLOSE     0x3C2
    #define MIM_DATA      0x3C3
    #define MIM_LONGDATA  0x3C4
    #define MIM_ERROR     0x3C5
    #define MIM_LONGERROR 0x3C6
    #define MIM_MOREDATA  0x3CC
    #define MM_MOM_OPEN   0x3C7
    #define MM_MOM_CLOSE  0x3C8
    #define MM_MOM_DONE   0x3C9

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
    uint WINAPI midiConnect(uint hmidi, uint hmo, void * pReserved);
    uint WINAPI midiDisconnect(uint hmidi, uint hmo, void * pReserved);
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
    uint WINAPI midiOutShortMsg(uint hmo, ulong dwMsg);
    uint WINAPI midiInAddBuffer(uint hmi, MIDIHDR * lpMidiInHdr, uint cbMidiInHdr);

//****************************************************************************/
    void WINAPI Sleep(ulong dwMilliseconds);
    #define sleep(t) (Sleep(t))
}
#endif
#endif // WIN32_H
