/*
 * Copyright 2011 Anand Bose <anandbose@in.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

#include "WelcomeView.h"

WelcomeView::WelcomeView(QWidget *parent) : QGraphicsView(parent) {
	scene = new QGraphicsScene;
	timer = new QTimer;
	timer->setSingleShot(true);
	scene->setSceneRect(QRectF(0,0,800,600));
	nextPixmap = new Pixmap(QPixmap(":/images/SetupAssistant/next.png"));
	bgPixmap = new Pixmap(QPixmap(":/images/SetupAssistant/webrender-bg.png"));
	welcomePixmaps[0] = new Pixmap(QPixmap(":/images/SetupAssistant/01.png"));
	welcomePixmaps[1] = new Pixmap(QPixmap(":/images/SetupAssistant/02.png"));
	welcomePixmaps[2] = new Pixmap(QPixmap(":/images/SetupAssistant/03.png"));
	welcomePixmaps[3] = new Pixmap(QPixmap(":/images/SetupAssistant/04.png"));
	welcomePixmaps[4] = new Pixmap(QPixmap(":/images/SetupAssistant/05.png"));
	welcomePixmaps[5] = new Pixmap(QPixmap(":/images/SetupAssistant/06.png"));
	welcomePixmaps[6] = new Pixmap(QPixmap(":/images/SetupAssistant/07.png"));
	welcomePixmaps[7] = new Pixmap(QPixmap(":/images/SetupAssistant/08.png"));
	welcomePixmaps[8] = new Pixmap(QPixmap(":/images/SetupAssistant/09.png"));
	welcomePixmaps[9] = new Pixmap(QPixmap(":/images/SetupAssistant/10.png"));
	welcomePixmaps[10] = new Pixmap(QPixmap(":/images/SetupAssistant/11.png"));
	welcomePixmaps[11] = new Pixmap(QPixmap(":/images/SetupAssistant/12.png"));
	welcomePixmaps[12] = new Pixmap(QPixmap(":/images/SetupAssistant/13.png"));
	welcomePixmaps[13] = new Pixmap(QPixmap(":/images/SetupAssistant/14.png"));
	welcomePixmaps[14] = new Pixmap(QPixmap(":/images/SetupAssistant/15.png"));

	scene->addItem(bgPixmap);
	bgPixmap->setPos(0,0);
	for(int i =0;i<15;i++) scene->addItem(welcomePixmaps[i]);

	scene->addItem(nextPixmap);

	welcomePixmaps[0]->setPos(150,165);
	welcomePixmaps[1]->setPos(52,104);
	welcomePixmaps[2]->setPos(0,17);
	welcomePixmaps[3]->setPos(324,19);
	welcomePixmaps[4]->setPos(7,374);
	welcomePixmaps[5]->setPos(613,15);
	welcomePixmaps[6]->setPos(464,383);
	welcomePixmaps[7]->setPos(456,119);
	welcomePixmaps[8]->setPos(71,483);
	welcomePixmaps[9]->setPos(509,475);
	welcomePixmaps[10]->setPos(358,486);
	welcomePixmaps[11]->setPos(800,600);//Avoided
	welcomePixmaps[12]->setPos(600,600);//Avoided
	welcomePixmaps[13]->setPos(69,292);
	welcomePixmaps[14]->setPos(403,284);


	StateMachine = new QStateMachine;
	initialState = new QState;
	visibleState = new QState;

	for(int i=0 ;i<15; i++) {
		if(i==0) {
			initialState->assignProperty(welcomePixmaps[i], "opacity", QVariant(0.0));
			initialState->assignProperty(welcomePixmaps[i], "scale", QVariant(0.5));
			visibleState->assignProperty(welcomePixmaps[i], "scale", QVariant(1.0));
			visibleState->assignProperty(welcomePixmaps[i], "opacity", QVariant(1.0));
		} else {
			initialState->assignProperty(welcomePixmaps[i], "opacity", QVariant(0.0));
			initialState->assignProperty(welcomePixmaps[i], "scale", QVariant(0.25));
			visibleState->assignProperty(welcomePixmaps[i], "scale", QVariant(0.5));
			visibleState->assignProperty(welcomePixmaps[i], "opacity", QVariant(0.5));
		}
	}

	initialState->assignProperty(nextPixmap, "opacity", QVariant(0.0));
	initialState->assignProperty(nextPixmap, "pos", QVariant(QPointF(685,542)));

	visibleState->assignProperty(nextPixmap, "opacity", QVariant(1.0));
	visibleState->assignProperty(nextPixmap, "pos", QVariant(QPointF(742,542)));

	StateMachine->addState(initialState);
	StateMachine->addState(visibleState);
	StateMachine->setInitialState(initialState);

	transition = initialState->addTransition(timer,SIGNAL(timeout()),visibleState);

	QPropertyAnimation *animation;

	for(int i=0;i<15;i++) {
		animation = new QPropertyAnimation(welcomePixmaps[i], "scale");
		animation->setDuration(750);
		transition->addAnimation(animation);
		animation = new QPropertyAnimation(welcomePixmaps[i], "opacity");
		animation->setDuration(750);
		transition->addAnimation(animation);
	}

	animation = new QPropertyAnimation(nextPixmap, "pos");
	animation->setDuration(750);
	transition->addAnimation(animation);
	animation = new QPropertyAnimation(nextPixmap, "opacity");
	animation->setDuration(750);
	transition->addAnimation(animation);

	setScene(scene);
	setFixedSize(810,610);
	StateMachine->start();

	connect(nextPixmap,SIGNAL(clicked()),this,SIGNAL(nextClicked()));
}

void WelcomeView::startAnimation() {
	timer->start(250);
}

