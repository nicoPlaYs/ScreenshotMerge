#include "include/drawings/frame.h"



// Setter
void Frame::setEndPoint(QPoint endPoint)
{
    this->frame.setTopLeft(this->firstPoint);
    this->frame.setBottomRight(endPoint);
    this->frame = this->frame.normalized();
}



// Constructor
Frame::Frame(QPen pen, QPoint P1, QPoint P2) : Drawing(pen)
{
    this->firstPoint = P1;
    this->setEndPoint(P2);
}



// Destructor
Frame::~Frame()
{

}



// Methods

// Draw the frame
void Frame::draw(QPainter *painter)
{
    painter->setPen(this->pen);
    painter->drawRect(this->frame);
}

// Return true if the frame is hitted by the hitbox in argument
bool Frame::isHitted(QRect hitbox)
{
    // Increase the size of the hitbox depending on the of the pen
    int margin = pen.width()/2;
    hitbox = hitbox.marginsAdded(QMargins(margin,margin,margin,margin));

    // Check the points from the 4 line of the rectangle

    int x = this->frame.topLeft().x();
    int y = this->frame.topLeft().y();

    // Top line
    while(x != this->frame.topRight().x())
    {
        if(hitbox.contains(QPoint(x, y)))
        {
            return true;
        }

        x++;
    }
    // Right line
    while(y != this->frame.bottomRight().y())
    {
        if(hitbox.contains(QPoint(x, y)))
        {
            return true;
        }

        y++;
    }
    // Bottom line
    while(x != this->frame.bottomLeft().x())
    {
        if(hitbox.contains(QPoint(x, y)))
        {
            return true;
        }

        x--;
    }
    // Left line
    while(y != this->frame.topLeft().y() - 1)
    {
        if(hitbox.contains(QPoint(x, y)))
        {
            return true;
        }

        y--;
    }

    return false;
}
