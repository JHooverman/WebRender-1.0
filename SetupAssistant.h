#ifndef SETUPASSISTANT_H
#define SETUPASSISTANT_H

#include <QtGui/QWidget>
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QSignalTransition>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QDesktopWidget>
#include "WelcomeView.h"
#include "LicenseReader.h"
#include "DownloadSetup.h"
#include "FinishSetup.h"

class SetupAssistant : public QWidget {
	Q_OBJECT
	public:
	SetupAssistant(QWidget *parent = 0);
	void showAnimated();
	private:
        QDesktopWidget *desktopWidget;
	WelcomeView *welcomeView;
	LicenseReader *licenseReader;
	DownloadSetup *downloadSetup;
	FinishSetup *finishSetup;
	QStateMachine *stateMachine;
	QState *welcomeState;
	QState *licenseReaderState;
	QState *downloadSetupState;
	QState *finishState;

	QSignalTransition *transition1;
	QSignalTransition *transition2;
	QSignalTransition *transition3;
	private slots:
	void saveSettings();
	signals:
	void setupFinished();
};

#endif
