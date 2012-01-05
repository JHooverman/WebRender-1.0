#ifndef POPOVER_H
#define POPOVER_H
#include <QtGui/QWidget>
#include <QtGui/QPixmap>
#include <QtGui/QBitmap>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
class PopOver : public QWidget {
	Q_OBJECT
	public:
	PopOver(QWidget *parent = 0);
	private:
	QPixmap *pixmap;
	protected:
	void paintEvent(QPaintEvent *event);
};
#endif
