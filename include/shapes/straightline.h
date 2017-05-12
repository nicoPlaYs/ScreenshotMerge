#ifndef STRAIGHTLINE_H
#define STRAIGHTLINE_H



#include <QLine>


// Abstract class which contains the shape drawn by the user on his screenshots
#include "include/shapes/shape.h"



// A straight line which can be drawn by the user
class StraightLine : public Shape
{
    // Variable
    private :
        // The straight line;
        QLineF straightLine;

    // Setter
    public :
        void setEndPoint(QPoint endPoint);

    // Constructor
    public:
        StraightLine(QPen pen, QPoint P1, QPoint P2);
        StraightLine(StraightLine const& straightline);

    // Destructor
    public:
        ~StraightLine();

    // Methods
    public :
        // Clone the straight line
        virtual Shape* clone();

        // Draw the straight line
        virtual void draw(QPainter *painter);
        // Return true if the straight line is hitted by the hitbox in argument
        virtual bool isHitted(QRect hitbox);
};



#endif // STRAIGHTLINE_H
