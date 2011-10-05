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

#ifndef ADDBOOKMARKWINDOW_H
#define ADDBOOKMARKWINDOW_H
#include "infowidget.h"
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include "bookmark.h"

class AddBookmarkWindow : public InfoWidget
{
	Q_OBJECT
	public:
	AddBookmarkWindow();
	private:
	void setupConnections();
	QLineEdit *titleEdit;
	QLineEdit *urlEdit;
	QLabel *titleLabel;
	QLabel *urlLabel;
	QPushButton *addButton;
	QPushButton *closeButton;
	QHBoxLayout *titleLayout;
	QHBoxLayout *urlLayout;
	QHBoxLayout *buttonLayout;
	QVBoxLayout *mainLayout;
	private slots:
	void on_addButton_clicked();
	signals:
	void addBookmark(Bookmark *bookmark);
};
#endif
