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
    parse/asignacion.cpp \
    sm/Varchar.cpp \
    sm/Template.cpp \
    sm/SystemBlock.cpp \
    sm/StorageManager.cpp \
    sm/SMException.cpp \
    sm/Registro.cpp \
    sm/MetadataContinuo.cpp \
    sm/Metadata.cpp \
    sm/mapabits.cpp \
    sm/InfoV.cpp \
    sm/InfoReg.cpp \
    sm/InfoMDC.cpp \
    sm/InfoMD.cpp \
    sm/InfoD.cpp \
    sm/InfoCMD.cpp \
    sm/Data.cpp \
    sm/Block.cpp \
    parse/semantico.cpp \
    arbol.cpp

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
    parse/asignacion.h \
    sm/Varchar.h \
    sm/Template.h \
    sm/SystemBlock.h \
    sm/StorageManager.h \
    sm/SMException.h \
    sm/Registro.h \
    sm/MetadataContinuo.h \
    sm/Metadata.h \
    sm/mapabits.h \
    sm/InfoV.h \
    sm/InfoReg.h \
    sm/InfoMDC.h \
    sm/InfoMD.h \
    sm/InfoD.h \
    sm/InfoCMD.h \
    sm/Data.h \
    sm/Block.h \
    smm/smm.h \
    parse/semantico.h \
    arbol.h






















