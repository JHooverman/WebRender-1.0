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


#include "ipfinder.h"
#include <QtCore/QUrl>

IpFinder::IpFinder()
{
	urlEdit = new QLineEdit;
	urlEdit->setText("http://");
	urlLabel = new QLabel(tr("Enter Url:"));
	findButton = new QPushButton(tr("Find"));
	closeButton = new QPushButton(tr("Close"));
	buttonLayout = new QHBoxLayout;
	urlLayout = new QHBoxLayout;
	mainLayout = new QVBoxLayout;
	urlLayout->addWidget(urlLabel);
	urlLayout->addWidget(urlEdit);
	buttonLayout->addStretch();
	buttonLayout->addWidget(findButton);
	buttonLayout->addWidget(closeButton);
	mainLayout->addLayout(urlLayout);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
	connect(findButton,SIGNAL(clicked()),this,SLOT(on_findButton_clicked()));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
	setWindowTitle("IP Address Finder");
}

void IpFinder::on_findButton_clicked()
{
	if(!urlEdit->text().isEmpty())
	{
		QUrl Url(urlEdit->text());
		emit openUrl(QString("http://www.ip-adress.com/ip_tracer/") + Url.host());
	}
}
