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
#include "backforward.h"
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QPen>
#include <QtGui/QLinearGradient>

BackForwardButtonGroup::BackForwardButtonGroup(QWidget *parent) : QWidget(parent)
{
	backImage = QImage(":/icons/arrow-left.png").scaled(16,16);
	forwardImage = QImage(":/icons/arrow-right.png").scaled(16,16);
	mousePressed = false;
	setFixedSize(60,20);
}

void BackForwardButtonGroup::paintEvent(QPaintEvent *event)
{
	QImage image(size(),QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(QColor("#A1A1A1"),1,Qt::SolidLine,Qt::RoundCap));
	QLinearGradient gradient(0,0,0,20);
	gradient.setColorAt(0.0, QColor("#FFFFFF"));
	gradient.setColorAt(1.0, QColor("#CCCCFF"));
	painter.setBrush(gradient);
	painter.drawRect(0,0,60,20);
	painter.drawImage(6,2, backImage);
	painter.drawImage(38,2, forwardImage);
	painter.drawLine(30,0,30,20);

	QLinearGradient clickedGradient(0,0,0,20);
	clickedGradient.setColorAt(0.0,QColor("#FFFFFF"));
	clickedGradient.setColorAt(1.0,QColor("#CCFFCC"));
	if(mousePressed)
	{
		if(mousePressPos > 30)
		{
			painter.setBrush(clickedGradient);
			painter.drawRect(30,0,30,20);
			painter.drawImage(38,2, forwardImage);
		}
		else
		{
			painter.setBrush(clickedGradient);
			painter.drawRect(0,0,30,20);
			painter.drawImage(6,2, backImage);
		}
	}

	QPainter WidgetPainter(this);
	WidgetPainter.drawImage(0,0,image);
}

void BackForwardButtonGroup::mousePressEvent(QMouseEvent *event)
{
	if(event->button() & Qt::LeftButton)
	{
		mousePressed = true;
		mousePressPos = event->pos().x();
		if(mousePressPos > 30)
			emit forwardButtonClicked();
		else
			emit backButtonClicked();
		update();
	}
	else
	{
		mousePressed = false;
		update();
	}
}

void BackForwardButtonGroup::mouseReleaseEvent(QMouseEvent *event)
{
	mousePressed = false;
	update();
}
