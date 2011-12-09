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
#include "about.h"
#include <QtGui/QPixmap>

AboutDialog::AboutDialog(QWidget *parent)
{
	imageLabel = new QLabel;
	imageLabel->setPixmap(QPixmap(":/icons/webrender2.png").scaled(64,64));
	imageLayout = new QHBoxLayout;
	webrenderLayout = new QHBoxLayout;
	versionLayout = new QHBoxLayout;
	authorNameLayout = new QHBoxLayout;
	authorEmailLayout = new QHBoxLayout;
	buttonLayout = new QHBoxLayout;
	webrenderLabel = new QLabel(tr("<b>WebRender</b>"));
	versionLabel = new QLabel(tr("Version 1.0 RC3"));
	authorNameLabel = new QLabel(tr("by <b>Anand Bose</b>"));
	authorEmailLabel = new QLabel(tr("Email: anandbose@in.com"));
	closeButton = new QPushButton(tr("Close"));
	mainLayout = new QVBoxLayout;

	imageLayout->addStretch();
	imageLayout->addWidget(imageLabel);
	imageLayout->addStretch();

	webrenderLayout->addStretch();
	webrenderLayout->addWidget(webrenderLabel);
	webrenderLayout->addStretch();

	versionLayout->addStretch();
	versionLayout->addWidget(versionLabel);
	versionLayout->addStretch();

	authorNameLayout->addStretch();
	authorNameLayout->addWidget(authorNameLabel);
	authorNameLayout->addStretch();

	authorEmailLayout->addStretch();
	authorEmailLayout->addWidget(authorEmailLabel);
	authorEmailLayout->addStretch();

	buttonLayout->addStretch();
	buttonLayout->addWidget(closeButton);
	buttonLayout->addStretch();


	mainLayout->addLayout(imageLayout);
	mainLayout->addLayout(webrenderLayout);
	mainLayout->addLayout(versionLayout);
	mainLayout->addLayout(authorNameLayout);
	mainLayout->addLayout(authorEmailLayout);
	mainLayout->addLayout(buttonLayout);
	mainLayout->setContentsMargins(5,25,5,5);
	setLayout(mainLayout);
	setTitle("About WebRender");
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}
