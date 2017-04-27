#include "include/checkforupdate.h"



// Constructor
CheckForUpdate::CheckForUpdate(QString currentVersion) : QThread()
{
    this->currentVersion = currentVersion;

    // Destroy this thread when its job is over
    QObject::connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}



// Destructor
CheckForUpdate::~CheckForUpdate()
{

}



// Methods

void CheckForUpdate::run()
{
    QNetworkRequest request;
    request.setUrl(QString("https://api.github.com/repos/nicolasfostier/ScreenshotMerge/releases/latest"));

    QNetworkAccessManager manager;
    reply = manager.get(request);
    reply->ignoreSslErrors();
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));

    // Enter the event loop
    this->exec();
}



// Qt slots

// Read and process the reply from github
void CheckForUpdate::replyFinished()
{
    // Check if everything went well
    if(reply->error() == QNetworkReply::NoError)
    {
        QJsonDocument jsonReply = QJsonDocument::fromJson(reply->readAll());
        QString lastVersionAvailable = jsonReply.object().value("tag_name").toString();
        if(lastVersionAvailable > currentVersion)
        {
            QMessageBox().about(nullptr, QObject::tr("Update available !"),"<p>" + QObject::tr("A new version of Screenshot Merge is available on github.") + "<br/>" +
                                                                "<b>" + QObject::tr("Your version :") + "</b> " + currentVersion + "<br/>" +
                                                                "<b>" + QObject::tr("Latest version available :") + "</b> " + jsonReply.object().value("tag_name").toString() + "</p>" +
                                                                "<h3 style='text-align: center'><a href='" + jsonReply.object().value("html_url").toString() + "'>" + QObject::tr("Download the latest version") + "</a></h3>");
        }
    }

    // Exit the event loop, and stop the thread
    this->exit();
}
