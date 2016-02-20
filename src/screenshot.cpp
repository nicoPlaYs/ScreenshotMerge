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
    QPixmap finalPixmap = QPixmap(this->image);
    QPainter* painter = new QPainter(&finalPixmap);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    painter->drawPixmap(this->image.rect(), this->image);
    ColoredPoly coloredPolyline;
    foreach(coloredPolyline, this->drawings)
    {
        painter->setPen(coloredPolyline.getColor());
        painter->drawPolyline(*coloredPolyline.getPtrPolyline());
    }
    painter->end();

    return finalPixmap;
}
