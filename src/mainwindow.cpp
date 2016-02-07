#include "include/mainwindow.h"



// Constructor
MainWindow::MainWindow() : QMainWindow()
{
    // We define the minimum size of the window...
    this->setMinimumSize(400,400);
    // ...and the curent size of the window
    this->resize(400,400);

    // File menu
    menuFile = menuBar()->addMenu("Fichier");
        actionQuit = menuFile->addAction(QIcon("://images/menu/quit.ico"), "Quitter");
        QObject::connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Help menu
    menuHelp = menuBar()->addMenu("?");
        actionAbout = menuHelp->addAction(QIcon("://images/menu/about.ico"), "À propos");
        QObject::connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    // Main Widget
    widgetMain = new QWidget(this);
    this->setCentralWidget(widgetMain);

        // Main layout
        layoutMain = new QGridLayout(widgetMain);

            // Toolbar
            toolBarMain = new QToolBar(widgetMain);

                actionTakeScreenshot = toolBarMain->addAction(QIcon("://images/toolbar/takescreenshot.ico"), "Prendre un screenshot");
                QObject::connect(actionTakeScreenshot, SIGNAL(triggered()), this, SLOT(takeScreenshot()));

                actionMerge = toolBarMain->addAction(QIcon("://images/toolbar/merge.ico"), "Fusionner");
                QObject::connect(actionMerge, SIGNAL(triggered()), this, SLOT(merge()));

            toolBarMain->addSeparator();

                actionView = toolBarMain->addAction(QIcon("://images/toolbar/view.ico"), "Afficher");
                QObject::connect(actionView, SIGNAL(triggered()), this, SLOT(openViewerWindow()));

                actionUp = toolBarMain->addAction(QIcon("://images/toolbar/up.ico"), "Monter");
                QObject::connect(actionUp, SIGNAL(triggered()), this, SLOT(upImage()));

                actionDown = toolBarMain->addAction(QIcon("://images/toolbar/down.ico"), "Descendre");
                QObject::connect(actionDown, SIGNAL(triggered()), this, SLOT(downImage()));

                actionDelete = toolBarMain->addAction(QIcon("://images/toolbar/delete.ico"), "Supprimer");
                QObject::connect(actionDelete, SIGNAL(triggered()), this, SLOT(deleteImage()));

        layoutMain->addWidget(toolBarMain, 0, 0, 1, 1, 0);

            // List of the images / screenshots
            listWidgetImage = new QListWidget(widgetMain);
            listWidgetImage->setSelectionMode(QAbstractItemView::SingleSelection);
            QObject::connect(listWidgetImage, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openViewerWindow(QListWidgetItem*)));

        layoutMain->addWidget(listWidgetImage, 1, 0, 1, 1, 0);

}



// Destructor
MainWindow::~MainWindow()
{

}



// Method


// Qt slots

// About dialog
void MainWindow::about()
{
    QMessageBox::about(this, "À propos", "<h2><b>Screenshot Merge</b></h2>"
                                         "<p><b>Version :</b> 1.0<br/>"
                                         "<b>Développé par :</b> Nicolas Fostier<br/>"
                                         "<b>Librairie utilisée :</b> Qt 5.5.1<br/>"
                                         "<b>Logo :</b> Nicolas Fostier<br/>"
                                         "<b>Icônes :</b> <a href='http://www.customicondesign.com/'>Custom Icon Design</a></p>");
}


// Wait and take a screenshot
void MainWindow::takeScreenshot()
{
    this->hide();

    QTimer::singleShot(500, this, SLOT(shootScreenshot()));
}
// Shoot the screenshot
void MainWindow::shootScreenshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmapFullscreen = screen->grabWindow(0);

    CropWindow* cropWindow = new CropWindow(pixmapFullscreen, listWidgetImage);
    cropWindow->showFullScreen();
    QObject::connect(cropWindow, SIGNAL(destroyed()), this, SLOT(show()));
}

// Merge the image in the list
void MainWindow::merge()
{
    int height = 0;
    int width = 0;
    QPixmap currentPixmap;
    for(int i = 0; i < listWidgetImage->count(); i++)
    {
        currentPixmap = ((Screenshot*)listWidgetImage->item(i))->getImage();

        height += currentPixmap.height();
        if(width < currentPixmap.width())
        {
            width = currentPixmap.width();
        }
    }

    QPixmap* mergedScreenshots = new QPixmap(width, height);
    mergedScreenshots->fill(Qt::white);
    QPainter *painterMergedScreenshots = new QPainter(mergedScreenshots);

    int currentY = 0;
    for(int i = 0; i < listWidgetImage->count(); i++)
    {
        currentPixmap = ((Screenshot*)listWidgetImage->item(i))->getImage();

        painterMergedScreenshots->drawPixmap(0, currentY, currentPixmap);

        currentY += ((Screenshot*)listWidgetImage->item(i))->getImage().height();
    }

    QString path = QFileDialog::getSaveFileName(this, "Enregistrer l'image sous...", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "JPG (*.jpg);;PNG (*.png)");
    mergedScreenshots->save(path, 0, 85);
}

// Open a window to visualize the selected image on the list
void MainWindow::openViewerWindow()
{
    QList<QListWidgetItem*> selectedItems = listWidgetImage->selectedItems();
    if(!selectedItems.empty())
    {
        Screenshot* firstSelectedItem = (Screenshot*)(selectedItems.first());
        (new viewerWindow(firstSelectedItem->getImage()))->show();
    }
}

// Raise an image on the list
void MainWindow::upImage()
{
    QList<QListWidgetItem*> selectedItems = listWidgetImage->selectedItems();
    if(!selectedItems.empty())
    {
        int previousRow = listWidgetImage->row(selectedItems.first());

        if(previousRow != 0)
        {
            listWidgetImage->takeItem(previousRow);
            listWidgetImage->insertItem(previousRow-1, selectedItems.first());

            listWidgetImage->setCurrentRow(previousRow-1);
        }
    }
}

// Descend an image on the list
void MainWindow::downImage()
{
    QList<QListWidgetItem*> selectedItems = listWidgetImage->selectedItems();
    if(!selectedItems.empty())
    {
        int previousRow = listWidgetImage->row(selectedItems.first());

        if(previousRow < listWidgetImage->count() - 1)
        {
            listWidgetImage->takeItem(previousRow);
            listWidgetImage->insertItem(previousRow+1, selectedItems.first());

            listWidgetImage->setCurrentRow(previousRow+1);
        }
    }
}

// Delete the selected image in the list
void MainWindow::deleteImage()
{
    QList<QListWidgetItem*> selectedItems = listWidgetImage->selectedItems();
    if(!selectedItems.empty())
    {
        listWidgetImage->takeItem(listWidgetImage->row(selectedItems.first()));
        delete selectedItems.first();
    }
}


// Open a window to visualize the double-clicked image on the list
void MainWindow::openViewerWindow(QListWidgetItem* imageClicked)
{
    (new viewerWindow(((Screenshot*)imageClicked)->getImage()))->show();
}


// Quit the application when the main window is closed
void MainWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
    qApp->quit();
}

