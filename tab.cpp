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
#include "tab.h"
#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QLinearGradient>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtCore/QPoint>
#include <QtNetwork>
#include <iostream>

Tab::Tab(QWidget *parent) : QWidget(parent)
{
	tabMenu = new QMenu(this);
	openInNewWindow = new QAction(tr("Open in new Window"),this);
	openInNewWindow->setIcon(QIcon(":/icons/window-new.png"));
	bookmarkThisTab = new QAction(tr("Bookmark this tab"),this);
	bookmarkThisTab->setIcon(QIcon(":/icons/bookmark-menu.png"));
	closeTab = new QAction(tr("Close tab"),this);
	closeTab->setIcon(QIcon(":/icons/tab-close.png"));
	stopAction = new QAction(tr("Stop"),this);
	stopAction->setIcon(QIcon(":/icons/stop.png"));
	stopAction->setVisible(false);
	infoAction = new QAction(tr("Host Information"),this);
	tabMenu->addAction(openInNewWindow);
	tabMenu->addAction(bookmarkThisTab);
	tabMenu->addAction(closeTab);
	tabMenu->addAction(stopAction);
	tabMenu->addAction(infoAction);
	tabMenu->setWindowOpacity(0.9);
	setFixedSize(150,20);
	textSet = false;
	iconSet = false;
	mouseOverIcon = false;
	setMouseTracking(true);
	connect(closeTab,SIGNAL(triggered()),this,SLOT(_closeTab()));
	connect(openInNewWindow,SIGNAL(triggered()),this,SLOT(_newWindow()));
	connect(bookmarkThisTab,SIGNAL(triggered()),this,SLOT(_bookmark()));
	connect(infoAction,SIGNAL(triggered()),this,SLOT(showInfo()));
	loading = false;
}

int Tab::currentTab = 0;

void Tab::showInfo()
{
	HostInfoView *viewer = new HostInfoView;
	viewer->setWebView(WebView);
	viewer->show();
	viewer->move(mapToGlobal(QPoint(-85,20)));
}
void Tab::setText(QString t)
{
	text = t;
	textSet = true;
}

void Tab::setIcon(QIcon i)
{
	icon = i.pixmap(16,16);
	iconSet = true;
}

void Tab::setTabIndex(int x)
{
	index = x;
}

int Tab::tabIndex()
{
	return index;
}

void Tab::setCurrentTab()
{
	currentTab = index;
}

void Tab::paintEvent(QPaintEvent *event)
{
	QImage image(QSize(150,20), QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(Qt::black,1, Qt::SolidLine, Qt::RoundCap));
	QLinearGradient gradient(0,0,0,20);
	if(index == currentTab) //means that the tab is selected
	{
		gradient.setColorAt(0.0, Qt::white);
		gradient.setColorAt(0.3, Qt::white);
		gradient.setColorAt(1.0, QColor("#FF925F"));
	}
	else
	{
		gradient.setColorAt(0.0, Qt::white);
		gradient.setColorAt(1.0, QColor("#AAAAAA"));
	}
	painter.setBrush(gradient);
	painter.drawRoundedRect(0,0,150,20,5,5);

	QLinearGradient loadGradient(0,0,0,20);

	if(loading)
	{
		loadGradient.setColorAt(0.0, QColor("#EEFFEE"));
		loadGradient.setColorAt(1.0, QColor("#44EE44"));
		painter.setBrush(loadGradient);
		painter.setPen(QPen(Qt::black,0.5, Qt::SolidLine, Qt::RoundCap));
		painter.drawRoundedRect(0,0,(150*LoadProgress/100),20,5,5);
	}

//	painter.setPen(QPen(Qt::black,1, Qt::SolidLine, Qt::RoundCap));
	if(!mouseOverIcon)
	{
		if(iconSet)
		{
			painter.drawPixmap(2,2,icon);
		}
		else
		{
			painter.drawPixmap(2,2,QPixmap(":/icons/arrow-down.png").scaled(16,16));
		}
	}
	else
	{
		painter.drawPixmap(2,2,QPixmap(":/icons/arrow-down.png").scaled(16,16));
	}

	if(textSet)
	{
		painter.drawText(24,1,120,20, Qt::AlignLeft, text);
	}
	else
	{
		painter.drawText(24,1,120,20, Qt::AlignLeft, tr("Untitled")); //24,2,120,20
	}
	painter.end();
	QPainter widgetPainter(this);
	widgetPainter.drawImage(0,0,image);
}

void Tab::mousePressEvent(QMouseEvent *event)
{
	if(event->button() & Qt::LeftButton)
	{
		currentTab = index;
		update();
		if((event->pos().x() < 22) && (event->pos().x() > 2) && (event->pos().y() < 22) && (event->pos().y() > 2))
		{//means that the cursor lies with in the icon
			tabMenu->popup(mapToGlobal(QPoint(0,25)));
		}
		emit clicked(index);
	} else if(event->button() & Qt::MiddleButton) {
		_closeTab();
	}
	update();
	QWidget::mousePressEvent(event);
}

void Tab::_closeTab()
{
	WebView->setHtml("<html></html>");
	emit tabCloseRequested();
}
void Tab::mouseMoveEvent(QMouseEvent *event)
{
	if((event->pos().x() < 22) && (event->pos().x() > 2) && (event->pos().y() < 22) && (event->pos().y() > 2))
	{//means that the cursor lies with in the icon
		mouseOverIcon = true;
		update();
	}
	else
	{
		mouseOverIcon = false;
		update();
	}
	QWidget::mouseMoveEvent(event);
}

void Tab::assignWebView(QWebView *view)
{
	WebView = view;
	connect(WebView,SIGNAL(titleChanged(QString)),this,SLOT(setText(QString)));
	connect(WebView,SIGNAL(iconChanged()),this,SLOT(setTabIcon()));
	connect(WebView,SIGNAL(loadProgress(int)),this,SLOT(loadProgress(int)));
	connect(WebView,SIGNAL(loadStarted()),this,SLOT(loadStarted()));
	connect(WebView,SIGNAL(loadFinished(bool)),this,SLOT(loadFinished(bool)));
        connect(WebView->page(),SIGNAL(downloadRequested(QNetworkRequest)),this,SLOT(startDownload(QNetworkRequest)));
	connect(WebView->page(),SIGNAL(unsupportedContent(QNetworkReply*)),this,SLOT(startDownload(QNetworkReply*)));
	connect(stopAction,SIGNAL(triggered()),WebView,SLOT(stop()));
	connect(WebView->page()->networkAccessManager(),SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),this,SLOT(showAccessError()));
	connect(WebView->page()->networkAccessManager(),SIGNAL(sslErrors(QNetworkReply*,const QList<QSslError> &)),this,SLOT(showSSLerror()));
}

void Tab::startDownload(QNetworkRequest request)
{
    std::cout<<"startDownload(QNetworkRequest request): downloadrequested() signal emitted by the webpage\n";
	Downloader *downloader = new Downloader;
	if(downloader->handleDownloadRequest(WebView->page()->networkAccessManager(),request))
		downloader->show();
}

void Tab::startDownload(QNetworkReply *reply)
{
    std::cout<<"startDownload(QNetworkReply *reply): downloadrequested() signal emitted by the webpage\n";
	Downloader *downloader = new Downloader;
	if(downloader->handleDownloadRequest(WebView->page()->networkAccessManager(),reply))
		downloader->show();
}

void Tab::setTabIcon()
{
	setIcon(WebView->icon());
}

void Tab::loadStarted()
{
	loading = true;
	stopAction->setVisible(true);
	update();
}

void Tab::loadProgress(int progress)
{
	LoadProgress = progress;
	update();
}

void Tab::loadFinished(bool ok)
{
	if(loading)
	{
		if(!ok)
		std::cout<<"Loading finished with error"<<std::endl;
	}
	loading = false;
	stopAction->setVisible(false);
	update();
}

void Tab::closeEvent(QCloseEvent *event)
{
	event->accept();
}

void Tab::hideEvent(QHideEvent *event)
{
	event->accept();
}

void Tab::_bookmark()
{
	Bookmark *bm = new Bookmark;
	bm->addData(Bookmark::Title, WebView->title());
	bm->addData(Bookmark::Address, WebView->url().toString());
	emit bookmarkRequest(bm);
}

void Tab::_newWindow()
{
	emit openInNewWindowRequested(WebView->url().toString());
}

void Tab::showAccessError()
{
	WebView->setHtml("<html><head><title>Error :: No Network Access</title></head><body><table border = '0' align = 'center' width = '850' cellspacing = '20' cellpadding = '20' bgcolor = '#FF8888'><tr><td><font face = 'sans'><h1 align = 'center'>Error :: No Network Access!</h1></font></td></tr><tr><td><font face = 'sans'><p>The network is not currently accessible, either because there is currently no network coverage or your ISP denied access to the internet.</p><p><b>What you can do:</b></p><p>* Check your modem or router is connected and configured properly.</p><p>* If you are using WiFi or GPRS/3G, check your network coverage.</p><p>* Contact your administrator and check you have proper permissions to access the internet.</p><p>* Contact the ISP if you still experience the problem.</p></font></td></tr></table></body></html>");
}

void Tab::showSSLerror()
{
	
	WebView->setHtml(QString("<html><head><title>Error :: SSL Error</title></head><body><table border = '0' align = 'center' width = '850' cellspacing = '20' cellpadding = '20' bgcolor = '#FF8888'><tr><td><font face = 'sans'><h1 align = 'center'>Error :: Untrusted connection!</h1></font></td></tr><tr><td><font face = 'sans'><p>You just entered a website ") + WebView->url().host() + " with a secure connection but WebRender can't confirm that your connection is secure. When you tries to visit a website with secure connection, website will present their identity to ensure your security. But unfortunately, the identity of this website can't be verified.</p><p><b>Why you are seeing this error:</b></p><p>* If WebRender was unable to get issuer certificate.</p><p>* If unable to decrypt the certificate signature.</p><p>* If unable to decode issuer public key.</p><p>* If certificate is expired.</p><p>* If you have no SSL support.</p><p><b>What you can do:</b></p><p>* WebRender recommends you to avoid visiting these websites that shows you false identities.</p><p>* If you trust this website, you can disable this security check.</p><p>* If you have no SSL support, get it from www.openssl.org</p></font></td></tr></table></body></html>");
	std::cout<<"SSL error\n";
}
