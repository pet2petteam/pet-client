#ifndef PETCLIENTWINDOW_H
#define PETCLIENTWINDOW_H

#include <QMainWindow>
#include <stdint.h>

namespace Ui {
	class PetClientWindow;
}

class QWidget;
class QVBoxLayout;

namespace PetGUI {

class InitScreenWidget;
class LogRegWidget;
class MessengerWidget;


enum class WindowState : int8_t {
	Start = 0,
	SignIn = 1,
	SignUp = 2,
	Messeging = 3,
	Confirmation = 4
};

class PetClientWindow : public QMainWindow {
	
	Q_OBJECT
	
	QWidget * m_centralWidget;
	QVBoxLayout * m_centralLayout;
	
	InitScreenWidget * m_initScreen;
	LogRegWidget * m_signInUpWidget;
	MessengerWidget * m_messenger;
	
	WindowState m_state;
	
	Ui::PetClientWindow *ui;
	
public:
	
	explicit PetClientWindow(QWidget *parent = nullptr);
	~PetClientWindow();
	
private:
	
	void initSignInForm();
	void initSignUpForm();
	void onPressSignInUp();
	void onPressConfirmation();
	
};

}

#endif // PETCLIENTWINDOW_H
