#TEMPLATE = app
#CONFIG += console c++17
#CONFIG -= app_bundle
#CONFIG += qt
#CONFIG += network

QT -= gui
QT += network

CONFIG += c++17 console
CONFIG -= app_bundle


SOURCES += \
        chat.cpp \
        client.cpp \
        clientstate.cpp \
        main.cpp \
        message.cpp \
        server.cpp \
        state.cpp \
        strangerstate.cpp \
        user.cpp

HEADERS += \
    chat.h \
    client.h \
    clientstate.h \
    message.h \
    server.h \
    state.h \
    strangerstate.h \
    user.h \
    utils.h
