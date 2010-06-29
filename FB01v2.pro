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
    core/operateur.h \
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
    interface/qbank.h \
    interface/mainwindow.h \
    editeur.h \
    core/config.h \
    core/edit.h \
    interface/qconfig.h \
    core/bank_voice.h \
    excep/memory_ex.h \
    excep/midi_ex.h \
    excep/ex.h \
    interface/qautomation.h \
    core/automation.h \
    core/automated.h \
    excep/automation_ex.h
RESOURCES += FB01.qrc
SOURCES += core/set.cpp \
    core/midi.cpp \
    core/block.cpp \
    core/voice.cpp \
    core/operateur.cpp \
    core/instrument.cpp \
    core/bank.cpp \
    interface/qoperateur.cpp \
    interface/qbutton.cpp \
    interface/qclavier.cpp \
    interface/qvoice.cpp \
    interface/qinstrument.cpp \
    interface/qenveloppe.cpp \
    interface/qbank.cpp \
    interface/mainwindow.cpp \
    editeur.cpp \
    core/config.cpp \
    core/edit.cpp \
    interface/qconfig.cpp \
    core/bank_voice.cpp \
    excep/memory_ex.cpp \
    excep/midi_ex.cpp \
    excep/ex.cpp \
    interface/qautomation.cpp \
    core/automation.cpp \
    excep/automation_ex.cpp
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
    interface/qbank.ui \
    interface/qconfig.ui \
    interface/qautomation.ui
