#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H


#include <QDialog>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>



class viewerWindow : public QDialog
{
    // Variables
    private :
        QHBoxLayout* layout;
            QLabel* labelImage;

    // Constructor
    public :
        viewerWindow(QPixmap image);

    // Destructor
    public :
        ~viewerWindow();
};



#endif // VIEWERWINDOW_H
