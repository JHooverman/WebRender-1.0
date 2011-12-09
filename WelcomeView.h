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

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include "pixmap.h"
#include <QtCore/QStateMachine>
#include <QtCore/QSignalTransition>
#include <QtCore/QState>
#include <QtCore/QTimer>
#include <QtCore/QPropertyAnimation>

class WelcomeView : public QGraphicsView {
	Q_OBJECT
	public:
	WelcomeView(QWidget *parent = 0);
	public slots:
	void startAnimation();
	private:
	QGraphicsScene *scene;
	Pixmap *welcomePixmaps[15];
	Pixmap *bgPixmap;
	Pixmap *nextPixmap;
	QStateMachine *StateMachine;
	QState *initialState;
	QState *visibleState;
	QSignalTransition *transition;
	QTimer *timer;
	signals:
	void nextClicked();
};
#endif
