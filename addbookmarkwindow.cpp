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

#include "addbookmarkwindow.h"
#include "bookmark.h"
AddBookmarkWindow::AddBookmarkWindow()
{
	titleEdit = new QLineEdit;
	urlEdit = new QLineEdit;
	urlEdit->setText("http://");
	titleLabel = new QLabel(tr("Title:"));
	urlLabel = new QLabel(tr("Address:"));
	addButton = new QPushButton(tr("Add"));
	closeButton = new QPushButton(tr("Close"));
	titleLayout = new QHBoxLayout;
	urlLayout = new QHBoxLayout;
	buttonLayout = new QHBoxLayout;
	mainLayout = new QVBoxLayout;

	titleLayout->addWidget(titleLabel);
	titleLayout->addWidget(titleEdit);
	urlLayout->addWidget(urlLabel);
	urlLayout->addWidget(urlEdit);
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(closeButton);
	mainLayout->addLayout(titleLayout);
	mainLayout->addLayout(urlLayout);
	mainLayout->addLayout(buttonLayout);
	mainLayout->setContentsMargins(5,25,5,5);
	setLayout(mainLayout);
        setTitle(tr("Add Bookmark"));
	setupConnections();
}

void AddBookmarkWindow::setupConnections()
{
	connect(addButton,SIGNAL(clicked()),this,SLOT(on_addButton_clicked()));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

void AddBookmarkWindow::on_addButton_clicked()
{
	Bookmark *bookmark = new Bookmark;
	bookmark->addData(Bookmark::Title,titleEdit->text());
	bookmark->addData(Bookmark::Address, urlEdit->text());
	emit addBookmark(bookmark);
	close();
}
