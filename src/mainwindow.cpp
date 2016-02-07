#include "include/mainwindow.h"



// Constructor
MainWindow::MainWindow() : QMainWindow()
{
    // We define the minimum size of the window...
    this->setMinimumSize(300,400);
    // ...and the curent size of the window
    this->resize(300,400);


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

        actionTakeScreenshot = toolBarMain->addAction(QIcon("://images/toolbar/takescreenshot.ico"), tr("Take a screenshot"));
        QObject::connect(actionTakeScreenshot, SIGNAL(triggered()), this, SLOT(takeScreenshot()));

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
}



// Destructor
MainWindow::~MainWindow()
{

}



// Method


// Qt slots

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
    this->hide();

    // Wait 500ms for the window to vanish beforce taking the screenshot
    QTimer::singleShot(500, this, SLOT(shootScreenshot()));
}
// Shoot the screenshot and put it in the list
void MainWindow::shootScreenshot()
{
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


// Quit the application when the main window is closed
void MainWindow::closeEvent(QCloseEvent* event)
{
    // Accept the event
    event->accept();

    // Close the app
    qApp->quit();
}

