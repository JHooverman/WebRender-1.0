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

#ifndef HISTORYVIEWER_H
#define HISTORYVIEWER_H
#include "infowidget.h"
#include <QtGui/QTreeWidget>
#include <QtWebKit/QWebHistory>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>

class HistoryViewer : public InfoWidget
{
    Q_OBJECT
public:
    HistoryViewer();
    void setHistory(QWebHistory *history);
public slots:
    void updateHistoryLists();
private:
    QWebHistory *WebHistory;
    QList<QWebHistoryItem> historylistitems;
    QDateTime currentDate;
    QDateTime prevDate;
    QTreeWidgetItem *currentTreeItem;
    QTreeWidgetItem *currentChildItem;
    void generateList(QWebHistory *history, QTreeWidget *historylist);
    QTreeWidget *historylist;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
    QPushButton *goButton;
    QPushButton *closeButton;
private slots:
    void goButton_clicked();
    void doubleClickedOnItem(QTreeWidgetItem *item, int column);
signals:
    void openLinkRequested(QString &text);
};

#endif // HISTORYVIEWER_H

/* Documentation
   This class displays history from QWebHistory instance.
   After creation of an instance, you need to initialise using HistoryViewer::setHistory(QWebHistory *history)
   For refreshing, call HistoryViewer::updateHistoryLists() [public slot]
   This class was brought to you by Anand Bose <anandbose@in.com>
*/
