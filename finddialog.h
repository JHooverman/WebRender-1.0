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

#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include "infowidget.h"
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtWebKit/QWebPage>

class FindDialog : public InfoWidget
{
	Q_OBJECT
	public:
	FindDialog(QWebPage *page);
	void setPage(QWebPage *page);
	private:
	QWebPage *webPage;
	QLineEdit *searchEdit;
	QPushButton *findButton;
	QHBoxLayout *mainLayout;
	QPushButton *closeButton;
	private slots:
	void on_findButton_clicked();
};
#endif
