# -------------------------------------------------
# QMake project for the PrintHtml program
# -------------------------------------------------
TARGET = PrintHtml
TEMPLATE = app
CONFIG += precompile_header
INCLUDEPATH += ../includes ../common
DEPENDPATH += ../includes ../common
PRECOMPILED_HEADER = stable.h
precompile_header:!isEmpty(PRECOMPILED_HEADER):DEFINES += USING_PCH
QT += network webkitwidgets printsupport webenginewidgets

HEADERS = stable.h \
    globals.h \
    printhtml.h
SOURCES = main.cpp \
    printhtml.cpp
FORMS =
RESOURCES =

DISTFILES += \
    LICENSE \
    README.md \
    .gitignore
