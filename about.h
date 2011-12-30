#ifndef ABOUT_H
#define ABOUT_H
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsTextItem>
#include "pixmap.h"
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QSignalTransition>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>

class About : public QGraphicsView {
	Q_OBJECT
	public:
	About(QWidget *parent = 0);
	public slots:
	void showAnimated();
	private:
	QPropertyAnimation *animation;
	QTimer *timer;
	QGraphicsScene *scene;
	Pixmap *bgPixmap;
	Pixmap *icon;
	Pixmap *closeButton;
	QGraphicsTextItem *headerTextItem;//WebRender
	QGraphicsTextItem *versionTextItem;//Release Candidate 4
	QGraphicsTextItem *subHeaderTextItem;// Brought to you by
	QGraphicsTextItem *textItem1;// Anand Bose
	QGraphicsTextItem *textItem2;// Jaideep

	QStateMachine *stateMachine;
	QState *initialState;
	QState *finalState;
	QSignalTransition *transition;
};

#endif
