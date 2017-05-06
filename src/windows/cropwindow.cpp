#include "include/windows/cropwindow.h"



// Constructor
CropWindow::CropWindow(QPixmap pixmapFullscreen, QRect screensRect) : QLabel()
{
    dateShooting = QDateTime::currentDateTime().toString("yy/mm/dd HH:mm:ss");
    this->originalPixmap = new QPixmap(pixmapFullscreen);

    // Create the white version of the fullscreen screenshot
    this->whitePixmap = new QPixmap(pixmapFullscreen);
        this->painterMix = new QPainter(whitePixmap);
        this->painterMix->fillRect(pixmapFullscreen.rect(), QColor(255,255,255,127));
        delete this->painterMix;

    // Create the version of the fullscreen screenshot which will be display in the window
    this->mixPixmap = new QPixmap(*(this->whitePixmap));

    // Prepare the painter
    this->painterMix = new QPainter(mixPixmap);

    // Update the pixmap to display
    this->setPixmap(*mixPixmap);

    // Configure the window
    this->setCursor(Qt::CrossCursor);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowModality(Qt::ApplicationModal);
    this->show();
    this->resize(screensRect.size());
    this->move(screensRect.topLeft());
}



// Destructor
CropWindow::~CropWindow()
{
    delete painterMix;
    delete originalPixmap;
    delete whitePixmap;
    delete mixPixmap;
}



// Methods

// When we click on the window
void CropWindow::mousePressEvent(QMouseEvent *event)
{
    // Accept the event
    event->accept();

    // Keep the origin position of the crop area
    cropOrigin = event->pos();
    // Initialize the crop area
    cropArea.setTopLeft(cropOrigin);
    cropArea.setSize(QSize(0,0));
}

// When we move on the window
void CropWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Accept the event
    event->accept();

    QRect previousCropArea = cropArea + QMargins(1,1,1,1);
    // Update the two corner of the crop Area
    cropArea.setTopLeft(cropOrigin);
    cropArea.setBottomRight(event->pos());
    // Normalized it to have propers values
    cropArea = cropArea.normalized();

    // Redraw the white version of screenshot where was the previous crop area...
    painterMix->drawPixmap(previousCropArea, whitePixmap->copy(previousCropArea));
    // ...then draw the original fullscreen screenshot on the current crop area...
    painterMix->drawPixmap(cropArea, originalPixmap->copy(cropArea));

    // ... and finnaly draw the border of the crop area
    painterMix->setPen(QPen("#6324bd"));
    painterMix->drawRect(cropArea);

    // Update the pixmap which is displayed
    this->setPixmap(*mixPixmap);
}

// When we release the click on the window
void CropWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Accept the event
    event->accept();

    // Verify if the size of the crop area is not null. If it's not the case...
    if(!cropArea.size().isEmpty())
    {
        // ...send the cropped screenshot to the edit window
        emit cropOver(new Screenshot(this->originalPixmap->copy(cropArea), dateShooting, 0));

        // The crop process is complete, we close the window
        this->close();
    }
    // If it's null, the user need to crop it again
    else
    {
        painterMix->drawPixmap(whitePixmap->rect(), *whitePixmap);
        this->setPixmap(*mixPixmap);
    }
}
