#ifndef SCREENSHOT_H
#define SCREENSHOT_H



#include <QListWidgetItem>
#include <QDateTime>
#include <QKeyEvent>



class Screenshot : public QListWidgetItem
{
    // Variables
    private :
        QPixmap image;

    // Getter
    public :
        QPixmap getImage();

    // Constructor
    public :
        Screenshot(QPixmap image, const QString &text, QListWidget* parent = 0, int type = Type);

    // Destructor
    public :
        ~Screenshot();
};



#endif // SCREENSHOT_H
