// Qt application
#include <QApplication>

// Qt translation & co
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>


// Main window of the program
#include "include/mainwindow.h"



// Main function
int main(int argc, char *argv[])
{
    // Creation and configuration of the Qt application
    QApplication app(argc, argv);
    app.setApplicationName("Screenshot Merge");
    app.setOrganizationName("Nicolas Fostier");
    app.setOrganizationDomain("nicolasfostier.free.fr");
    app.setWindowIcon(QIcon(":/images/app.ico"));
    app.setQuitOnLastWindowClosed(false);

    // Force the app to use the same language as the system
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("screenshotmerge_") + locale, ":/lang");
    app.installTranslator(&translator);

    // Creation of the main window of the program
    MainWindow mainWindow;

    // Display the main window (minimized if the launch argument say so)
    if(QCoreApplication::arguments().count() > 1 &&
            QCoreApplication::arguments().at(1) == "-minimized")
    {
        mainWindow.setWindowState(Qt::WindowMinimized);
    }
    else
    {
        mainWindow.show();
    }

    // Execute the Qt application
    return app.exec();
}
