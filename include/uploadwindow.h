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



// Window which appears when uploading an image to NoelShack
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

        // Reply of NoelShack
        QNetworkReply* reply;

    // Constructor
    public :
        UploadWindow(QNetworkReply* reply);

    // Destructor
    public :
        ~UploadWindow();

    // Qt slots
    public slots :
        // Update the value of the upload progress bar
        void updateUploadProgress(qint64 bytesSent, qint64 bytesTotal);
        // Upload is finished
        void uploadFinished();
        // Copy the link into the clipboard
        void copyLinkInClipboard();
        // Cancel the upload
        void cancel();
};



#endif // UPLOADWINDOW_H
