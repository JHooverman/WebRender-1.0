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

#include "pagesourceviewer.h"
#include <QtWebKit/QWebFrame>

SourceView::SourceView()
{
    mainLayout = new QVBoxLayout;
    textEdit = new QTextEdit;
    buttonLayout = new QHBoxLayout;
    closeButton = new QPushButton(tr("Close"));
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    textEdit->setReadOnly(true);
    mainLayout->addWidget(textEdit);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setContentsMargins(5,25,5,5);
    setLayout(mainLayout);
    setTitle("Page Source");
    resize(500,500);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}
void SourceView::setPage(QWebPage *page)
{
    textEdit->setPlainText(page->mainFrame()->toHtml());
}
