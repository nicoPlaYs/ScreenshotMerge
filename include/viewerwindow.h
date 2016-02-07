#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H



#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>



// The window to display an image
class viewerWindow : public QDialog
{
    // Variables
    private :
        // Main layout of the dialog
        QHBoxLayout* layout;
            // The label of the image we want to see
            QLabel* labelImage;

    // Constructor
    public :
        viewerWindow(QPixmap image);

    // Destructor
    public :
        ~viewerWindow();
};



#endif // VIEWERWINDOW_H
