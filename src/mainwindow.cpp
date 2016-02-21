#include "include/mainwindow.h"



// Constructor
MainWindow::MainWindow() : QMainWindow()
{
    /* At the begin of the program, there is no screenshot on his way
     * so we can take one */
    canTakeNewScreenshot = true;
    // Initialization of the settings variable
    settings = new QSettings();
    // We define the minimum size of the window...
    this->setMinimumSize(300,300);
    // ... and we restore the size of the window from the previous session
    this->restoreGeometry(settings->value("MainWindow/geometry").toByteArray());


    // File menu
    menuFile = menuBar()->addMenu(tr("File"));
        actionQuit = menuFile->addAction(QIcon("://images/menu/quit.ico"), tr("Quit"));
        QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Options menu
    menuTools = menuBar()->addMenu(tr("Tools"));
        actionSettings = menuTools->addAction(QIcon("://images/menu/settings.ico"), tr("Settings"));
        QObject::connect(actionSettings, SIGNAL(triggered()), this, SLOT(openSettings()));

    // Help menu
    menuHelp = menuBar()->addMenu("?");
        actionAbout = menuHelp->addAction(QIcon("://images/menu/about.ico"), tr("About"));
        QObject::connect(actionAbout, SIGNAL(triggered()), this, SLOT(openAbout()));


    // Toolbar
    toolBar = new QToolBar(this);
    toolBar->setMovable(false);
    toolBar->setContextMenuPolicy(Qt::PreventContextMenu);

        actionTakeScreenshot = toolBar->addAction(QIcon("://images/toolbar/takescreenshot.ico"), tr("Take a screenshot (Print Screen)"));
        QObject::connect(actionTakeScreenshot, SIGNAL(triggered()), this, SLOT(takeScreenshot()));
        RegisterHotKey((HWND) this->winId(), 1, 0x4000, VK_SNAPSHOT);

        actionMerge = toolBar->addAction(QIcon("://images/toolbar/merge.ico"), tr("Merge (Ctrl+S)"));
        QObject::connect(actionMerge, SIGNAL(triggered()), this, SLOT(merge()));

    toolBar->addSeparator();

        actionEdit = toolBar->addAction(QIcon("://images/toolbar/edit.ico"), tr("Edit (Enter)"));
        actionEdit->setShortcut(QKeySequence(Qt::Key_Return));
        QObject::connect(actionEdit, SIGNAL(triggered()), this, SLOT(openEditWindowOldScreenshot()));

        actionUp = toolBar->addAction(QIcon("://images/toolbar/up.ico"), tr("Rise (Ctrl+Up)"));
        actionUp->setShortcut(QKeySequence("Ctrl+Up"));
        QObject::connect(actionUp, SIGNAL(triggered()), this, SLOT(upImage()));

        actionDown = toolBar->addAction(QIcon("://images/toolbar/down.ico"), tr("Descend (Ctrl+Down)"));
        actionDown->setShortcut(QKeySequence("Ctrl+Down"));

        QObject::connect(actionDown, SIGNAL(triggered()), this, SLOT(downImage()));

        actionDelete = toolBar->addAction(QIcon("://images/toolbar/delete.ico"), tr("Delete (Delete)"));
        actionDelete->setShortcut(QKeySequence::Delete);
        QObject::connect(actionDelete, SIGNAL(triggered()), this, SLOT(deleteImage()));

    this->addToolBar(toolBar);


    // Main Widget
    widgetMain = new QWidget(this);
    this->setCentralWidget(widgetMain);

        // Main layout
        layoutMain = new QGridLayout(widgetMain);

            // List of the images / screenshots
            listWidgetImage = new QListWidget(widgetMain);
            listWidgetImage->setSelectionMode(QAbstractItemView::SingleSelection);
            QObject::connect(listWidgetImage, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openEditWindowOldScreenshot(QListWidgetItem*)));

        layoutMain->addWidget(listWidgetImage, 0, 0, 1, 1, 0);


    // System tray icon
    this->trayIcon = new QSystemTrayIcon(QIcon(":/images/app.ico"), this);
        menuTrayIcon = new QMenu(this);
            actionOpen = menuTrayIcon->addAction(QIcon("://images/menu/restore.ico"), tr("Restore"));
            QObject::connect(actionOpen, SIGNAL(triggered()), this, SLOT(restore()));
        menuTrayIcon->addAction(actionSettings);
        menuTrayIcon->addAction(actionQuit);
    trayIcon->setToolTip("Screenshot Merge");
    trayIcon->setContextMenu(menuTrayIcon);
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(activationTrayIcon(QSystemTrayIcon::ActivationReason)));
}



// Destructor
MainWindow::~MainWindow()
{

}



// Methods


// Give the next screenshot name available for the default directory
QString MainWindow::nextScreenshotName()
{
    QString path = this->settings->value("SettingsWindow/defaultDirectory", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)).toString();

    // We check every number of screenshot on the directory to find the next screenshot name available
    QFile nextScreenshotJPG(path + "\\Screenshot00001.jpg");
    QFile nextScreenshotPNG(path + "\\Screenshot00001.png");
    for(int i = 2; i < 99999 && (nextScreenshotJPG.exists() || nextScreenshotPNG.exists()); i++)
    {
        nextScreenshotJPG.setFileName(path + QString("\\Screenshot") + QString::number(i).rightJustified(5, '0', false) + ".jpg");
        nextScreenshotPNG.setFileName(path + QString("\\Screenshot") + QString::number(i).rightJustified(5, '0', false) + ".png");
    }

    return nextScreenshotJPG.fileName();
}


// When 1 state of the window has changed
void MainWindow::changeEvent(QEvent *event)
{
    // We verify the type of event
    if(event->type() == QEvent::WindowStateChange)
    {
        // We hide the window and show the tray icon if the "Minimize to tray" setting is activate
        if(this->settings->value("SettingsWindow/minimizeTray", false).toBool() &&
                (this->windowState().testFlag(Qt::WindowMinimized) == true))
        {
            this->hide();
            this->trayIcon->show();
        }
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
        // ... and if it's the hotkey to take a screenshot
        if(msg.wParam == 1)
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

    // We save all the settings and data usefull for a next session
    settings->setValue("MainWindow/geometry", this->saveGeometry());

    // Close the app
    qApp->quit();
}



// Qt slots


// Open the window if it's minimize
void MainWindow::restore()
{
    this->showNormal();
    this->activateWindow();
    this->trayIcon->hide();
}

// Open the settings dialog
void MainWindow::openSettings()
{
    (new SettingsWindow());
}

// Open the about dialog : the credits of the program
void MainWindow::openAbout()
{
    QMessageBox::about(this, tr("About"),   "<h2><b>Screenshot Merge</b></h2>"
                                            "<p><b>" + tr("Version :") + "</b>" + " 1.2 (<a href='https://github.com/nicolasfostier/ScreenshotMerge/releases'>" + tr("Latest releases") + "</a>)<br/>"
                                            "<b>" + tr("Developped by :") + "</b> <a href='https://github.com/nicolasfostier'>Nicolas Fostier</a><br/>"
                                            "<b>" + tr("Library used :") + "</b> Qt 5.5.1<br/>"
                                            "<b>" + tr("Logo :") + "</b> <a href='https://github.com/nicolasfostier'>Nicolas Fostier</a><br/>"
                                            "<b>" + tr("Icon :") + "</b> <a href='http://www.customicondesign.com/'>Custom Icon Design</a></p>");
}


// Wait, shot a screenshot and put it in the list
void MainWindow::takeScreenshot()
{
    // We verify if we can take a new screenshot (if there is no other screenshot on his way to be taken / cropped)
    if(canTakeNewScreenshot == true)
    {
        // So now that we will take one, we need to wait the end of the process before take an other one
        canTakeNewScreenshot = false;

        // Lower the main window, so it can't be see in the screenshot
        this->lower();

        // Get the pixmap of the primary screen
        QScreen *screen = QGuiApplication::primaryScreen();
        QPixmap pixmapFullscreen = screen->grabWindow(0);

        // Create and show the window with the crop tool
        CropWindow* crop = new CropWindow(pixmapFullscreen);
        crop->showFullScreen();

        // When the crop windows is closing, we open the edit windows
        QObject::connect(crop, SIGNAL(cropOver(Screenshot*)), this, SLOT(openEditWindowNewScreenshot(Screenshot*)));
    }
}

// Merge the screenshots in the list
void MainWindow::merge()
{
    // We verify that there is at least 1 screenshot on the list
    if(listWidgetImage->count() != 0)
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
            currentPixmap = ((Screenshot*)listWidgetImage->item(i))->withDrawing();

            painterMergedScreenshots->drawPixmap(0, currentY, currentPixmap);

            currentY += ((Screenshot*)listWidgetImage->item(i))->getImage().height();
        }

        // And we save it
        save(*mergedScreenshots);
    }
}
// Save an image
void MainWindow::save(QPixmap image)
{
    // We check if the user want to use the default directory or if he want the program to ask him
    QString path;
    if(!this->settings->value("SettingsWindow/alwaysUseDefaultDirectory", false).toBool())
    {
        // Open the dialog for the user to indicate where he want his merged screenhosts to be saved
        path = QFileDialog::getSaveFileName(this, tr("Save as..."), nextScreenshotName(), "JPG (*.jpg);;PNG (*.png)");
    }
    else
    {
        path = nextScreenshotName();
    }

    // We verify that the user has really selected a path
    if(path != 0)
    {
        // Save the merged screenshots
        image.save(path, 0, settings->value("SettingsWindow/imageQuality", 85).toInt());
        if(settings->value("SettingsWindow/alwaysUseDefaultDirectory", false).toBool())
        {
            QMessageBox::information(this, tr("Image successfully saved"), tr("Your image has been saved in your default directory !"));
        }
    }
}

// Open a window to edit a new screenshot
void MainWindow::openEditWindowNewScreenshot(Screenshot* screenshot)
{
    // Create a window to edit the screenshot
    EditWindow* editWindow = new EditWindow(screenshot, listWidgetImage, &canTakeNewScreenshot);
    QObject::connect(editWindow, SIGNAL(editOver()), this, SLOT(restore()));
    QObject::connect(editWindow, SIGNAL(retakeSignal()), this, SLOT(takeScreenshot()));
    QObject::connect(editWindow, SIGNAL(saveSignal(QPixmap)), this, SLOT(save(QPixmap)));

    // And open it
    editWindow->show();
}

// Open a window to edit the selected screenshot on the list
void MainWindow::openEditWindowOldScreenshot()
{
    // Get the selected screenshot
    QList<QListWidgetItem*> selectedItems = listWidgetImage->selectedItems();
    // Verify that there is a selected screenshot
    if(!selectedItems.empty())
    {
        // Create a window to edit the screenshot and open it
        this->openEditWindowOldScreenshot(selectedItems.first());
    }
}
// Open a window to edit a screenshot on the list
void MainWindow::openEditWindowOldScreenshot(QListWidgetItem* screenshotClicked)
{
    // Create a window to edit the screenshot
    EditWindow* editWindow = new EditWindow((Screenshot*)screenshotClicked);
    QObject::connect(editWindow, SIGNAL(saveSignal(QPixmap)), this, SLOT(save(QPixmap)));

    // And open it
    editWindow->show();
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
    // If the user double-click on the icon on the tray, we restore the main window
    if(reason == QSystemTrayIcon::DoubleClick)
    {
        this->restore();
    }
}
