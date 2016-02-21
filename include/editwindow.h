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
#include <QListWidget>
#include <QMessageBox>
#include <QShortcut>
#include <QPainter>


// Store a screenshot which can be put in a QListWidget
#include "include/screenshot.h"



// The window to display and edit an screenshot
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

        // Screenshot
        Screenshot* screenshot;
        // List of all the taken screenshots
        QListWidget* listWidgetImage;
        // Usefull to refuse new screenshot to be taken when one is on his way to be taken / cropped
        bool* canTakeNewScreenshot;
        // QPixmap to show
        QPixmap* screenshotToShow;
        // QPainter to draw on the screenshot
        QPainter* painterScreenshot;
        // List of the new drawings
        QList<ColoredPoly> newDrawings;


    // Constructor
    public :
        EditWindow(Screenshot* screenshot, QListWidget* listWidgetImage = 0, bool* canTakeNewScreenshot = 0);

    // Destructor
    public :
        ~EditWindow();

    // Methods
    public :
        // Update the pixmap of the displayed screenshot with the new drawings
        void updateScreenshotToShow();

        // When we press the right click on the window
        void mousePressEvent(QMouseEvent* event);
        // When we move on the window
        void mouseMoveEvent(QMouseEvent* event);

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

    // Qt signals
    signals :
        // Signal the main window to retake a screenshot
        void retakeSignal();
        // Signal the main window that the edit is over
        void editOver();
        // Signal to save the screenshot
        void saveSignal(QPixmap screenshot);
};



#endif // VIEWERWINDOW_H
