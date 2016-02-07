#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QGridLayout>
#include <QToolBar>
#include <QListWidget>
#include <QTimer>
#include <QScreen>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QFileDialog>
#include <QString>
#include <QStandardPaths>


#include "include/cropwindow.h"
#include "include/viewerwindow.h"



// Main window of the program
class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Variables
    private :
        // Menu
        QMenu* menuFile;
            QAction* actionQuit;
        QMenu* menuHelp;
            QAction* actionAbout;

        // Body of the window
        QWidget* widgetMain;
            QGridLayout* layoutMain;
                QToolBar* toolBarMain;
                    QAction* actionTakeScreenshot;
                    QAction* actionMerge;
                    QAction* actionView;
                    QAction* actionUp;
                    QAction* actionDown;
                    QAction* actionDelete;
                QListWidget* listWidgetImage;


    // Constructor
    public :
        MainWindow();

    // Destructor
    public :
        ~MainWindow();

    // Methods
    public:


    // Qt slots
    public slots :
        // About dialog
        void about();

        // Wait, shot a screenshot and put it in the list
        void takeScreenshot();
            // Shoot the screenshot and put it in the list
            void shootScreenshot();
        // Merge the images in the list
        void merge();
        // Open a window to visualize the selected image on the list
        void openViewerWindow();
        // Raise an image on the list
        void upImage();
        // Descend an image on the list
        void downImage();
        // Delete the selected image in the list
        void deleteImage();

        // Open a window to visualize the double-clicked image on the list
        void openViewerWindow(QListWidgetItem* imageClicked);

        // Quit the application when the main window is closed
        void closeEvent(QCloseEvent* event);
};



#endif // MAINWINDOW_H
