#ifndef INCLUDECHECKFORUPDATE_H
#define INCLUDECHECKFORUPDATE_H


#include <QTranslator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QThread>



// Check if there is an update available on github
class CheckForUpdate : public QThread
{
    Q_OBJECT

    // Variable
    private :
        // Current version of the program
        QString currentVersion;
        // Reply from github
        QNetworkReply* reply;

    // Constructor
    public :
        CheckForUpdate(QString currentVersion);

    // Destructor
    public :
        ~CheckForUpdate();

    // Methods
    public :
        // The thread task
        void run();

    // Qt slots
    public slots :
        // Read and process the reply from github
        void replyFinished();
};



#endif // INCLUDECHECKFORUPDATE_H
