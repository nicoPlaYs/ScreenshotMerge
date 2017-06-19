#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QApplication>
#include <QMainWindow>
#include <QSettings>
#include <QMenuBar>
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
#include <QStandardPaths>
#include <QTranslator>
#include <QSystemTrayIcon>
#include <QClipboard>
#include <QComboBox>
#include <QVariant>

// Specfic include for Windows
#ifdef Q_OS_WIN
    // For globals hotkeys on Windows
    #include <windows.h>
#endif

// Specific include for macOS
#ifdef Q_OS_MACOS

#endif

// Specific include for Linux
#ifdef Q_OS_LINUX

#endif



// The window to change the program settings
#include "include/windows/settingswindow.h"
// The window to crop the screenshot of the entire screen
#include "include/windows/cropwindow.h"
// The window to display an image
#include "include/windows/editwindow.h"
// Window which appears when uploading an image to an image host website
#include "include/windows/uploadwindow.h"
// Upload function in order to send the screenshots to an image host
#include "include/upload.h"
// Save function
#include "include/save.h"



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

            QAction* actionSaveMerged;
            QAction* actionCopyIntoClipboard;
            QComboBox* comboBoxImageHost;
            QAction* actionUploadMergedScreenshots;

            QAction* actionEdit;
            QAction* actionUp;
            QAction* actionDown;
            QAction* actionDelete;
            QAction* actionClearList;

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

    // Constructor
    public :
        MainWindow();

    // Destructor
    public :
        ~MainWindow();

    // Methods
    public :
        // Merge the screenshots in the list and return the result
        QPixmap* merge();

        // Use to receive globals hotkeys events from Windows
        bool nativeEvent(const QByteArray &eventType, void *message, long *result);
        // When 1 state of the window has changed
        void changeEvent(QEvent *event);
        // Called when the main window is closed
        void closeEvent(QCloseEvent* event);

    // Qt slots
    public slots :
        //
        void showNewUpdateAvailable(QJsonDocument jsonReply);

        // Restore the window if it's minimize
        void restore();
        // Open the settings dialog
        void openSettings();
        // Open the about dialog : the credits of the program
        void openAbout();

        // Specify the action when the user interact with the tray icon
        void activationTrayIcon(QSystemTrayIcon::ActivationReason reason);

        // Shot a screenshot and open a window to edit it
        void takeScreenshot();
            // Open a window to edit a new screenshot
            void openEditWindowNewScreenshot(Screenshot* screenshot);
        // Merge the screenshots in the list and save the result
        void saveMergedScreenshots();
        // Merge the screenshots in the list and copy the result into the clipboard
        void copyIntoClipboardMergedScreenshots();
        // Merge the screenshots in the list and upload the result to an image host
        void uploadMergedScreenshots();
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
};



#endif // MAINWINDOW_H
