# FB01 : Sound editor
# Copyright Meslin Frdric 2009
# fredericmeslin@hotmail.com
# This file is part of FB01 SE
# FB01 SE is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# FB01 SE is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with FB01 SE. If not, see <http://www.gnu.org/licenses/>.
OTHER_FILES += FB01.rc
HEADERS += types.h \
    linux.h \
    win32.h \
    core/midi.h \
    core/block.h \
    core/set.h \
    core/operator.h \
    core/instrument.h \
    core/voice.h \
    interface/qoperateur.h \
    interface/qbutton.h \
    interface/qclavier.h \
    interface/qvoice.h \
    interface/qinstrument.h \
    interface/qenveloppe.h \
    core/bank.h \
    interface/mainwindow.h \
    interface/qbanks.h
RESOURCES += FB01.qrc
SOURCES += core/set.cpp \
    core/midi.cpp \
    core/block.cpp \
    core/voice.cpp \
    core/set.cpp \
    core/operator.cpp \
    core/instrument.cpp \
    core/bank.cpp \
    interface/qoperateur.cpp \
    interface/qbutton.cpp \
    interface/qclavier.cpp \
    interface/qvoice.cpp \
    interface/qinstrument.cpp \
    interface/qenveloppe.cpp \
    interface/mainwindow.cpp \
    interface/qbanks.cpp \
    main.cpp
winnt { 
    DEFINES += WIN32
    LIBS += -luser32 \
        \ \
        -lwinmm
}
win32 { 
    DEFINES += WIN32
    LIBS += -luser32 \
        -lwinmm
}
unix { 
    DEFINES += LINUX
    LIBS += 
}
FORMS += interface/qoperateur.ui \
    interface/qinstrument.ui \
    interface/qvoice.ui \
    interface/mainwindow.ui \
    interface/qbanks.ui
