#include "WebRenderAnimation.h"
#include <QtGui/QPalette>

WebRenderAnimation::WebRenderAnimation(QWidget *parent) : QGraphicsView(parent) {
	scene = new QGraphicsScene;
	scene->setBackgroundBrush((new QPalette)->window());
	logo = new Pixmap(QPixmap(":/images/SetupAssistant/webrender.png"));
	glow = new Pixmap(QPixmap(":/images/SetupAssistant/glow.png"));

	largeIcons[0] = new Pixmap(QPixmap(":/images/SetupAssistant/angrybirds.png"));
	largeIcons[1] = new Pixmap(QPixmap(":/images/SetupAssistant/blogger.png"));
	largeIcons[2] = new Pixmap(QPixmap(":/images/SetupAssistant/facebook.png"));
	largeIcons[3] = new Pixmap(QPixmap(":/images/SetupAssistant/gmail.png"));
	largeIcons[4] = new Pixmap(QPixmap(":/images/SetupAssistant/googlemusic.png"));
	largeIcons[5] = new Pixmap(QPixmap(":/images/SetupAssistant/googleplus.png"));
	largeIcons[6] = new Pixmap(QPixmap(":/images/SetupAssistant/skype.png"));
	largeIcons[7] = new Pixmap(QPixmap(":/images/SetupAssistant/youtube.png"));

	smallIcons[0] = new Pixmap(QPixmap(":/images/SetupAssistant/linkedin.png"));
	smallIcons[1] = new Pixmap(QPixmap(":/images/SetupAssistant/myspace.png"));
	smallIcons[2] = new Pixmap(QPixmap(":/images/SetupAssistant/orkut.png"));
	smallIcons[3] = new Pixmap(QPixmap(":/images/SetupAssistant/twitter.png"));
	smallIcons[4] = new Pixmap(QPixmap(":/images/SetupAssistant/ubuntuone.png"));
	smallIcons[5] = new Pixmap(QPixmap(":/images/SetupAssistant/yahoo.png"));

	StateMachine = new QStateMachine;
	initialState = new QState;
	finalState = new QState;

	scene->addItem(logo);
	scene->addItem(glow);

	for(int i=0;i<8;i++) {
		largeIcons[i]->setPos(165,165);
		scene->addItem(largeIcons[i]);
	}
	for(int i=0;i<6;i++) {
		smallIcons[i]->setPos(165,165);
		scene->addItem(smallIcons[i]);
	}


	initialState->assignProperty(logo, "pos", QVariant(QPointF(0,0)));
	initialState->assignProperty(glow, "pos", QVariant(QPointF(0,0)));
	initialState->assignProperty(glow, "opacity", QVariant(0.0));

	for(int i=0;i<8;i++) {
		initialState->assignProperty(largeIcons[i], "pos", QVariant(QPointF(165,165)));
		initialState->assignProperty(largeIcons[i], "opacity", QVariant(0.0));
		initialState->assignProperty(largeIcons[i], "scale", QVariant(0.0));
	}
	for(int i=0;i<6;i++) {
		initialState->assignProperty(smallIcons[i], "pos", QVariant(QPointF(165,165)));
		initialState->assignProperty(smallIcons[i], "opacity", QVariant(0.0));
		initialState->assignProperty(smallIcons[i], "scale", QVariant(0.0));
	}

	finalState->assignProperty(logo, "pos", QVariant(QPointF(0,0)));
	finalState->assignProperty(glow, "pos", QVariant(QPointF(0,0)));
	finalState->assignProperty(glow, "opacity", QVariant(1.0));

	for(int i=0;i<8;i++) {
		finalState->assignProperty(largeIcons[i], "opacity", QVariant(1.0));
		finalState->assignProperty(largeIcons[i], "scale", QVariant(1.0));
	}
	for(int i=0;i<6;i++) {
		finalState->assignProperty(smallIcons[i], "opacity", QVariant(0.5));
		finalState->assignProperty(smallIcons[i], "scale", QVariant(1.0));
	}

	finalState->assignProperty(largeIcons[0], "pos", QVariant(QPointF(286,34)));
	finalState->assignProperty(largeIcons[1], "pos", QVariant(QPointF(48,271)));
	finalState->assignProperty(largeIcons[2], "pos", QVariant(QPointF(300,268)));
	finalState->assignProperty(largeIcons[3], "pos", QVariant(QPointF(2,156)));
	finalState->assignProperty(largeIcons[4], "pos", QVariant(QPointF(39,42)));
	finalState->assignProperty(largeIcons[5], "pos", QVariant(QPointF(329,151)));
	finalState->assignProperty(largeIcons[6], "pos", QVariant(QPointF(162,12)));
	finalState->assignProperty(largeIcons[7], "pos", QVariant(QPointF(170,325)));

	finalState->assignProperty(smallIcons[0], "pos", QVariant(QPointF(177,90)));
	finalState->assignProperty(smallIcons[1], "pos", QVariant(QPointF(255,123)));
	finalState->assignProperty(smallIcons[2], "pos", QVariant(QPointF(254,196)));
	finalState->assignProperty(smallIcons[3], "pos", QVariant(QPointF(105,126)));
	finalState->assignProperty(smallIcons[4], "pos", QVariant(QPointF(101,193)));
	finalState->assignProperty(smallIcons[5], "pos", QVariant(QPointF(181,239)));



	timer = new QTimer;
	timer->setSingleShot(true);
	transition = initialState->addTransition(timer, SIGNAL(timeout()), finalState);

	transition->addAnimation(new QPropertyAnimation(glow, "opacity"));

	for(int i=0;i<8;i++) {
		animation = new QPropertyAnimation(largeIcons[i], "opacity");
		animation->setDuration(750);
		transition->addAnimation(animation);
		animation = new QPropertyAnimation(largeIcons[i], "pos");
		animation->setDuration(750);
		transition->addAnimation(animation);
		animation = new QPropertyAnimation(largeIcons[i], "scale");
		animation->setDuration(750);
		transition->addAnimation(animation);
	}
	for(int i=0;i<6;i++) {
		animation = new QPropertyAnimation(smallIcons[i], "opacity");
		animation->setDuration(650);
		transition->addAnimation(animation);
		animation = new QPropertyAnimation(smallIcons[i], "pos");
		animation->setDuration(650);
		transition->addAnimation(animation);
		animation = new QPropertyAnimation(smallIcons[i], "scale");
		animation->setDuration(650);
		transition->addAnimation(animation);
	}

	StateMachine->addState(initialState);
	StateMachine->addState(finalState);
	StateMachine->setInitialState(initialState);

	setScene(scene);
	setFixedSize(790,410);
	StateMachine->start();
}

void WebRenderAnimation::startAnimation() {
	timer->start(550);
}

