#ifndef DRAWING_H
#define DRAWING_H



#include <QPen>
#include <QColor>
#include <QPainter>



// Abstract class which contains the shape drawn by the user on his screenshots
class Drawing
{
    // Variable
    protected :
        // Pen used to draw the shape
        QPen pen;
        // Indicate if the shape is currently being drawn
        bool inProgress;

    // Getter
    public :
        bool getInProgess();

    // Setter
    public :
        void setPen(QPen pen);
        void setInProgress(bool inProgress);

    // Constructor
    public :
        Drawing(QPen pen);

    // Destructor
    public :
        virtual ~Drawing();

    // Methods
    public :
        // Draw the shape
        virtual void draw(QPainter* painter) = 0;
        // Return true if the shape is hitted by the hitbox in argument
        virtual bool isHitted(QRect hitbox) = 0;
};



#endif // DRAWING_H
