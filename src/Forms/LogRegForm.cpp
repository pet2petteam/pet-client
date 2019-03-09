#include "Forms/LogRegForm.h"
#include "ui_LogRegForm.h"
#include "PetGUI_const.h"

#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFrame>

namespace PetGUI {

LogRegForm::LogRegForm(QWidget *parent, LogRegMode mode) :
	QWidget(parent), m_mode(mode), ui(new Ui::LogRegForm) {
	ui->setupUi(this);
	
	m_logRegButton = ui->LogRegButton;
	m_loginLine = ui->LoginLine;
	m_emailLine = ui->EmailLine;
	m_passLine = ui->PassLine;
	m_emailFrame = ui->EmailFrame;
	
	if (mode == LogRegMode::SignIn) {
		m_emailFrame->setVisible(false);
		m_logRegButton->setText("Sign In");
	} else m_logRegButton->setText("Sign Up");
	
	connect(m_logRegButton, &QPushButton::pressed, this, &LogRegForm::onLogRegPressedHandler);
}

LogRegForm::~LogRegForm() { delete ui; }

void LogRegForm::onLogRegPressedHandler() {
	switch (m_mode) {
		case LogRegMode::SignIn:
			loginMode();
			break;
		case LogRegMode::SignUp:
			registrationMode();
			break;
	}
}

void LogRegForm::registrationMode() {
	if (!isValidLogin(m_loginLine->text())) return;
	if (!isValidEmail(m_emailLine->text())) return;
	if (!isValidPassword(m_passLine->text())) return;
	emit onLogRegPressed();
}

void LogRegForm::loginMode() {
	if (!isValidLogin(m_loginLine->text())) return;
	if (!isValidPassword(m_passLine->text())) return;
	emit onLogRegPressed();
}

bool LogRegForm::isValidLogin(const QString & login) {
	if (login.isEmpty()) {
		QMessageBox::critical(this, Const::ERROR_TITLE, "Login can't be empty.");
		return false;
	}
	if (!QRegExp(Const::LOGIN_REGEX).exactMatch(login)) {
		QMessageBox::critical(this, Const::ERROR_TITLE, "Login has forbidden symbols.");
		return false;
	}
	return true;
}

bool LogRegForm::isValidEmail(const QString & email) {
	if (email.isEmpty()) {
		QMessageBox::critical(this, Const::ERROR_TITLE, "Email can't be empty.");
		return false;
	}
	if (!QRegExp(Const::EMAIL_REGEX).exactMatch(email)) {
		QMessageBox::critical(this, Const::ERROR_TITLE, "Email is not valid.");
		return false;
	}
	return true;
}

bool LogRegForm::isValidPassword(const QString & pass) {
	if (pass.isEmpty()) {
		QMessageBox::critical(this, Const::ERROR_TITLE, "Password can't be empty.");
		return false;
	}
	if (!QRegExp(Const::PASSWORD_REGEX).exactMatch(pass)) {
		QMessageBox::information(this, Const::INFO_TITLE, "Password must has: 1 lowercase letter,\n"
		                                                  "1 uppercase letter and 1 special letter");
		return false;
	}
	return true;
}

}
