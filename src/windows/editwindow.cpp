#include "include/windows/editwindow.h"



// Constructor
EditWindow::EditWindow(Screenshot* screenshot, ImageHost host, QListWidget* listWidgetImage) : QMainWindow(){
	this->screenshot = screenshot;
	this->listWidgetImage = listWidgetImage;

	Shape* shape;
	foreach(shape, screenshot->getShapes()){
		this->newShapesList.append(shape->clone());
	}

	this->screenshotToShow = new QPixmap(screenshot->withDrawings());
	this->painterScreenshot = new QPainter(screenshotToShow);
	painterScreenshot->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	// Settings
	settings = new QSettings(this);

	// Pen
	QColor drawColor;
	drawColor.setRed(settings->value("EditWindow/drawColorR",
									 QColor(Qt::red).red()).toInt());
	drawColor.setGreen(settings->value("EditWindow/drawColorG",
									   QColor(Qt::red).green()).toInt());
	drawColor.setBlue(settings->value("EditWindow/drawColorB",
									  QColor(Qt::red).blue()).toInt());
	drawPen.setColor(drawColor);
	drawPen.setWidth(settings->value("EditWindow/width", 2).toInt());
	drawPen.setStyle(Qt::SolidLine);
	drawPen.setCapStyle(Qt::RoundCap);
	drawPen.setJoinStyle(Qt::RoundJoin);
	painterScreenshot->setPen(drawPen);

	// Creation of the toolbar
	toolBar = new QToolBar(this);
	toolBar->setMovable(false);
	toolBar->setContextMenuPolicy(Qt::PreventContextMenu);

	actionValidate = toolBar->addAction(QIcon("://images/editwindow/validate.ico"), tr("Validate (Enter)"));
	actionValidate->setShortcut(QKeySequence(Qt::Key_Return));
	QObject::connect(actionValidate, SIGNAL(triggered()),
					 this, SLOT(validate()));

	actionCancel = toolBar->addAction(QIcon("://images/editwindow/cancel.ico"), tr("Cancel (Escape)"));
	actionCancel->setShortcut(QKeySequence(Qt::Key_Escape));
	QObject::connect(actionCancel, SIGNAL(triggered()),
					 this, SLOT(close()));

	// If we edit a fresh new screenshot...
	if(this->listWidgetImage != 0){
		// ... we add the possibility to retake it
		actionRetake = toolBar->addAction(QIcon("://images/editwindow/retakescreenshot.ico"), tr("Retake the screenshot (Ctrl+N)"));
		actionRetake->setShortcut(QKeySequence::New);
		QObject::connect(actionRetake, SIGNAL(triggered()),
						 this, SLOT(retake()));
	}

	toolBar->addSeparator();

	actionSave = toolBar->addAction(QIcon("://images/toolbar/save.ico"), tr("Save it (Ctrl+S)"));
	actionSave->setShortcut(QKeySequence::Save);
	QObject::connect(actionSave, SIGNAL(triggered()),
					 this, SLOT(save()));

	actionCopyIntoClipboard = toolBar->addAction(QIcon("://images/editwindow/copytoclipboard.ico"), tr("Copy to clipboard (Ctrl+C)"));
	actionCopyIntoClipboard->setShortcut(QKeySequence::Copy);
	QObject::connect(actionCopyIntoClipboard, SIGNAL(triggered()),
					 this, SLOT(copyIntoClipboard()));

	actionUploadScreenshot = toolBar->addAction(QIcon("://images/toolbar/upload.ico"), tr("Merge and upload it (Ctrl+U)"));
	actionUploadScreenshot->setShortcut(QKeySequence("Ctrl+U"));
	QObject::connect(actionUploadScreenshot, SIGNAL(triggered()),
					 this, SLOT(uploadScreenshot()));

	comboBoxImageHost = new QComboBox(this);
	comboBoxImageHost->addItem(QIcon("://images/toolbar/imgur.ico"), "imgur", QVariant(imgur));
	comboBoxImageHost->addItem(QIcon("://images/toolbar/noelshack.ico"), "NoelShack", QVariant(noelshack));
	comboBoxImageHost->setCurrentIndex(comboBoxImageHost->findData(host));
	toolBar->addWidget(comboBoxImageHost);

	toolBar->addSeparator();

	sliderPenWidth = new QSlider(Qt::Horizontal, toolBar);
	sliderPenWidth->setToolTip(tr("Size of the drawing tools"));
	sliderPenWidth->setValue(drawPen.width());
	sliderPenWidth->setRange(1,10);
	sliderPenWidth->setFixedWidth(50);
	toolBar->addWidget(sliderPenWidth);

	spinBoxPenWidth = new QSpinBox(toolBar);
	spinBoxPenWidth->setToolTip(tr("Size of the drawing tools"));
	spinBoxPenWidth->setValue(sliderPenWidth->value());
	spinBoxPenWidth->setRange(1,10);
	spinBoxPenWidth->setFixedWidth(35);
	QObject::connect(sliderPenWidth, SIGNAL(valueChanged(int)),
					 spinBoxPenWidth, SLOT(setValue(int)));
	QObject::connect(spinBoxPenWidth, SIGNAL(valueChanged(int)),
					 sliderPenWidth, SLOT(setValue(int)));
	QObject::connect(spinBoxPenWidth, SIGNAL(valueChanged(int)),
					 this, SLOT(changePenWidth(int)));
	toolBar->addWidget(spinBoxPenWidth);

	actionColor = toolBar->addAction(QIcon("://images/editwindow/color.ico"), tr("Color of the drawing tools"));
	QObject::connect(actionColor, SIGNAL(triggered()),
					 this, SLOT(changePenColor()));

	toolBar->addSeparator();

	actionGroupDrawTool = new QActionGroup(toolBar);
	QObject::connect(actionGroupDrawTool, SIGNAL(triggered(QAction*)),
					 this, SLOT(changeDrawingTool()));

	actionPen = actionGroupDrawTool->addAction(QIcon("://images/editwindow/pen.ico"), tr("Pen"));
	actionPen->setCheckable(true);

	actionStraightLine = actionGroupDrawTool->addAction(QIcon("://images/editwindow/straightline.ico"), tr("Straight line"));
	actionStraightLine->setCheckable(true);

	actionFrame = actionGroupDrawTool->addAction(QIcon("://images/editwindow/frame.ico"), tr("Frame"));
	actionFrame->setCheckable(true);

	actionEraser = actionGroupDrawTool->addAction(QIcon("://images/editwindow/eraser.ico"), tr("Eraser"));
	actionEraser->setCheckable(true);

	// Activate the last drawing tool used by the user
	switch(settings->value("EditWindow/drawingTool", TypeDrawTool(PEN)).toInt())
	{
		case PEN :
		actionPen->setChecked(true);
		break;

		case STRAIGHTLINE :
		actionStraightLine->setChecked(true);
		break;

		case FRAME :
		actionFrame->setChecked(true);
		break;

		case ERASER :
		actionEraser->setChecked(true);
		break;
	}

	toolBar->addActions(actionGroupDrawTool->actions());

	this->addToolBar(toolBar);


	// Creation of the main widget
	widgetMain = new QWidget(this);
	this->setCentralWidget(widgetMain);

	// Creation of the layout of the window
	layout = new QHBoxLayout(widgetMain);
	layout->setContentsMargins(10,10,10,10);

	// Creation of the label which contain the image to display
	labelImage = new QLabel(this);
	labelImage->setPixmap(*this->screenshotToShow);
	labelImage->setFixedSize(this->screenshot->getImage().size());

	// If the screenshot is to big
	scrollArea = new QScrollArea(widgetMain);
	scrollArea->setWidget(labelImage);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setMaximumSize(QApplication::desktop()->screenGeometry().size() - QSize(175,175));
	QSize minimumSize(labelImage->size() + QSize(2,2));
	if(minimumSize.width() > scrollArea->maximumSize().width()){
		minimumSize.setWidth(scrollArea->maximumSize().width());
		minimumSize.setHeight(minimumSize.height() + scrollArea->horizontalScrollBar()->sizeHint().height());
	}
	if(minimumSize.height() > scrollArea->maximumSize().height()){
		minimumSize.setHeight(scrollArea->maximumSize().height());
		minimumSize.setWidth(minimumSize.width() + scrollArea->verticalScrollBar()->sizeHint().width());
	}
	scrollArea->setMinimumSize(minimumSize);
	layout->addWidget(scrollArea, Qt::AlignCenter);


	// The edit isn't validated yet
	this->closingReason = REJECT;

	// Configuration of the window
	this->setWindowTitle(tr("Edit your screenshot"));
	this->setFixedSize(this->sizeHint());
	this->setWindowModality(Qt::ApplicationModal);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	this->show();
}



// Destructor
EditWindow::~EditWindow(){
	delete painterScreenshot;
	delete screenshotToShow;
}



// Methods


// Refresh the pixmap of the displayed screenshot by redraw everything
void EditWindow::refreshScreenshotToShow(){
	// Take the screenshot without any shapes
	QPixmap screenshotPixmap = screenshot->getImage();
	painterScreenshot->drawPixmap(screenshotPixmap.rect(), screenshotPixmap);

	// Draw every shape one by one on the clean screenshot
	Shape* shape;
	foreach(shape, newShapesList)	{
		shape->draw(painterScreenshot);
	}

	// Update the pixmap of the label
	labelImage->setPixmap(*screenshotToShow);
}


// When we press the right click on the window
void EditWindow::mousePressEvent(QMouseEvent* event){
	// Position of the mouse on the label
	QPoint mousePosLabel = labelImage->mapFrom(this, event->pos());

	// Check if the mouse is inside the image to edit it
	if(labelImage->rect().contains(mousePosLabel)){
		// We check which tool is selected
		if(this->actionPen->isChecked()){
			// Create a new polyline
			Polyline* polyline = new Polyline(drawPen, mousePosLabel);

			// Add the new polyline to the shape list
			newShapesList.append(polyline);

			// Draw the single point of this polyline
			painterScreenshot->drawPoint(mousePosLabel);

			// Update the pixmap of the label
			labelImage->setPixmap(*screenshotToShow);

			// We keep this new point as the last point
			lastPointPolyline = mousePosLabel;
		}
		else if(this->actionStraightLine->isChecked()){
			// Create a new straight line
			StraightLine* straightLine = new StraightLine(drawPen, mousePosLabel, mousePosLabel);

			// Add the new straight line to the shape list
			newShapesList.append(straightLine);

			// Prepare the pen to erase the temporary straight line
			eraseTempPen.setBrush(QBrush(*screenshotToShow));
			eraseTempPen.setWidth(drawPen.width() + 2);

			// Draw the line
			straightLine->draw(painterScreenshot);

			// Update the pixmap of the label
			labelImage->setPixmap(*screenshotToShow);
		}
		else if(this->actionFrame->isChecked()){
			// Create a new straight line
			Frame* frame = new Frame(drawPen, mousePosLabel, mousePosLabel);

			// Add the new frame to the shape list
			newShapesList.append(frame);

			// Prepare the pen to erase the temporary frame
			eraseTempPen.setBrush(QBrush(*screenshotToShow));
			eraseTempPen.setWidth(drawPen.width() + 2);

			// Draw the frame
			frame->draw(painterScreenshot);

			// Update the pixmap of the label
			labelImage->setPixmap(*screenshotToShow);
		}
	}
}

// When we move on the window
void EditWindow::mouseMoveEvent(QMouseEvent* event){
	// Position of the mouse on the label
	QPoint mousePosLabel = labelImage->mapFrom(this, event->pos());

	if(!newShapesList.isEmpty() && newShapesList.last()->isInProgress()){
		// We check which tool is selected
		if(this->actionPen->isChecked()){
			Polyline* polyline = static_cast<Polyline*>(newShapesList.last());

			// Add the new point to the newest polyline
			polyline->addPoint(mousePosLabel);

			// Draw the line from the last point and this new point of the polyline
			painterScreenshot->drawLine(lastPointPolyline, mousePosLabel);

			// Update the pixmap of the label
			labelImage->setPixmap(*screenshotToShow);

			// We keep this new point as the last point
			lastPointPolyline = mousePosLabel;
		}
		else if(this->actionStraightLine->isChecked()){
			// Create a new straight line
			StraightLine* straightLine = static_cast<StraightLine*>(newShapesList.last());

			// Erase the previous temporary straight line
			straightLine->setPen(eraseTempPen);
			straightLine->draw(painterScreenshot);


			// Change the end point of the line to the new one
			straightLine->setEndPoint(mousePosLabel);

			// Draw the new temporary (or not) straight line
			straightLine->setPen(drawPen);
			straightLine->draw(painterScreenshot);

			// Update the pixmap of the label
			labelImage->setPixmap(*screenshotToShow);

		}
		else if(this->actionFrame->isChecked()){
			// Create a new straight line
			Frame* frame = static_cast<Frame*>(newShapesList.last());

			// Erase the previous temporary straight line
			frame->setPen(eraseTempPen);
			frame->draw(painterScreenshot);


			// Change the end point of the frame
			frame->setEndPoint(mousePosLabel);

			// Draw the new temporary (or not) frame
			frame->setPen(drawPen);
			frame->draw(painterScreenshot);

			// Update the pixmap of the label
			labelImage->setPixmap(*screenshotToShow);

		}
	}
}

// When we release the click on the window
void EditWindow::mouseReleaseEvent(QMouseEvent* event){
	// Position of the mouse on the label
	QPoint mousePosLabel = labelImage->mapFrom(this, event->pos());

	if(!newShapesList.isEmpty() && newShapesList.last()->isInProgress()){
		newShapesList.last()->setInProgress(false);
	}
	// If it's the eraser which is selected...
	else if(this->actionEraser->isChecked()){
		// Check if the mouse is on the image to edit it
		if(labelImage->rect().contains(mousePosLabel)){
			// Create a hitbox around the position of the mouse
			QRect hitbox(mousePosLabel, mousePosLabel);
			hitbox = hitbox.marginsAdded(QMargins(3,3,3,3));

			// Check if this hitbox hit a shape
			QLinkedList<Shape*>::iterator i;
			for(i = newShapesList.begin(); i != newShapesList.end(); ++i){
				// if it's the case, destroy the shape and refresh the screenshot to show
				if((*i)->isHitted(hitbox)){
					delete *i;
					newShapesList.erase(i);

					refreshScreenshotToShow();

					return;
				}
			}
		}
	}
}

// When we close the window
void EditWindow::closeEvent(QCloseEvent *event){
	// Accept the event
	event->accept();

	// Check why the edit window is closing
	switch(this->closingReason){
		case REJECT:
			// If we edit a fresh new screenshot...
			if(listWidgetImage != 0){
				// ...we delete the screenshot
				delete screenshot;
			}

			// Delete every new shapes
			while(!newShapesList.isEmpty()){
				delete newShapesList.takeFirst();
			}

			// We signal that the edit is over
			emit editOver(comboBoxImageHost->currentText());
		break;

		case VALIDATED:
			// We add the new shapes to the screenshot after deleting the newest which is empty
			screenshot->setShapes(newShapesList);

			// If we edit a fresh new screenshot...
			if(listWidgetImage != 0){
				// ...we add the screenshot to the list
				listWidgetImage->addItem(screenshot);
			}

			// We signal that the edit is over
			emit editOver(comboBoxImageHost->currentText());
		break;

		case RETAKE:
			// If we edit a fresh new screenshot...
			if(listWidgetImage != 0){
				// ...we delete the screenshot
				delete screenshot;
			}

			// Delete every new shapes
			while(!newShapesList.isEmpty()){
				delete newShapesList.takeFirst();
			}

			// We lower the edit windows
			#if defined(Q_OS_WIN) || defined(Q_OS_LINUX)
				this->lower();
			#endif

			// In macOS, it's better to minimized the window
			#ifdef Q_OS_MACOS
				this->showMinimized();
			#endif

			// And we retake one
			emit retakeSignal();
		break;
	}
}



// Qt slots


// Update the pixmap of the displayed screenshot with the new shapes
void EditWindow::validate(){
	// The edit is validated
	this->closingReason = VALIDATED;

	// Close the edit window
	this->close();
}

// Retake the screenshot
void EditWindow::retake(){
	// A retake has been resquested
	this->closingReason = RETAKE;

	// And we finally completely close the window
	this->close();
}


// Save the screenshot
void EditWindow::save(){
	// We signal the main window that we want to save a screenshot
	saveImage(*(labelImage->pixmap()));
}

// Copy the screenshot to the clipboard
void EditWindow::copyIntoClipboard(){
	// We get access to the clipboard
	QClipboard* clipboard = QApplication::clipboard();

	// Put the pixmap into it
	clipboard->setPixmap(*(labelImage->pixmap()));

	// Display a dialog to inform that it's done
	QMessageBox::information(this, tr("Clipboard"),
							 tr("Your screenshot has been successfuly put in your clipboard !"));
}

// Upload the screenshot to an image host website
void EditWindow::uploadScreenshot(){
	uploadImage(*(labelImage->pixmap()), comboBoxImageHost->currentData().value<ImageHost>(),
				settings->value("SettingsWindow/imageQuality", 85).toInt());
}

// Change the width of the draw tool
void EditWindow::changePenWidth(int width){
	drawPen.setWidth(width);
	painterScreenshot->setPen(drawPen);
	settings->setValue("EditWindow/width", width);
}

// Change the color of the draw tool
void EditWindow::changePenColor(){
	QColor newColor = QColorDialog::getColor(drawPen.color(), this, tr("Choose your color"));
	if(newColor.isValid()){
		drawPen.setColor(newColor);
		painterScreenshot->setPen(drawPen);

		// We save the color for a next session
		settings->setValue("EditWindow/drawColorR", newColor.red());
		settings->setValue("EditWindow/drawColorG", newColor.green());
		settings->setValue("EditWindow/drawColorB", newColor.blue());
	}
}

// When the drawing tool is changing
void EditWindow::changeDrawingTool(){
	TypeDrawTool drawingTool(PEN);

	if(actionPen->isChecked()){
		drawingTool = PEN;
	}
	else if(actionStraightLine->isChecked()){
		drawingTool = STRAIGHTLINE;
	}
	else if(actionFrame->isChecked()){
		drawingTool = FRAME;
	}
	else if(actionEraser->isChecked()){
		drawingTool = ERASER;
	}

	// Save the last drawing tool used by the user
	settings->setValue("EditWindow/drawingTool", drawingTool);
}
