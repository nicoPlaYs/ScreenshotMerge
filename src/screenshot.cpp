#include "include/screenshot.h"



// Getter
QPixmap Screenshot::getImage()
{
    return image;
}



// Constructor
Screenshot::Screenshot(QPixmap image, const QString &text, QListWidget* parent, int type) : QListWidgetItem(text, parent, type)
{
    this->image = image;
}



// Destructor
Screenshot::~Screenshot()
{

}
