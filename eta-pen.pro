QT       += core gui widgets network

RESOURCES += images.qrc


TARGET = eta-pen
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp\
        singleinstance.cpp

HEADERS  += mainwindow.h\
        singleinstance.h

target.path = /usr/bin/

desktop_file.files = eta-pen.desktop
desktop_file.path = /usr/share/applications/

icon.files = images/etapen.svg
icon.commands = mkdir -p /usr/share/eta/eta-pen
icon.path = /usr/share/eta/eta-pen/

INSTALLS += target desktop_file icon
