TEMPLATE = app
TARGET = ExchangeAlert

BASEDIR = $${PWD}/..
SRCDIR = $${BASEDIR}/src
INCDIR = $${BASEDIR}/include
LANGDIR = $${BASEDIR}/lang

QT *= network

#TRANSLATIONS += $${LANGDIR}/KDWall_zh_TW.ts
RESOURCES += $${BASEDIR}/ExchangeAlert.qrc
RC_FILE = $${BASEDIR}/ExchangeAlert.rc

PRECOMPILED_HEADER += $${SRCDIR}/stable.h

SOURCES += $${SRCDIR}/Debug.cpp
SOURCES += $${SRCDIR}/mainApp.cpp
HEADERS += $${SRCDIR}/WinMainApp.h
SOURCES += $${SRCDIR}/WinMainApp.cpp
SOURCES += $${SRCDIR}/ConfMainApp.cpp

include($${INCDIR}/qtsingleapplication/qtsingleapplication.pri)
include($${BASEDIR}/general.pri)
