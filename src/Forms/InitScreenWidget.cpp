#include "Forms/InitScreenWidget.h"
#include "ui_InitScreenWidget.h"

#include <QPushButton>

namespace PetGUI {

InitScreenWidget::InitScreenWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::InitScreenWidget) {
	ui->setupUi(this);
	
	m_loginButton = ui->LoginButton;
	m_registrationButton = ui->RegistrationButton;
	
	connect(m_loginButton, &QPushButton::pressed, this, &InitScreenWidget::onLoginPressedHandler);
	connect(m_registrationButton, &QPushButton::pressed, this, &InitScreenWidget::onRegistrationPressedHandler);
}

InitScreenWidget::~InitScreenWidget() { delete ui; }

void InitScreenWidget::onLoginPressedHandler() { emit onLoginPressed(); }

void InitScreenWidget::onRegistrationPressedHandler() { emit onRegistrationPressed(); }

}
