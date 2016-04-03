#include "include/screenshot.h"



// Getter
QPixmap Screenshot::getImage()
{
    return image;
}
QList<ColoredPoly> Screenshot::getDrawings()
{
    return drawings;
}



// Setter
void Screenshot::setImage(QPixmap image)
{
    this->image = image;
}
void Screenshot::setDrawings(QList<ColoredPoly> drawings)
{
    this->drawings = drawings;
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



// Methods


// Return a pixmap of the screenshot with all of his drawing on it
QPixmap Screenshot::withDrawing()
{
    // First, we make a clone of the screenshot without any drawings
    QPixmap finalPixmap = QPixmap(this->image);

    // We prepare the painter and his pen
    QPainter* painter = new QPainter(&finalPixmap);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPen pen;

    // We draw one by one all the drawings of the user on the screenshot
    ColoredPoly coloredPolyline;
    foreach(coloredPolyline, this->drawings)
    {
        pen.setColor(coloredPolyline.getColor());
        pen.setWidth(2);
        painter->setPen(pen);

        // If it's just a point...
        if(coloredPolyline.getPtrPolyline()->count() == 1)
        {
            painter->drawPoint(coloredPolyline.getPtrPolyline()->first());
        }
        // If it's a line...
        else
        {
            painter->drawPolyline(*coloredPolyline.getPtrPolyline());
        }
    }

    // The painting is over
    delete painter;

    // We return the result
    return finalPixmap;
}
