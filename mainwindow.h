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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QCompleter>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtCore/QString>
#include <QtGui/QWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLineEdit>
#include <QtWebKit/QWebView>
#include <QtGui/QPushButton>
#include <QtGui/QProgressBar>
#include <QtCore/QUrl>
#include <QtCore/QList>
#include <QtWebKit/QWebHistory>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebInspector>
#include <QtGui/QStackedLayout>
#include <QtCore/QFile>
#include <QtGui/QCloseEvent>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkReply>
#include <QtGui/QSplitter>
#include <QtCore/QDir>
#include <QtCore/QListIterator>
#include <QtGui/QShortcut>
#include <QtGui/QKeySequence>
#include "about.h"
#include "historyviewer.h"
#include "pagesourceviewer.h"
#include "downloader.h"
#include "preferencewindow.h"
#include "preferences.h"
#include "bookmarkswindow.h"
#include "addbookmarkwindow.h"
#include "finddialog.h"
#include "ipfinder.h"
#include "resetwindow.h"
#include "tabview.h"
#include "tab.h"
#include "addressbar.h"
#include "toolbar.h"
#include "backforward.h"
#include "toolbutton.h"
#include "SetupAssistant.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
	MainWindow();
	private:
	bool setupMenus();
	bool setupActions();
	bool setupToolBar();
	bool setupCentralWidget();
	bool createConnections();
	bool loadWidgets();
        bool setDirectory();
        bool loadSettings();
	bool loadPreferences(); //
	bool savePreferences();//
	void loadHomePage();
	bool saveBrowserGeometry();
	bool loadBrowserGeometry();
	bool setupShortcutKeys();
        bool enablePopUp;
	TabView *tabView;////////////////
	Tab *currentTab;////////////////
	QMenu *MainMenu;

	ToolBar *MainToolBar;
	AddressBarWidget *addressBar;
	BackForwardButtonGroup *backForwardButtonGroup;
	ToolButton *ReloadToolButton;
	ToolButton *menuToolButton;
        QLineEdit *GoogleSearch;
	QHBoxLayout *MainToolBarLayout;

	QList<QWebView*> WebViewList;
	QWebInspector *WebInspector;
	QStackedLayout *WebViewStack;
	ResetWindow *resetWindow;
	IpFinder *ipFinder;
	qreal zoomFactor;
	qreal currentZoomFactor;
	FindDialog *findDialog;
	AddBookmarkWindow *addBookmarkWindow;
	BookmarksWindow *bookmarksWindow;
	Preferences *preferences;
        QHBoxLayout *addressBarLayout;
        QWidget *addressBarWidget;
        QSplitter *toolBarSplitter;
        SourceView *sourceview;
        About *aboutDialog;
	PreferenceWindow *preferenceWindow;
        HistoryViewer *historyViewer;
        QCompleter *addressCompleter;
        QNetworkCookieJar *cookieJar;
        QNetworkAccessManager *networkAccessManager;
        QNetworkDiskCache *networkDiskCache;
        QWebInspector *webInspector;
        QWebPage *webpage;
	QWebHistory *history;
        QDir settingsDir;
	QString link;
        QString downloadsDir;
        QString homePage;
        QWebView *webview;
//	QPushButton *goButton;
	QWidget *centralWidget;
	QVBoxLayout *mainLayout;
        QString settingsDirectory;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *viewMenu;
	QMenu *historyMenu;
	QMenu *bookmarksMenu;
	QMenu *toolsMenu;
	QMenu *helpMenu;
	QToolBar *mainBar;
	/* File Menu actions */
	QAction *newWindowAction;
	QAction *newTabAction;
	QAction *openFileAction;
	QAction *savePageAction;
	QAction *printAction;
	QAction *quitAction;
	/* Edit Actions */
	QAction *cutAction;
	QAction *copyAction;
	QAction *pasteAction;
	QAction *deleteAction;
	QAction *findAction;
	QAction *preferencesAction;
	/* View Actions */
	QAction *zoomInAction;
	QAction *zoomOutAction;
	QAction *resetZoomAction;
	QAction *sourceAction;
	/* History Actions*/
	QAction *backAction;
	QAction *forwardAction;
	QAction *homeAction;
	QAction *showAllHistoryAction;
	QAction *historyItem1;
	QAction *historyItem2;
	QAction *historyItem3;
	QAction *historyItem4;
	QAction *historyItem5;
	/* Bookmarks Menu*/
	QAction *addBookmarkAction;
	QAction *manageBookmarksAction;
	/* Tools Menu*/
	QAction *ipFinderAction;
        QAction *showWebInspectorAction;
        QAction *privateBrowsingAction;
	QAction *resetAction;
	/* Help Menu*/
	QAction *whatIsThisAction;
	QAction *reportBugAction;
	QAction *aboutAction;
	/*Toolbar actions*/
	QAction *reloadAction;
	QAction *stopAction;
	QAction *websiteIconAction;
	SetupAssistant *setupAssistant;
    private slots:
	void GoToAddress();
	void setAddressBarUrl(const QUrl &url);//
	void setTitle(const QString &title);//
	void setBrowserIcon();
        void showWebInspector();
        void setPrivateBrowsing(bool status);
        void goToAddressFromHistory(QString &address);
        void openLocalFile();
        void saveToLocalFile();
        void newWindow();
        void newWindow(QString url);
        void viewPageSource();
        void cut();
        void copy();
        void paste();
        void print();
        void NavigateToHomePage();
        void onLinkHovered(QString link,QString /* title */, QString /*textcontent*/);
	void setPreferences();
	void showBookmarksWindow();
	void doGoogleSearch();
	void doFindText();
	void on_zoomInAction_triggered();
	void on_zoomOutAction_triggered();
	void on_resetZoomAction_triggered();
	void newTab();
	void createConnections(QWebView *view);
	void disconnectAllConnections(QWebView *view);
	void setTab(int x);
	void completeAddressBar();
	void reportBugAction_triggered();
	void popUpMainMenu();
    public slots:
        void updateCompleter();
        void saveBrowserSettings();
        void showHistoryWindow();
	void loadUrl(QUrl url);
	void loadUrl(QString url);
protected:
        void closeEvent(QCloseEvent *event);
};

#endif
