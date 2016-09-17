#include "include/screenshot.h"

#include <QDebug>

// Getter
QPixmap Screenshot::getImage()
{
    return image;
}
QLinkedList<Drawing*> Screenshot::getDrawings()
{
    return drawingsList;
}



// Setter
void Screenshot::setImage(QPixmap image)
{
    this->image = image;
}
void Screenshot::setDrawings(QLinkedList<Drawing*> drawings)
{
    this->drawingsList = drawings;
}



// Constructor
Screenshot::Screenshot(QPixmap image, const QString &text, QListWidget* parent, int type) : QListWidgetItem(text, parent, type)
{
    this->image = image;
}



// Destructor
Screenshot::~Screenshot()
{
    while(!drawingsList.isEmpty())
    {
        delete drawingsList.takeFirst();
    }
}



// Methods


// Return a pixmap of the screenshot with all of his drawings on it
QPixmap Screenshot::withDrawings()
{
    // First, we make a clone of the screenshot without any drawings
    QPixmap finalPixmap = QPixmap(this->image);

    // We prepare the painter and his pen
    QPainter* painter = new QPainter(&finalPixmap);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // We draw one by one all the drawings of the user on the screenshot
    Drawing* drawing;
    foreach(drawing, this->drawingsList)
    {
        drawing->draw(painter);
    }

    // The painting is over
    delete painter;

    // We return the result
    return finalPixmap;
}
