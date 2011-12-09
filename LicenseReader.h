#ifndef LICENSEREADER_H
#define LICENSEREADER_H
#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

class LicenseReader : public QWidget {
	Q_OBJECT
	public:
	LicenseReader(QWidget *parent=0);
	private:
	QLabel *headingLabel;
	QHBoxLayout *buttonLayout;
	QVBoxLayout *mainLayout;
	QPushButton *acceptButton;
	QPushButton *rejectButton;
	QTextEdit *textEdit;
	signals:
	void accepted();
	void rejected();
};
#endif
