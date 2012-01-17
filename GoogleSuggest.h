#ifndef GOOGLESUGGEST_H
#define GOOGLESUGGEST_H
#include "PopOver.h"
#include <QtGui/QHBoxLayout>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QTimer>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtXml/QDomElement>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QUrl>
#include <QtXml/QDomDocument>
#include <QtGui/QListWidgetItem>
#include <QtXml/QDomNode>
#include <QtCore/QEvent>
#include <QtGui/QKeyEvent>
#include <iostream>
class GoogleSuggest : public QObject {
    Q_OBJECT
public:
    GoogleSuggest(QLineEdit *parent = 0);
    void setNetworkAccessManager(QNetworkAccessManager *m);
    bool eventFilter(QObject *object, QEvent *event);
private:
    QNetworkAccessManager *manager;
    QLineEdit *lineEdit;
    QListWidget *suggestionList;
	PopOver *popover;
	QHBoxLayout *layout;
	QNetworkReply *reply;
	QTimer *timer;
	QString Query;
private slots:
	void timerStart();
    void fetchSuggestions(QString query);
	void sendRequest();
	void populate();
	void fillSearchBar(QListWidgetItem *item);
};

#endif // GOOGLESUGGEST_H
