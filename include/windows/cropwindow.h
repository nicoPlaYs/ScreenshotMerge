#ifndef CROPWINDOW_H
#define CROPWINDOW_H



#include <QLabel>
#include <QPoint>
#include <QRect>
#include <QListWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>



// Store a screenshot which can be put in a QListWidget
#include "include/screenshot.h"



// The window to crop the screenshot of the entire screen
class CropWindow : public QLabel{
	Q_OBJECT

	// Variables
	private :
		// Date when the screenshot has been taken
		QString dateShooting;

		// Size and position for the crop tool
		QPoint cropOrigin;
		QRect cropArea;

		// Differents pixmaps to draw usefull for the crop tool
		QPixmap* originalPixmap;
		QPixmap* whitePixmap;
		QPixmap* mixPixmap;

		// Painter use to modify the differents pixmaps above
		QPainter* painterMix;

	// Constructor
	public :
		CropWindow(QPixmap pixmapFullscreen, QRect screensRect);

	// Destructor
	public :
		~CropWindow();

	// Methods
	public :
		// When we click on the window
		void mousePressEvent(QMouseEvent *event);
		// When we move on the window
		void mouseMoveEvent(QMouseEvent *event);
		// When we release the click on the window
		void mouseReleaseEvent(QMouseEvent *event);

	// Qt signals
	signals :
		// When the user has finished to crop his screenshot
		void cropOver(Screenshot* croppedScreenshot);
};



#endif // CROPWINDOW_H
