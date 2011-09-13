#-------------------------------------------------
#
# Project created by QtCreator 2011-09-13T10:27:11
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = QueryAnal
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    update.cpp \
    select.cpp \
    insert.cpp \
    delete.cpp \
    parse/valor.cpp \
    parse/validacion.cpp \
    parse/token.cpp \
    parse/tabla.cpp \
    parse/sintactico.cpp \
    parse/lexico.cpp \
    parse/campo.cpp \
    parse/asignacion.cpp

HEADERS += \
    update.h \
    select.h \
    insert.h \
    delete.h \
    parse/valor.h \
    parse/validacion.h \
    parse/token.h \
    parse/tabla.h \
    parse/sintactico.h \
    parse/lexico.h \
    parse/campo.h \
    parse/asignacion.h




