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

#include <QColor>
#include <QCursor>
#include <QDesktopWidget>
#include <QGroupBox>
#include <QIcon>
#include <QImage>
#include <QMouseEvent>
#include <QSize>
#include <QPainter>
#include <QPalette>
#include <QPen>
#include <QPixmap>
#include <QPoint>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QRegion>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QSlider>
#include <QLabel>
#include <QProcess>

#include <ctime>
#include <iostream>
#include <sys/stat.h>


#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)


#include "mainwindow.h"

int hudsize=100;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      clearMode(false),
      paperMode(false),
      drawing(false)
{
    setlocale (LC_ALL, "");
    bindtextdomain ("pardus-pen", "/usr/share/locale/");
    textdomain ("pardus-pen");

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint
                   | Qt::X11BypassWindowManagerHint);

    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_TranslucentBackground, true);

    innerWidget = new QWidget(this);
    verticalLayout = new QVBoxLayout(innerWidget);
    verticalLayout->setAlignment(Qt::AlignCenter);

    QDesktopWidget widget;
    mainScreenSize = widget.screenGeometry(widget.primaryScreen());
    avaibleScreenSize = widget.availableGeometry(widget.primaryScreen());

    setGeometry(mainScreenSize);

    hudsize=mainScreenSize.height()/13;

    previousPenLevel = 4;
    previousEraserLevel = 4;

    myPenWidth = previousPenLevel * 2 - 1;

    myPenColor = QColor(255,108,0);

    image.fill(qRgba(0, 0, 0, 0));
    paper.fill(qRgba(238, 238, 238, 255));


    clearButton = new QPushButton(this);
    eraseButton = new QPushButton(this);
    closeButton = new QPushButton(this);
    colorButton = new QPushButton(this);
    switchButton = new QPushButton(this);
    paperButton = new QPushButton(this);
    scrotButton = new QPushButton(this);
    penSizeSelector = new QSlider(Qt::Vertical, this);
    thickness = new QLabel(this);

    colorButton->setStyleSheet("background:rgb(255,108,0);"
                               "border-radius:3px;"
                               "border: 2px solid rgb(171,171,171);"
                               "color:rgb(255,108,0);");

    thickness->setText(QString::number(myPenWidth));
    QFont f( "Helvetica", hudsize/5, QFont::Bold);
    thickness->setFont(f);
    thickness->setAlignment(Qt::AlignCenter);
    thickness->setStyleSheet("background:rgba(242,242,242,54);"
                             "border-radius:3px;"
                             "border: 2px solid rgb(171, 171, 171);"
                             "color:rgb(255,108,0);");

    penSizeSelector->setMinimum(1);
    penSizeSelector->setMaximum(31);
    penSizeSelector->setSliderPosition(2);

    penSizeSelector->setStyleSheet(".QSlider::groove:vertical {"
                                   "background: rgba(242, 242, 242,64);"
                                   "border-radius: 2px;"
                                   "border: 2px solid rgb(171,171,171);"
                                   "width: 20px;"
                                   "}"

                                   ".QSlider::handle:vertical {"
                                   "background: rgb(242, 242, 242);"

                                   "border: 2px solid rgb(255,108,0);"
                                   "width: 30px;"
                                   "height: 40px;"
                                   "border-radius: 3px;"
                                   "margin: 0 -15px 0 -15px;"
                                   "}");


    currentGeometry = this->geometry();

    eraseButton->setCheckable(true);
    eraseButton->setIcon(QIcon(":images/eraser.svg"));
    clearButton->setIcon(QIcon(":images/wipe.svg"));
    closeButton->setIcon(QIcon(":images/close.svg"));
    switchButton->setIcon(QIcon(":images/screen.svg"));
    paperButton->setIcon(QIcon(":images/paper.svg"));
    scrotButton->setIcon(QIcon(":images/screenshot.svg"));
    eraseButton->setIconSize(QSize(hudsize*0.64,hudsize*0.64));
    clearButton->setIconSize(QSize(hudsize*0.64,hudsize*0.64));
    closeButton->setIconSize(QSize(hudsize*0.64,hudsize*0.64));
    switchButton->setIconSize(QSize(hudsize*0.64,hudsize*0.64));
    paperButton->setIconSize(QSize(hudsize*0.64,hudsize*0.64));
    scrotButton->setIconSize(QSize(hudsize*0.64,hudsize*0.64));
    colorButton->setFixedSize(QSize(hudsize*0.64,hudsize*0.64));
    penSizeSelector->setFixedSize(QSize(hudsize*0.64,hudsize*5));
    thickness->setFixedSize(QSize(hudsize*0.64,hudsize*0.64));


    palette = new QPalette();
    palette->setColor(QPalette::Button, myPenColor);
    colorButton->setPalette(*palette);
    colorButton->setAutoFillBackground(true);



    groupBox = new QGroupBox(this);

   /* closeButton->setStyleSheet("border: 2px solid rgb(171,171,171);");
    switchButton->setStyleSheet("border: 2px solid rgb(171,171,171);");
    eraseButton->setStyleSheet("border: 2px solid rgb(171,171,171);");
    clearButton->setStyleSheet("border: 2px solid rgb(171,171,171);");
    paperButton->setStyleSheet("border: 2px solid rgb(171,171,171);");
*/

    verticalLayout->addWidget(closeButton);
    verticalLayout->addWidget(switchButton);
    verticalLayout->addWidget(penSizeSelector);
    verticalLayout->addWidget(colorButton);
    verticalLayout->addWidget(thickness);
    verticalLayout->addWidget(eraseButton);
    verticalLayout->addWidget(clearButton);
    verticalLayout->addWidget(scrotButton);
    verticalLayout->addWidget(paperButton);


    groupBox->setLayout(verticalLayout);
    groupBox->setStyleSheet("border: None;");



    connect(eraseButton,SIGNAL(clicked()),this,SLOT(toggleClearMode()));
    connect(scrotButton,SIGNAL(clicked()),this,SLOT(screenshot()));
    connect(penSizeSelector,SIGNAL(valueChanged(int)),this,SLOT(penSize(int)));
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clearImage()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(colorButton,SIGNAL(clicked()),this,SLOT(penColor()));
    connect(switchButton,SIGNAL(clicked()),this,SLOT(switchScreen()));
    connect(paperButton,SIGNAL(clicked()),this,SLOT(togglePaperMode()));

    switched = true;
    this->updateButtons();
    this->setCursor(QCursor(QPixmap(":images/cursor.svg")));
}

MainWindow::~MainWindow()
{
    
}
void MainWindow::updateButtons()
{
    if(switched) {

        groupBox->setGeometry(QRect( mainScreenSize.width()-hudsize,hudsize,hudsize, mainScreenSize.height()-hudsize*2));
        switchButton->setIcon(QIcon(":images/screen.svg"));
    } else {

        groupBox->setGeometry(QRect( 0,0,hudsize, mainScreenSize.height()-hudsize*2));
        switchButton->setIcon(QIcon(":images/parduspen_mode.svg"));
    }

}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        drawLineTo(event->pos());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawLineTo(event->pos());
        drawing = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    currentGeometry = this->geometry();
    this->updateButtons();
    QWidget::resizeEvent(event);
}

void MainWindow::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    if(clearMode) {
        if (paperMode) {
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.setPen(QPen(QColor(238,238,238), myPenWidth,
                                Qt::SolidLine, Qt::RoundCap,
                                Qt::RoundJoin));
        } else {
            painter.setCompositionMode(QPainter::CompositionMode_Clear);
        }
    } else {
        painter.setCompositionMode(QPainter::CompositionMode_Source);
    }

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawLine(lastPoint, endPoint);

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
           .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void MainWindow::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0, 0, 0));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void MainWindow::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
    palette->setColor(QPalette::Button, myPenColor);
    thickness->setStyleSheet("background:rgba(242,242,242,95);"
                             "border-radius:3px;"
                             "border: 2px solid rgb(171,171,171);"
                             "color:"+newColor.name()+";");
    colorButton->setStyleSheet("background:"+newColor.name()+";"
                                                             "border-radius:3px;");
    penSizeSelector->setStyleSheet(".QSlider::groove:vertical {"
                             "background: rgb(242, 242, 242);"
                             "border-radius: 2px;"
                             "border: 2px solid rgb(171,171,171);"
                             "width: 20px;"
                             "}"

                             ".QSlider::handle:vertical {"
                             "background: rgb(242, 242, 242);"
                             "border: 2px solid "+newColor.name()+";"
                             "width: 30px;"
                             "height: 40px;"
                             "border-radius: 3px;"
                             "margin: 0 -15px 0 -15px;"
                             "}");
}

void MainWindow::setPenSize(int size)
{
    if (clearMode) {
        int t = size*10;
        this->myPenWidth = t;
        thickness->setText(QString::number(t/10));
        this->setCursor(QCursor(QPixmap(":images/eraser_cursor.svg").
                                scaled(myPenWidth,myPenWidth,
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation),
                                myPenWidth/2,myPenWidth/2));
    } else {;
        this->setCursor(QCursor(QPixmap(":images/cursor.svg")));
        this->myPenWidth = size;
        thickness->setText(QString::number(size));
    }

}



void MainWindow::setPaperMode(QImage *myimage, QImage *mypreviousImage)
{
    if (paperMode) {
        QPainter painter(&previousImage);
        painter.drawImage(QPoint(0, 0), previousImage);
        *myimage = previousImage;

        paperButton->setIcon(QIcon(":images/paper.svg"));
    }

    else {
        *mypreviousImage = image;

        QImage newImage(image.size(), QImage::Format_ARGB32);
        newImage.fill(qRgba(238, 238, 238, 255));
        QPainter painter(&newImage);
        painter.drawImage(QPoint(0, 0), newImage);
        *myimage = newImage;

        paperButton->setIcon(QIcon(":images/paper_selected.svg"));

    }

    update();
    paperMode = !paperMode;
}

void MainWindow::screenshot()
{
    // Thanks to Bayram Karahan
    time_t now = time(0);

    mkdir("pardus-pen", 0755);
    QString imgname = QDir::homePath()+"/pardus-pen/"+ctime(&now)+".png";
    if(paperMode){
        image.save(imgname.toStdString().c_str());
    }else{
        char *cmd = (char*)malloc(1024*sizeof(char));
        strcpy(cmd,"scrot '");
        strcat(cmd,imgname.toStdString().c_str());
        strcat(cmd,"'");
        system(cmd);;
    }
    QMessageBox messageBox;
    Qt::WindowFlags flags = 0;
    flags |= Qt::Dialog;
    flags |= Qt::X11BypassWindowManagerHint;
    messageBox.setWindowFlags(flags);
    messageBox.setText(_("Info"));
    char *msg = (char*)malloc(1024*sizeof(char));
    strcpy(msg,_("Screenshot saved:"));
    strcat(msg,imgname.toStdString().c_str());
    messageBox.setInformativeText(msg);
    messageBox.setIcon(QMessageBox::Information);
    messageBox.exec();
}

void MainWindow::penColor()
{
    if(switched) {
        switchScreen();
    }
    QColor newColor = QColorDialog::getColor(myPenColor);
    if (newColor.isValid()) {
        setPenColor(newColor);
    }

    if(!switched) {
        switchScreen();
    }

}

void MainWindow::penSize(const int &size)
{
    setPenSize(size);
}

void MainWindow::togglePaperMode()
{
    if(!switched) {
        switchScreen();
    }
    setPaperMode(&image, &previousImage);
}

void MainWindow::switchScreen()
{

    if(clearMode) {
        toggleClearMode();
        clearButton->setChecked(false);
    }

    if(switched) {
        this->setGeometry(QRect( mainScreenSize.width()-hudsize,hudsize,hudsize, hudsize*1.9));
        switched = false;
        this->updateButtons();
    } else {
        this->setGeometry(mainScreenSize);
        switched = true;
        this->updateButtons();
    }
}

void MainWindow::clearImage()
{
    if (paperMode) {
        image.fill(qRgba(238, 238, 238, 255));
    } else {
        image.fill(qRgba(0, 0, 0, 0));
    }
    if(clearMode) {
        toggleClearMode();
        clearButton->setChecked(false);
    }
    update();
}

void MainWindow::toggleClearMode()
{
    if(!switched) {
        switchScreen();
    }
    if(clearMode) {
        clearMode = false;
        previousEraserLevel = penSizeSelector->value();
        penSizeSelector->setValue(previousPenLevel);
        setPenSize(previousPenLevel);
        this->setCursor(QCursor());
        eraseButton->setIcon(QIcon(":images/eraser.svg"));
        eraseButton->setChecked(false);
        this->setCursor(QCursor(QPixmap(":images/cursor.svg")));
    } else {
        clearMode = true;
        previousPenLevel = penSizeSelector->value();
        penSizeSelector->setValue(previousEraserLevel);
        setPenSize(previousEraserLevel);
        this->setCursor(QCursor(QPixmap(":images/eraser_cursor.svg").
                                scaled(myPenWidth,myPenWidth,
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation),
                                myPenWidth/2,myPenWidth/2));
        eraseButton->setIcon(QIcon(":images/eraser_selected.svg"));
        eraseButton->setChecked(true);
    }
}
