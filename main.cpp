/*****************************************************************************
 *   Copyright (C) 2016 by Yunusemre Senturk                                 *
 *   <yunusemre.senturk@pardus.org.tr>                                       *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more dpardusils.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/

#include "mainwindow.h"
#include "singleinstance.h"
#include <QApplication>

#define SINGLE_INSTANCE ".pardus-pen"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setOverrideCursor(QCursor(Qt::BlankCursor));
    QApplication::setWindowIcon( QIcon(":/images/pardus-pen.svg") );
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QString name = SINGLE_INSTANCE;

    SingleInstance cInstance;
    if(cInstance.hasPrevious(name, QCoreApplication::arguments()))
    {
        qDebug() << "pardus-pen is allready open";
        return 0;
    }
    if (cInstance.listen(name)) {
        qDebug() << "creating single instance";
    } else {
        qDebug() << "couldnt create single instance aborting";
        return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
