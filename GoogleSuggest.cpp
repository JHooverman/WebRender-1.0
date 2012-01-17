#include "GoogleSuggest.h"


GoogleSuggest::GoogleSuggest(QLineEdit *parent) : QObject(parent) {
    suggestionList = new QListWidget;
	layout = new QHBoxLayout;
	popover = new PopOver;
	popover->setWindowOpacity(0.95);
	layout->addWidget(suggestionList);
	layout->setContentsMargins(15,40,15,15);
	popover->setLayout(layout);
	popover->setWindowFlags(Qt::Popup);
	popover->setFocusPolicy(Qt::NoFocus);
	suggestionList->installEventFilter(this);
    lineEdit = parent;
	timer = new QTimer;
	timer->setSingleShot(true);
    connect(lineEdit,SIGNAL(textEdited(QString)),this,SLOT(fetchSuggestions(QString)));
	connect(timer,SIGNAL(timeout()),this,SLOT(sendRequest()));
	connect(suggestionList, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(fillSearchBar(QListWidgetItem*)));
    manager = new QNetworkAccessManager;
}

void GoogleSuggest::setNetworkAccessManager(QNetworkAccessManager *m)
{
	manager = m;
}

void GoogleSuggest::fetchSuggestions(QString query) {
//    query.replace(" ", "+");
//    query.replace("+","%%2B");
	Query = query;
	timer->start(250);
}

void GoogleSuggest::timerStart() {
	std::cout<<"Finished reading"<<std::endl;
	timer->start(250);
}
void GoogleSuggest::sendRequest() {
    QNetworkRequest request(QUrl(QString("http://google.com/complete/search?output=toolbar&q=%1").arg(Query)));
    reply = manager->get(request);
	connect(reply,SIGNAL(finished()),this,SLOT(populate()));
}

void GoogleSuggest::populate()
{
	suggestionList->clear();
	QDomDocument document;
	if(!document.setContent(reply)) {
		std::cout<<"Parse failed\n";
		return;
	}
	QDomElement root = document.documentElement();// Represents <toplevel> tag
	QDomNode child = root.firstChild();//Represents <CompleteSuggestion> tag
	QListWidgetItem *listWidgetItem;
	while(!child.isNull()) {
		listWidgetItem = new QListWidgetItem;
		listWidgetItem->setText(child.firstChildElement("suggestion").attribute("data"));
		suggestionList->addItem(listWidgetItem);
		child = child.nextSibling();//Represents next <CompleteSuggestion> tag
	}

	popover->move(lineEdit->mapToGlobal(QPoint((lineEdit->width()-320)/2,lineEdit->height())));
	if(suggestionList->count() != 0) {
		popover->show();
		suggestionList->setFocus();
	}
}

void GoogleSuggest::fillSearchBar(QListWidgetItem *item)
{
	lineEdit->setText(item->text());
	suggestionList->clear();
	popover->close();
	lineEdit->setFocus();
}

bool GoogleSuggest::eventFilter(QObject *object, QEvent *event)
{

	if(object != suggestionList) return false;

	if(event->type() == QEvent::MouseButtonPress) {
		popover->hide();
		lineEdit->setFocus();
		return true;
	}

	if(event->type() == QEvent::KeyPress) {
		int key = static_cast<QKeyEvent*>(event)->key();
		switch(key) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				lineEdit->setText(suggestionList->currentItem()->text());
				lineEdit->event(event);
				popover->close();
				lineEdit->setFocus();
				return true;

			case Qt::Key_Up:
			case Qt::Key_Down:
			case Qt::Key_Home:
			case Qt::Key_End:
			case Qt::Key_PageUp:
			case Qt::Key_PageDown:
				break;

			default:
				lineEdit->setFocus();
				lineEdit->event(event);
				popover->hide();
				break;
		};

		return false;
	}
	return false;
}
