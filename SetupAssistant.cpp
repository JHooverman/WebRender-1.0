#include "SetupAssistant.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDir>
#include <QtGui/QMessageBox>
#include "mainwindow.h"
SetupAssistant::SetupAssistant(QWidget *parent) : QWidget(parent) {
	welcomeView = new WelcomeView(this);
	licenseReader = new LicenseReader(this);
	downloadSetup = new DownloadSetup(this);
	finishSetup = new FinishSetup(this);

	stateMachine = new QStateMachine;
	welcomeState = new QState;
	licenseReaderState = new QState;
	downloadSetupState = new QState;
	finishState = new QState;

	welcomeState->assignProperty(welcomeView,"pos",QVariant(QPointF(0,0)));
	welcomeState->assignProperty(licenseReader,"pos",QVariant(QPointF(810,0)));
	welcomeState->assignProperty(downloadSetup,"pos",QVariant(QPointF(1620,0)));
	welcomeState->assignProperty(finishSetup,"pos",QVariant(QPointF(2430,0)));

	licenseReaderState->assignProperty(welcomeView,"pos",QVariant(QPointF(-810,0)));
	licenseReaderState->assignProperty(licenseReader,"pos",QVariant(QPointF(0,0)));
	licenseReaderState->assignProperty(downloadSetup,"pos",QVariant(QPointF(810,0)));
	licenseReaderState->assignProperty(finishSetup,"pos",QVariant(QPointF(1620,0)));

	downloadSetupState->assignProperty(welcomeView,"pos",QVariant(QPointF(-1620,0)));
	downloadSetupState->assignProperty(licenseReader,"pos",QVariant(QPointF(-810,0)));
	downloadSetupState->assignProperty(downloadSetup,"pos",QVariant(QPointF(0,0)));
	downloadSetupState->assignProperty(finishSetup,"pos",QVariant(QPointF(810,0)));

	finishState->assignProperty(welcomeView,"pos",QVariant(QPointF(-2430,0)));
	finishState->assignProperty(licenseReader,"pos",QVariant(QPointF(-1620,0)));
	finishState->assignProperty(downloadSetup,"pos",QVariant(QPointF(-810,0)));
	finishState->assignProperty(finishSetup,"pos",QVariant(QPointF(0,0)));


	transition1 = welcomeState->addTransition(welcomeView, SIGNAL(nextClicked()), licenseReaderState);
	transition2 = licenseReaderState->addTransition(licenseReader, SIGNAL(accepted()), downloadSetupState);
	transition3 = downloadSetupState->addTransition(downloadSetup, SIGNAL(setupFinished()), finishState);

	transition1->addAnimation(new QPropertyAnimation(welcomeView,"pos"));
	transition1->addAnimation(new QPropertyAnimation(licenseReader,"pos"));

	transition2->addAnimation(new QPropertyAnimation(licenseReader,"pos"));
	transition2->addAnimation(new QPropertyAnimation(downloadSetup,"pos"));

	transition3->addAnimation(new QPropertyAnimation(downloadSetup,"pos"));
	transition3->addAnimation(new QPropertyAnimation(finishSetup,"pos"));

	stateMachine->addState(welcomeState);
	stateMachine->addState(licenseReaderState);
	stateMachine->addState(downloadSetupState);
	stateMachine->addState(finishState);
	stateMachine->setInitialState(welcomeState);

	stateMachine->start();
	setFixedSize(810,610);
	setWindowTitle("WebRender Setup Assistant");
	connect(licenseReader, SIGNAL(rejected()),this,SLOT(close()));
	connect(finishSetup, SIGNAL(setupFinished()), this, SLOT(saveSettings()));
	connect(downloadSetup, SIGNAL(setupFinished()), finishSetup, SLOT(getReady()));
}

void SetupAssistant::showAnimated()
{
	this->show();
	welcomeView->startAnimation();
}

void SetupAssistant::saveSettings()
{
	QDir homeDir = QDir::home();
	homeDir.mkdir(".WebRender");
	if(!homeDir.cd(".WebRender")) {
		QMessageBox::critical(this,"Error","WebRender is unable to create the configuration directory. Check the permissions and run setup again.");
		return;
	}
	QFile file(homeDir.absoluteFilePath("download.path"));
	QFile versionFile(homeDir.absoluteFilePath("version.info"));
	if(!file.open(QIODevice::WriteOnly) || !versionFile.open(QIODevice::WriteOnly)) {
		QMessageBox::critical(this,"Error","WebRender is unable to save the configuration settings. Check the permissions and run setup again.");
		return;
	}
	QTextStream stream(&file);
	QTextStream versionFileStream(&versionFile);
	stream<<downloadSetup->getDownloadPath();
	versionFileStream<<QString("RC 3");
	close();
	(new MainWindow)->show();
	emit setupFinished();
}
