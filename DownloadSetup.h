#ifndef DOWNLOADSETUP_H
#define DOWNLOADSETUP_H
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtCore/QDir>

class DownloadSetup : public QWidget {
	Q_OBJECT
	public:
	DownloadSetup(QWidget *parent = 0);
	QString getDownloadPath();
	private:
	QDir downloadDir;
	QString downloadPath;
	QPushButton *setButton;
	QHBoxLayout *setButtonLayout;
	QPushButton *nextButton;
	QLabel *headingLabel;
	QHBoxLayout *headingLabelLayout;
	QLabel *mainLabel;
	QHBoxLayout *mainLabelLayout;
	QLabel *pathLabel;
	QHBoxLayout *pathLabelLayout;
	QLabel *imageLabel;
	QHBoxLayout *imageLabelLayout;
	QVBoxLayout *mainLayout;
	QHBoxLayout *buttonsLayout;
	private slots:
	void chooseDownloadDirectory();
	signals:
	void setupFinished();
};
#endif
