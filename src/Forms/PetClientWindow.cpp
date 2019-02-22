#include "Forms/PetClientWindow.h"
#include "Forms/MessengerWidget.h"
#include "ui_PetClientWindow.h"

#include <QWidget>
#include <QMessageBox>

#include <iostream>

PetClientWindow::PetClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PetClientWindow) {
	ui->setupUi(this);
	
	m_state = WindowState::Start;
	
	m_startFrame = ui->startWindowFrame;
	
	m_signInUpFrame = ui->signInUpWindowFrame;
	m_signInUpFrame->setVisible(false);
	
	m_confirmationFrame = ui->confirmationWindowFrame;
	m_confirmationFrame->setVisible(false);
	
	m_messenger = new MessengerWidget(this);
	m_messagingFrame = ui->messagingWindowFrame;
	ui->messengerLayout->addWidget(m_messenger);
	m_messenger->show();
	m_messagingFrame->setVisible(false);
	
	m_messenger->appendReceivedMessage("This is a text message");
	m_messenger->appendReceivedMessage("Это тестовое сообщение");
	
	
	connect(ui->signInButton, &QPushButton::clicked, this, &PetClientWindow::onPressSignIn);
	connect(ui->signUpButton, &QPushButton::clicked, this, &PetClientWindow::onPressSignUp);
	connect(ui->signInButton_2, &QPushButton::clicked, this, &PetClientWindow::onPressSignInUp);
	
	connect(m_messenger, &MessengerWidget::onMessageSend, this, [=](const QString & messString){
		std::cout << "send message: " + messString.toStdString();
	});
}

PetClientWindow::~PetClientWindow() {
	delete m_messenger;
	delete ui;
}

LoginStatus PetClientWindow::checkLogin(const QString & login, QString & mess) {
	mess.clear();
	if (login.isEmpty()) {
		mess = "Login is empty";
		return LoginStatus::Empty;
	}
	if (login.length() < MIN_LOGIN_LENGTH) {
		mess = "Login is too short";
		return  LoginStatus::Short;
	}
	if (login.length() > MAX_LOGIN_LENGTH) {
		mess = "Login is too long";
		return LoginStatus::Long;
	}
	if (checkForWrongSymbols(login)) {
		mess = "Login has forbidden symbols";
		return LoginStatus::Invalid;
	}
	if (!checkLoginIsFree(login)) {
		mess = "Login is already taken";
		return LoginStatus::Taken;
	}
	return LoginStatus::Ok;
}

PasswordStatus PetClientWindow::checkPassword(const QString & pass, QString & mess) {
	mess.clear();
	if (pass.isEmpty()) {
		mess = "Password is empty";
		return PasswordStatus::Empty;
	}
	if (pass.length() < MIN_PASSWORD_LENGTH) {
		mess = "Password is too short";
		return  PasswordStatus::Short;
	}
	if (pass.length() > MAX_PASSWORD_LENGTH) {
		mess = "Password is too long";
		return PasswordStatus::Long;
	}
	if (!checkPassComplexity(pass)) {
		mess = "Password is easy";
		return PasswordStatus::Easy;
	}
	if (QRegExp("^\\d+$").exactMatch(pass)) {
		mess = "Password can't be a number";
		return PasswordStatus::NumOnly;
	}
	return PasswordStatus::Ok;
}

EmailStatus PetClientWindow::checkEmail(const QString & email, QString & mess) {
	mess.clear();
	if (email.isEmpty()) {
		mess = "Email is empty";
		return EmailStatus::Empty;
	}
	if (!checkLoginIsFree(email)) {
		mess = "Email is already taken";
		return EmailStatus::Taken;
	}
	QString regexp = "^(([^<>()\\[\\]\\\\.,;:\\s@\"]+(\\.[^<>()\\[\\]\\\\.,;:\\s@\"]+)*)|(\".+\"))@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}])|(([a-zA-Z\\-0-9]+\\.)+[a-zA-Z]{2,}))$";
	if (QRegExp(regexp).exactMatch(email)) {
		mess = "Email isn't valid";
		return EmailStatus::Invalid;
	}
	return EmailStatus::Ok;
}

bool PetClientWindow::checkLoginIsFree(const QString & login) const {
	//TODO: send query to server
	(void)login;
	return true;
}

bool PetClientWindow::checkEmailIsFree(const QString & email) const {
	//TODO: send query to server
	(void)email;
	return true;
}

bool PetClientWindow::checkForWrongSymbols(const QString & string) const {
	//TODO: check this
	(void)string;
	return false;
}

bool PetClientWindow::checkPassComplexity(const QString & pass) const {
	return QRegExp("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,10}$").exactMatch(pass);
}

void PetClientWindow::onPressSignIn() {
	m_startFrame->setVisible(false);
	m_signInUpFrame->setVisible(true);
	m_state = WindowState::SignIn;
	ui->signInButton_2->setText(u8"Войти");
}

void PetClientWindow::onPressSignUp() {
	m_startFrame->setVisible(false);
	m_signInUpFrame->setVisible(true);
	m_state = WindowState::SignUp;
	ui->signInButton_2->setText(u8"Зарегистрироваться");
}

void PetClientWindow::onPressSignInUp() {
	QString login = ui->loginField->text();
	QString pass = ui->passField->text();
	
	QString loginErr;
	QString emailErr;
	QString passErr;
	
	if (checkLogin(login, loginErr) != LoginStatus::Ok) {
		QMessageBox::critical(this, "Error", loginErr);
		return;
	}
	if (checkPassword(pass, passErr) != PasswordStatus::Ok) {
		QMessageBox::critical(this, "Error", passErr);
		return;
	}
	//WARNING: hardcode
	if (checkEmail("user@example.com", emailErr) != EmailStatus::Ok) {
		QMessageBox::critical(this, "Error", emailErr);
		return;
	}
	
	if (m_state == WindowState::SignUp) {
		m_state = WindowState::Confirmation;
		m_confirmationFrame->setVisible(true);
	} else {
		m_state = WindowState::Messeging;
		m_messagingFrame->setVisible(true);
	}
	
	m_signInUpFrame->setVisible(false);
}

void PetClientWindow::onPressConfirmation() {
	if (ui->confirmField->text().isEmpty()) {
		QMessageBox::critical(this, "Error", u8"Вам нужно подтвердить регистрацию");
		return;
	}
	m_state = WindowState::Messeging;
	m_messagingFrame->setVisible(true);
	if (m_confirmationFrame->isVisible())
		m_confirmationFrame->setVisible(false);
}

