# FB01 : Sound editor
# Copyright Meslin Frédéric 2009
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
TARGET = FB01
TEMPLATE = app
CONFIG += staticlib \
    static
SOURCES += main.cpp \
    mainwindow.cpp \
    midi.cpp \
    qclavier.cpp \
    expandeur.cpp \
    qinstrument.cpp \
    qoperateur.cpp \
    qvoice.cpp \
    qenveloppe.cpp
HEADERS += mainwindow.h \
    midi.h \
    qclavier.h \
    expandeur.h \
    types.h \
    win32.h \
    qinstrument.h \
    qoperateur.h \
    qvoice.h \
    qenveloppe.h
FORMS += mainwindow.ui \
    qinstrument.ui \
    qoperateur.ui \
    qvoice.ui
LIBS += -luser32 \
    -lwinmm
RESOURCES += FB01.qrc
RC_FILE = FB01.rc
OTHER_FILES += FB01.rc
