QT       += core gui widgets network

RESOURCES += images.qrc

TARGET = pardus-pen
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp\
        singleinstance.cpp

HEADERS  += mainwindow.h\
        singleinstance.h

target.path = /usr/bin/

desktop_file.files = pardus-pen.desktop
desktop_file.path = /usr/share/applications/

icon.files = images/parduspen.svg
icon.commands = mkdir -p /usr/share/pardus/pardus-pen
icon.path = /usr/share/pardus/pardus-pen

INSTALLS += target desktop_file icon

DISTFILES += \
    sliderstyle.qss
