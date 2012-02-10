#ifndef HISTORYWRITER_H
#define HISTORYWRITER_H
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtWebKit/QWebHistoryItem>
#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDir>
#include <QtCore/QVariant>

class HistoryWriter : public QObject {
	Q_OBJECT
	public:
	HistoryWriter();
	void addHistoryItem(QWebHistoryItem item);
	void save();
	private:
	QString xmlContent;
	bool successfullyOpenedHistoryFile;
	QDir settingsDir;
	QFile *file;

};
#endif
