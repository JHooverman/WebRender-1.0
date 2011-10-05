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

#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include "infowidget.h"
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QFile>

class Downloader : public InfoWidget
{
    Q_OBJECT
public:
    Downloader(QWidget *parent = 0);
    bool handleDownloadRequest(QNetworkAccessManager *manager, QNetworkRequest &request);
    bool handleDownloadRequest(QNetworkAccessManager *manager, QNetworkReply *r);
private:
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *cancelButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *layout;
    QNetworkReply *reply;
    QString absFileName;
    QString fileName;
    QFile *file;
    bool finishedDownloading;
private slots:
    void setProgress(qint64 received, qint64 total);
    void abortDownload();
    void finished();
    void httpReadyRead();
};

#endif // DOWNLOADER_H
