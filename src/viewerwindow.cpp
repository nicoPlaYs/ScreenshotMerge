#include "include/viewerwindow.h"

// Constructor
viewerWindow::viewerWindow(QPixmap image) : QDialog()
{
    // Creation of the layout of the window
    layout = new QHBoxLayout(this);

        // Creation of the label which contain the image to display
        labelImage = new QLabel(this);
        labelImage->setPixmap(image);

    // Add the label to the layout
    layout->addWidget(labelImage, Qt::AlignCenter);

    // Configuraiton of the window
    this->setMaximumSize(labelImage->size());
    this->setModal(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
}

// Destructor
viewerWindow::~viewerWindow()
{

}
