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

#include "pixmap.h"

Pixmap::Pixmap(const QPixmap &pix) : QGraphicsObject(), p(pix)
{}
void Pixmap::paint(QPainter *painter,const QStyleOptionGraphicsItem *, QWidget *) {
	painter->drawPixmap(QPointF(), p);
}
QRectF Pixmap::boundingRect() const {
	return QRectF( QPointF(0, 0), p.size());
}

void Pixmap::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	if(event->buttons() & Qt::LeftButton) {
		emit clicked();
	}
}
