#ifndef CROPWINDOW_H
#define CROPWINDOW_H


#include <QLabel>
#include <QPoint>
#include <QSize>
#include <QRubberBand>
#include <QListWidget>
#include <QMouseEvent>
#include <QPainter>



#include "include/screenshot.h"


class CropWindow : public QLabel
{
    Q_OBJECT

    // Variables
    private :
        QListWidget* listWidgetImage;
        QPoint cropOrigin;
        QRect cropArea;
        QPixmap* originalPixmap;
        QPixmap* whitePixmap;
        QPixmap* mixPixmap;
        QPainter* painterMix;


    // Constructor
    public :
        CropWindow(QPixmap pixmapFullscreen, QListWidget* listWidgetImage);

    // Destructor
    public :
        ~CropWindow();

    // Qt slots
    public slots :
        // When we click on the window
        void mousePressEvent(QMouseEvent *event);
        // When we move on the window
        void mouseMoveEvent(QMouseEvent *event);
        // When we release the click on the window
        void mouseReleaseEvent(QMouseEvent *event);
};



#endif // CROPWINDOW_H
