#ifndef LOGREGWIDGET_H
#define LOGREGWIDGET_H

#include <QWidget>

namespace Ui {
class LogRegWidget;
}

class QPushButton;
class QLineEdit;
class QFrame;

namespace PetGUI {

enum class LogRegMode : short {
	SignIn = 0,
	SignUp = 1
};

class LogRegWidget : public QWidget {
	
	Q_OBJECT
	
	LogRegMode m_mode;
	
	QPushButton * m_logRegButton;
	QLineEdit * m_loginLine;
	QLineEdit * m_emailLine;
	QLineEdit * m_passLine;
	QFrame * m_emailFrame;
	
	Ui::LogRegWidget *ui;
	
public:
	
	explicit LogRegWidget(QWidget *parent = nullptr, LogRegMode mode = LogRegMode::SignIn);
	~LogRegWidget();
	
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
