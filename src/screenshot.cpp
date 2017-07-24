#include "include/screenshot.h"



// Getter
QPixmap Screenshot::getImage(){
	return image;
}
QLinkedList<Shape*> Screenshot::getShapes(){
	return shapesList;
}



// Setter
void Screenshot::setImage(QPixmap image){
	this->image = image;
}
void Screenshot::setShapes(QLinkedList<Shape*> shapesList){
	// Delete every old shapes
	while(!this->shapesList.isEmpty()){
		delete this->shapesList.takeFirst();
	}

	this->shapesList = shapesList;
}



// Constructor
Screenshot::Screenshot(QPixmap image, const QString &text,
					   QListWidget* parent, int type) : QListWidgetItem(text, parent, type){
	this->image = image;
}



// Destructor
Screenshot::~Screenshot(){
	while(!shapesList.isEmpty()){
		delete shapesList.takeFirst();
	}
}



// Methods


// Return a pixmap of the screenshot with all of its shapes drawn
QPixmap Screenshot::withDrawings(){
	// First, we make a clone of the screenshot without any shapes
	QPixmap finalPixmap = QPixmap(this->image);

	// We prepare the painter and his pen
	QPainter* painter = new QPainter(&finalPixmap);
	painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	// We draw one by one all the shapes of the user on the screenshot
	Shape* shape;
	foreach(shape, this->shapesList){
		shape->draw(painter);
	}

	// The painting is over
	delete painter;

	// We return the result
	return finalPixmap;
}
