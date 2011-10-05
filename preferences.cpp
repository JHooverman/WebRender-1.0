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



#include "preferences.h"
#include <QtWebKit/QWebSettings>
#include <QtWebKit/QWebPage>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkProxy>
#include <QtCore/QFile>
#include <QtCore/QDataStream>

void Preferences::getSettings(QWebPage *page) {
	settings = page->settings();
	autoLoadImages = settings->testAttribute(QWebSettings::AutoLoadImages);
	DnsPrefetchEnabled = settings->testAttribute(QWebSettings::DnsPrefetchEnabled);
	JavascriptEnabled = settings->testAttribute(QWebSettings::JavascriptEnabled);
	JavaAppletsEnabled = settings->testAttribute(QWebSettings::JavaEnabled);
	JavascriptCanOpenWindows = settings->testAttribute(QWebSettings::JavascriptCanOpenWindows);
	JavascriptCanAccessClipboard = settings->testAttribute(QWebSettings::JavascriptCanAccessClipboard);
	SpatialNavigationEnabled = settings->testAttribute(QWebSettings::SpatialNavigationEnabled);
	PrintElementBackgrounds = settings->testAttribute(QWebSettings::PrintElementBackgrounds);
	LocalContentCanAccessFileUrls = settings->testAttribute(QWebSettings::LocalContentCanAccessFileUrls);
	XSSAuditingEnabled = settings->testAttribute(QWebSettings::XSSAuditingEnabled);
	AcceleratedCompositingEnabled = settings->testAttribute(QWebSettings::AcceleratedCompositingEnabled);
	SiteSpecificQuirksEnabled = settings->testAttribute(QWebSettings::SiteSpecificQuirksEnabled);
	ProxyEnabled = (page->networkAccessManager()->proxy().type() != QNetworkProxy::NoProxy);
	port = page->networkAccessManager()->proxy().port();
	proxyhostname = page->networkAccessManager()->proxy().hostName();
	Password = page->networkAccessManager()->proxy().password();
}

bool Preferences::getSettingsFor(Preferences::SettingsList type) {
	switch(type)
	{
	case Preferences::LoadHomePageOnStartUp:
		return loadHomePageOnStartup;
	case Preferences::LoadImages:
		return autoLoadImages;
	case Preferences::DnsPrefetch:
		return DnsPrefetchEnabled;
	case Preferences::JavaScript:
		return JavascriptEnabled;
	case Preferences::JSApplet:
		return JavaAppletsEnabled;
	case Preferences::JScanOpenWindows:
		return JavascriptCanOpenWindows;
	case Preferences::JScanAccessclipboard:
		return JavascriptCanAccessClipboard;
	case Preferences::SpatialNavigation:
		return SpatialNavigationEnabled;
	case Preferences::PrintElementBG:
		return PrintElementBackgrounds;
	case Preferences::LocalContentAccess:
		return LocalContentCanAccessFileUrls;
	case Preferences::XSSAuditing:
		return XSSAuditingEnabled;
	case Preferences::AccleratedCompositing:
		return AcceleratedCompositingEnabled;
	case Preferences::SiteSpecificQuirks:
		return SiteSpecificQuirksEnabled;
	case Preferences::Proxy:
		return ProxyEnabled;
	default:
		return false;
	}
}

QString Preferences::homePage() 
{
	return homepage;
}

void Preferences::setHomePage(QString page)
{
	homepage = page;
}

void Preferences::setEnableHomePage(bool on)
{
	loadHomePageOnStartup = on;
}

void Preferences::setProxyPort(quint16 no)
{
	port = no;
}

quint16 Preferences::proxyPort()
{
	return port;
}

void Preferences::setProxyHostName(QString name)
{
	proxyhostname = name;
}

QString Preferences::proxyHostName()
{
	return proxyhostname;
}

bool Preferences::set(QWebPage *page)
{
	page->settings()->setAttribute(QWebSettings::AutoLoadImages,autoLoadImages);
	page->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled,DnsPrefetchEnabled);
	page->settings()->setAttribute(QWebSettings::JavascriptEnabled,JavascriptEnabled);
	page->settings()->setAttribute(QWebSettings::JavaEnabled,JavaAppletsEnabled);
	page->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows,JavascriptCanOpenWindows);
	page->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard,JavascriptCanAccessClipboard);
	page->settings()->setAttribute(QWebSettings::SpatialNavigationEnabled,SpatialNavigationEnabled);
	page->settings()->setAttribute(QWebSettings::PrintElementBackgrounds,PrintElementBackgrounds);
	page->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,LocalContentCanAccessFileUrls);
	page->settings()->setAttribute(QWebSettings::XSSAuditingEnabled,XSSAuditingEnabled);
	page->settings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled,AcceleratedCompositingEnabled);
	page->settings()->setAttribute(QWebSettings::SiteSpecificQuirksEnabled,SiteSpecificQuirksEnabled);
	page->networkAccessManager()->proxy().setPort(port);
	page->networkAccessManager()->proxy().setHostName(proxyhostname);
	page->networkAccessManager()->proxy().setPassword(Password);
	return true;
}

bool Preferences::writeToFile(QFile &file)
{
	if(!file.open(QIODevice::WriteOnly))
		return false;
	QDataStream in(&file);
	in<<homepage;
	in<<loadHomePageOnStartup;
	in<<autoLoadImages;
	in<<DnsPrefetchEnabled;
	in<<JavascriptEnabled;
	in<<JavaAppletsEnabled;
	in<<JavascriptCanOpenWindows;
	in<<JavascriptCanAccessClipboard;
	in<<SpatialNavigationEnabled;
	in<<PrintElementBackgrounds;
	in<<LocalContentCanAccessFileUrls;
	in<<XSSAuditingEnabled;
	in<<AcceleratedCompositingEnabled;
	in<<SiteSpecificQuirksEnabled;
	in<<port;
	in<<ProxyEnabled;
	in<<Password;
	in<<proxyhostname;
	return true;
}

bool Preferences::readFromFile(QFile &file)
{
	if(!file.open(QIODevice::ReadOnly))
		return false;
	QDataStream out(&file);
	out>>homepage;
	out>>loadHomePageOnStartup;
	out>>autoLoadImages;
	out>>DnsPrefetchEnabled;
	out>>JavascriptEnabled;
	out>>JavaAppletsEnabled;
	out>>JavascriptCanOpenWindows;
	out>>JavascriptCanAccessClipboard;
	out>>SpatialNavigationEnabled;
	out>>PrintElementBackgrounds;
	out>>LocalContentCanAccessFileUrls;
	out>>XSSAuditingEnabled;
	out>>AcceleratedCompositingEnabled;
	out>>SiteSpecificQuirksEnabled;
	out>>port;
	out>>ProxyEnabled;
	out>>Password;
	out>>proxyhostname;
	return true;
}
void Preferences::setPassword(QString passwd)
{
	Password = passwd;
}
QString Preferences::password()
{
	return Password;
}

void Preferences::setParameter(Preferences::SettingsList type, bool enabled)
{
	switch(type) 
	{
	case Preferences::LoadHomePageOnStartUp:
		loadHomePageOnStartup = enabled;
	break;
	case Preferences::LoadImages:
		autoLoadImages = enabled;
	break;
	case Preferences::DnsPrefetch:
		DnsPrefetchEnabled = enabled;
	case Preferences::JavaScript:
		JavascriptEnabled = enabled;
	break;
	case Preferences::JSApplet:
		JavaAppletsEnabled = enabled;
	break;
	case Preferences::JScanOpenWindows:
		JavascriptCanOpenWindows = enabled;
	break;
	case Preferences::JScanAccessclipboard:
		JavascriptCanAccessClipboard = enabled;
	break;
	case Preferences::SpatialNavigation:
		SpatialNavigationEnabled = enabled;
	break;
	case Preferences::PrintElementBG:
		PrintElementBackgrounds = enabled;
	break;
	case Preferences::LocalContentAccess:
		LocalContentCanAccessFileUrls = enabled;
	break;
	case Preferences::XSSAuditing:
		XSSAuditingEnabled = enabled;
	break;
	case Preferences::AccleratedCompositing:
		AcceleratedCompositingEnabled = enabled;
	break;
	case Preferences::SiteSpecificQuirks:
		SiteSpecificQuirksEnabled = enabled;
	break;
	case Preferences::Proxy:
		ProxyEnabled = enabled;
	break;
	default:
		return;
	}
}
