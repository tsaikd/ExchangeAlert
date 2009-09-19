CONFIG += ordered
TEMPLATE = subdirs

QT_BUILD_PARTS += ExchangeAlertApp
SUBDIRS += ExchangeAlertApp

!macx-xcode:addExclusiveBuilds(debug, Debug, release, Release)

