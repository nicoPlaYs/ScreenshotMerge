#include "include/editwindow.h"

// Constructor
EditWindow::EditWindow(QPixmap image) : QMainWindow()
{
    // Settings
    settings = new QSettings();
    drawColor = settings->value("EditWindow/drawColor", QColor(Qt::red).value()).toInt();

    // Creation of the toolbar
    toolBar = new QToolBar(this);
    toolBar->setMovable(false);
    toolBar->setContextMenuPolicy(Qt::PreventContextMenu);

        actionValidate = toolBar->addAction(QIcon("://images/editwindow/validate.ico"), tr("Validate"));
        QObject::connect(actionValidate, SIGNAL(triggered()), this, SLOT(validate()));

        actionCancel = toolBar->addAction(QIcon("://images/editwindow/cancel.ico"), tr("Cancel"));
        QObject::connect(actionCancel, SIGNAL(triggered()), this, SLOT(cancel()));

        actionRetake = toolBar->addAction(QIcon("://images/editwindow/retakescreenshot.ico"), tr("Retake the screenshot"));
        QObject::connect(actionRetake, SIGNAL(triggered()), this, SLOT(retake()));

    toolBar->addSeparator();

        actionSave = toolBar->addAction(QIcon("://images/editwindow/save.ico"), tr("Save it"));
        QObject::connect(actionSave, SIGNAL(triggered()), this, SLOT(save()));

        actionCopyToClipboard = toolBar->addAction(QIcon("://images/editwindow/copytoclipboard.ico"), tr("Copy to clipboard"));
        QObject::connect(actionCopyToClipboard, SIGNAL(triggered()), this, SLOT(copyToClipboard()));

    toolBar->addSeparator();

        actionColor = toolBar->addAction(QIcon("://images/editwindow/color.ico"), tr("Color of the draw tools"));
        QObject::connect(actionColor, SIGNAL(triggered()), this, SLOT(changeColor()));

    toolBar->addSeparator();

        actionGroupDrawTool = new QActionGroup(toolBar);

            actionPen = actionGroupDrawTool->addAction(QIcon("://images/editwindow/pen.ico"), tr("Pen"));
            actionPen->setCheckable(true);
            actionPen->setChecked(true);

            actionEraser = actionGroupDrawTool->addAction(QIcon("://images/editwindow/eraser.ico"), tr("Eraser"));
            actionEraser->setCheckable(true);

    toolBar->addActions(actionGroupDrawTool->actions());


    this->addToolBar(toolBar);

    // Creation of the main widget
    widgetMain = new QWidget();
    this->setCentralWidget(widgetMain);

        // Creation of the layout of the window
        layout = new QHBoxLayout(widgetMain);
        layout->setContentsMargins(15,15,15,15);

            // Creation of the label which contain the image to display
            labelImage = new QLabel(widgetMain);
            labelImage->setPixmap(image);
            labelImage->setAlignment(Qt::AlignCenter);

        // Add the label to the layout
        layout->addWidget(labelImage, Qt::AlignCenter);

    // Configuration of the window
    this->setWindowTitle(tr("Edit your screenshot"));
    this->setMinimumSize(400,400);
    this->setMaximumSize(labelImage->pixmap()->size());
    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}



// Destructor
EditWindow::~EditWindow()
{

}



// Methods


// When the window is closing
void EditWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    settings->setValue("EditWindow/drawColor", drawColor.value());
}



// Qt slots


// Validate
void EditWindow::validate()
{

}

// Cancel
void EditWindow::cancel()
{

}


// Retake the screenshot
void EditWindow::retake()
{

}

// Save the screenshot
void EditWindow::save()
{

}

// Copy the screenshot to the clipboard
void EditWindow::copyToClipboard()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setPixmap(*(labelImage->pixmap()));
}


// Change the color of the draw tool
void EditWindow::changeColor()
{
    drawColor = QColorDialog::getColor(drawColor, this, tr("Choose your color"));
}
