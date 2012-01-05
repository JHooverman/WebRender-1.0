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
#ifndef TABVIEW_H
#define TABVIEW_H
#include <QtGui/QWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPaintEvent>
#include <QtGui/QMenu>
#include "tab.h"
class TabView : public QWidget
{
	Q_OBJECT
	public:
	TabView(QWidget *parent = 0);
	void addTab(Tab *tab);
	void setMenu(QMenu *menu);
	private:
	QHBoxLayout *tabLayout;
	QHBoxLayout *buttonLayout;
	QPushButton *addTabButton;
	QPushButton *menuButton;
	protected:
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	signals:
	void addTabPressed();
};
#endif
