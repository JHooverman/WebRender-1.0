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

#include "bookmark.h"
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDataStream>

void Bookmark::addData(Field type, QString data)
{
	switch(type)
	{
		case Bookmark::Title:
			title = data;
		break;
		case Bookmark::Address:
			address = data;
		break;
		default:
			return;
	}
}

QString Bookmark::get(Field type)
{
	switch(type)
	{
		case Bookmark::Title:
			return title;
		break;
		case Bookmark::Address:
			return address;
		break;
		default:
			return QString();
	}
}

void Bookmark::readFromFile(QFile &file)
{
	if(!file.open(QIODevice::ReadOnly))
		return;
	QDataStream in(&file);
	in>>title;
	in>>address;
}

void Bookmark::saveToFile(QFile &file)
{
	if(!file.open(QIODevice::WriteOnly))
		return;
	QDataStream out(&file);
	out<<title;
	out<<address;
}
