#include "include/viewerwindow.h"

// Constructor
viewerWindow::viewerWindow(QPixmap image) : QDialog()
{
    layout = new QHBoxLayout(this);

        labelImage = new QLabel(this);
        labelImage->setPixmap(image);

    layout->addWidget(labelImage, Qt::AlignCenter);

    this->setMaximumSize(labelImage->size());
    this->setModal(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
}

// Destructor
viewerWindow::~viewerWindow()
{

}
