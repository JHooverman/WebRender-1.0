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



#include "mainwindow.h"
#include <QtGui/QWhatsThis>
#include <QtCore/QUrl>
#include <QtGui/QIcon>
#include <QtNetwork/QUrlInfo>
#include <QtCore/QDir>
#include <QtCore/QDataStream>
#include <QtCore/QTextStream>
#include <QtCore/QIODevice>
#include <QtGui/QMessageBox>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QList>
#include <QtCore/QListIterator>
#include <QtWebKit/QWebHistoryItem>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebFrame>
#include <QtGui/QFileDialog>
#include <QtGui/QTextEdit>
#include <QtGui/QPrintDialog>
#include <QtGui/QPrinter>
#include "downloader.h"
#include "preferencewindow.h"
#include "addressbar.h"
#include "HistoryWriter.h"
#include <iostream>
#include <fstream>
using namespace std;

MainWindow::MainWindow()
{
	setupMenus();
	setupActions();
	setupToolBar();
	setupCentralWidget();
	loadWidgets();
	createConnections();
	setCentralWidget(centralWidget);
        setDirectory();
        setWindowTitle(tr("WebRender"));
	setWindowIcon(QIcon(":/icons/webrender.png"));
        loadSettings();
	setupShortcutKeys();
        updateCompleter();
        enablePopUp = true;
	loadHomePage();
}

void MainWindow::saveAsPDF()
{
	QPrinter *printer = new QPrinter;
	printer->setOutputFormat(QPrinter::PdfFormat);
	QString fileName = QFileDialog::getSaveFileName(this,tr("Save as PDF"),QDir::homePath(),tr("PDF Document (*.pdf)"));
	if(!fileName.endsWith(".pdf")) fileName + ".pdf";
	printer->setOutputFileName(fileName);
	webview->page()->mainFrame()->print(printer);
	delete printer;
	
}
bool MainWindow::setupCentralWidget()
{
	tabView = new TabView;
	tabView->setMenu(MainMenu);
	currentTab = new Tab;
	WebViewStack = new QStackedLayout;
	WebViewStack->setContentsMargins(0,0,0,0);
        webview = new QWebView;
	createConnections(webview);
	WebViewList<<webview;
	currentTab->setTabIndex(WebViewStack->addWidget(webview));//<DONE>
	currentTab->assignWebView(webview);
	tabView->addTab(currentTab);
	history = webview->history();
        webpage = webview->page();
        networkAccessManager = webpage->networkAccessManager();
        cookieJar = networkAccessManager->cookieJar();
	mainLayout = new QVBoxLayout;
	mainLayout->setContentsMargins(0,0,0,0);
	centralWidget = new QWidget;
	mainLayout->addWidget(MainToolBar);
	mainLayout->addWidget(tabView);
	mainLayout->addLayout(WebViewStack);
	mainLayout->setSpacing(0);
	centralWidget->setLayout(mainLayout);
	zoomFactor = webview->zoomFactor();
	currentZoomFactor = zoomFactor;
	connect(currentTab,SIGNAL(clicked(int)),WebViewStack,SLOT(setCurrentIndex(int)));
	connect(currentTab,SIGNAL(clicked(int)),this,SLOT(setTab(int)));
	connect(currentTab,SIGNAL(openInNewWindowRequested(QString)),this,SLOT(newWindow(QString)));
	return true;
}
bool MainWindow::setupMenus()
{
	MainMenu = new QMenu();
	MainMenu->setWindowOpacity(0.9);
	fileMenu = MainMenu->addMenu(tr("File"));
	editMenu = MainMenu->addMenu(tr("Edit"));
	viewMenu = MainMenu->addMenu(tr("View"));
	historyMenu = MainMenu->addMenu(tr("History"));
	bookmarksMenu = MainMenu->addMenu(tr("Bookmarks"));
	toolsMenu = MainMenu->addMenu(tr("Tools"));
	helpMenu = MainMenu->addMenu(tr("Help"));

	fileMenu->setWindowOpacity(0.9);
	editMenu->setWindowOpacity(0.9);
	viewMenu->setWindowOpacity(0.9);
	historyMenu->setWindowOpacity(0.9);
	bookmarksMenu->setWindowOpacity(0.9);
	toolsMenu->setWindowOpacity(0.9);
	helpMenu->setWindowOpacity(0.9);
	return true;
}

bool MainWindow::setupActions()
{
	newWindowAction = new QAction(tr("New Window"),this);
	newWindowAction->setIcon(QIcon(":/icons/window-new.png"));
	newWindowAction->setToolTip(tr("Open a new WebRender window."));
	newWindowAction->setWhatsThis(tr("Open a new WebRender window."));
	newTabAction = new QAction(tr("New Tab"),this);
	newTabAction->setIcon(QIcon(":/icons/new-tab.png"));
	newTabAction->setWhatsThis(tr("Opens a new tab."));
	openFileAction = new QAction(tr("Open File"),this);
	openFileAction->setToolTip(tr("Opens a web page saved in your computer."));
	openFileAction->setWhatsThis(tr("Opens a web page saved in your computer."));
	openFileAction->setIcon(QIcon(":/icons/window-new.png"));
	savePageAction = new QAction(tr("Save Page"),this);
	savePageAction->setIcon(QIcon(":/icons/save.png"));
	savePageAction->setToolTip(tr("Saves the web page as HTML."));
	savePageAction->setWhatsThis(tr("Saves the web page as HTML."));
	savePDFAction = new QAction(tr("Save as PDF"),this);
	savePDFAction->setIcon(QIcon(":/icons/save.png"));
	savePDFAction->setToolTip(tr("Saves the web page as PDF."));
	savePDFAction->setWhatsThis(tr("Saves the web page as PDF."));
	printAction = new QAction(tr("Print page"),this);
	printAction->setToolTip(tr("Prints the page currently viewing."));
	printAction->setWhatsThis(tr("Prints the page currently viewing."));
	printAction->setIcon(QIcon(":/icons/print.png"));
	quitAction = new QAction(tr("Quit WebRender"),this);
	quitAction->setIcon(QIcon(":/icons/quit.png"));
	quitAction->setToolTip(tr("Quit WebRender"));
	quitAction->setWhatsThis(tr("Quit WebRender"));
	fileMenu->addAction(newWindowAction);
	fileMenu->addAction(newTabAction);
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(savePageAction);
	fileMenu->addAction(savePDFAction);
	fileMenu->addAction(printAction);
	fileMenu->addAction(quitAction);
        cutAction = new QAction(tr("Cut"),this);
	cutAction->setIcon(QIcon(":/icons/cut.png"));
	cutAction->setToolTip(tr("Cut the selected text"));
	cutAction->setWhatsThis(tr("Cut the selected text"));
        copyAction = new QAction(tr("Copy"),this);
	copyAction->setIcon(QIcon(":/icons/copy.png"));
	copyAction->setToolTip(tr("Copies the selected text"));
	copyAction->setWhatsThis(tr("Copies the selected text"));
        pasteAction = new QAction(tr("Paste"),this);
	pasteAction->setIcon(QIcon(":/icons/paste.png"));
	pasteAction->setToolTip(tr("Places the cut or copied text to the field"));
	pasteAction->setWhatsThis(tr("Places the cut or copied text to the field"));
	deleteAction = new QAction(tr("Delete"),this);
	deleteAction->setIcon(QIcon(":/icons/edit-delete.png"));
	deleteAction->setToolTip(tr("Removes the selected text"));
	deleteAction->setWhatsThis(tr("Removes the selected text"));
	findAction = new QAction(tr("Find"),this);
	findAction->setIcon(QIcon(":/icons/find.png"));
	findAction->setToolTip(tr("Search the page for the given text"));
	findAction->setWhatsThis(tr("Search the page for the given text"));
	preferencesAction = new QAction(tr("Preferences"),this);
	preferencesAction->setIcon(QIcon(":/icons/preferences.png"));
	preferencesAction->setToolTip(tr("Opens the WebRender preference window"));
	preferencesAction->setWhatsThis(tr("Opens the WebRender Preferences window."));
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);
	editMenu->addAction(deleteAction);
	editMenu->addAction(findAction);
	editMenu->addAction(preferencesAction);
	zoomInAction = new QAction(tr("Zoom In"),this);
	zoomInAction->setToolTip(tr("Magnifies the web page currently viewing."));
	zoomInAction->setWhatsThis(tr("Magnifies the web page currently viewing."));
	zoomInAction->setIcon(QIcon(":/icons/zoom-in.png"));
	zoomInAction->setShortcuts(QKeySequence::ZoomIn);
	zoomOutAction = new QAction(tr("Zoom Out"),this);
	zoomOutAction->setToolTip(tr("Demagnifies the web page currently viewing."));
	zoomOutAction->setWhatsThis(tr("Demagnifies the web page currently viewing."));
	zoomOutAction->setIcon(QIcon(":/icons/zoom-out.png"));
	zoomOutAction->setShortcuts(QKeySequence::ZoomOut);
	resetZoomAction = new QAction(tr("Reset zoom"),this);
	resetZoomAction->setToolTip(tr("Restore the page's original zoom level"));
	resetZoomAction->setWhatsThis(tr("Restore the page's original zoom level"));
	resetZoomAction->setIcon(QIcon(":/icons/zoom-fit-best.png"));
	sourceAction = new QAction(tr("Page Source"),this);
	sourceAction->setToolTip(tr("Views the HTML source of the page currently visiting"));
	sourceAction->setWhatsThis(tr("Views the HTML source of the page currently visiting"));
	sourceAction->setIcon(QIcon(":/icons/page-source.png"));
	viewMenu->addAction(zoomInAction);
	viewMenu->addAction(zoomOutAction);
	viewMenu->addAction(resetZoomAction);
	viewMenu->addAction(sourceAction);
	backAction = new QAction(tr("Go Back"),this);
	backAction->setToolTip(tr("Navigate to the previous page you visited"));
	backAction->setWhatsThis(tr("Navigate to the previous page you visited"));
	backAction->setIcon(QIcon(":/icons/go-previous.png"));
	backAction->setShortcuts(QKeySequence::Back);
	forwardAction = new QAction(tr("Go Forward"),this);
	forwardAction->setToolTip(tr("Navigate you to the next page in the History"));
	forwardAction->setWhatsThis(tr("Navigate you to the next page in the History"));
	forwardAction->setIcon(QIcon(":/icons/go-next.png"));
	forwardAction->setShortcuts(QKeySequence::Forward);
        homeAction = new QAction(tr("Navigate to the home page"),this);
	homeAction->setToolTip(tr("Navigate to the home page of the website"));
	homeAction->setWhatsThis(tr("Navigate quickly to the home page of the website when you visits other pages of the website"));
	homeAction->setIcon(QIcon(":/icons/home.png"));
        showAllHistoryAction = new QAction(tr("Show All History"),this);
	showAllHistoryAction->setToolTip(tr("Show the list of web pages you visited."));
	showAllHistoryAction->setWhatsThis(tr("Show the list of web pages you visited."));
	showAllHistoryAction->setIcon(QIcon(":/icons/history.png"));
	historyMenu->addAction(backAction);
	historyMenu->addAction(forwardAction);
	historyMenu->addAction(homeAction);
	historyMenu->addAction(showAllHistoryAction);
	addBookmarkAction = new QAction(tr("Add Bookmarks"),this);
	addBookmarkAction->setToolTip(tr("Save your favourite and important links and access them next time"));
	addBookmarkAction->setWhatsThis(tr("Save your favourite and important links and access them next time"));
	addBookmarkAction->setIcon(QIcon(":/icons/bookmarks.png"));
	manageBookmarksAction = new QAction(tr("Manage Bookmarks"),this);
	manageBookmarksAction->setToolTip(tr("View, add or remove bookmarks."));
	manageBookmarksAction->setWhatsThis(tr("View, add or remove bookmarks."));
	manageBookmarksAction->setIcon(QIcon(":/icons/bookmarks.png"));
	bookmarksMenu->addAction(addBookmarkAction);
	bookmarksMenu->addAction(manageBookmarksAction);
	ipFinderAction = new QAction(tr("IP Address Finder"),this);
	ipFinderAction->setIcon(QIcon(":/icons/IP-finder.png"));
	ipFinderAction->setToolTip(tr("Find the IP address, location and details of the host."));
	ipFinderAction->setWhatsThis(tr("Find the IP address, location and details of the host. This service is provided by http://www.ip-adress.com .Please read terms and conditions."));
	resetAction = new QAction(tr("Reset Browser"),this);
	resetAction->setIcon(QIcon(":/icons/reset-browser.png"));
	resetAction->setToolTip(tr("Restores the browser's original settings."));
	resetAction->setWhatsThis(tr("Restores the browser's original settings."));
        showWebInspectorAction = new QAction(tr("Show Web Inspector"), this);
	showWebInspectorAction->setToolTip(tr("Shows WebKit's Web Inspector."));
	showWebInspectorAction->setWhatsThis(tr("Shows WebKit's Web Inspector."));
	showWebInspectorAction->setIcon(QIcon(":/icons/webkit-icon.png"));
        privateBrowsingAction = new QAction(tr("Start Private Browsing"),this);
	privateBrowsingAction->setIcon(QIcon(":/icons/private-browsing.png"));
	privateBrowsingAction->setToolTip(tr("Enables private browsing."));
	privateBrowsingAction->setWhatsThis(tr("When you enable private browsing, WebRender will not record history when you surfing. You can quit private browsing any time."));
        privateBrowsingAction->setCheckable(true);
	toolsMenu->addAction(ipFinderAction);
//        toolsMenu->addAction(showWebInspectorAction);
        toolsMenu->addAction(privateBrowsingAction);
	toolsMenu->addAction(resetAction);
	whatIsThisAction = QWhatsThis::createAction(this);
	aboutAction = new QAction(tr("About WebRender"),this);
	aboutAction->setToolTip(tr("About WebRender"));
	aboutAction->setWhatsThis(tr("About WebRender"));
	aboutAction->setIcon(QIcon(":/icons/about.png"));
	helpMenu->addAction(whatIsThisAction);
	helpMenu->addAction(aboutAction);
	/*Tool bar actions*/
	reloadAction = new QAction(tr("Reload"),this);
	reloadAction->setToolTip(tr("Reloads the page"));
	reloadAction->setWhatsThis(tr("Reloads the page currently viewing."));
	reloadAction->setIcon(QIcon(":/icons/reload.png"));
	reloadAction->setShortcuts(QKeySequence::Refresh);

	reportBugAction = new QAction(tr("Report Bugs"),this);
	reportBugAction->setToolTip(tr("Report bug about WebRender"));
	reportBugAction->setWhatsThis(tr("Report bug about WebRender"));
	reportBugAction->setIcon(QIcon(":/icons/bugs.png"));
	helpMenu->addAction(reportBugAction);
	return true;
}

bool MainWindow::setupShortcutKeys()
{
	new QShortcut(QKeySequence(tr("F11")),this,SLOT(showFullScreen()));
	new QShortcut(QKeySequence(tr("Shift+F11")),this,SLOT(showNormal()));
	new QShortcut(QKeySequence(QKeySequence::AddTab),this,SLOT(newTab()));
        new QShortcut(QKeySequence(QKeySequence::HelpContents),aboutDialog,SLOT(showAnimated()));
	new QShortcut(QKeySequence(tr("Ctrl+H")),this,SLOT(showHistoryWindow()));
	new QShortcut(QKeySequence(QKeySequence::Save),this,SLOT(saveToLocalFile()));
	new QShortcut(QKeySequence(QKeySequence::Find),this,SLOT(doFindText()));
	new QShortcut(QKeySequence(QKeySequence::Print),this,SLOT(print()));
//	new QShortcut(QKeySequence(QKeySequence::ZoomIn),zoomInAction,SLOT(trigger()));
//	new QShortcut(QKeySequence(QKeySequence::ZoomOut),zoomOutAction,SLOT(trigger()));
//	new QShortcut(QKeySequence(QKeySequence::Back),backAction,SLOT(trigger()));
//	new QShortcut(QKeySequence(QKeySequence::Forward),forwardAction,SLOT(trigger()));
	new QShortcut(QKeySequence(QKeySequence::Preferences),preferenceWindow,SLOT(show()));
	new QShortcut(QKeySequence(QKeySequence::Open),this,SLOT(openLocalFile()));
	new QShortcut(QKeySequence(tr("Ctrl+Return")),this,SLOT(completeAddressBar()));
	return true;
}

bool MainWindow::setupToolBar()
{
	websiteIconAction = new QAction("",this);

	MainToolBar = new ToolBar;
	addressBar = new AddressBarWidget;
	backForwardButtonGroup = new BackForwardButtonGroup;
	ReloadToolButton = new ToolButton;
	ReloadToolButton->setIconPath(":/icons/reload-toolbutton.png");
	GoogleSearch = new QLineEdit;
	new GoogleSuggest(GoogleSearch);
	GoogleSearch->setStyleSheet(QString("QLineEdit { border: 1px solid gray; border-radius: 10px; padding: 0 8px; background: white; selection-background-color: darkgray;}"));
	GoogleSearch->setPlaceholderText(tr("Google Search"));
	GoogleSearch->setMaximumWidth(200);
        GoogleSearch->setFixedHeight(20);
	MainToolBarLayout = new QHBoxLayout;
        MainToolBarLayout->setContentsMargins(5,3,5,3);

	MainToolBarLayout->addWidget(backForwardButtonGroup);
	MainToolBarLayout->addWidget(ReloadToolButton);
	MainToolBarLayout->addWidget(addressBar);
	MainToolBarLayout->addWidget(GoogleSearch);
	MainToolBar->setLayout(MainToolBarLayout);

	connect(backForwardButtonGroup,SIGNAL(backButtonClicked()),backAction,SLOT(trigger()));
	connect(backForwardButtonGroup,SIGNAL(forwardButtonClicked()),forwardAction,SLOT(trigger()));
	connect(ReloadToolButton,SIGNAL(clicked()),reloadAction,SLOT(trigger()));
	return true;
}
bool MainWindow::loadWidgets()
{
    aboutDialog = new About;
    historyViewer = new HistoryViewer;
    historyViewer->setHistory(history);
    sourceview = new SourceView;
    preferences = new Preferences;
    preferences->getSettings(webview->page());
    preferenceWindow = new PreferenceWindow(preferences);
    bookmarksWindow = new BookmarksWindow;
    connect(currentTab,SIGNAL(bookmarkRequest(Bookmark*)),bookmarksWindow,SLOT(addBookmark(Bookmark*)));
    addBookmarkWindow = new AddBookmarkWindow;
    findDialog = new FindDialog(webview->page());
    ipFinder = new IpFinder;
    resetWindow = new ResetWindow;
    return true;
}
bool MainWindow::setDirectory()
{
    QDir dir;
    dir.cd(QDir::homePath());
    if(!dir.cd(QString(".WebRender")))
    {
        dir.mkdir(QString(".WebRender"));
    }
    dir.cd(QString(".WebRender"));
    settingsDir = dir;
    if(!dir.exists(QString("LocalStorage")))
        dir.mkdir("LocalStorage");
    if(!dir.exists(QString("Cache")))
        dir.mkdir("Cache");
    if(!dir.exists(QString("OfflineStorage")))
        dir.mkdir("OfflineStorage");
    if(!dir.exists(QString("Cookies")))
        dir.mkdir("Cookies");
    QWebSettings::globalSettings()->setIconDatabasePath(settingsDir.absolutePath());
    QWebSettings::globalSettings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled,true);
    dir.cd("LocalStorage");
    QWebSettings::globalSettings()->setLocalStoragePath(dir.absolutePath());
    dir.cdUp();
    dir.cd("Cache");
    QWebSettings::globalSettings()->setOfflineWebApplicationCachePath(dir.absolutePath());
    dir.cdUp();
    dir.cd("OfflineStorage");
    QWebSettings::globalSettings()->setOfflineStoragePath(dir.absolutePath());
    webpage->setForwardUnsupportedContent(true);
    return true;
}
bool MainWindow::loadSettings()
{
//    QFile file(settingsDir.absoluteFilePath("historyfile"));
//    if(!file.open(QIODevice::ReadOnly))
//    {
//        return false;
//    }
//    QDataStream historyFileIn(&file);
//    historyFileIn>> (*history);
    networkDiskCache = new QNetworkDiskCache(this);
    settingsDir.cd("Cache");
    networkDiskCache->setCacheDirectory(settingsDir.absolutePath());
    settingsDir.cdUp();
    networkAccessManager->setCache(networkDiskCache);
    QFile preferencesFile(settingsDir.absoluteFilePath("preferencesFile"));
    preferences->readFromFile(preferencesFile);
    preferenceWindow->initialise();
    QFile bookmarksFile(settingsDir.absoluteFilePath("bookmarksFile"));
    bookmarksWindow->loadBookmarksFromFile(bookmarksFile);
    loadBrowserGeometry();
    return true;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    saveBrowserSettings();
    QMainWindow::closeEvent(event);
}
void MainWindow::loadUrl(QUrl url)
{
    webview->load(url);
}

void MainWindow::loadHomePage()
{
	if(preferences->getSettingsFor(Preferences::LoadHomePageOnStartUp))
		webview->load(preferences->homePage());
}
/* slots defenition */

void MainWindow::GoToAddress()
{
	link = addressBar->text();
	if(!link.contains("http://") && !link.contains("https://") && !link.contains("file://"))
	{
		link = QString("http://") + link;
	}
	webview->load(QUrl(link));
}

void MainWindow::setAddressBarUrl(const QUrl &url)//
{
        addressBar->setText(url.toString());
}
void MainWindow::setTitle(const QString &title) //
{
        if(!title.isEmpty())
                setWindowTitle(title + tr(" - WebRender"));
        else
            setWindowTitle(tr("WebRender"));
}
void MainWindow::setBrowserIcon()
{
	
}

void MainWindow::showWebInspector()
{
	if(!WebInspector)
	{
		std::cout<<"showWebInspector(): Uninitialized QWebInspector* WebInspector\n";
		return;
	}
	WebInspector->show();
	webview->page()->action(QWebPage::InspectElement)->trigger();
}
void MainWindow::saveBrowserSettings()
{
	HistoryWriter *historyWriter = new HistoryWriter;//
	QListIterator<QWebView*> i(WebViewList);
	QWebHistory *_history;
	int count, currentHistoryIndex=0;
	while(i.hasNext())
	{
		_history = i.next()->history();
		count = _history->count();
		currentHistoryIndex = 0;
		while(currentHistoryIndex<count) {
			historyWriter->addHistoryItem(_history->itemAt(currentHistoryIndex));
			currentHistoryIndex++;
		}
	}
	historyWriter->save();
    QFile preferencesFile(settingsDir.absoluteFilePath("preferencesFile"));
    preferences->writeToFile(preferencesFile);
    QFile bookmarksFile(settingsDir.absoluteFilePath("bookmarksFile"));
    bookmarksWindow->saveBookmarksToFile(bookmarksFile);
    saveBrowserGeometry();
}

bool MainWindow::saveBrowserGeometry()
{
	QFile file(settingsDir.absoluteFilePath("BrowserGeometry"));
	if(file.open(QIODevice::WriteOnly))
	{
		file.write(saveGeometry());
		return true;
	}
	else
		return false;
}

bool MainWindow::loadBrowserGeometry()
{
	QFile file(settingsDir.absoluteFilePath("BrowserGeometry"));
	if(file.open(QIODevice::ReadOnly))
	{
		restoreGeometry(file.readAll());
		return true;
	}
	else
	{
		resize(1024,768);
		return false;
	}
}
void MainWindow::setPrivateBrowsing(bool status)
{
    webpage->settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, status);
    if(status)
        QMessageBox::information(this,tr("Private Browsing started"),tr("WebRender has started private browsing according to your request. WebRender now will not store any information of websites. You can leave private browsing any time."),QMessageBox::Ok);
}

void MainWindow::showHistoryWindow()
{
    historyViewer->updateHistoryLists();
    historyViewer->show();
}
void MainWindow::updateCompleter()
{
    QList<QWebHistoryItem> historys = history->items();
    QListIterator<QWebHistoryItem> i(historys);
    QStringList addresslist;
    QWebHistoryItem currentHistoryItem(history->backItem());
    while(i.hasNext())
    {
        currentHistoryItem = i.next();
        addresslist<<currentHistoryItem.url().host();
    }
    addresslist.removeDuplicates();
    addressBar->setCompleter(new QCompleter(addresslist,this));
}
void MainWindow::goToAddressFromHistory(QString &address)
{
    webview->load(QUrl(address));
}
void MainWindow::openLocalFile()
{
    QString fileName =  QFileDialog::getOpenFileName(this,tr("Open file"),QDir::homePath());
    webview->load(QUrl(fileName));
}
void MainWindow::saveToLocalFile()
{
    QString saveFileName = QFileDialog::getSaveFileName(this,tr("Save File"),QDir::homePath(),tr("HTML Document (*.htm *.html)"));
    QFile file(saveFileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    QTextStream out(&file);
    out << webpage->mainFrame()->toHtml();
}
void MainWindow::newWindow()
{
    (new MainWindow)->show();
}
void MainWindow::newWindow(QString url)
{
    MainWindow *w = new MainWindow;
    w->loadUrl(url);
    w->show();
}
void MainWindow::viewPageSource()
{
    sourceview->setPage(webpage);
    sourceview->show();
}



void MainWindow::cut()
{
    webpage->triggerAction(QWebPage::Cut);
}
void MainWindow::copy()
{
    webpage->triggerAction(QWebPage::Copy);
}
void MainWindow::paste()
{
    webpage->triggerAction(QWebPage::Paste);
}
void MainWindow::print()
{
    QPrinter printer;
    QPrintDialog printdialog(&printer,this);
    if(printdialog.exec())
    {
        webpage->mainFrame()->print(&printer);
    }
}
void MainWindow::NavigateToHomePage()
{
    loadUrl(QUrl(webview->url().scheme() + QString("://") + webview->url().host()));
}
void MainWindow::onLinkHovered(QString link,QString /* title */, QString /*textcontent*/)
{
    if(!link.isEmpty())
    {
        addressBar->setText(link);
        addressBar->setStyleSheet(QString("QLineEdit { border: 1px solid gray; border-radius: 10px; padding-left: 8px; padding-right: 41px; background: #DDDDFF; selection-background-color: darkgray; }"));
    }
    else
    {
        addressBar->setText(webview->url().toString());
        addressBar->setStyleSheet(QString("QLineEdit { border: 1px solid gray; border-radius: 10px; padding-left: 8px; padding-right: 41px; background: white; selection-background-color: darkgray; }"));
    }
}


void MainWindow::setPreferences()
{
	preferences->set(webpage);
}
void MainWindow::showBookmarksWindow()
{
	bookmarksWindow->show();
}

void MainWindow::loadUrl(QString url)
{
	if(!url.isEmpty())
	{
		QUrl Url(url);
		webview->load(Url);
	}

}

void MainWindow::doGoogleSearch()
{
	QString query = GoogleSearch->text();
	QString addressPart1 = "http://www.google.co.in/search?hl=en&q=";
	query.replace(QString(" "),QString("+"));
	QString addressPart3 = "&aq=f&aqi=&aql=&oq=&gs_rfai=";
	QString url = addressPart1 + query + addressPart3;
	loadUrl(url);
}

void MainWindow::doFindText()
{
	findDialog->show();
}

void MainWindow::on_zoomInAction_triggered()
{
	currentZoomFactor = currentZoomFactor*1.25;
	webview->setZoomFactor(currentZoomFactor);
}

void MainWindow::on_zoomOutAction_triggered()
{
	currentZoomFactor = currentZoomFactor/1.25;
	webview->setZoomFactor(currentZoomFactor);
}

void MainWindow::on_resetZoomAction_triggered()
{
	webview->setZoomFactor(zoomFactor);
}


void MainWindow::newTab()
{
	Tab *tab = new Tab;
	QWebView *view = new QWebView;
	WebViewList<<view;
	tab->assignWebView(view);
	tabView->addTab(tab);
	tab->setTabIndex(WebViewStack->addWidget(view));//<DONE>
	connect(tab,SIGNAL(clicked(int)),WebViewStack,SLOT(setCurrentIndex(int)));
	connect(tab,SIGNAL(clicked(int)),this,SLOT(setTab(int)));
	connect(tab,SIGNAL(bookmarkRequest(Bookmark*)),bookmarksWindow,SLOT(addBookmark(Bookmark*)));
	connect(tab,SIGNAL(openInNewWindowRequested(QString)),this,SLOT(newWindow(QString)));
    	view->page()->setForwardUnsupportedContent(true);
	preferences->set(view->page());
	tab->setCurrentTab();
	setTab(tab->tabIndex());
	WebViewStack->setCurrentIndex(tab->tabIndex());
	tabView->update();
}

void MainWindow::setTab(int x)
{
	disconnectAllConnections(webview);
	webview = WebViewList[x];
	webpage = webview->page();
	createConnections(webview);
        setTitle(webview->title());
	addressBar->setText(webview->url().toString());
	findDialog->setPage(webpage);

}

void MainWindow::completeAddressBar()
{
	QString url = addressBar->text();
	if(url.isEmpty() || url.contains("http://"))
		return;
	url.prepend("http://www.");
	url.append(".com");
	addressBar->setText(url);
	loadUrl(url);
}

/*End of slot defenition*/
void MainWindow::createConnections(QWebView *view)
{
	webview = view;
	webpage = view->page();
	connect(view, SIGNAL(urlChanged(QUrl)), this, SLOT(setAddressBarUrl(QUrl)));
	connect(view, SIGNAL(titleChanged(QString)), this, SLOT(setTitle(QString)));
	connect(view, SIGNAL(iconChanged()), this, SLOT(setBrowserIcon()));
	connect(backAction, SIGNAL(triggered()), view, SLOT(back()));
	connect(forwardAction, SIGNAL(triggered()), view, SLOT(forward()));
	connect(reloadAction, SIGNAL(triggered()), view, SLOT(reload()));
        connect(view->page(),SIGNAL(windowCloseRequested()),this,SLOT(close()));
        connect(view->page(),SIGNAL(linkHovered(QString,QString,QString)),this,SLOT(onLinkHovered(QString,QString,QString)));
}

void MainWindow::disconnectAllConnections(QWebView *view)
{
	view->disconnect(this);
	backAction->disconnect();
	forwardAction->disconnect();
	reloadAction->disconnect();
	view->page()->disconnect(this);
}

void MainWindow::reportBugAction_triggered()
{
	loadUrl("http://www.facebook.com/pages/WebRender-Web-Browser/116988251715251");
}
bool MainWindow::createConnections()
{
	connect(addressBar, SIGNAL(GoClicked()), this, SLOT(GoToAddress()));
	connect(addressBar, SIGNAL(returnPressed()), this , SLOT(GoToAddress()));
        connect(aboutAction, SIGNAL(triggered()), aboutDialog , SLOT(showAnimated()));
        connect(showWebInspectorAction, SIGNAL(triggered()), this, SLOT(showWebInspector()));
        connect(privateBrowsingAction, SIGNAL(toggled(bool)), this, SLOT(setPrivateBrowsing(bool)));
        connect(showAllHistoryAction, SIGNAL(triggered()), this, SLOT(showHistoryWindow()));
        connect(historyViewer,SIGNAL(openLinkRequested(QString&)),this,SLOT(goToAddressFromHistory(QString&)));
        connect(openFileAction,SIGNAL(triggered()),this,SLOT(openLocalFile()));
        connect(savePageAction,SIGNAL(triggered()),this,SLOT(saveToLocalFile()));
	connect(savePDFAction,SIGNAL(triggered()),this,SLOT(saveAsPDF()));
        connect(newWindowAction,SIGNAL(triggered()),this,SLOT(newWindow()));
        connect(quitAction,SIGNAL(triggered()),this,SLOT(close()));
        connect(sourceAction,SIGNAL(triggered()),this,SLOT(viewPageSource()));
        connect(cutAction,SIGNAL(triggered()),this,SLOT(cut()));
        connect(copyAction,SIGNAL(triggered()),this,SLOT(copy()));
        connect(pasteAction,SIGNAL(triggered()),this,SLOT(paste()));
        connect(printAction,SIGNAL(triggered()),this,SLOT(print()));
        connect(homeAction,SIGNAL(triggered()),this,SLOT(NavigateToHomePage()));
        connect(preferencesAction, SIGNAL(triggered()), preferenceWindow, SLOT(show()));
	connect(preferenceWindow, SIGNAL(settingsChanged()), this, SLOT(setPreferences()));
        connect(manageBookmarksAction,SIGNAL(triggered()),bookmarksWindow,SLOT(show()));
	connect(addBookmarkWindow,SIGNAL(addBookmark(Bookmark *)),bookmarksWindow,SLOT(addBookmark(Bookmark*)));
        connect(addBookmarkAction,SIGNAL(triggered()),addBookmarkWindow,SLOT(show()));
	connect(bookmarksWindow,SIGNAL(openUrlRequest(QString)),this,SLOT(loadUrl(QString)));
	connect(GoogleSearch, SIGNAL(returnPressed()), this , SLOT(doGoogleSearch()));
	connect(findAction,SIGNAL(triggered()),this,SLOT(doFindText()));
	connect(zoomInAction,SIGNAL(triggered()),this,SLOT(on_zoomInAction_triggered()));
	connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(on_zoomOutAction_triggered()));
	connect(resetZoomAction,SIGNAL(triggered()),this,SLOT(on_resetZoomAction_triggered()));
        connect(ipFinderAction,SIGNAL(triggered()),ipFinder,SLOT(show()));
	connect(ipFinder,SIGNAL(openUrl(QString)),this,SLOT(loadUrl(QString)));
        connect(resetAction,SIGNAL(triggered()),resetWindow,SLOT(show()));
	connect(newTabAction,SIGNAL(triggered()),this,SLOT(newTab()));
	connect(websiteIconAction,SIGNAL(triggered()),this,SLOT(completeAddressBar()));
	connect(reportBugAction,SIGNAL(triggered()),this,SLOT(reportBugAction_triggered()));
	connect(tabView,SIGNAL(addTabPressed()),this,SLOT(newTab()));
	return true;
}
