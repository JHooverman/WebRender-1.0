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

#include "addressbar.h"
#include <QtCore/QMargins>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <iostream>
AddressBarWidget::AddressBarWidget(QWidget *parent) : QLineEdit(parent)
{

        setStyleSheet(QString("QLineEdit { border: 1px solid gray; border-radius: 10px; padding: 0 8px; background: white; selection-background-color: darkgray;}"));
	GoArrow = QImage(":/icons/arrow-right.png").scaled(16,16);
        setFixedHeight(20);
}

void AddressBarWidget::paintEvent(QPaintEvent *event)
{
	QLineEdit::paintEvent(event);
	if(isModified())
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setPen(QPen(QColor("#DDDDDD"), 1, Qt::SolidLine, Qt::RoundCap));
		painter.setBrush(QBrush(QColor("#CCCCCC"), Qt::SolidPattern));
                painter.drawRoundedRect(width() - 43,3,40,height()-5,7,7);
		painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
		//painter.drawText(QPoint(width()- 35,16),"Go");
		painter.drawImage(width()- 30,3,GoArrow);
	}
}

void AddressBarWidget::mouseMoveEvent(QMouseEvent *event)
{
	QLineEdit::mouseMoveEvent(event);
	if(isModified())
	{
		if(event->pos().x() > (width() - 43))
			setCursor(Qt::PointingHandCursor);
		else
		{
			setCursor(Qt::IBeamCursor);
		}
	}
}

void AddressBarWidget::mousePressEvent(QMouseEvent *event)
{
	QLineEdit::mousePressEvent(event);
	setCursor(Qt::IBeamCursor);
	if(isModified())
	{
		if(event->pos().x() > (width() - 43))
		{
			emit GoClicked();
			//std::cout<<"DEBUG: click() emitted\n";
		}
	}
}
