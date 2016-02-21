#include "include/editwindow.h"

// Constructor
EditWindow::EditWindow(Screenshot* screenshot, QListWidget* listWidgetImage, bool* canTakeNewScreenshot) : QMainWindow()
{
    this->screenshot = screenshot;
    this->listWidgetImage = listWidgetImage;
    this->canTakeNewScreenshot = canTakeNewScreenshot;
    this->newDrawings = screenshot->getDrawings();
    this->screenshotToShow = new QPixmap(screenshot->getImage());
    this->painterScreenshot = new QPainter(screenshotToShow);
    QPen pen = QPen(drawColor);
    pen.setWidth(2);
    painterScreenshot->setPen(pen);
    painterScreenshot->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Settings
    settings = new QSettings(this);
    drawColor.setRed(settings->value("EditWindow/drawColorR", QColor(Qt::red).red()).toInt());
    drawColor.setGreen(settings->value("EditWindow/drawColorG", QColor(Qt::red).green()).toInt());
    drawColor.setBlue(settings->value("EditWindow/drawColorB", QColor(Qt::red).blue()).toInt());

    // Creation of the toolbar
    toolBar = new QToolBar(this);
    toolBar->setMovable(false);
    toolBar->setContextMenuPolicy(Qt::PreventContextMenu);


        actionValidate = toolBar->addAction(QIcon("://images/editwindow/validate.ico"), tr("Validate (Enter)"));
        actionValidate->setShortcut(QKeySequence(Qt::Key_Return));
        QObject::connect(actionValidate, SIGNAL(triggered()), this, SLOT(validate()));

        actionCancel = toolBar->addAction(QIcon("://images/editwindow/cancel.ico"), tr("Cancel (Escape)"));
        actionCancel->setShortcut(QKeySequence(Qt::Key_Escape));
        QObject::connect(actionCancel, SIGNAL(triggered()), this, SLOT(cancel()));

        // If we edit a fresh new screenshot...
        if(this->canTakeNewScreenshot != 0 && this->listWidgetImage != 0)
        {
            // ... we add the possibility to retake it
            actionRetake = toolBar->addAction(QIcon("://images/editwindow/retakescreenshot.ico"), tr("Retake the screenshot (Ctrl+N)"));
            actionRetake->setShortcut(QKeySequence::New);
            QObject::connect(actionRetake, SIGNAL(triggered()), this, SLOT(retake()));
        }

    toolBar->addSeparator();

        actionSave = toolBar->addAction(QIcon("://images/editwindow/save.ico"), tr("Save it (Ctrl+S)"));
        actionSave->setShortcut(QKeySequence::Save);
        QObject::connect(actionSave, SIGNAL(triggered()), this, SLOT(save()));

        actionCopyToClipboard = toolBar->addAction(QIcon("://images/editwindow/copytoclipboard.ico"), tr("Copy to clipboard (Ctrl+C)"));
        actionCopyToClipboard->setShortcut(QKeySequence::Copy);
        QObject::connect(actionCopyToClipboard, SIGNAL(triggered()), this, SLOT(copyToClipboard()));

    toolBar->addSeparator();

        actionColor = toolBar->addAction(QIcon("://images/editwindow/color.ico"), tr("Color of the draw tools"));
        QObject::connect(actionColor, SIGNAL(triggered()), this, SLOT(changeColor()));

    toolBar->addSeparator();

        actionGroupDrawTool = new QActionGroup(toolBar);

            actionPen = actionGroupDrawTool->addAction(QIcon("://images/editwindow/pen.ico"), tr("Pen (P)"));
            actionPen->setShortcut(QKeySequence(Qt::Key_P));
            actionPen->setCheckable(true);
            actionPen->setChecked(true);

            actionEraser = actionGroupDrawTool->addAction(QIcon("://images/editwindow/eraser.ico"), tr("Eraser (E)"));
            actionEraser->setShortcut(QKeySequence(Qt::Key_E));
            actionEraser->setCheckable(true);

    toolBar->addActions(actionGroupDrawTool->actions());

    this->addToolBar(toolBar);


    // Creation of the main widget
    widgetMain = new QWidget(this);
    this->setCentralWidget(widgetMain);

        // Creation of the layout of the window
        layout = new QHBoxLayout(widgetMain);
        layout->setContentsMargins(10,10,10,10);

            // If the screenshot is to big
            scrollArea = new QScrollArea(this);

                // Creation of the label which contain the image to display
                labelImage = new QLabel(widgetMain);
                labelImage->setPixmap(this->screenshot->getImage());
                labelImage->setFixedSize(this->screenshot->getImage().size());

            scrollArea->setWidget(labelImage);
            scrollArea->setAlignment(Qt::AlignCenter);
            scrollArea->setMaximumSize(QApplication::desktop()->screenGeometry().size() - (QApplication::desktop()->screenGeometry().size() / 5));
            QSize minimumSize(labelImage->size() + QSize(2,2));
            if(minimumSize.width() > scrollArea->maximumSize().width())
            {
                minimumSize.setWidth(scrollArea->maximumSize().width());
                minimumSize.setHeight(minimumSize.height() + scrollArea->horizontalScrollBar()->sizeHint().height());
            }
            if(minimumSize.height() > scrollArea->maximumSize().height())
            {
                minimumSize.setHeight(scrollArea->maximumSize().height());
                minimumSize.setWidth(minimumSize.width() + scrollArea->verticalScrollBar()->sizeHint().width());
            }
            scrollArea->setMinimumSize(minimumSize);

        // Add the scroll area to the layout
        layout->addWidget(scrollArea, Qt::AlignCenter);


    // Configuration of the window
    this->setWindowTitle(tr("Edit your screenshot"));
    this->setFixedSize(this->sizeHint());
    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);


    updateScreenshotToShow();
}



// Destructor
EditWindow::~EditWindow()
{
    painterScreenshot->end();

    delete screenshotToShow;
}



// Methods


// Update the pixmap of the displayed screenshot with the new drawings
void EditWindow::updateScreenshotToShow()
{
    // Take the screenshot without any drawings
    QPixmap screenshotPixmap = screenshot->getImage();
    painterScreenshot->drawPixmap(screenshotPixmap.rect(), screenshotPixmap);

    // Draw every drawings one by one on the clean screenshot
    ColoredPoly coloredPoly;
    foreach(coloredPoly, newDrawings)
    {
        QPen pen(coloredPoly.getColor());
        pen.setWidth(2);
        painterScreenshot->setPen(pen);
        painterScreenshot->drawPolyline(*coloredPoly.getPtrPolyline());
    }

    // Update the pixmap of the label
    labelImage->setPixmap(*screenshotToShow);
}


// When we press the right click on the window
void EditWindow::mousePressEvent(QMouseEvent* event)
{
    // We check which tool is selected
    if(this->actionPen->isChecked())
    {
        // Accept the event
        event->accept();

        // Create a new polyline which begin with the point of our click
        ColoredPoly newPolyline = ColoredPoly();
        newPolyline.setColor(drawColor);
        newPolyline.getPtrPolyline()->append(labelImage->mapFrom(this, event->pos()));

        // Add the new polyline to the drawing list
        newDrawings.prepend(newPolyline);

        // Update the display of the screenshot
        updateScreenshotToShow();
    }
    else if(this->actionEraser->isChecked())
    {
        // Accept the event
        event->accept();

        // We will check every point of all the drawing of the screenshot
        QPoint point;
        QRectF rect;
        ColoredPoly coloredPoly;
        foreach(coloredPoly, newDrawings)
        {
            foreach(point, *(coloredPoly.getPtrPolyline()))
            {
                // If our click is near a polyline, the polyline will be delete
                rect = QRectF(double(point.x()) - (8.0 / 2.0), double(point.y()) - (8.0 / 2.0), 8.0, 8.0);
                if(rect.contains(QPointF(labelImage->mapFrom(this, event->pos()))))
                {
                    newDrawings.removeOne(coloredPoly);
                    updateScreenshotToShow();
                }
            }
        }
    }
    else
    {
        // Ignore the event
        event->ignore();
    }
}

// When we move on the window
void EditWindow::mouseMoveEvent(QMouseEvent* event)
{
    // Check if the pen is selected
    if(this->actionPen->isChecked())
    {
        // Accept the event
        event->accept();

        // We add the new point to the newest polyline
        newDrawings.first().getPtrPolyline()->append(labelImage->mapFrom(this, event->pos()));

        // Update the display of the screenshot to see the polyline with his new point
        updateScreenshotToShow();
    }
    else
    {
        // Ignore the event
        event->ignore();
    }
}


// When the window is closing
void EditWindow::closeEvent(QCloseEvent *event)
{
    // We accept the event
    event->accept();

    // We save the color for a next session
    settings->setValue("EditWindow/drawColorR", drawColor.red());
    settings->setValue("EditWindow/drawColorG", drawColor.green());
    settings->setValue("EditWindow/drawColorB", drawColor.blue());

    // If we edit a fresh new screenshot...
    if(canTakeNewScreenshot != 0 && listWidgetImage != 0)
    {
        // ...we indicate that we can retake screenshot
        *canTakeNewScreenshot = true;
    }
}



// Qt slots


// Update the pixmap of the displayed screenshot with the new drawings
void EditWindow::validate()
{
    // We add the new drawings to the screenshot
    screenshot->setDrawings(newDrawings);

    // If we edit a fresh new screenshot...
    if(canTakeNewScreenshot != 0 && listWidgetImage != 0)
    {
        // ...we indicate that we can retake screenshot
        *canTakeNewScreenshot = true;
        // and we add the screenshot to the list
        listWidgetImage->addItem(screenshot);
    }

    // We signal that the edit is over
    emit editOver();

    // Close the edit window
    this->close();
}

// Cancel
void EditWindow::cancel()
{
    // If we edit a fresh new screenshot...
    if(canTakeNewScreenshot != 0 && listWidgetImage != 0)
    {
        // ...we indicate that we can retake screenshot
        *canTakeNewScreenshot = true;

        //and we delete the screenshot
        delete screenshot;
    }

    // We signal that the edit is over
    emit editOver();

    // We close the edit window, nothing is modified
    this->close();
}

// Retake the screenshot
void EditWindow::retake()
{
    //and we delete the screenshot
    delete screenshot;

    // We lower the edit windows
    this->lower();

    // And we retake one
    *canTakeNewScreenshot = true;
    emit retakeSignal();

    // And we finally completely close the window
    this->close();
}


// Save the screenshot
void EditWindow::save()
{
    // We signal the main window that we want to save a screenshot
    emit saveSignal(*(labelImage->pixmap()));
}

// Copy the screenshot to the clipboard
void EditWindow::copyToClipboard()
{
    // We get access to the clipboard
    QClipboard* clipboard = QApplication::clipboard();

    // Put the pixmap into it
    clipboard->setPixmap(*(labelImage->pixmap()));

    // Display a dialog to inform that it's done
    QMessageBox::information(this, tr("Clipboard"), tr("Your screenshot has been successfuly put in your clipboard !"));
}


// Change the color of the draw tool
void EditWindow::changeColor()
{
    drawColor = QColorDialog::getColor(drawColor, this, tr("Choose your color"));
}
