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

#include "downloader.h"
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtGui/QFileDialog>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QFileInfo>
#include <QtCore/QByteArray>

#include <QtCore/QUrl>
#include <QtGui/QMessageBox>

Downloader::Downloader(QWidget *parent)
{
    label = new QLabel;
    progressBar = new QProgressBar;
    progressBar->setFormat(" %v / %m KB");
    cancelButton = new QPushButton(tr("Cancel"));
    layout = new QHBoxLayout;
    layout->addWidget(progressBar);
    layout->addWidget(cancelButton);
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addLayout(layout);
    mainLayout->setContentsMargins(5,25,5,5);
    setLayout(mainLayout);
    setTitle(tr("Downloader"));
	finishedDownloading = false;

	configurationDir = QDir::home();
	configurationDir.cd(".WebRender");
	downloadConfFile = new QFile(configurationDir.absoluteFilePath("download.path"));
	downloadConfFile->open(QIODevice::ReadOnly);
	QTextStream stream(downloadConfFile);
	downloadsDir = QDir(stream.readAll());
}

bool Downloader::handleDownloadRequest(QNetworkAccessManager *manager, QNetworkRequest &request)
{
    QNetworkReply* r = manager->get(request);
    handleDownloadRequest(manager, r);
    return true;
}

bool Downloader::handleDownloadRequest(QNetworkAccessManager *manager, QNetworkReply *r)
{
    reply = r;
    QUrl url = reply->url();
    fileName = QFileInfo(url.path()).fileName();
	if(QMessageBox::question(this,tr("Download the file?"),tr("Do you really wish to download ") + fileName) != QMessageBox::Ok)
		return false;
    absFileName = downloadsDir.absoluteFilePath(fileName);
    if(absFileName.isEmpty())
        return false;
    file = new QFile(absFileName);
    file->open(QIODevice::WriteOnly);
    label->setText(tr("Downloading ") + fileName);
    setTitle(tr("Downloading"));
    cancelButton->setText(tr("Cancel"));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(setProgress(qint64,qint64)));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(abortDownload()));
    connect(reply,SIGNAL(finished()),this,SLOT(finished()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));
    return true;
}

void Downloader::setProgress(qint64 received, qint64 total)
{
    progressBar->setRange(0,(total/1024));
    progressBar->setValue(received/1024);
//  file->write(reply->readAll());
}

void Downloader::httpReadyRead()
{
	file->write(reply->readAll());
}

void Downloader::abortDownload()
{
	if(file != NULL) {
		file->close();
		if(!finishedDownloading) file->remove();
		file->deleteLater();
	}
	if(reply != NULL) {
		reply->deleteLater();
	}
	close();
}

void Downloader::finished()
{
	if(!file || !reply) return;
	file->flush();
	file->close();
    	if(reply->error()) {
		file->remove();
                setTitle(tr("Download failed."));
		finishedDownloading = false;
	} else {
                setTitle(tr("Download finished."));
		finishedDownloading = true;
	}
        cancelButton->setText(tr("Close"));
	reply->deleteLater();
	file->deleteLater();
	file = NULL;
	reply = NULL;
}
