#include <QApplication>
#include <QTranslator>
#include <QLocale>

// Check if there is an update available on github
#include "include/checkforupdate.h"
// Main window of the program
#include "include/windows/mainwindow.h"



// Main function
int main(int argc, char *argv[])
{
    // Creation and configuration of the Qt application
    QApplication app(argc, argv);
    app.setApplicationName("Screenshot Merge");
    app.setOrganizationName("Nicolas Fostier");
    app.setOrganizationDomain("nicolasfostier.free.fr");
    app.setApplicationVersion("1.7.1");
    app.setWindowIcon(QIcon(":/images/app.ico"));

    // Initialize the random seed
    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());

    // Force the app to use the same language as the system
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("screenshotmerge_") + locale, ":/lang");
    app.installTranslator(&translator);

    // Check if there is an update available on github
    // (It's executed on its own thread)
    QThread* threadCFU = new QThread();
    QObject::connect(threadCFU, SIGNAL(finished()), threadCFU, SLOT(deleteLater()));
    CheckForUpdate* cfu = new CheckForUpdate(app.applicationVersion());
    cfu->moveToThread(threadCFU);
    QObject::connect(threadCFU, SIGNAL(started()), cfu, SLOT(askGithub()));
    threadCFU->start();

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

    // Execute the Qt application : enter the event loop
    return app.exec();
}
