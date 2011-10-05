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


#ifndef PREFERENCEWINDOW_H
#define PREFERENCEWINDOW_H
#include "infowidget.h"
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTabWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QPushButton>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include "preferences.h"

class PreferenceWindow : public InfoWidget
{
	Q_OBJECT
	public:
	PreferenceWindow(Preferences *prefs);
	void initialise();
	private:
	Preferences *preferences;
	QTabWidget *mainTabWidget;
	QWidget *page1;
	QWidget *page2;
	QWidget *page3;
	/* Home page tab */
	QGroupBox *homePageGroupBox; 
	QRadioButton *showLastVisitedRadioButton;// (*) Show Last Visited Page 
	QRadioButton *showHomePageRadioButton;// (*) Show Home Page 
	QLabel *homePageLabel;
	QLineEdit *homePageUrlLineEdit;
//	QPushButton *selectHomePageTempleteButton;
	QVBoxLayout *homePageRadioButtonLayout;
	QHBoxLayout *homePageUrlLayout;
	QVBoxLayout *homepageMainLayout;
	/* end of home page tab */

	/* Misc tab */
	QGroupBox *miscSettingsGroupBox;
	QCheckBox *autoLoadImagesCheckBox;
	QCheckBox *DnsPrefetchCheckBox;
	QCheckBox *EnableJavascriptCheckBox;
	QCheckBox *EnableJavaAppletsCheckBox;
	QCheckBox *JavascriptCanOpenWindowsCheckBox;
	QCheckBox *JavascriptCanAccessClipboardCheckBox;
	QCheckBox *EnableSpatialNavigationCheckBox;
	QCheckBox *PrintElementBackgroundsCheckBox;
	QCheckBox *LocalContentCanAccessFileUrlsCheckBox;
	QCheckBox *EnableXSSAuditingCheckBox;
	QCheckBox *EnableAcceleratedCompositingCheckBox;
	QCheckBox *EnableSiteSpecificQuirksCheckBox;
	QVBoxLayout *miscTabLayout;
	/* End of misc tab */

	/* network settings tab */
	QGroupBox *proxyGroupBox;
	QCheckBox *enableProxyCheckBox;
	QLabel *proxyHostNameLabel;
	QLineEdit *proxyHostNameEdit;
	QLabel *proxyPasswordLabel;
	QLineEdit *proxyPasswordEdit;
	QLabel *portLabel;
	QSpinBox *portSpinBox;
	QHBoxLayout *proxyHostNameLayout;
	QHBoxLayout *proxyPasswordLayout;
	QHBoxLayout *proxyPortLayout;
	QVBoxLayout *proxyMainLayout;
	/* eof network settings tab */
	QHBoxLayout *tab1Layout;
	QHBoxLayout *tab2Layout;
	QHBoxLayout *tab3Layout;

	QVBoxLayout *mainLayout;
	QHBoxLayout *buttons;
	QPushButton *applyButton;
	QPushButton *closeButton;
	private slots:
	void on_applyButton_clicked();
	signals:
	void settingsChanged();
};
#endif
