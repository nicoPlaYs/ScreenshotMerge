#include "include/windows/uploadwindow.h"



// Constructor
UploadWindow::UploadWindow(QNetworkReply* reply) : QDialog()
{
    this->reply = reply;
    QObject::connect(this->reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(updateUploadProgress(qint64,qint64)));
    QObject::connect(this->reply, SIGNAL(finished()), this, SLOT(uploadFinished()));


    // The main layout
    mainLayout = new QGridLayout(this);
    mainLayout->setVerticalSpacing(10);

        // Progress bar of the upload
        uploadProgressBar = new QProgressBar(this);
        uploadProgressBar->setTextVisible(true);

    mainLayout->addWidget(uploadProgressBar, 0, 0, 1, 2);

        // Will contain the link to the uploaded image
        lineEditLink = new QLineEdit(this);
        lineEditLink->setDisabled(true);

    mainLayout->addWidget(lineEditLink, 1, 0, 1, 2);

        // Copy the link to the clipboard and close this window
        copyLinkInClipboardButton = new QPushButton(tr("Copy to clipboard"), this);
        copyLinkInClipboardButton->setDisabled(true);
        QObject::connect(copyLinkInClipboardButton, SIGNAL(pressed()), this, SLOT(copyLinkInClipboard()));

    mainLayout->addWidget(copyLinkInClipboardButton, 2, 0, 1, 1, Qt::AlignCenter);

        // Cancel the upload and close the window
        cancelButton = new QPushButton(tr("Cancel"), this);
        QObject::connect(cancelButton, SIGNAL(pressed()), this, SLOT(cancel()));

    mainLayout->addWidget(cancelButton, 2, 1, 1, 1, Qt::AlignCenter);


    // Configuration of the window
    this->setWindowTitle(tr("Uploading to NoelShack"));
    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setFixedSize(430,100);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->show();
}



// Destructor
UploadWindow::~UploadWindow()
{

}



// Qt slots


// Update the value of the progress bar
void UploadWindow::updateUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    if (bytesTotal != -1 && bytesSent != bytesTotal)
    {
        uploadProgressBar->setRange(0, bytesTotal);
        uploadProgressBar->setValue(bytesSent);
    }
}

// Upload is finished
void UploadWindow::uploadFinished()
{
    // Get the correct link of just the image
    QString link = reply->readAll();
    QRegExp exp("(\\d+)-(\\d+)-(\\d+)-(\\S+)");
    exp.indexIn(link);
    link = "http://image.noelshack.com/fichiers/" + exp.cap(1) + "/" + exp.cap(2) + "/" + exp.cap(3) + "-" + exp.cap(4);

    // Update the progressbar to 100%
    uploadProgressBar->setRange(0,100);
    uploadProgressBar->setValue(100);

    // Write the link into the QLineEdit
    lineEditLink->setEnabled(true);
    lineEditLink->setText(link);
    lineEditLink->setReadOnly(true);
    lineEditLink->setSelection(0, link.length());

    // Enable the button to copy the link to clipboard
    copyLinkInClipboardButton->setEnabled(true);
}

// Copy the link into the clipboard
void UploadWindow::copyLinkInClipboard()
{
     // We get access to the clipboard
    QClipboard* clipboard = QApplication::clipboard();

    // Put the link into it
    clipboard->setText(lineEditLink->text());

    // Close the upload window
    this->close();
}

// Cancel the upload
void UploadWindow::cancel()
{
    // End the upload if it's not over yet
    this->reply->abort();

    // Close the upload window
    this->close();
}
