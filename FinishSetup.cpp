#include "FinishSetup.h"

FinishSetup::FinishSetup(QWidget *parent) : QWidget(parent) {
	headingLabel = new QLabel(tr("<b>Congratulations!</b>"));
	mainLabel = new QLabel(tr("The setup is complete. Surf and enjoy!"));
	imageLabel = new WebRenderAnimation;
//	exploreButton = new QPushButton(tr("Explore the tour"));
	finishButton = new QPushButton(tr("Finish"));

	headingLabelLayout = new QHBoxLayout;
	headingLabelLayout->addStretch();
	headingLabelLayout->addWidget(headingLabel);
	headingLabelLayout->addStretch();

	mainLabelLayout = new QHBoxLayout;
	mainLabelLayout->addStretch();
	mainLabelLayout->addWidget(mainLabel);
	mainLabelLayout->addStretch();

	imageLabelLayout = new QHBoxLayout;
	imageLabelLayout->addStretch();
	imageLabelLayout->addWidget(imageLabel);
	imageLabelLayout->addStretch();

	buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
//	buttonsLayout->addWidget(exploreButton);
	buttonsLayout->addWidget(finishButton);
	buttonsLayout->addStretch();

	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(headingLabelLayout);
	mainLayout->addLayout(mainLabelLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(imageLabelLayout);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(buttonsLayout);
	mainLayout->addStretch();

	setFixedSize(810,610);
	setLayout(mainLayout);

	connect(finishButton, SIGNAL(clicked()), this, SIGNAL(setupFinished()));
}

void FinishSetup::getReady() {
	imageLabel->startAnimation();
}
