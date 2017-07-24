#ifndef SHAPE_H
#define SHAPE_H



#include <QPen>
#include <QColor>
#include <QPainter>



// Abstract class which contains the shape drawn by the user on his screenshots
class Shape{
	// Variable
	protected :
		// Pen used to draw the shape
		QPen pen;
		// Indicate if the shape is currently being drawn
		bool isInProgressValue;

	// Getter
	public :
		bool isInProgress();

	// Setter
	public :
		void setPen(QPen pen);
		void setInProgress(bool isInProgressValue);

	// Constructor
	public :
		Shape(QPen pen);

	// Destructor
	public :
		virtual ~Shape();

	// Methods
	public :
		// Clone the shape
		virtual Shape* clone() = 0;

		// Draw the shape
		virtual void draw(QPainter* painter) = 0;
		// Return true if the shape is hitted by the hitbox in argument
		virtual bool isHitted(QRect hitbox) = 0;
};



#endif // SHAPE_H
