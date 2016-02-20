#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QApplication>
#include <QMainWindow>
#include <QSettings>
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
#include <QTranslator>
#include <QSystemTrayIcon>
#include <QSignalMapper>


// For globals hotkeys on Windows
#include <windows.h>


// The window to change the program settings
#include "include/settingswindow.h"
// The window to crop the screenshot of the entire screen
#include "include/cropwindow.h"
// The window to display an image
#include "include/editwindow.h"



// Main window of the program
class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Variables
    private :
        // Settings
        QSettings* settings;

        // Menu
        QMenu* menuFile;
            QAction* actionQuit;
        QMenu* menuTools;
            QAction* actionSettings;
        QMenu* menuHelp;
            QAction* actionAbout;

        // The main toolbar
        QToolBar* toolBar;
            QAction* actionTakeScreenshot;
            QAction* actionMerge;

            QAction* actionEdit;
            QAction* actionUp;
            QAction* actionDown;
            QAction* actionDelete;

        // The main widget
        QWidget* widgetMain;
            // The main layout
            QGridLayout* layoutMain;
                // List of all the taken screenshots
                QListWidget* listWidgetImage;

        // System tray icon
        QSystemTrayIcon* trayIcon;
            QMenu* menuTrayIcon;
                QAction* actionOpen;

        // Usefull to refuse new screenshot to be taken when one is on his way to be taken / cropped
        bool canTakeNewScreenshot;

    // Constructor
    public :
        MainWindow();

    // Destructor
    public :
        ~MainWindow();

    // Methods
    public :
        // Give the next screenshot name available for the default directory
        QString nextScreenshotName();

        // When 1 state of the window has changed
        void changeEvent(QEvent *event);
        // Use to receive globals hotkeys events from Windows
        bool nativeEvent(const QByteArray &eventType, void *message, long *result);
        // Quit the application when the main window is closed
        void closeEvent(QCloseEvent* event);

    // Qt slots
    public slots :
        // Restore the window if it's minimize
        void restore();
        // Open the settings dialog
        void openSettings();
        // Open the about dialog : the credits of the program
        void openAbout();

        // Wait, shot a screenshot and put it in the list
        void takeScreenshot(bool force = false);
        // Merge the screenshots in the list
        void merge();
            // Save an image
            void save(QPixmap image);
        // Open a window to edit a new screenshot
        void openEditWindowNewScreenshot(Screenshot* screenshot);
        // Open a window to edit the selected image on the list
        void openEditWindowOldScreenshot();
            // Open a window to edit a screenshot
            void openEditWindowOldScreenshot(QListWidgetItem* screenshotClicked);
        // Raise the selected image on the list
        void upImage();
        // Descend the selected image on the list
        void downImage();
        // Delete the selected image in the list
        void deleteImage();

        // Specify the action when the user interact with the tray icon
        void activationTrayIcon(QSystemTrayIcon::ActivationReason reason);
};



#endif // MAINWINDOW_H
