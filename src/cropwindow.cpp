#include "include/cropwindow.h"



// Constructor
CropWindow::CropWindow(QPixmap pixmapFullscreen, QListWidget* listWidgetImage, bool* canTakeNewScreenshot) : QLabel()
{
    this->listWidgetImage = listWidgetImage;
    this->originalPixmap = new QPixmap(pixmapFullscreen);
    this->canTakeNewScreenshot = canTakeNewScreenshot;

    // Create the white version of the fullscreen screenshot
    this->whitePixmap = new QPixmap(pixmapFullscreen);
        this->painterMix = new QPainter(whitePixmap);
        this->painterMix->fillRect(pixmapFullscreen.rect(), QColor(255,255,255,127));
        this->painterMix->end();

    // Create the version of the fullscreen screenshot which will be display in the window
    this->mixPixmap = new QPixmap(*(this->whitePixmap));
        this->painterMix->begin(mixPixmap);

    // Update the pixmap to display
    this->setPixmap(*mixPixmap);

    // Configure the window
    this->setCursor(Qt::CrossCursor);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
}



// Destructor
CropWindow::~CropWindow()
{

}



// Methods


// When we click on the window
void CropWindow::mousePressEvent(QMouseEvent *event)
{
    // Accept the event
    event->accept();

    // Keep the origin position of the cropArea
    cropOrigin = event->pos();
    // Initialize the cropArea
    cropArea.setTopLeft(cropOrigin);
    cropArea.setSize(QSize());
}

// When we move on the window
void CropWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Accept the event
    event->accept();

    // Update the two corner of the crop Area
    cropArea.setTopLeft(cropOrigin);
    cropArea.setBottomRight(event->pos());
    // Normalized it to have propers values
    cropArea = cropArea.normalized();

    // Redraw the white version of the fullscreen screenshot...
    painterMix->drawPixmap(whitePixmap->rect(), *whitePixmap);
    // ...then draw the original fullscreen screenshot on the cropArea...
    painterMix->drawPixmap(cropArea, originalPixmap->copy(cropArea));
    // ... and finnaly draw the border of the cropArea
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

    // Get the screenshot cropped by the crop tool
    QPixmap croppedScreenshot = this->originalPixmap->copy(cropArea);

    // Add the screenshot to the list
    listWidgetImage->addItem(new Screenshot(croppedScreenshot, QDateTime::currentDateTime().toString("yy/mm/dd HH:mm:ss")));

    // Signal that's we can retake screenshot
    *canTakeNewScreenshot = true;

    // The crop process is complete, we close the window
    this->close();
}
