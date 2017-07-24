#ifndef FRAME_H
#define FRAME_H



#include <QRectF>


// Abstract class which contains the shape drawn by the user on his screenshots
#include "include/shapes/shape.h"



// A frame which can be drawn by the user
class Frame : public Shape{
	// Variable
	private :
		// The frame
		QRect frame;
		// The first point of the frame
		QPoint firstPoint;

	// Setter
	public :
		void setEndPoint(QPoint endPoint);

	// Constructor
	public :
		Frame(QPen pen, QPoint P1, QPoint P2);
		Frame(Frame const& frame);

	// Destructor
	public :
		~Frame();

	// Methods
	public :
		// Clone the frame
		virtual Shape* clone();

		// Draw the frame
		virtual void draw(QPainter *painter);
		// Return true if the frame is hitted by the hitbox in argument
		virtual bool isHitted(QRect hitbox);
};



#endif // FRAME_H
