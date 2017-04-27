#ifndef UPLOADWINDOW_H
#define UPLOADWINDOW_H



#include <QDialog>
#include <QTranslator>
#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>
#include <QClipboard>
#include <QApplication>
#include <QNetworkReply>


// Upload function in order to send the screenshots to an image host
#include "include/upload.h"



// Window which appears when uploading an image to an image host website
class UploadWindow : public QDialog
{
    Q_OBJECT

    // Variables
    private :
        // Main layout
        QGridLayout* mainLayout;
            // Progress bar of the upload
            QProgressBar* uploadProgressBar;
            // Will contain the link to the uploaded image
            QLineEdit* lineEditLink;
            // Copy the link to the clipboard and close this window
            QPushButton* copyLinkInClipboardButton;
            // Cancel the upload and close the window
            QPushButton* cancelButton;

        // Host
        ImageHost host;
        // Reply of the image host
        QNetworkReply* reply;

    // Constructor
    public :
        UploadWindow(QNetworkReply* reply, ImageHost host);

    // Destructor
    public :
        ~UploadWindow();

    // Qt slots
    public slots :
        // Update the value of the upload progress bar
        void updateUploadProgress(qint64 bytesSent, qint64 bytesTotal);
        // Read and process the reply from the image host
        void uploadFinished();
        // Copy the link into the clipboard
        void copyLinkInClipboard();
        // Cancel the upload
        void cancel();
};



#endif // UPLOADWINDOW_H
