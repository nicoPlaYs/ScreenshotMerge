#include "include/upload.h"



// Upload an image
void uploadImage(QPixmap image, ImageHost host, int quality){
	// Transform the image into an array of base64
	QByteArray imageData;
	QBuffer bufferImageData(&imageData);
	bufferImageData.open(QIODevice::ReadWrite);
	image.save(&bufferImageData, "JPG", quality);
	bufferImageData.reset();

	// Create a request
	QNetworkRequest request;

	// Organize the data to sent
	QHttpMultiPart* data = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	QHttpPart dataImage;
	dataImage.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
	dataImage.setBody(bufferImageData.readAll());

	switch(host){
		case noelshack :{
			request.setUrl(QUrl("http://www.noelshack.com/api.php"));

			dataImage.setHeader(QNetworkRequest::ContentDispositionHeader,
								QVariant("form-data; name=\"fichier\"; filename=\"screenshot-"
										 + QString::number(1000 + (qrand() % (9999 - 1000 + 1)))
										 + ".jpg\";"));
		}
		break;

		case imgur :{
			request.setUrl(QUrl("https://api.imgur.com/3/image"));
			request.setRawHeader("Authorization", IMGUR_CLIENT_ID.toLatin1());

			dataImage.setHeader(QNetworkRequest::ContentDispositionHeader,
								QVariant("form-data; name=\"image\""));
		}
		break;
	}

	data->append(dataImage);

	QNetworkAccessManager* manager = new QNetworkAccessManager();
	QNetworkReply* reply = manager->post(request, data);

	// Open the upload dialog
	UploadWindow* uploadWindow = new UploadWindow(reply, host);
	manager->setParent(uploadWindow);
}

// Return the link of the uploaded screenshot
QString linkUploadedScreenshot(QByteArray byteReplied, ImageHost host){
	QString link = QString();

	switch(host){
		case noelshack :{
			link = byteReplied;
			QRegExp exp("(\\d+)-(\\d+)-(\\d+)-(\\S+)");
			exp.indexIn(link);
			link = "http://image.noelshack.com/fichiers/"
				   + exp.cap(1) + "/" + exp.cap(2) + "/" + exp.cap(3) + "/" + exp.cap(4);
		}
		break;

		case imgur :{
			QJsonDocument imageInfo = QJsonDocument::fromJson(byteReplied);
			link = imageInfo.object().value("data").toObject().value("link").toString();
		}
		break;
	}

	return link;
}
