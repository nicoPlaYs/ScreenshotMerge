#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H



#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QTranslator>



// The window to display an image
class ViewerWindow : public QDialog
{
    // Variables
    private :
        // Main layout of the dialog
        QHBoxLayout* layout;
            // The label of the image we want to see
            QLabel* labelImage;

    // Constructor
    public :
        ViewerWindow(QPixmap image);

    // Destructor
    public :
        ~ViewerWindow();
};



#endif // VIEWERWINDOW_H
