#ifndef SAVE_H
#define SAVE_H



#include <QString>
#include <QSettings>
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>
#include <QFileDialog>
#include <QTranslator>



// Give the next screenshot name available for the default directory
QString nextScreenshotName();
// Save an image
void saveImage(QPixmap image);


#endif // SAVE_H
