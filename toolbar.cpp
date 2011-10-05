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

#include "toolbar.h"
#include <QtGui/QImage>
#include <QtGui/QLinearGradient>
#include <QtGui/QPen>
#include <QtGui/QPainter>

ToolBar::ToolBar(QWidget *parent) : QWidget(parent)
{
}

void ToolBar::paintEvent(QPaintEvent *event)
{
	QImage image(size(), QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(Qt::NoPen);
	QLinearGradient gradient(0,0,0,height());
	gradient.setColorAt(0.0,QColor("#000000")); //#EEEEEE
	gradient.setColorAt(1.0,QColor("#111111")); //#CCCCCC
	painter.setBrush(gradient);
	painter.drawRect(0,0,width(),height());
	QPainter WidgetPainter(this);
	WidgetPainter.drawImage(0,0,image);
}
