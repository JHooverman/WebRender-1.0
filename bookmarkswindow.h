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

#ifndef BOOKMARKSWINDOW_H
#define BOOKMARKSWINDOW_H
#include "infowidget.h"
#include <QtGui/QTreeWidget>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtCore/QFile>
#include "bookmark.h"
#include "addbookmarkwindow.h"

class BookmarksWindow : public InfoWidget
{
	Q_OBJECT
	public:
	BookmarksWindow();
	void addBookmark(QString title, QString url);
	Bookmark* getBookmarkAt(int index);
	bool saveBookmarksToFile(QFile &file);
	bool loadBookmarksFromFile(QFile &file);
	public slots:
	void addBookmark(Bookmark *bookmark);
	private:
	void setupConnections();
	AddBookmarkWindow *addBookmarkWindow;
	QTreeWidget *bookmarksTreeWidget;
	QPushButton *addButton;
	QPushButton *closeButton;
	QPushButton *loadButton;
	QPushButton *saveButton;
	QPushButton *removeButton;
	QPushButton *openButton;
	QHBoxLayout *buttonsLayout;
	QVBoxLayout *mainLayout;
	private slots:
	void on_addButton_clicked();
	void on_removeButton_clicked();
	void on_closeButton_clicked();
	void on_loadButton_clicked();
	void on_saveButton_clicked();
	void on_openButton_clicked();
	void addBookmarkItem(Bookmark *bookmark);
	signals:
	void openUrlRequest(QString url);
};
#endif
