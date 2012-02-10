#include "HistoryWriter.h"
#include <iostream>

HistoryWriter::HistoryWriter() {
	successfullyOpenedHistoryFile = false;
	settingsDir = QDir::home();
	settingsDir.cd(".WebRender");
	file = new QFile(settingsDir.absoluteFilePath("history.xml"));
	successfullyOpenedHistoryFile = file->open(QIODevice::WriteOnly | QIODevice::Append);
}

void HistoryWriter::addHistoryItem(QWebHistoryItem item) {

	QDomDocument history("history");
	QDomElement historyElement = history.createElement("history");
	history.appendChild(historyElement);

	QDomElement titleElement = history.createElement("title");
	historyElement.appendChild(titleElement);
	QDomText title = history.createTextNode(item.title());
	titleElement.appendChild(title);

	QDomElement urlElement = history.createElement("url");
	historyElement.appendChild(urlElement);
	QDomText url = history.createTextNode(item.url().toString());
	urlElement.appendChild(url);

	QDomElement dateElement = history.createElement("date");
	historyElement.appendChild(dateElement);
	QDomText date = history.createTextNode(item.lastVisited().toString());
	dateElement.appendChild(date);

	xmlContent.append(history.toString());
}

void HistoryWriter::save() {
	if(!successfullyOpenedHistoryFile) return;
	QTextStream doc(file);
	doc<<xmlContent;
}
