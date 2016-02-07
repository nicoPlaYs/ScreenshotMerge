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
    // Creation of the Qt application
    QApplication app(argc, argv);
    app.setApplicationName("Screenshot Merge");
    app.setWindowIcon(QIcon(":/images/app.ico"));
    app.setQuitOnLastWindowClosed(false);

    // Force the app to use the same language as the system
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    // Creation of the main window of the program
    MainWindow mainWindow;

    // Shows the main window
    mainWindow.show();

    // Execute the Qt application
    return app.exec();
}
