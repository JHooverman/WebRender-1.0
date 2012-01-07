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

#include "historyviewer.h"
#include <QtWebKit/QWebHistoryItem>
#include <QtCore/QList>
#include <QtCore/QListIterator>
#include <QtCore/QDateTime>
#include <QtGui/QTreeWidgetItem>
#include <QtCore/QDate>
#include <QtCore/QUrl>
#include <QtCore/QTime>

HistoryViewer::HistoryViewer()
{
    mainLayout = new QVBoxLayout;
    historylist = new QTreeWidget;
    QTreeWidgetItem *headerItem = historylist->headerItem();
    headerItem->setText(0,tr("Website"));
    headerItem->setText(1,tr("Address"));
    goButton = new QPushButton(tr("Go"));
    closeButton = new QPushButton(tr("Close"));
    buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(goButton);
    buttonLayout->addWidget(closeButton);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(goButton, SIGNAL(clicked()), this, SLOT(goButton_clicked()));
    connect(historylist, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(doubleClickedOnItem(QTreeWidgetItem*,int)));
    mainLayout->addWidget(historylist);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setContentsMargins(5,25,5,5);
    setLayout(mainLayout);
    setTitle(tr("History"));
    resize(400,300);
}

void HistoryViewer::generateList(QWebHistory *history, QTreeWidget *historylist)
{
    historylistitems = history->items();
    QListIterator<QWebHistoryItem> i(historylistitems);
    QWebHistoryItem currentItem(history->backItem());
    while(i.hasNext())
    {
         currentItem = i.next();
         currentTreeItem = new QTreeWidgetItem;
         currentTreeItem->setText(0,currentItem.title());
         currentTreeItem->setText(1,currentItem.originalUrl().toString());
         historylist->addTopLevelItem(currentTreeItem);
    }
}
void HistoryViewer::setHistory(QWebHistory *history)
{
    WebHistory = history;
    generateList(history,historylist);
}
void HistoryViewer::updateHistoryLists()
{
    historylist->clear();
    generateList(WebHistory,historylist);
}
void HistoryViewer::goButton_clicked()
{
    QTreeWidgetItem *currentItem = historylist->currentItem();
    QString address = currentItem->text(1);
    emit openLinkRequested(address);
}
void HistoryViewer::doubleClickedOnItem(QTreeWidgetItem *item, int column)
{
    QString address = item->text(1);
    emit openLinkRequested(address);
}
