#include "Forms/InitScreenForm.h"
#include "ui_InitScreenForm.h"

#include <QPushButton>

namespace PetGUI {

InitScreenForm::InitScreenForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::InitScreenForm) {
	ui->setupUi(this);
	
	m_loginButton = ui->LoginButton;
	m_registrationButton = ui->RegistrationButton;
	
	connect(m_loginButton, &QPushButton::pressed, this, &InitScreenForm::onPressSignInHandler);
	connect(m_registrationButton, &QPushButton::pressed, this, &InitScreenForm::onPressSignUpHandler);
}

InitScreenForm::~InitScreenForm() { delete ui; }

void InitScreenForm::onPressSignInHandler() { emit onSignInPressed(); }

void InitScreenForm::onPressSignUpHandler() { emit onSignUpPressed(); }

}
