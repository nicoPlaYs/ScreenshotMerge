#include "include\coloredpoly.h"



// Getter
QPolygon* ColoredPoly::getPtrPolyline()
{
    return &polyline;
}
QColor ColoredPoly::getColor()
{
    return color;
}



// Setter
void ColoredPoly::setPolyline(QPolygon polyline)
{
    this->polyline = polyline;
}
void ColoredPoly::setColor(QColor color)
{
    this->color = color;
}



// Constructor
ColoredPoly::ColoredPoly()
{

}



// Operator overloading
bool ColoredPoly::operator==(const ColoredPoly second)
{
    if(this->polyline == second.polyline)
    {
        return true;
    }
    else
    {
        return false;
    }
}
