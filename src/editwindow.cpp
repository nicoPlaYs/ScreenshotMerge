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

            // Creation of the label which contain the image to display
            labelImage = new QLabel(widgetMain);
            labelImage->setPixmap(this->screenshot->getImage());
            labelImage->setBaseSize(this->screenshot->getImage().size());
            labelImage->setFixedSize(this->screenshot->getImage().size());
//            labelImage->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        // Add the label to the layout
        layout->addWidget(labelImage, Qt::AlignCenter);

    // Configuration of the window
    this->setWindowTitle(tr("Edit your screenshot"));
    this->setMinimumSize(400,400);
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

//
void EditWindow::updateScreenshotToShow()
{
    QPixmap screenshotPixmap = screenshot->getImage();
    painterScreenshot->drawPixmap(screenshotPixmap.rect(), screenshotPixmap);

    ColoredPoly coloredPoly;
    foreach(coloredPoly, newDrawings)
    {
        QPen pen(coloredPoly.getColor());
        pen.setWidth(2);
        painterScreenshot->setPen(pen);
        painterScreenshot->drawPolyline(*coloredPoly.getPtrPolyline());
    }
    labelImage->setPixmap(*screenshotToShow);
}

//
void EditWindow::mousePressEvent(QMouseEvent* event)
{
    if(this->actionPen->isChecked())
    {
        event->accept();
        ColoredPoly newPolyline = ColoredPoly();
        newPolyline.setColor(drawColor);
        newPolyline.getPtrPolyline()->append(labelImage->mapFrom(this, event->pos()));

        newDrawings.prepend(newPolyline);

        updateScreenshotToShow();
    }
    else if(this->actionEraser->isChecked())
    {
        event->accept();

        QPoint point;
        QRectF rect;
        ColoredPoly coloredPoly;
        int i = 0;
        foreach(coloredPoly, newDrawings)
        {
            foreach(point, *(coloredPoly.getPtrPolyline()))
            {
                rect = QRectF(double(point.x()) - (8.0 / 2.0), double(point.y()) - (8.0 / 2.0), 8.0, 8.0);

                if(rect.contains(QPointF(labelImage->mapFrom(this, event->pos()))))
                {
                    newDrawings.removeOne(coloredPoly);
                    updateScreenshotToShow();
                }
            }
            i++;
        }
    }
    else
    {
        event->ignore();
    }
}
//
void EditWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(this->actionPen->isChecked())
    {
        event->accept();

        newDrawings.first().getPtrPolyline()->append(labelImage->mapFrom(this, event->pos()));

        updateScreenshotToShow();
    }
    else
    {
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


// Validate
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
    emit retakeSignal(true);

    // And we finally completely close the window
    this->close();
}


// Save the screenshot
void EditWindow::save()
{
    emit saveSignal(*(labelImage->pixmap()));
}

// Copy the screenshot to the clipboard
void EditWindow::copyToClipboard()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setPixmap(*(labelImage->pixmap()));

    QMessageBox::information(this, tr("Clipboard"), tr("Your screenshot has been successfuly put in your clipboard !"));
}


// Change the color of the draw tool
void EditWindow::changeColor()
{
    drawColor = QColorDialog::getColor(drawColor, this, tr("Choose your color"));
}