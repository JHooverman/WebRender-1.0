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
#include "tabview.h"
#include <QtGui/QIcon>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QImage>

TabView::TabView(QWidget *parent) : QWidget(parent)
{
	tabLayout = new QHBoxLayout;
	tabLayout->setAlignment(Qt::AlignLeft);
	tabLayout->setContentsMargins(1,2,5,0);
	addTabButton = new QPushButton();
	addTabButton->setFlat(true);
	addTabButton->setIcon(QIcon(":/icons/addtab.png"));
	addTabButton->setMaximumHeight(20);
	addTabButton->setMaximumWidth(20);
	tabLayout->addWidget(addTabButton);
	connect(addTabButton,SIGNAL(clicked()),this,SIGNAL(addTabPressed()));
	setLayout(tabLayout);
}

void TabView::addTab(Tab *tab)
{
	tabLayout->addWidget(tab);
	connect(tab,SIGNAL(tabCloseRequested()),tab,SLOT(close()));
}


void TabView::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);
	this->update();
}

void TabView::paintEvent(QPaintEvent *event)
{
	QImage image(size(), QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&image);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
	painter.drawRect(0,0,width(),height());
	QPainter WidgetPainter(this);
	WidgetPainter.drawImage(0,0,image);
	QWidget::paintEvent(event);
}

