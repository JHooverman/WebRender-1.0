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


#include "preferencewindow.h"
#include "preferences.h"
#include <QtGui/QLabel>

PreferenceWindow::PreferenceWindow(Preferences *prefs)
{
	preferences = prefs;
	/* Home page tab */
	/* Home Page */
	homePageGroupBox = new QGroupBox(tr("Home page"),this);
	showLastVisitedRadioButton = new QRadioButton(tr("Show last visited page"),this);
	showHomePageRadioButton = new QRadioButton(tr("Show home page"),this);
	homePageLabel = new QLabel(tr("Home page:"));
	homePageUrlLineEdit = new QLineEdit;
////	selectHomePageTempleteButton = new QPushButton(tr("Select home page"));
	homePageRadioButtonLayout = new QVBoxLayout;
	homePageRadioButtonLayout->addWidget(showLastVisitedRadioButton);
	homePageRadioButtonLayout->addWidget(showHomePageRadioButton);
	homePageUrlLayout = new QHBoxLayout;
	homePageUrlLayout->addWidget(homePageLabel);
	homePageUrlLayout->addWidget(homePageUrlLineEdit);
//	homePageUrlLayout->addWidget(selectHomePageTempleteButton);
	homepageMainLayout = new QVBoxLayout;
	homepageMainLayout->addLayout(homePageRadioButtonLayout);
	homepageMainLayout->addLayout(homePageUrlLayout);
	homepageMainLayout->addStretch();
	homePageGroupBox->setLayout(homepageMainLayout);
	tab1Layout = new QHBoxLayout;
	tab1Layout->addWidget(homePageGroupBox);
	page1 = new QWidget;
	page1->setLayout(tab1Layout);
	/* End of Home Page */
	/* End of Home page tab */

	/* Miscallaneous tab */
	miscSettingsGroupBox = new QGroupBox(tr("Miscallaneous Settings"),this);
	autoLoadImagesCheckBox = new QCheckBox(tr("Automatically load images"),this);
	autoLoadImagesCheckBox->setToolTip(tr("Specifies whether images are automatically loaded in web pages."));
	DnsPrefetchCheckBox = new QCheckBox(tr("Enable DNS prefetch"),this);
	DnsPrefetchCheckBox->setToolTip(tr("Specifies whether QtWebkit will try to pre-fetch DNS entries to speed up browsing."));
	EnableJavascriptCheckBox = new QCheckBox(tr("Enable Java Script"),this);
	EnableJavascriptCheckBox->setToolTip(tr("Enables or disables the running of JavaScript programs."));
	EnableJavaAppletsCheckBox = new QCheckBox(tr("Enable Java Applets"),this);
	EnableJavaAppletsCheckBox->setToolTip(tr("Enables or disables Java applets."));
	JavascriptCanOpenWindowsCheckBox = new QCheckBox(tr("Java script can open windows"),this);
	JavascriptCanOpenWindowsCheckBox->setToolTip(tr("Specifies whether JavaScript programs can open new windows."));
	JavascriptCanAccessClipboardCheckBox = new QCheckBox(tr("Java script can access ClipBoard"),this);
	JavascriptCanAccessClipboardCheckBox->setToolTip(tr("Specifies whether JavaScript programs can read or write to the clipboard."));
	EnableSpatialNavigationCheckBox = new QCheckBox(tr("Enable spatial navigation"),this);
	EnableSpatialNavigationCheckBox->setToolTip(tr("Enables or disables the Spatial Navigation feature, which consists in the ability to navigate between focusable elements in a Web page, such as hyperlinks and form controls, by using Left, Right, Up and Down arrow keys. For example, if a user presses the Right key, heuristics determine whether there is an element he might be trying to reach towards the right and which element he probably wants."));
	PrintElementBackgroundsCheckBox = new QCheckBox(tr("Print element backgrounds"),this);
	PrintElementBackgroundsCheckBox->setToolTip(tr("Specifies whether the background color and images are also drawn when the page is printed."));
	LocalContentCanAccessFileUrlsCheckBox = new QCheckBox(tr("Local content can access files"),this);
	LocalContentCanAccessFileUrlsCheckBox->setToolTip(tr("Specifies whether locally loaded documents are allowed to access remote urls."));
	EnableXSSAuditingCheckBox = new QCheckBox(tr("Enable XSS Auditing"),this);
	EnableXSSAuditingCheckBox->setToolTip(tr("Specifies whether load requests should be monitored for cross-site scripting attempts. Suspicious scripts will be blocked and reported in the inspector's JavaScript console. Enabling this feature might have an impact on performance and it is disabled by default."));
	EnableAcceleratedCompositingCheckBox = new QCheckBox(tr("Enable acclerated compositing"),this);
	EnableAcceleratedCompositingCheckBox->setToolTip(tr("This feature, when used in conjunction with QGraphicsWebView, accelerates animations of web content. CSS animations of the transform and opacity properties will be rendered by composing the cached content of the animated elements."));
	EnableSiteSpecificQuirksCheckBox = new QCheckBox(tr("Enable site specific quirks"),this);
	EnableSiteSpecificQuirksCheckBox->setToolTip(tr("This setting enables WebKit's workaround for broken sites. It is enabled by default."));
	miscTabLayout = new QVBoxLayout;
	miscTabLayout->addWidget(autoLoadImagesCheckBox);
	miscTabLayout->addWidget(DnsPrefetchCheckBox);
	miscTabLayout->addWidget(EnableJavascriptCheckBox);
	miscTabLayout->addWidget(EnableJavaAppletsCheckBox);
	miscTabLayout->addWidget(JavascriptCanOpenWindowsCheckBox);
	miscTabLayout->addWidget(JavascriptCanAccessClipboardCheckBox);
	miscTabLayout->addWidget(EnableSpatialNavigationCheckBox);
	miscTabLayout->addWidget(PrintElementBackgroundsCheckBox);
	miscTabLayout->addWidget(LocalContentCanAccessFileUrlsCheckBox);
	miscTabLayout->addWidget(EnableXSSAuditingCheckBox);
	miscTabLayout->addWidget(EnableAcceleratedCompositingCheckBox);
	miscTabLayout->addWidget(EnableSiteSpecificQuirksCheckBox);
	miscTabLayout->addStretch();
	miscSettingsGroupBox->setLayout(miscTabLayout);
	tab2Layout = new QHBoxLayout;
	tab2Layout->addWidget(miscSettingsGroupBox);
	page2 = new QWidget;
	page2->setLayout(tab2Layout);
	/* End of Miscallaneous tab */

	/* Network Tab */
	proxyGroupBox = new QGroupBox(tr("Network proxy configuration"),this);
	enableProxyCheckBox = new QCheckBox(tr("Enable Proxy"),this);
	proxyHostNameLabel = new QLabel(tr("Proxy host name: "));
	proxyHostNameEdit = new QLineEdit;
	proxyPasswordLabel = new QLabel(tr("Password: "));
	proxyPasswordEdit = new QLineEdit;
	portLabel = new QLabel(tr("Port: "));
	portSpinBox = new QSpinBox;
	portSpinBox->setRange(0,10000);
	proxyHostNameLayout = new QHBoxLayout;
	proxyHostNameLayout->addWidget(proxyHostNameLabel);
	proxyHostNameLayout->addWidget(proxyHostNameEdit);
	proxyPasswordLayout = new QHBoxLayout;
	proxyPasswordLayout->addWidget(proxyPasswordLabel);
	proxyPasswordLayout->addWidget(proxyPasswordEdit);
	proxyPortLayout = new QHBoxLayout;
	proxyPortLayout->addWidget(portLabel);
	proxyPortLayout->addWidget(portSpinBox);
	proxyMainLayout = new QVBoxLayout;
	proxyMainLayout->addWidget(enableProxyCheckBox);
	proxyMainLayout->addLayout(proxyHostNameLayout);
	proxyMainLayout->addLayout(proxyPasswordLayout);
	proxyMainLayout->addLayout(proxyPortLayout);
	proxyMainLayout->addStretch();
	proxyGroupBox->setLayout(proxyMainLayout);
	page3 = new QWidget;
	tab3Layout = new QHBoxLayout;
	tab3Layout->addWidget(proxyGroupBox);
	page3->setLayout(tab3Layout);
	/* End of Network Tab */

	/* Setting up tabs */
	mainTabWidget = new QTabWidget(this);
	mainTabWidget->addTab(page1, tr("Home page"));
	mainTabWidget->addTab(page2, tr("Miscallaneous"));
	mainTabWidget->addTab(page3, tr("Network"));
	/* Tabs set up */

	mainLayout = new QVBoxLayout;
	buttons = new QHBoxLayout;
	applyButton = new QPushButton(tr("Apply"));
	closeButton = new QPushButton(tr("Close"));
	buttons->addWidget(applyButton);
	buttons->addWidget(closeButton);
	mainLayout->addWidget(mainTabWidget);
	mainLayout->addLayout(buttons);
	mainLayout->setContentsMargins(5,25,5,5);
	setLayout(mainLayout);
	setTitle("WebRender Preferences");
	/* UI setup complete */
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
	connect(applyButton,SIGNAL(clicked()), this, SLOT(on_applyButton_clicked()));
	initialise();
}

void PreferenceWindow::initialise()
{
	if(preferences->getSettingsFor(Preferences::LoadHomePageOnStartUp))
	{
		showHomePageRadioButton->setChecked(true);
		showLastVisitedRadioButton->setChecked(false);
	}
	else
	{
		showHomePageRadioButton->setChecked(false);
		showLastVisitedRadioButton->setChecked(true);
	}
	if(preferences->getSettingsFor(Preferences::LoadImages))
		autoLoadImagesCheckBox->setCheckState(Qt::Checked);
	else
		autoLoadImagesCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::DnsPrefetch))
		DnsPrefetchCheckBox->setCheckState(Qt::Checked);
	else
		DnsPrefetchCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::JavaScript))
		EnableJavascriptCheckBox->setCheckState(Qt::Checked);
	else
		EnableJavascriptCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::JSApplet))
		EnableJavaAppletsCheckBox->setCheckState(Qt::Checked);
	else
		EnableJavaAppletsCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::JScanOpenWindows))
		JavascriptCanOpenWindowsCheckBox->setCheckState(Qt::Checked);
	else
		JavascriptCanOpenWindowsCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::JScanAccessclipboard))
		JavascriptCanAccessClipboardCheckBox->setCheckState(Qt::Checked);
	else
		JavascriptCanAccessClipboardCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::SpatialNavigation))
		EnableSpatialNavigationCheckBox->setCheckState(Qt::Checked);
	else
		EnableSpatialNavigationCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::PrintElementBG))
		PrintElementBackgroundsCheckBox->setCheckState(Qt::Checked);
	else
		PrintElementBackgroundsCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::LocalContentAccess))
		LocalContentCanAccessFileUrlsCheckBox->setCheckState(Qt::Checked);
	else
		LocalContentCanAccessFileUrlsCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::XSSAuditing))
		EnableXSSAuditingCheckBox->setCheckState(Qt::Checked);
	else
		EnableXSSAuditingCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::AccleratedCompositing))
		EnableAcceleratedCompositingCheckBox->setCheckState(Qt::Checked);
	else
		EnableAcceleratedCompositingCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::SiteSpecificQuirks))
		EnableSiteSpecificQuirksCheckBox->setCheckState(Qt::Checked);
	else
		EnableSiteSpecificQuirksCheckBox->setCheckState(Qt::Unchecked);
	if(preferences->getSettingsFor(Preferences::Proxy))
		enableProxyCheckBox->setCheckState(Qt::Checked);
	else
		enableProxyCheckBox->setCheckState(Qt::Unchecked);
	proxyHostNameEdit->setText(preferences->proxyHostName());
	proxyPasswordEdit->setText(preferences->password());
	portSpinBox->setValue(preferences->proxyPort());
	homePageUrlLineEdit->setText(preferences->homePage());
}
void PreferenceWindow::on_applyButton_clicked()
{
	preferences->setParameter(Preferences::LoadHomePageOnStartUp, !showLastVisitedRadioButton->isChecked());
	preferences->setParameter(Preferences::LoadImages, (autoLoadImagesCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::DnsPrefetch,(DnsPrefetchCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::JavaScript,(EnableJavascriptCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::JSApplet,(EnableJavaAppletsCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::JScanOpenWindows,(JavascriptCanOpenWindowsCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::JScanAccessclipboard,(JavascriptCanAccessClipboardCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::SpatialNavigation,(EnableSpatialNavigationCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::PrintElementBG,(PrintElementBackgroundsCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::LocalContentAccess,(LocalContentCanAccessFileUrlsCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::XSSAuditing,(EnableXSSAuditingCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::AccleratedCompositing,(EnableAcceleratedCompositingCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::SiteSpecificQuirks,(EnableSiteSpecificQuirksCheckBox->checkState() == Qt::Checked));
	preferences->setParameter(Preferences::Proxy,(enableProxyCheckBox->checkState() == Qt::Checked));
	preferences->setHomePage(homePageUrlLineEdit->text());
	preferences->setProxyPort(portSpinBox->value());
	preferences->setProxyHostName(proxyHostNameEdit->text());
	preferences->setPassword(proxyPasswordEdit->text());
	emit settingsChanged();
}
