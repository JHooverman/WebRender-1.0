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

#ifndef IPFINDER_H
#define IPFINDER_H
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

class IpFinder : public QWidget
{
	Q_OBJECT
	public:
	IpFinder();
	private:
	QLineEdit *urlEdit;
	QLabel *urlLabel;
	QPushButton *findButton;
	QPushButton *closeButton;
	QHBoxLayout *buttonLayout;
	QHBoxLayout *urlLayout;
	QVBoxLayout *mainLayout;
	private slots:
	void on_findButton_clicked();
	signals:
	void openUrl(QString url);
};
#endif
