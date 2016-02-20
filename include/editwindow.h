#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H



#include <QMainWindow>
#include <QHBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QClipboard>
#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QSettings>
#include <QCloseEvent>
#include <QLabel>
#include <QTranslator>



// The window to display an image
class EditWindow : public QMainWindow
{
    Q_OBJECT

    // Variables
    private :
        // Settings
        QSettings* settings;

        // Color of the draw tool
        QColor drawColor;

        // The toolbar
        QToolBar* toolBar;
            QAction* actionValidate;
            QAction* actionCancel;

            QAction* actionRetake;
            QAction* actionSave;
            QAction* actionCopyToClipboard;

            QAction* actionColor;
            QActionGroup* actionGroupDrawTool;
                QAction* actionPen;
                QAction* actionEraser;

        // Main widget of the window
        QWidget* widgetMain;
            // Main layout of the dialog
            QHBoxLayout* layout;
                // The label of the image we want to see
                QLabel* labelImage;

    // Constructor
    public :
        EditWindow(QPixmap image);

    // Destructor
    public :
        ~EditWindow();

    // Methods
    public :
        // When the window is closing
        void closeEvent(QCloseEvent* event);

    // Qt slots
    public slots:
        // Validate
        void validate();
        // Cancel
        void cancel();

        // Retake the screenshot
        void retake();
        // Save the screenshot
        void save();
        // Copy the screenshot to the clipboard
        void copyToClipboard();

        // Change the color of the draw tool
        void changeColor();
};



#endif // VIEWERWINDOW_H
