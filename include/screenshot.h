#ifndef SCREENSHOT_H
#define SCREENSHOT_H



#include <QListWidgetItem>
#include <QDateTime>



// Store a screenshot which can be put in a QListWidget
class Screenshot : public QListWidgetItem
{
    // Variables
    private :
        // The screenshot
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
