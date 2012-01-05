#include "LicenseReader.h"

LicenseReader::LicenseReader(QWidget *parent) : QWidget(parent) {
        headingLabel = new QLabel(tr("<b>You must accept the license agreement to use this software product.</b>"));
	acceptButton = new QPushButton(tr("Accept"));
	rejectButton = new QPushButton(tr("Reject"));
	buttonLayout = new QHBoxLayout;
	mainLayout = new QVBoxLayout;
	textEdit = new QTextEdit;

	buttonLayout->addStretch();
	buttonLayout->addWidget(acceptButton);
	buttonLayout->addWidget(rejectButton);

	mainLayout->addWidget(headingLabel);
	mainLayout->addWidget(textEdit);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
	setFixedSize(810,610);

	QFile file(":/LICENSE.GPL3");
	file.open(QIODevice::ReadOnly);
	QTextStream stream(&file);
	textEdit->setText(stream.readAll());
	textEdit->setReadOnly(true);

	connect(acceptButton,SIGNAL(clicked()),this,SIGNAL(accepted()));
	connect(rejectButton,SIGNAL(clicked()),this,SIGNAL(rejected()));
}
