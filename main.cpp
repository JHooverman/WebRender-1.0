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


#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QUrl>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
        QCoreApplication::setApplicationName(QString("WebRender"));
        QCoreApplication::setOrganizationName(QString("WebRender"));
	MainWindow *window = new MainWindow;
        if(app.arguments().count() > 1)
        {
            QUrl url = QUrl(app.arguments().at(1));
            url.setScheme("file");
            window->loadUrl(url);
        }
	window->show();
	return app.exec();
}
