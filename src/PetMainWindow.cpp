#include "PetMainWindow.h"
#include "ui_PetMainWindow.h"

#include "Forms/MessengerForm.h"
#include "Forms/InitScreenForm.h"
#include "Forms/LogRegForm.h"

#include <QWidget>
#include <QMessageBox>

#include <QDebug>

namespace PetGUI {

PetMainWindow::PetMainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::PetMainWindow) {
	ui->setupUi(this);
	init();
}

PetMainWindow::~PetMainWindow() { destroy(); }

void PetMainWindow::init() {
	m_currentType = FormType::Init;
	m_centralWidget = ui->centralwidget;
	try {
		m_centralLayout = dynamic_cast<QVBoxLayout*>(m_centralWidget->layout());
	} catch (const std::bad_cast & error) {
		qDebug() << error.what();
	}
	
	initInitForm();
	initSignInForm();
	initSignUpForm();
}

void PetMainWindow::initInitForm() {
	m_forms[FormType::Init] = new InitScreenForm(this);
	m_centralLayout->addWidget(m_forms[FormType::Init]);
	
	InitScreenForm * initForm = nullptr;
	try {
		initForm = dynamic_cast<InitScreenForm *>(m_forms[FormType::Init]);
	} catch (const std::bad_cast & error) {
		qDebug() << error.what();
	}
	
	initForm->setVisible(true);
	connect(initForm, &InitScreenForm::onSignInPressed, this, [this]() { setCurrentForm(FormType::SignIn); });
	connect(initForm, &InitScreenForm::onSignUpPressed, this, [this]() { setCurrentForm(FormType::SignUp); });
}

void PetMainWindow::initSignInForm() {
	m_forms[FormType::SignIn] = new LogRegForm(this);
	m_centralLayout->addWidget(m_forms[FormType::SignIn]);
	
	LogRegForm * form = nullptr;
	try {
		form = dynamic_cast<LogRegForm*>(m_forms[FormType::SignIn]);
	} catch (const std::bad_cast & error) {
		qDebug() << error.what();
	}
	
	form->setVisible(false);
}

void PetMainWindow::initSignUpForm() {
	m_forms[FormType::SignUp] = new LogRegForm(this, LogRegMode::SignUp);
	m_centralLayout->addWidget(m_forms[FormType::SignUp]);
	
	LogRegForm * form = nullptr;
	try {
		form = dynamic_cast<LogRegForm*>(m_forms[FormType::SignUp]);
	} catch (const std::bad_cast & error) {
		qDebug() << error.what();
	}
	
	form->setVisible(false);
}

void PetMainWindow::initMessengerForm() {
	
}

void PetMainWindow::destroy() {
	for (auto pair : m_forms)
		delete pair.second;
	m_forms.clear();
	
	m_centralLayout = nullptr;
	m_centralWidget = nullptr;
	delete ui;
}

void PetMainWindow::setCurrentForm(FormType type) {
	if (m_currentType == type) return;
	m_forms[m_currentType]->setVisible(false);
	m_currentType = type;
	m_forms[m_currentType]->setVisible(true);
}

}

