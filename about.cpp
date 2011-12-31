#include "about.h"
#include <QtGui/QPixmap>
#include <QtGui/QFont>
#include <QtCore/QPointF>

About::About(QWidget *parent) : QGraphicsView(parent) {
	scene = new QGraphicsScene;
	scene->setSceneRect(0,0,500,300);
	bgPixmap = new Pixmap(QPixmap(":/images/AboutWindow/background.png"));
	bgPixmap->setPos(0,0);
	icon = new Pixmap(QPixmap(":/icons/webrender.png"));
	closeButton = new Pixmap(QPixmap(":/images/AboutWindow/close.png"));


	headerTextItem = new QGraphicsTextItem(tr("WebRender"));
	headerTextItem->setFont(QFont("sans",25));
	versionTextItem = new QGraphicsTextItem(tr("Release Candidate 4"));
	versionTextItem->setFont(QFont("sans",10));
	subHeaderTextItem = new QGraphicsTextItem(tr("Brought to you by,"));
	subHeaderTextItem->setFont(QFont("sans",10, 75));
	textItem1 = new QGraphicsTextItem(tr("Anand Bose (Software Developer)"));
	textItem1->setFont(QFont("sans",10));
	textItem2 = new QGraphicsTextItem(tr("Jaideep Sasi (Mac OS X deployment)"));
	textItem2->setFont(QFont("sans",10));

	timer = new QTimer;
	timer->setSingleShot(true);

	stateMachine = new QStateMachine;
	initialState = new QState;
	finalState = new QState;

	initialState->assignProperty(icon, "pos", QPointF(122,5));
	initialState->assignProperty(closeButton, "pos", QPointF(375,270));
	initialState->assignProperty(headerTextItem, "pos", QPointF(255,0));
	initialState->assignProperty(versionTextItem, "pos", QPointF(255,0));
	initialState->assignProperty(subHeaderTextItem, "pos", QPointF(255,0));
	initialState->assignProperty(textItem1, "pos", QPointF(255,0));
	initialState->assignProperty(textItem2, "pos", QPointF(255,0));

	initialState->assignProperty(icon, "opacity", 0.0);
	initialState->assignProperty(closeButton, "opacity", 0.0);
	initialState->assignProperty(headerTextItem, "opacity", 0.0);
	initialState->assignProperty(versionTextItem, "opacity", 0.0);
	initialState->assignProperty(subHeaderTextItem, "opacity", 0.0);
	initialState->assignProperty(textItem1, "opacity", 0.0);
	initialState->assignProperty(textItem2, "opacity", 0.0);

	finalState->assignProperty(icon, "pos", QPointF(0,5));
	finalState->assignProperty(closeButton, "pos", QPointF(425,270));
	finalState->assignProperty(headerTextItem, "pos", QPointF(255,45));
	finalState->assignProperty(versionTextItem, "pos", QPointF(255,80));
	finalState->assignProperty(subHeaderTextItem, "pos", QPointF(255,125));
	finalState->assignProperty(textItem1, "pos", QPointF(255,141));
	finalState->assignProperty(textItem2, "pos", QPointF(255,157));

	finalState->assignProperty(icon, "opacity", 1.0);
	finalState->assignProperty(closeButton, "opacity", 1.0);
	finalState->assignProperty(headerTextItem, "opacity", 1.0);
	finalState->assignProperty(versionTextItem, "opacity", 0.6);
	finalState->assignProperty(subHeaderTextItem, "opacity", 1.0);
	finalState->assignProperty(textItem1, "opacity", 1.0);
	finalState->assignProperty(textItem2, "opacity", 1.0);

	transition = initialState->addTransition(timer, SIGNAL(timeout()), finalState);

	animation = new QPropertyAnimation(icon, "pos");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(closeButton, "pos");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(headerTextItem, "pos");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(versionTextItem, "pos");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(subHeaderTextItem, "pos");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(textItem1, "pos");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(textItem2, "pos");
	animation->setDuration(800);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(icon, "opacity");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(closeButton, "opacity");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(headerTextItem, "opacity");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(versionTextItem, "opacity");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(subHeaderTextItem, "opacity");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(textItem1, "opacity");
	animation->setDuration(800);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(textItem2, "opacity");
	animation->setDuration(800);
	transition->addAnimation(animation);


	stateMachine->addState(initialState);
	stateMachine->addState(finalState);
	stateMachine->setInitialState(initialState);

	scene->addItem(bgPixmap);
	scene->addItem(icon);
	scene->addItem(closeButton);
	scene->addItem(headerTextItem);
	scene->addItem(versionTextItem);
	scene->addItem(subHeaderTextItem);
	scene->addItem(textItem1);
	scene->addItem(textItem2);


	setScene(scene);
	setFixedSize(505,305);
	setWindowTitle(tr("About WebRender"));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
	connect(closeButton, SIGNAL(clicked()), stateMachine, SLOT(stop()));
}

void About::showAnimated() {
	stateMachine->start();
	timer->start(100);
	show();
}
