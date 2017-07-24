#include "include/shapes/shape.h"



// Getter
bool Shape::isInProgress(){
	return isInProgressValue;
}



// Setter
void Shape::setPen(QPen pen){
	this->pen = pen;
}
void Shape::setInProgress(bool inProgress){
	this->isInProgressValue = inProgress;
}



// Constructor
Shape::Shape(QPen pen){
	this->pen = pen;
	this->isInProgressValue = true;
}



// Destructeur
Shape::~Shape(){

}
