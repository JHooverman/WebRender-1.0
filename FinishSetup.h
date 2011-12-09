#ifndef FINISHSETUP_H
#define FINISHSETUP_H
#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include "WebRenderAnimation.h"
class FinishSetup : public QWidget {
	Q_OBJECT
	public:
	FinishSetup(QWidget *parent = 0);
	public slots:
	void getReady();
	private:
//	QPushButton *exploreButton;
	QPushButton *finishButton;
	QLabel *headingLabel;
	QHBoxLayout *headingLabelLayout;
	QLabel *mainLabel;
	QHBoxLayout *mainLabelLayout;
	WebRenderAnimation *imageLabel;//done
	QHBoxLayout *imageLabelLayout;
	QVBoxLayout *mainLayout;
	QHBoxLayout *buttonsLayout;
	signals:
	void setupFinished();
};
#endif
