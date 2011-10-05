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

#include "infowidget.h"
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QPen>
#include <QtGui/QLinearGradient>
#include <QtGui/QBitmap>
#include <QtGui/QCursor>
#include <iostream>

InfoWidget::InfoWidget(QWidget *parent) : QWidget(parent)
{
	parentWidget = parent;
	pressed = false;
	titleSet = false;
	setWindowFlags(Qt::FramelessWindowHint | Qt::SplashScreen);
	setWindowOpacity(0.93);
}

void InfoWidget::paintEvent(QPaintEvent *event)
{
	image = new QImage(size(), QImage::Format_ARGB32_Premultiplied);
	QPainter painter(image);
	painter.setRenderHint(QPainter::Antialiasing,true);
	painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
	QLinearGradient gradient(0,0,0,height());
	gradient.setColorAt(0.0,QColor("#FFFFFF"));
	gradient.setColorAt(1.0,QColor("#DDDDDD"));
	painter.setBrush(gradient);
	painter.drawRect(0,0,width(),height());
	QLinearGradient titleGradient(1,1,1,21);
	titleGradient.setColorAt(0.0,QColor("#DDDDDD"));
	titleGradient.setColorAt(1.0,QColor("#BBBBBB"));
	painter.setPen(Qt::NoPen);
	painter.setBrush(titleGradient);
	painter.drawRect(1,1,width()-2,20);

	painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
	if(titleSet)
	{
		painter.drawText(30,18,titleString);
	}

	QPainter WidgetPainter(this);
	WidgetPainter.drawImage(0,0,*image);
}
void InfoWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() & Qt::LeftButton)
		pressed = true;
	else
		pressed = false;
	lastPos = event->pos();
}
void InfoWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(pressed)
	{
		move(QCursor::pos() - lastPos);
	}
}

void InfoWidget::setTitle(QString title)
{
	titleString = title;
	titleSet = true;
	update();
}
