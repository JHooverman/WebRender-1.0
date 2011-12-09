#include "DownloadSetup.h"
#include <QtGui/QFileDialog>
DownloadSetup::DownloadSetup(QWidget *parent) : QWidget(parent) {
	setButton = new QPushButton(tr("Select Directory"));
	nextButton = new QPushButton(tr("Next"));
	headingLabel = new QLabel(tr("<b>Select your downloads directory</b>"));
	mainLabel = new QLabel(tr("Choose a directory to keep the downloaded files."));
	downloadDir = QDir::home();
	downloadDir.cd("Downloads");
	downloadPath = downloadDir.absolutePath();
	pathLabel = new QLabel(tr("Default: ") + downloadPath); //okay
	imageLabel = new QLabel;
	imageLabel->setPixmap(QPixmap(":/images/SetupAssistant/downloads.png"));

	setButtonLayout = new QHBoxLayout;
	setButtonLayout->addStretch();
	setButtonLayout->addWidget(setButton);
	setButtonLayout->addStretch();


	headingLabelLayout = new QHBoxLayout;
	headingLabelLayout->addStretch();
	headingLabelLayout->addWidget(headingLabel);
	headingLabelLayout->addStretch();

	mainLabelLayout = new QHBoxLayout;
	mainLabelLayout->addStretch();
	mainLabelLayout->addWidget(mainLabel);
	mainLabelLayout->addStretch();

	pathLabelLayout = new QHBoxLayout;
	pathLabelLayout->addStretch();
	pathLabelLayout->addWidget(pathLabel);
	pathLabelLayout->addStretch();

	imageLabelLayout = new QHBoxLayout;
	imageLabelLayout->addStretch();
	imageLabelLayout->addWidget(imageLabel);
	imageLabelLayout->addStretch();

	buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(nextButton);

	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(headingLabelLayout);
	mainLayout->addLayout(mainLabelLayout);
	mainLayout->addLayout(pathLabelLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(imageLabelLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(setButtonLayout);
	mainLayout->addStretch();
	mainLayout->addLayout(buttonsLayout);

	setLayout(mainLayout);
	setFixedSize(810,610);
	connect(nextButton,SIGNAL(clicked()),this,SIGNAL(setupFinished()));
	connect(setButton,SIGNAL(clicked()),this,SLOT(chooseDownloadDirectory()));
}

void DownloadSetup::chooseDownloadDirectory() {
	downloadPath = QFileDialog::getExistingDirectory(this,tr("Choose a folder"),QDir::homePath());
	if(downloadPath.isEmpty()) {
		downloadPath = downloadDir.absolutePath();
		pathLabel = new QLabel(tr("Default: ") + downloadPath);
	} else {
		pathLabel->setText(tr("Your downloads will be saved to: ") + downloadPath);
	}
}

QString DownloadSetup::getDownloadPath() {
	return downloadPath;
}
