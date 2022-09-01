TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        chat.cpp \
        clientstate.cpp \
        main.cpp \
        message.cpp \
        state.cpp \
        strangerstate.cpp \
        user.cpp

HEADERS += \
    chat.h \
    clientstate.h \
    message.h \
    state.h \
    strangerstate.h \
    user.h \
    utils.h
