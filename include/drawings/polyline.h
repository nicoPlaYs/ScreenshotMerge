#ifndef POLYLINE_H
#define POLYLINE_H



#include <QPolygon>


// Abstract class which contains the shape drawn by the user on his screenshots
#include "include/drawings/drawing.h"



// A polyline which can be drawn by the user
class Polyline : public Drawing
{
    // Variable
    private :
        // The points of the polyline is stored in this polygon
        QPolygon polyline;

    // Constructor
    public :
        Polyline(QPen pen, QPoint firstPoint);
        Polyline(Polyline const& polyline);

    // Destructor
    public :
        ~Polyline();

    // Methods
    public :
        // Clone the polyline
        virtual Drawing* clone();

        // Draw the polyline
        void draw(QPainter* painter);
        // Return true if the polyline is hitted by the hitbox in argument
        bool isHitted(QRect hitbox);

        // Return true if the polyline is empty
        bool isEmpty();
        // Add a point at the end of the polyline
        void addPoint(QPoint newPoint);
};



#endif // POLYLINE_H
