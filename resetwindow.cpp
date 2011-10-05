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


#include "resetwindow.h"
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtWebKit/QWebSettings>

ResetWindow::ResetWindow()
{
	clearCacheCheckBox = new QCheckBox(tr("Clear cache"));
	clearCookiesCheckBox = new QCheckBox(tr("Clear cookies"));
	clearHistoryCheckBox = new QCheckBox(tr("Clear browsing history"));
	clearBookmarksCheckBox = new QCheckBox(tr("Clear bookmarks"));
	clearPreferencesCheckBox = new QCheckBox(tr("Clear preferences"));
	resetButton = new QPushButton(tr("Reset"));
	closeButton = new QPushButton(tr("Close"));
	buttonLayout = new QHBoxLayout;
	mainLayout = new QVBoxLayout;

	buttonLayout->addStretch();
	buttonLayout->addWidget(resetButton);
	buttonLayout->addWidget(closeButton);

	mainLayout->addWidget(clearCacheCheckBox);
	mainLayout->addWidget(clearCookiesCheckBox);
	mainLayout->addWidget(clearHistoryCheckBox);
	mainLayout->addWidget(clearBookmarksCheckBox);
	mainLayout->addWidget(clearPreferencesCheckBox);
	mainLayout->addLayout(buttonLayout);
        mainLayout->setContentsMargins(5,25,5,5);
	setLayout(mainLayout);
        setTitle("Reset Browser Settings");
	connect(resetButton,SIGNAL(clicked()),this,SLOT(doReset()));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

void ResetWindow::doReset()
{
	QDir dir = QDir::home();
	dir.cd(".WebRender");
	if(clearCacheCheckBox->checkState() == Qt::Checked)
	{
		dir.cd("Cache");
		deleteDir(dir.absolutePath());
		dir.cdUp();
	}
	if(clearCookiesCheckBox->checkState() == Qt::Checked)
	{
		dir.cd("Cookies");
		deleteDir(dir.absolutePath());
		dir.cdUp();
		dir.cd("LocalStorage");
		deleteDir(dir.absolutePath());
		dir.cdUp();
		dir.cd("OfflineStorage");
		deleteDir(dir.absolutePath());
		dir.cdUp();
	}
	if(clearHistoryCheckBox->checkState() == Qt::Checked)
		dir.remove("historyFile");
	if(clearBookmarksCheckBox->checkState() == Qt::Checked)
		dir.remove("bookmarksFile");
	if(clearPreferencesCheckBox->checkState() == Qt::Checked)
		dir.remove("preferencesFile");
}

void ResetWindow::deleteDir(QString dir)
{
	QDirIterator i(dir, QDirIterator::Subdirectories);
	QDir Dir(dir);
	while(i.hasNext())
	{
		i.next();
		Dir.remove(i.filePath());
	}
	
}
