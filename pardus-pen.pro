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

icon.files = images/pardus-pen.svg
icon.path = /usr/share/icons/hicolor/scalable/apps

INSTALLS += target desktop_file icon

DISTFILES += \
    sliderstyle.qss
