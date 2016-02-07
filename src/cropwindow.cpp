#include "include/cropwindow.h"



// Constructor
CropWindow::CropWindow(QPixmap pixmapFullscreen, QListWidget* listWidgetImage) : QLabel()
{
    this->listWidgetImage = listWidgetImage;
    this->originalPixmap = new QPixmap(pixmapFullscreen);
    this->whitePixmap = new QPixmap(pixmapFullscreen);
        this->painterMix = new QPainter(whitePixmap);
        this->painterMix->fillRect(pixmapFullscreen.rect(), QColor(255,255,255,127));
        this->painterMix->end();
    this->mixPixmap = new QPixmap(*(this->whitePixmap));
        this->painterMix->begin(mixPixmap);

    this->setPixmap(*mixPixmap);
    this->setCursor(Qt::CrossCursor);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
}



// Destructor
CropWindow::~CropWindow()
{

}



// Qt slots

// When we click on the window
void CropWindow::mousePressEvent(QMouseEvent *event)
{
    event->accept();

    cropOrigin = event->pos();
    cropArea.setTopLeft(cropOrigin);
    cropArea.setSize(QSize());
}

// When we move on the window
void CropWindow::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    cropArea.setTopLeft(cropOrigin);
    cropArea.setBottomRight(event->pos());
    cropArea = cropArea.normalized();

    painterMix->drawPixmap(whitePixmap->rect(), *whitePixmap);
    painterMix->drawPixmap(cropArea, originalPixmap->copy(cropArea));
    painterMix->setPen(QPen("#528e33"));
    painterMix->drawRect(cropArea);

    this->setPixmap(*mixPixmap);
}

// When we release the click on the window
void CropWindow::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();

    QPixmap croppedScreenshot = this->originalPixmap->copy(cropArea);

    listWidgetImage->addItem(new Screenshot(croppedScreenshot, QDateTime::currentDateTime().toString("yy/mm/dd HH:mm:ss")));

    this->close();
}
