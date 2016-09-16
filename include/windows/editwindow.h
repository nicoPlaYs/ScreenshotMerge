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
#include <QScrollArea>
#include <QScrollBar>
#include <QDesktopWidget>
#include <QSpinBox>


// Store a screenshot which can be put in a QListWidget
#include "include/screenshot.h"

#include <QDebug>



// The window to display and edit an screenshot
class EditWindow : public QMainWindow
{
    Q_OBJECT

    // Variables
    private :
        // Settings
        QSettings* settings;

        // Pen of the draw tool
        QPen drawPen;
        //
        QPen eraseTempPen;

        // Last point of the current polyline
        QPoint lastPointPolyline;

        // The toolbar
        QToolBar* toolBar;
            QAction* actionValidate;
            QAction* actionCancel;
            QAction* actionRetake;

            QAction* actionSave;
            QAction* actionCopyIntoClipboard;
            QAction* actionUpload;

            QAction* actionColor;
            QActionGroup* actionGroupDrawTool;
                QAction* actionFreeLine;
                QAction* actionLine;
                QAction* actionFrame;
                QAction* actionEraser;
            QSlider* sliderPenWidth;
                QSpinBox* spinBoxPenWidth;

        // Main widget of the window
        QWidget* widgetMain;
            // Main layout of the dialog
            QHBoxLayout* layout;
                // If the screenshot is to big
                QScrollArea* scrollArea;
                    // The label of the image we want to see
                    QLabel* labelImage;

        // Screenshot
        Screenshot* screenshot;
        // List of all the taken screenshots
        QListWidget* listWidgetImage;
        // QPixmap to show
        QPixmap* screenshotToShow;
        // QPainter to draw on the screenshot
        QPainter* painterScreenshot;
        // List of the new drawings
        QLinkedList<Drawing*> newDrawingsList;

    // Constructor
    public :
        EditWindow(Screenshot* screenshot, QListWidget* listWidgetImage = 0);

    // Destructor
    public :
        ~EditWindow();

    // Methods
    public :
        // Refresh the pixmap of the displayed screenshot by redraw everything
        void refreshScreenshotToShow();

        // When we press the right click on the window
        void mousePressEvent(QMouseEvent* event);
        // When we move on the window
        void mouseMoveEvent(QMouseEvent* event);
        // When we release the click on the window
        void mouseReleaseEvent(QMouseEvent* event);

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
        void copyIntoClipboard();
        // Upload the screenshot to NoelShack
        void upload();

        // Change the width of the draw tool
        void changePenWidth(int width);
        // Change the color of the draw tool
        void changePenColor();

    // Qt signals
    signals :
        // Signal the main window to retake a screenshot
        void retakeSignal();
        // Signal the main window that the edit is over and validated
        void editOverValidated();
        // Signal the main window that the edit is over and canceled
        void editOverCanceled();
        // Signal to save the screenshot
        void saveSignal(QPixmap screenshot);
        // Signal to upload the screenshot on NoelShack
        void uploadSignal(QPixmap screenshot);
};



#endif // VIEWERWINDOW_H
