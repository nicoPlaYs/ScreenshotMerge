#ifndef SCREENSHOT_H
#define SCREENSHOT_H



#include <QListWidgetItem>
#include <QDateTime>
#include <QList>
#include <QPolygon>
#include <QPainter>


// Associate a polygon with a color
#include "include/coloredpoly.h"



// Store a screenshot which can be put in a QListWidget
class Screenshot : public QListWidgetItem
{
    // Variables
    private :
        // The screenshot
        QPixmap image;
        // The drawings on the screenshot
        QList<ColoredPoly> drawings;

    // Getter
    public :
        QPixmap getImage();
        QList<ColoredPoly> getDrawings();

    // Setter
    public :
        void setImage(QPixmap image);
        void setDrawings(QList<ColoredPoly> drawings);

    // Constructor
    public :
        Screenshot(QPixmap image, const QString &text, QListWidget* parent = 0, int type = Type);

    // Destructor
    public :
        ~Screenshot();

    // Methods
    public :
        // Return a pixmap of the screenshot with all of his drawing on it
        QPixmap withDrawing();
};



#endif // SCREENSHOT_H
