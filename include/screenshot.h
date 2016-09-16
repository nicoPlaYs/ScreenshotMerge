#ifndef SCREENSHOT_H
#define SCREENSHOT_H



#include <QListWidgetItem>
#include <QDateTime>
#include <QLinkedList>
#include <QMultiMap>
#include <QPolygon>
#include <QPainter>


// A polyline which can be drawn by the user
#include "include/drawings/polyline.h"
// A straight line which can be drawn by the user
#include "include/drawings/straightline.h"
// A frame which can be drawn by the user
#include "include/drawings/frame.h"



// Store a screenshot which can be put in a QListWidget
class Screenshot : public QListWidgetItem
{
    // Variables
    private :
        // The screenshot
        QPixmap image;
        // The drawings on the screenshot
        QLinkedList<Drawing*> drawingsList;

    // Getter
    public :
        QPixmap getImage();
        QLinkedList<Drawing*> getDrawings();

    // Setter
    public :
        void setImage(QPixmap image);
        void setDrawings(QLinkedList<Drawing*> drawingsList);

    // Constructor
    public :
        Screenshot(QPixmap image, const QString &text, QListWidget* parent = 0, int type = Type);

    // Destructor
    public :
        ~Screenshot();

    // Methods
    public :
        // Return a pixmap of the screenshot with all of his drawings on it
        QPixmap withDrawings();
};



#endif // SCREENSHOT_H
