#ifndef CROPWINDOW_H
#define CROPWINDOW_H



#include <QLabel>
#include <QPoint>
#include <QRect>
#include <QListWidget>
#include <QMouseEvent>
#include <QPainter>


#include "include/screenshot.h"



// The window to crop the screenshot of the entire screen
class CropWindow : public QLabel
{
    Q_OBJECT

    // Variables
    private :
        // List of all the taken screenshots
        QListWidget* listWidgetImage;

        // Size and position for the crop tool
        QPoint cropOrigin;
        QRect cropArea;

        // Differents pixmaps to draw usefull for the crop tool
        QPixmap* originalPixmap;
        QPixmap* whitePixmap;
        QPixmap* mixPixmap;

        // Painter use to modify the differents pixmaps above
        QPainter* painterMix;

        // Usefull to refuse new screenshot to be taken when one is on his way to be taken / cropped
        bool* canTakeNewScreenshot;


    // Constructor
    public :
        CropWindow(QPixmap pixmapFullscreen, QListWidget* listWidgetImage, bool* canTakeNewScreenshot);

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
