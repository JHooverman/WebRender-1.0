#ifndef HOSTINFOVIEW_H
#define HOSTINFOVIEW_H

#include "PopOver.h"
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebSecurityOrigin>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QHostAddress>

class HostInfoView : public PopOver {
	Q_OBJECT
	public:
	HostInfoView(QWidget *parent = 0);
	void setWebView(QWebView *view);
	private:
	QWebView *webView;
	QLabel *headerLabel;
	QLabel *hostLabel;
	QLabel *portLabel;
	QLabel *IPLabel;
	QPushButton *closeButton;
	QVBoxLayout *mainLayout;
	QHBoxLayout *headerLayout;

	QString host;
	int port;

	private slots:
	void fetchLookupData(const QHostInfo &info);
};
#endif
