#include "HostInfoView.h"

HostInfoView::HostInfoView(QWidget *parent) : PopOver(parent) {
	headerLabel = new QLabel(tr("<b>Information</b>"));
	hostLabel = new QLabel(tr("Host: Unknown"));
	portLabel = new QLabel(tr("Port: Unknown"));
	IPLabel = new QLabel(tr("IP Address: Unknown"));
	closeButton = new QPushButton(tr("Close"));
	headerLayout = new QHBoxLayout;
	headerLayout->addWidget(headerLabel);
	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(headerLayout);
	mainLayout->addWidget(hostLabel);
	mainLayout->addWidget(portLabel);
	mainLayout->addWidget(IPLabel);
	mainLayout->addWidget(closeButton);
	mainLayout->setContentsMargins(15,40,15,15);
	setLayout(mainLayout);
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
	setWindowOpacity(0.9);
}

void HostInfoView::setWebView(QWebView *view)
{
	webView = view;
	host = webView->page()->mainFrame()->securityOrigin().host();
	port = webView->page()->mainFrame()->securityOrigin().port();

	if(!host.isEmpty()) {
		hostLabel->setText(tr("Host: ") + host);
		portLabel->setText(tr("port: ") + QString::number(port));
		IPLabel->setText(tr("IP Address: Looking up"));
		QHostInfo::lookupHost(host, this, SLOT(fetchLookupData(QHostInfo)));
	} else {
		hostLabel->setText(" ");
		portLabel->setText(tr("Sorry. An error occured"));
		IPLabel->setText(" ");
	}
}

void HostInfoView::fetchLookupData(const QHostInfo &info)
{
	if(info.error() != QHostInfo::NoError) {
		hostLabel->setText(host);
		portLabel->setText(tr("Host lookup failed."));
		IPLabel->setText("No data available");
		return;
	}

	hostLabel->setText(tr("Host: ") + host);
	portLabel->setText(tr("port: ") + QString::number(port));
	IPLabel->setText(tr("IP Address: ") + info.addresses().first().toString());

}
