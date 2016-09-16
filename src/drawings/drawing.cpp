#include "include/drawings/drawing.h"



// Getter
bool Drawing::getInProgess()
{
    return inProgress;
}



// Setter
void Drawing::setPen(QPen pen)
{
    this->pen = pen;
}
void Drawing::setInProgress(bool inProgress)
{
    this->inProgress = inProgress;
}



// Constructor
Drawing::Drawing(QPen pen)
{
    this->pen = pen;
    this->inProgress = true;
}



// Destructeur
Drawing::~Drawing()
{

}
