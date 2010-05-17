OTHER_FILES += FB01.rc
HEADERS += types.h \
    linux.h \
    win32.h \
    core/set.h \
    core/voice.h \
    core/instrument.h \
    core/operator.h \
    core/midi.h
RESOURCES += FB01.qrc
SOURCES += core/set.cpp \
    core/voice.cpp \
    core/instrument.cpp \
    core/operator.cpp \
    core/midi.cpp
