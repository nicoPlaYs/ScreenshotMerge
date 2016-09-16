#include "include/drawings/polyline.h"



// Constructor
Polyline::Polyline(QPen pen, QPoint firstPoint) : Drawing(pen)
{
    this->polyline.append(firstPoint);
}



// Destructeur
Polyline::~Polyline()
{

}



// Methods

// Draw the polyline
void Polyline::draw(QPainter* painter)
{
    painter->setPen(pen);

    // If it's just a point...
    if(polyline.count() == 1)
    {
        painter->drawPoint(polyline.first());
    }
    // If it's a line...
    else
    {
        painter->drawPolyline(polyline);
    }
}

// Return true if the polyline is empty
bool Polyline::isEmpty()
{
    return polyline.isEmpty();
}

// Return true if the polyline is hitted by the hitbox in argument
bool Polyline::isHitted(QRect hitbox)
{
    // Increase the size of the hitbox depending on the of the pen
    int margin = pen.width()/2;
    hitbox = hitbox.marginsAdded(QMargins(margin,margin,margin,margin));

    // Check points one by one
    QPoint point;
    foreach(point, polyline)
    {
        if(hitbox.contains(point))
        {
            return true;
        }
    }
    return false;
}


// Add a point at the end of the polyline
void Polyline::addPoint(QPoint newPoint)
{
    polyline.append(newPoint);
}