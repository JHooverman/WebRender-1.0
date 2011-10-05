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



#ifndef PREFERENCES_H
#define PREFERENCES_H
#include <QtCore/QString>
#include <QtWebKit/QWebSettings>
#include <QtWebKit/QWebPage>
#include <QtCore/QDir>
#include <QtCore/QFile>

class Preferences
{
	public:
	void getSettings(QWebPage *page);
	bool set(QWebPage *page);
	bool readFromFile(QFile &file);
	bool writeToFile(QFile &file);
	enum SettingsList
	{
		LoadHomePageOnStartUp,
		LoadImages,
		DnsPrefetch,
		JavaScript,
		JSApplet,
		JScanOpenWindows,
		JScanAccessclipboard,
		SpatialNavigation,
		PrintElementBG,
		LocalContentAccess,
		XSSAuditing,
		AccleratedCompositing,
		SiteSpecificQuirks,
		Proxy
	};
	void setParameter(Preferences::SettingsList type, bool enabled);
	bool getSettingsFor(Preferences::SettingsList type);
	void setHomePage(QString page);
	void setEnableHomePage(bool on);
	QString homePage();
	void setProxyPort(quint16 no);
	void setProxyHostName(QString name);
	quint16 proxyPort();
	QString proxyHostName();
	void setPassword(QString passwd);
	QString password();
	private:
	QWebSettings *settings;
	QString homepage;
	bool loadHomePageOnStartup;
	bool autoLoadImages;
	bool DnsPrefetchEnabled;
	bool JavascriptEnabled;
	bool JavaAppletsEnabled;
	bool JavascriptCanOpenWindows;
	bool JavascriptCanAccessClipboard;
	bool SpatialNavigationEnabled;
	bool PrintElementBackgrounds;
	bool LocalContentCanAccessFileUrls;
	bool XSSAuditingEnabled;
	bool AcceleratedCompositingEnabled;
	bool SiteSpecificQuirksEnabled;
	/*Network settings */
	quint16 port;
	bool ProxyEnabled;
	QString Password;
	QString proxyhostname;
};
#endif
