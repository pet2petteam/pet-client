#ifndef LOGREGWIDGET_H
#define LOGREGWIDGET_H

#include <QWidget>

namespace Ui {
class LogRegForm;
}

class QPushButton;
class QLineEdit;
class QFrame;

namespace PetGUI {

enum class LogRegMode : short {
	SignIn = 0,
	SignUp = 1
};

class LogRegForm : public QWidget {
	
	Q_OBJECT
	
	LogRegMode m_mode;
	
	QPushButton * m_logRegButton;
	QLineEdit * m_loginLine;
	QLineEdit * m_emailLine;
	QLineEdit * m_passLine;
	QFrame * m_emailFrame;
	
	Ui::LogRegForm *ui;
	
public:
	
	explicit LogRegForm(QWidget *parent = nullptr, LogRegMode mode = LogRegMode::SignIn);
	~LogRegForm();
	
signals:
	
	void onLogRegPressed();
	
private:
	
	void onLogRegPressedHandler();
	void registrationMode();
	void loginMode();
	
	bool isValidLogin(const QString & login);
	bool isValidEmail(const QString & email);
	bool isValidPassword(const QString & pass);
	
};

}

#endif // LOGREGWIDGET_H
