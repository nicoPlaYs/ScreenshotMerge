#include "include/drawings/straightline.h"

#include <QDebug>

// Setter
void StraightLine::setEndPoint(QPoint endPoint)
{
    this->straightLine.setP2(endPoint);
}



// Constructeur
StraightLine::StraightLine(QPen pen, QPoint P1, QPoint P2) : Drawing(pen)
{
    this->straightLine.setP1(P1);
    this->straightLine.setP2(P2);
}



// Destructeur
StraightLine::~StraightLine()
{

}



// Methods

void StraightLine::draw(QPainter *painter)
{
    painter->setPen(this->pen);
    painter->drawLine(this->straightLine);
}

bool StraightLine::isHitted(QRect hitbox)
{
    // Increase the size of the hitbox depending on the of the pen
    int margin = pen.width()/2;
    hitbox = hitbox.marginsAdded(QMargins(margin,margin,margin,margin));

    // Check the point one by one...

    double x;
    double xMax;
    x = (straightLine.x1() < straightLine.x2()) ? straightLine.x1() : straightLine.x2();
    xMax = (straightLine.x1() < straightLine.x2()) ? straightLine.x2() : straightLine.x1();

    double y;
    double yMax;
    y = (straightLine.y1() < straightLine.y2()) ? straightLine.y1() : straightLine.y2();
    yMax = (straightLine.y1() < straightLine.y2()) ? straightLine.y2() : straightLine.y1();

    // ... with the equation y = a*x+b if the line isn't vertical...
    if(straightLine.x1() != straightLine.x2())
    {
        double a;
        double b;
        a = (straightLine.y2() - straightLine.y1()) / (straightLine.x2() - straightLine.x1());
        b = (straightLine.y1() - (a * straightLine.x1()));

        double inc = (xMax - x < yMax - y) ? (xMax - x) / (yMax - y) : 1;

        while(x <= xMax)
        {
            y = (a * x) + b;

            if(hitbox.contains(QPoint(x,y)))
            {
                return true;
            }

            x += inc;
        }
    }
    // and if it's the case, with all the possibles values of y
    else
    {
        while(y <= yMax)
        {
            if(hitbox.contains(QPoint(straightLine.x1(),y)))
            {
                return true;
            }

            y++;
        }
    }


    return false;
}
