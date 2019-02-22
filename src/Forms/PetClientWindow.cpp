#include "Forms/PetClientWindow.h"
#include "Forms/MessengerWidget.h"
#include "Forms/InitScreenWidget.h"
#include "Forms/LogRegWidget.h"
#include "ui_PetClientWindow.h"

#include <QWidget>
#include <QMessageBox>

#include <iostream>

namespace PetGUI {

PetClientWindow::PetClientWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::PetClientWindow) {
	ui->setupUi(this);
	
	m_state = WindowState::Start;
	m_centralWidget = ui->centralwidget;
	
	m_centralWidget->setLayout(m_centralLayout = new QVBoxLayout());
	m_centralLayout->addWidget(m_initScreen = new InitScreenWidget(this));
	
	connect(m_initScreen, &InitScreenWidget::onLoginPressed, this, &PetClientWindow::initSignInForm);
	connect(m_initScreen, &InitScreenWidget::onRegistrationPressed, this, &PetClientWindow::initSignUpForm);
}

PetClientWindow::~PetClientWindow() {
	delete ui;
}

void PetClientWindow::initSignInForm() {
	m_initScreen->setVisible(false);
	m_centralLayout->addWidget(m_signInUpWidget = new LogRegWidget(this));
	m_signInUpWidget->show();
}

void PetClientWindow::initSignUpForm() {
	m_initScreen->setVisible(false);
	m_centralLayout->addWidget(m_signInUpWidget = new LogRegWidget(this, LogRegMode::SignUp));
	m_signInUpWidget->show();
}

}

