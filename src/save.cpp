#include "include/save.h"



// Give the next screenshot name available for the default directory
QString nextScreenshotName()
{
    QSettings settings;

    QString path = settings.value("SettingsWindow/defaultDirectory", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)).toString();

    // We check every number of screenshot on the directory to find the next screenshot name available
    QFile nextScreenshotJPG(path + "\\Screenshot00001.jpg");
    QFile nextScreenshotPNG(path + "\\Screenshot00001.png");
    for(int i = 2; i < 99999 && (nextScreenshotJPG.exists() || nextScreenshotPNG.exists()); i++)
    {
        nextScreenshotJPG.setFileName(path + QString("\\Screenshot") + QString::number(i).rightJustified(5, '0', false) + ".jpg");
        nextScreenshotPNG.setFileName(path + QString("\\Screenshot") + QString::number(i).rightJustified(5, '0', false) + ".png");
    }

    return nextScreenshotJPG.fileName();
}

// Save an image
void saveImage(QPixmap image)
{
    QSettings settings;

    // We check if the user want to use the default directory or if he want the program to ask him
    QString path;
    if(!settings.value("SettingsWindow/alwaysUseDefaultDirectory", false).toBool())
    {
        // Open the dialog for the user to indicate where he want his merged screenhosts to be saved
        path = QFileDialog::getSaveFileName(0, QObject::tr("Save as..."), nextScreenshotName(), "JPG (*.jpg);;PNG (*.png)");
    }
    else
    {
        path = nextScreenshotName();
    }

    // We verify that the user has really selected a path
    if(path != 0)
    {
        // Save the merged screenshots
        image.save(path, 0, settings.value("SettingsWindow/imageQuality", 85).toInt());
        if(settings.value("SettingsWindow/alwaysUseDefaultDirectory", false).toBool())
        {
            QMessageBox::information(0, QObject::tr("Image successfully saved"), QObject::tr("Your image has been saved in your default directory !"));
        }
    }
}
