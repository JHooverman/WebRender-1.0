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
#ifndef TAB_H
#define TAB_H
#include <QtGui/QWidget>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtCore/QString>
#include <QtGui/QMouseEvent>
#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtWebKit/QWebView>
#include <QtGui/QCloseEvent>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "bookmark.h"
#include "downloader.h"

class Tab : public QWidget
{
	Q_OBJECT
	public:
	Tab(QWidget *parent = 0);
	void setTabIndex(int x);
	int tabIndex();
	void assignWebView(QWebView *view);
	public slots:
	void setText(QString t);
	void setIcon(QIcon i);
	void setTabIcon();
	void setCurrentTab();
	private slots:
	void loadStarted();
	void loadFinished(bool ok);
	void loadProgress(int progress);
	void showAccessError();
	void showSSLerror();
	protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	void hideEvent(QHideEvent *event);
	private:
	int LoadProgress;
	QWebView *WebView;
	bool loading;
	QString text;
	QPixmap icon;
	bool textSet;
	bool iconSet;
	bool mouseOverIcon;
	static int currentTab;
	int index;
	QMenu *tabMenu;
	QAction *openInNewWindow;
	QAction *bookmarkThisTab;
	QAction *closeTab;
	QAction *stopAction;
	private slots:
	void _closeTab();
	void _bookmark();
	void _newWindow();
	void startDownload(QNetworkRequest request);
	void startDownload(QNetworkReply *reply);
	signals:
	void tabCloseRequested();
	void clicked(int x);
	void bookmarkRequest(Bookmark *bookmark);
	void openInNewWindowRequested(QString address);
};
#endif
