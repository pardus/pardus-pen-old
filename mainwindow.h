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
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>


class QColor;
class QPoint;
class QImage;
class QSize;
class QMouseEvent;
class QPushButton;
class QPalette;
class QVBoxLayout;
class QGroupBox;
class QPropertyAnimation;
class QSlider;
class QLabel;
class QPixmap;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void clearImage();
    void penColor();
    void switchScreen();
    void toggleClearMode();
    void penSize(const int &size);
    void togglePaperMode();
    void screenshot();
    void record();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;


private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void setPenColor(const QColor &newColor);
    void setPenSize(int size);
    void updateButtons();
    void setPaperMode(QImage *myimage, QImage *mypreviousImage);
    void saveImage(QImage *image);

    bool drawing;
    bool switched;
    bool clearMode;
    bool paperMode;

    int previousEraserLevel;
    int previousPenLevel;
    int myPenWidth;
    bool isFfmpegActive;
    std::string recordName;
    QImage image;
    QImage previousImage;
    QImage paper;
    QColor myPenColor;
    QPoint lastPoint;
    QWidget *innerWidget;
    QWidget *leftInnerWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *leftVerticalLayout;
    QGroupBox *groupBox;
    QGroupBox *leftGroupBox;
    QPushButton *clearButton;
    QPushButton *eraseButton;
    QPushButton *closeButton;
    QPushButton *colorButton;
    QPushButton *switchButton;
    QPushButton *paperButton;
    QPushButton *scrotButton;
    QPushButton *recordButton;
    QPushButton *pardusButton;
    QPushButton *etapButton;
    QPalette *palette;
    QRect avaibleScreenSize;
    QRect mainScreenSize;
    QRect currentGeometry;
    QPropertyAnimation *animate;
    QSlider *penSizeSelector;
    QLabel *thickness;
    QLabel *leftTextLabel;
};

#endif // MAINWINDOW_H
