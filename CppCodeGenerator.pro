TEMPLATE = app
TARGET = CppCodeGenerator
INCLUDEPATH += .

QT += core
QT -= gui

# Input
SOURCES += main.cpp \
    generator.cpp

HEADERS += \
    generator.h \
    defs.h
