#ifndef UPLOAD_H
#define UPLOAD_H



#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHttpMultiPart>

enum ImageHost{noelshack, imgur};
Q_DECLARE_METATYPE(ImageHost)

#include "include/windows/uploadwindow.h"
#include "include/apikeys.h"


// Upload an image
void uploadImage(QPixmap image, ImageHost host, int quality);
// Return the link of the uploaded screenshot
QString linkUploadedScreenshot(QByteArray byteReplied, ImageHost host);



#endif // UPLOAD_H
