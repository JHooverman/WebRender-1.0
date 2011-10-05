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

#include "bookmarkswindow.h"
#include "bookmark.h"
#include <QtGui/QTreeWidgetItem>
#include <QtCore/QFile>
#include <QtCore/QDataStream>
#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include <iostream>

BookmarksWindow::BookmarksWindow()
{
	bookmarksTreeWidget = new QTreeWidget;
	addButton = new QPushButton(tr("Add"));
	closeButton = new QPushButton(tr("Close"));
	loadButton = new QPushButton(tr("Load"));
	saveButton = new QPushButton(tr("Save"));
	removeButton = new QPushButton(tr("Remove"));
	openButton = new QPushButton(tr("Open"));
	buttonsLayout = new QHBoxLayout;
	mainLayout = new QVBoxLayout;
	addBookmarkWindow = new AddBookmarkWindow;
	QTreeWidgetItem *item = new QTreeWidgetItem;
	item->setText(0, tr("Title"));
	item->setText(1,tr("Url"));
	bookmarksTreeWidget->setHeaderItem(item);
	buttonsLayout->addWidget(loadButton);
	buttonsLayout->addWidget(saveButton);
	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(removeButton);
	buttonsLayout->addWidget(openButton);
	buttonsLayout->addWidget(closeButton);
	mainLayout->addWidget(bookmarksTreeWidget);
	mainLayout->addLayout(buttonsLayout);
	mainLayout->setContentsMargins(5,25,5,5);
	setLayout(mainLayout);
	setTitle("WebRender Bookmarks");
	setupConnections();
}

void BookmarksWindow::addBookmark(QString title, QString url)
{
	QTreeWidgetItem *item = new QTreeWidgetItem;
	item->setText(0, title);
	item->setText(1, url);
	bookmarksTreeWidget->addTopLevelItem(item);
}

void BookmarksWindow::addBookmark(Bookmark *bookmark)
{
	QTreeWidgetItem *item = new QTreeWidgetItem;
	item->setText(0, bookmark->get(Bookmark::Title));
	item->setText(1, bookmark->get(Bookmark::Address));
	bookmarksTreeWidget->addTopLevelItem(item);
}

bool BookmarksWindow::saveBookmarksToFile(QFile &file)
{
	if(!file.open(QIODevice::WriteOnly))
		return false;
	QDataStream out(&file);
	int i;
	for(i =0; i<bookmarksTreeWidget->topLevelItemCount(); i++)
	{
		out<<bookmarksTreeWidget->topLevelItem(i)->text(0);
		out<<bookmarksTreeWidget->topLevelItem(i)->text(1);
	}
	return true;
}

bool BookmarksWindow::loadBookmarksFromFile(QFile &file)
{
	if(!file.open(QIODevice::ReadOnly))
		return false;
	QDataStream in(&file);
	QString text;
	int i=0;
	QTreeWidgetItem *item;
	while(!in.atEnd())
	{
		item = new QTreeWidgetItem;
		in>>text;
		item->setText(0,text);
		text.clear();
		in>>text;
		item->setText(1,text);
		bookmarksTreeWidget->insertTopLevelItem(i,item);
		i++;
	}
	return true;
}

Bookmark* BookmarksWindow::getBookmarkAt(int index)
{
	Bookmark *bookmark = new Bookmark;
	bookmark->addData(Bookmark::Title, bookmarksTreeWidget->topLevelItem(index)->text(0));
	bookmark->addData(Bookmark::Title, bookmarksTreeWidget->topLevelItem(index)->text(1));
	return bookmark;
}
void BookmarksWindow::on_addButton_clicked()
{
	addBookmarkWindow->show();
}
void BookmarksWindow::addBookmarkItem(Bookmark *bookmark)
{
	addBookmark(bookmark);
}
void BookmarksWindow::on_removeButton_clicked()
{
	delete bookmarksTreeWidget->currentItem();
}
void BookmarksWindow::on_closeButton_clicked()
{
	close();
}

void BookmarksWindow::on_saveButton_clicked()
{
	if(bookmarksTreeWidget->currentItem() != NULL)
	{
		QString fileName = QFileDialog::getSaveFileName(this,tr("Save bookmark"),QDir::homePath(),tr("WebRender Bookmark Files (*.wrbm)"));
		if(!fileName.isEmpty())
		{
			if(!fileName.endsWith(".wrbm"))
				fileName = fileName + ".wrbm";
			QFile file(fileName);
			Bookmark *bm = new Bookmark;
			bm->addData(Bookmark::Title, bookmarksTreeWidget->currentItem()->text(0));
			bm->addData(Bookmark::Address, bookmarksTreeWidget->currentItem()->text(1));
			bm->saveToFile(file);
			delete bm;
		}
	}
}

void BookmarksWindow::on_loadButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Save bookmark"),QDir::homePath(),tr("WebRender Bookmark Files (*.wrbm)"));
	if(!fileName.isEmpty())
	{
		QFile file(fileName);
		Bookmark *bm = new Bookmark;
		bm->readFromFile(file);
		QTreeWidgetItem *item = new QTreeWidgetItem;
		item->setText(0,bm->get(Bookmark::Title));
		item->setText(1,bm->get(Bookmark::Address));
		bookmarksTreeWidget->addTopLevelItem(item);
		delete bm;
	}
}

void BookmarksWindow::on_openButton_clicked()
{
	if(bookmarksTreeWidget->currentItem() != NULL)
		emit openUrlRequest(bookmarksTreeWidget->currentItem()->text(1));
}
void BookmarksWindow::setupConnections()
{
	connect(addButton,SIGNAL(clicked()),this, SLOT(on_addButton_clicked()));
	connect(addBookmarkWindow, SIGNAL(addBookmark(Bookmark *)), this, SLOT(addBookmarkItem(Bookmark *)));
	connect(removeButton,SIGNAL(clicked()),this, SLOT(on_removeButton_clicked()));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(on_closeButton_clicked()));
	connect(loadButton,SIGNAL(clicked()),this,SLOT(on_loadButton_clicked()));
	connect(saveButton,SIGNAL(clicked()),this,SLOT(on_saveButton_clicked()));
	connect(openButton,SIGNAL(clicked()),this,SLOT(on_openButton_clicked()));
}
