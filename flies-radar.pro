TEMPLATE = app

QT += qml quick

SOURCES += src/main.cpp \
    src/appcontroller.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/appcontroller.h
