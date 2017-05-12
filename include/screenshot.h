#ifndef SCREENSHOT_H
#define SCREENSHOT_H



#include <QListWidgetItem>
#include <QDateTime>
#include <QLinkedList>
#include <QMultiMap>
#include <QPolygon>
#include <QPainter>


// A polyline which can be drawn by the user
#include "include/shapes/polyline.h"
// A straight line which can be drawn by the user
#include "include/shapes/straightline.h"
// A frame which can be drawn by the user
#include "include/shapes/frame.h"



// Store a screenshot which can be put in a QListWidget
class Screenshot : public QListWidgetItem
{
    // Variables
    private :
        // The screenshot
        QPixmap image;
        // The shapes on the screenshot
        QLinkedList<Shape*> shapesList;

    // Getter
    public :
        QPixmap getImage();
        QLinkedList<Shape*> getShapes();

    // Setter
    public :
        void setImage(QPixmap image);
        void setShapes(QLinkedList<Shape*> shapesList);

    // Constructor
    public :
        Screenshot(QPixmap image, const QString &text, QListWidget* parent = 0, int type = Type);

    // Destructor
    public :
        ~Screenshot();

    // Methods
    public :
        // Return a pixmap of the screenshot with all of its shapes drawn
        QPixmap withDrawings();
};



#endif // SCREENSHOT_H
