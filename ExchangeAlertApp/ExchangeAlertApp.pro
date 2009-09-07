TEMPLATE = app
TARGET = ExchangeAlert

BASEDIR = $${PWD}/..
SRCDIR = $${BASEDIR}/src
INCDIR = $${BASEDIR}/include
LANGDIR = $${BASEDIR}/lang

QT *= network

TRANSLATIONS += $${LANGDIR}/ExchangeAlert_zh_TW.ts
RESOURCES += $${BASEDIR}/ExchangeAlert.qrc
RC_FILE = ExchangeAlertApp.rc

INCLUDEPATH += $${SRCDIR}
PRECOMPILED_HEADER += $${SRCDIR}/stable.h

SOURCES += $${SRCDIR}/QSyncHttp.cpp
HEADERS += $${SRCDIR}/QSyncHttp.h

SOURCES += main.cpp
SOURCES += $${SRCDIR}/Debug.cpp
HEADERS += $${SRCDIR}/WinExt.h
SOURCES += $${SRCDIR}/WinExt.cpp

HEADERS += $${SRCDIR}/WinMainApp.h
SOURCES += $${SRCDIR}/WinMainApp.cpp
SOURCES += $${SRCDIR}/ConfMainApp.cpp
HEADERS += $${SRCDIR}/WinConfMainApp.h
SOURCES += $${SRCDIR}/WinConfMainApp.cpp

include($${INCDIR}/qtsingleapplication/qtsingleapplication.pri)
include($${BASEDIR}/general.pri)
