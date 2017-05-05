#include "include/windows/mainwindow.h"


// Constructor
MainWindow::MainWindow() : QMainWindow()
{
    // Initialization of the settings variable
    settings = new QSettings();

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
        #ifdef Q_OS_WIN
            RegisterHotKey((HWND) this->winId(), 27156547, 0, VK_SNAPSHOT);
        #endif

    toolBar->addSeparator();

        actionSaveMerged = toolBar->addAction(QIcon("://images/toolbar/save.ico"), tr("Merge and save it (Ctrl+S)"));
        actionSaveMerged->setShortcut(QKeySequence::Save);
        QObject::connect(actionSaveMerged, SIGNAL(triggered()), this, SLOT(saveMergedScreenshots()));

        actionCopyIntoClipboard = toolBar->addAction(QIcon("://images/editwindow/copytoclipboard.ico"), tr("Copy to clipboard (Ctrl+C)"));
        actionCopyIntoClipboard->setShortcut(QKeySequence::Copy);
        QObject::connect(actionCopyIntoClipboard, SIGNAL(triggered()), this, SLOT(copyIntoClipboardMergedScreenshots()));

        actionUploadMergedScreenshots = toolBar->addAction(QIcon("://images/toolbar/upload.ico"), tr("Merge and upload it (Ctrl+U)"));
        actionUploadMergedScreenshots->setShortcut(QKeySequence("Ctrl+U"));
        QObject::connect(actionUploadMergedScreenshots, SIGNAL(triggered()), this, SLOT(uploadMergedScreenshots()));

        comboBoxImageHost = new QComboBox(this);
        comboBoxImageHost->addItem(QIcon("://images/toolbar/imgur.ico"), "imgur", QVariant(imgur));
        comboBoxImageHost->addItem(QIcon("://images/toolbar/noelshack.ico"), "NoelShack", QVariant(noelshack));
        comboBoxImageHost->setCurrentText(settings->value("imageHost", "imgur").toString());
        toolBar->addWidget(comboBoxImageHost);

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

        actionClearList = toolBar->addAction(QIcon("://images/toolbar/clearlist.ico"), tr("Clear the list"));

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
            QObject::connect(actionClearList, SIGNAL(triggered()), listWidgetImage, SLOT(clear()));

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

    // Define the minimum size of the window
    this->setMinimumSize(this->sizeHint());

    // Restore the size of the window from the previous session
    this->restoreGeometry(settings->value("MainWindow/geometry").toByteArray());
}



// Destructor
MainWindow::~MainWindow()
{

}



// Methods


// Merge the screenshots in the list and return the result
QPixmap* MainWindow::merge()
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
            currentPixmap = static_cast<Screenshot*>(listWidgetImage->item(i))->getImage();

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
            currentPixmap = static_cast<Screenshot*>(listWidgetImage->item(i))->withDrawings();

            painterMergedScreenshots->drawPixmap(0, currentY, currentPixmap);

            currentY += currentPixmap.height();
        }

        // We don't need the painter anymore
        delete painterMergedScreenshots;

        // Return the result
        return mergedScreenshots;
    }

    return 0;
}


// Use to receive globals hotkeys events
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    // Windows
    #ifdef Q_OS_WIN

        // If the mesage is about a Windows hotkey...
        MSG msg = *static_cast<MSG*>(message);
        if(msg.message == WM_HOTKEY)
        {
            // ... and if it's the hotkey to take a screenshot
            if(msg.wParam == 27156547)
            {
                // We verify if we can take a new screenshot (if there is no other screenshot on his way to be taken / cropped)
                if(QApplication::activeModalWidget() == 0)
                {
                    this->takeScreenshot();
                }
                else
                {
                    QApplication::activeModalWidget()->activateWindow();
                }

                return true;
            }
        }

    #endif

    // macOS
    #ifdef Q_OS_MACOS

    #endif

    // Linux
    #ifdef Q_OS_LINUX

    #endif

    return false;
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

// Quit the application when the main window is closed
void MainWindow::closeEvent(QCloseEvent* event)
{
    // Accept the event
    event->accept();

    // We save all the settings and data usefull for a next session
    settings->setValue("MainWindow/geometry", this->saveGeometry());
    settings->setValue("imageHost", this->comboBoxImageHost->currentText());

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
    new SettingsWindow();
}

// Open the about dialog : the credits of the program
void MainWindow::openAbout()
{
    QMessageBox::about(this, tr("About"),   "<h2><b>Screenshot Merge</b></h2>"
                                            "<p><b>" + tr("Version :") + "</b> " + qApp->applicationVersion() + " (<a href='https://github.com/nicolasfostier/ScreenshotMerge/releases'>" + tr("Latest releases") + "</a>)<br/>" +
                                            "<b>" + tr("Developped by :") + "</b> <a href='https://github.com/nicolasfostier'>Nicolas Fostier</a><br/>" +
                                            "<b>" + tr("Library used :") + "</b> Qt 5.7.1<br/>" +
                                            "<b>" + tr("Logo :") + "</b> <a href='https://github.com/nicolasfostier'>Nicolas Fostier</a><br/>" +
                                            "<b>" + tr("Icon :") + "</b> <a href='http://www.customicondesign.com/'>Custom Icon Design</a></p>");
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


// Shot a screenshot and open a window to edit it
void MainWindow::takeScreenshot()
{
    // Lower the main window, so it can't be see in the screenshot
    this->lower();

    // Get the size of the entire screen(s)
    int screens = QApplication::desktop()->screenCount();
    QRect screensRect;
    QRect currentScreenRect;
    for(int i = 0; i < screens; ++i ){
         currentScreenRect = QApplication::desktop()->screen(i)->geometry();
         screensRect = screensRect.united(currentScreenRect);
    }

    // Get the screenshot of the entire screen(s)
    QScreen* screen = QApplication::primaryScreen();
    QPixmap pixmapFullscreen = screen->grabWindow(QApplication::desktop()->winId(),
                                                   screensRect.x(),
                                                   screensRect.y(),
                                                   screensRect.width(),
                                                   screensRect.height());

    // Create and show the window with the crop tool
    CropWindow* crop = new CropWindow(pixmapFullscreen, screensRect);

    // When the crop windows is closing, we open the edit windows
    QObject::connect(crop, SIGNAL(cropOver(Screenshot*)), this, SLOT(openEditWindowNewScreenshot(Screenshot*)));
}

// Open a window to edit a new screenshot
void MainWindow::openEditWindowNewScreenshot(Screenshot* screenshot)
{
    // Create a window to edit the screenshot
    EditWindow* editWindow = new EditWindow(screenshot, comboBoxImageHost->currentData().value<ImageHost>(), listWidgetImage);
    if(this->isVisible())
    {
        QObject::connect(editWindow, SIGNAL(editOver(QString)), this, SLOT(restore()));
    }
    QObject::connect(editWindow, SIGNAL(retakeSignal()), this, SLOT(takeScreenshot()));
    QObject::connect(editWindow, SIGNAL(editOver(QString)), comboBoxImageHost, SLOT(setCurrentText(QString)));
}

// Merge the screenshots in the list and save the result
void MainWindow::saveMergedScreenshots()
{
    // Merge the screenshots in the list...
    QPixmap* mergedScreenshots = this->merge();

    // Verify if there is a result
    if(mergedScreenshots != 0)
    {
        //... and save the result
        saveImage(*mergedScreenshots);

        // We don't need the result of the merged screenshot anymore
        delete mergedScreenshots;
    }
}

// Merge the screenshots in the list and copy the result into the clipboard
void MainWindow::copyIntoClipboardMergedScreenshots()
{
    // Merge the screenshots in the list
    QPixmap* mergedScreenshots = this->merge();

    // Verify if there is a result
    if(mergedScreenshots != 0)
    {
        // We get access to the clipboard
        QClipboard* clipboard = QApplication::clipboard();
        // Put the pixmap of the merged screenshots into it
        clipboard->setPixmap(*mergedScreenshots);

        // Display a dialog to inform that it's done
        QMessageBox::information(this, tr("Clipboard"), tr("Your screenshot has been successfuly put in your clipboard !"));

        // We don't need the result of the merged screenshot anymore
        delete mergedScreenshots;
    }
}

// Merge the screenshots in the list and upload the result to noelshack
void MainWindow::uploadMergedScreenshots()
{
    // Merge the screenshots in the list...
    QPixmap* mergedScreenshots = this->merge();

    // Verify if there is a result
    if(mergedScreenshots != 0)
    {
        // ... and upload the result
        uploadImage(*mergedScreenshots, comboBoxImageHost->currentData().value<ImageHost>(), settings->value("SettingsWindow/imageQuality", 85).toInt());

        // We don't need the result of the merged screenshot anymore
        delete mergedScreenshots;
    }
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
    EditWindow* editWindow = new EditWindow((Screenshot*)screenshotClicked, comboBoxImageHost->currentData().value<ImageHost>());
    QObject::connect(editWindow, SIGNAL(editOver(QString)), this, SLOT(restore()));
    QObject::connect(editWindow, SIGNAL(editOver(QString)), comboBoxImageHost, SLOT(setCurrentText(QString)));
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
        delete listWidgetImage->takeItem(listWidgetImage->row(selectedScreenshot.first()));
    }
}
