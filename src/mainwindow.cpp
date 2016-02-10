#include "include/mainwindow.h"



// Constructor
MainWindow::MainWindow() : QMainWindow()
{
    setting = new QSettings();

    // We define the minimum size of the window...
    this->setMinimumSize(300,400);
    // ... and we restore the size of the window from a previous session
    this->restoreGeometry(setting->value("MainWindow/geometry").toByteArray());

    // File menu
    menuFile = menuBar()->addMenu(tr("File"));
        actionQuit = menuFile->addAction(QIcon("://images/menu/quit.ico"), tr("Quit"));
        QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Help menu
    menuHelp = menuBar()->addMenu("?");
        actionAbout = menuHelp->addAction(QIcon("://images/menu/about.ico"), tr("About"));
        QObject::connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));


    // Toolbar
    toolBarMain = new QToolBar(this);
    toolBarMain->setMovable(false);
    toolBarMain->setContextMenuPolicy(Qt::PreventContextMenu);

        actionTakeScreenshot = toolBarMain->addAction(QIcon("://images/toolbar/takescreenshot.ico"), tr("Take a screenshot"));
        QObject::connect(actionTakeScreenshot, SIGNAL(triggered()), this, SLOT(takeScreenshot()));
        RegisterHotKey((HWND) this->winId(), 1, 0x4000, VK_SNAPSHOT);

        actionMerge = toolBarMain->addAction(QIcon("://images/toolbar/merge.ico"), tr("Merge"));
        QObject::connect(actionMerge, SIGNAL(triggered()), this, SLOT(merge()));

    toolBarMain->addSeparator();

        actionView = toolBarMain->addAction(QIcon("://images/toolbar/view.ico"), tr("View"));
        QObject::connect(actionView, SIGNAL(triggered()), this, SLOT(openViewerWindow()));

        actionUp = toolBarMain->addAction(QIcon("://images/toolbar/up.ico"), tr("Rise"));
        QObject::connect(actionUp, SIGNAL(triggered()), this, SLOT(upImage()));

        actionDown = toolBarMain->addAction(QIcon("://images/toolbar/down.ico"), tr("Descend"));
        QObject::connect(actionDown, SIGNAL(triggered()), this, SLOT(downImage()));

        actionDelete = toolBarMain->addAction(QIcon("://images/toolbar/delete.ico"), tr("Delete"));
        QObject::connect(actionDelete, SIGNAL(triggered()), this, SLOT(deleteImage()));

    this->addToolBar(toolBarMain);


    // Main Widget
    widgetMain = new QWidget(this);
    this->setCentralWidget(widgetMain);

        // Main layout
        layoutMain = new QGridLayout(widgetMain);

            // List of the images / screenshots
            listWidgetImage = new QListWidget(widgetMain);
            listWidgetImage->setSelectionMode(QAbstractItemView::SingleSelection);
            QObject::connect(listWidgetImage, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openViewerWindow(QListWidgetItem*)));

        layoutMain->addWidget(listWidgetImage, 0, 0, 1, 1, 0);


    // System tray icon
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(QIcon(":/images/app.ico"), this);
        menuTrayIcon = new QMenu(this);
            actionOpen = menuTrayIcon->addAction(tr("Open"));
            QObject::connect(actionOpen, SIGNAL(triggered()), this, SLOT(open()));
        menuTrayIcon->addAction(actionQuit);
    trayIcon->setToolTip("Screenshot Merge");
    trayIcon->setContextMenu(menuTrayIcon);
    trayIcon->show();
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(activationTrayIcon(QSystemTrayIcon::ActivationReason)));
}



// Destructor
MainWindow::~MainWindow()
{

}



// Method


// Qt slots

// Open the window if it's minimize
void MainWindow::open()
{
    this->showNormal();
    this->activateWindow();
}

// Open the about dialog : the credits of the program
void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("<h2><b>Screenshot Merge</b></h2>"
                                         "<p><b>Version :</b>")

                                         + " 1.0<br/>" +

                                         tr("<b>Developped by :</b> <a href='http://nicoplays.error404.fr/'>Nicolas Fostier</a><br/>"
                                         "<b>Library used :</b> Qt 5.5.1<br/>"
                                         "<b>Logo :</b> <a href='http://nicoplays.error404.fr/'>Nicolas Fostier</a><br/>"
                                         "<b>Icon :</b> <a href='http://www.customicondesign.com/'>Custom Icon Design</a></p>"));
}


// Wait, shot a screenshot and put it in the list
void MainWindow::takeScreenshot()
{
    // Hide the main window, so it can't be see in the screenshot
    this->lower();

    // Get the pixmap of the primary screen
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmapFullscreen = screen->grabWindow(0);

    // Create and show the window with the crop tool
    CropWindow* cropWindow = new CropWindow(pixmapFullscreen, listWidgetImage);
    cropWindow->showFullScreen();
    QObject::connect(cropWindow, SIGNAL(destroyed()), this, SLOT(show()));
}

// Merge the images in the list
void MainWindow::merge()
{
    // Calculate the height and width of the merged screenshots
    int height = 0;
    int width = 0;
    QPixmap currentPixmap;
    // Loop to get the height and width to all the listed screenshots
    for(int i = 0; i < listWidgetImage->count(); i++)
    {
        currentPixmap = ((Screenshot*)listWidgetImage->item(i))->getImage();

        height += currentPixmap.height();
        if(width < currentPixmap.width())
        {
            width = currentPixmap.width();
        }
    }

    // Creation of the pixmap for the merged screenshots
    QPixmap* mergedScreenshots = new QPixmap(width, height);
    mergedScreenshots->fill(Qt::white);

    // And we need a QPainter to modify it
    QPainter *painterMergedScreenshots = new QPainter(mergedScreenshots);

    // Draw one per one the screenshots of the list into the pixmap created above
    int currentY = 0;
    for(int i = 0; i < listWidgetImage->count(); i++)
    {
        currentPixmap = ((Screenshot*)listWidgetImage->item(i))->getImage();

        painterMergedScreenshots->drawPixmap(0, currentY, currentPixmap);

        currentY += ((Screenshot*)listWidgetImage->item(i))->getImage().height();
    }

    // Open the dialog for the user to indicate where he want his merged screenhosts to be saved
    QString path = QFileDialog::getSaveFileName(this, tr("Save as..."), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "JPG (*.jpg);;PNG (*.png)");

    // Save the merged screenshots
    mergedScreenshots->save(path, 0, 85);
}

// Open a window to visualize the selected image on the list
void MainWindow::openViewerWindow()
{
    // Get the selected screenshot
    QList<QListWidgetItem*> selectedItems = listWidgetImage->selectedItems();
    // Verify that there is a selected screenshot
    if(!selectedItems.empty())
    {
        // Create a window to view the image and open it
        this->openViewerWindow(selectedItems.first());
    }
}
// Open a window to visualize an image on the list
void MainWindow::openViewerWindow(QListWidgetItem* imageClicked)
{
    // Create a window to view the image and open it
    (new viewerWindow(((Screenshot*)imageClicked)->getImage()))->show();
}

// Raise the selected image on the list
void MainWindow::upImage()
{
    // Get the selected screenshot
    QList<QListWidgetItem*> selectedItems = listWidgetImage->selectedItems();
    // Verify that there is a selected screenshot
    if(!selectedItems.empty())
    {
        // Remember the row before the change
        int previousRow = listWidgetImage->row(selectedItems.first());

        // Verify that the screenshot isn't at the top of the list
        if(previousRow != 0)
        {
            // Take the screenshot from the list and insert it 1 place lower
            listWidgetImage->takeItem(previousRow);
            listWidgetImage->insertItem(previousRow-1, selectedItems.first());

            // Update the selected row to the new position of the screenshot
            listWidgetImage->setCurrentRow(previousRow-1);
        }
    }
}

// Descend the selected image on the list
void MainWindow::downImage()
{
    // Get the selected screenshot
    QList<QListWidgetItem*> selectedItems = listWidgetImage->selectedItems();
    // Verify that there is a selected screenshot
    if(!selectedItems.empty())
    {
        // Remember the row before the change
        int previousRow = listWidgetImage->row(selectedItems.first());

        // Verify that the screenshot isn't at the bottom of the list
        if(previousRow < listWidgetImage->count() - 1)
        {
            // Take the screenshot from the list and insert it 1 place higher
            listWidgetImage->takeItem(previousRow);
            listWidgetImage->insertItem(previousRow+1, selectedItems.first());

            // Update the selected row to the new position of the screenshot
            listWidgetImage->setCurrentRow(previousRow+1);
        }
    }
}

// Delete the selected image in the list
void MainWindow::deleteImage()
{
    // Get the selected screenshot
    QList<QListWidgetItem*> selectedScreenshot = listWidgetImage->selectedItems();
    // Verify that there is a selected screenshot
    if(!selectedScreenshot.empty())
    {
        // If so, take the screenshot from the list and delete it
        listWidgetImage->takeItem(listWidgetImage->row(selectedScreenshot.first()));
        delete selectedScreenshot.first();
    }
}

// Specify the action when the user interact with the tray icon
void MainWindow::activationTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick)
    {
        this->open();
    }
}

// Use to receive globals hotkeys events from Windows
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    // If the mesage is about a Windows hotkey...
    MSG msg = *((MSG*)message);
    if(msg.message == WM_HOTKEY)
    {
        /* ... and if it's the hotkey to take a screenshot
         * and if there isn't an other screnshot on the go... */
        if(msg.wParam == 1 && this->isVisible())
        {
            this->takeScreenshot();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Quit the application when the main window is closed
void MainWindow::closeEvent(QCloseEvent* event)
{
    // Accept the event
    event->accept();

    // We save all the settings
    setting->setValue("MainWindow/geometry", this->saveGeometry());

    // Close the app
    qApp->quit();
}
