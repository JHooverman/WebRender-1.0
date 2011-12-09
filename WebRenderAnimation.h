#ifndef WEBRENDERANIMATION_H
#define WEBRENDERANIMATION_H
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QSignalTransition>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include <QtGui/QPixmap>
#include "pixmap.h"

class WebRenderAnimation : public QGraphicsView {
	Q_OBJECT
	public:
	WebRenderAnimation(QWidget *parent = 0);
	void startAnimation();
	private:
	QGraphicsScene *scene;
	Pixmap *logo;
	Pixmap *glow;

	Pixmap *largeIcons[8];
	Pixmap *smallIcons[6];

	QStateMachine *StateMachine;
	QState *initialState;
	QState *finalState;
	QSignalTransition *transition;
	QPropertyAnimation *animation;
	QTimer *timer;
};
#endif
