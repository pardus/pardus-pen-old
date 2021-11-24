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

buildmo.target = po
buildmo.path = /usr/share/locale/pardus-pen/
buildmo.commands = make -C po 


installmo.target = po
installmo.path = /usr/share/locale/pardus-pen/
installmo.commands = make -C po install


INSTALLS += target desktop_file icon buildmo installmo

DISTFILES += \
    sliderstyle.qss
