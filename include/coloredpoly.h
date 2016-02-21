#ifndef COLOREDPOLY_H
#define COLOREDPOLY_H



class ColoredPoly;
#include "include/screenshot.h"



// Associate a polygon with a color
class ColoredPoly
{
    // Variable
    private :
        QPolygon polyline;
        QColor color;

    // Getter
    public :
        QPolygon* getPtrPolyline();
        QColor getColor();

    // Setter
    public :
        void setPolyline(QPolygon polyline);
        void setColor(QColor color);

    // Constructor
    public :
        ColoredPoly();

    // Operator overloading
    public :
        bool operator==(const ColoredPoly second);
};



#endif // COLOREDPOLY_H
