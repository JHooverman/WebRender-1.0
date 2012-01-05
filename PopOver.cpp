#include "PopOver.h"
#include <QtGui/QImage>
#include <QtGui/QBrush>
#include <QtGui/QColor>
PopOver::PopOver(QWidget *parent) : QWidget(parent) {
	pixmap = new QPixmap(":/images/PopOver/mask.png");
	setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
	setMask(pixmap->mask());
	setFixedSize(320,170);
}

void PopOver::paintEvent(QPaintEvent *event)
{
	QImage image(QString(":/images/PopOver/mask.png"));
	QPainter widgetPainter(this);
	widgetPainter.drawImage(0,0,image);
}
