#ifndef PETCLIENTWINDOW_H
#define PETCLIENTWINDOW_H

#include <QMainWindow>
#include <stdint.h>

namespace Ui {
	class PetClientWindow;
}

const int8_t MIN_PASSWORD_LENGTH = 6;
const int8_t MAX_PASSWORD_LENGTH = 32;

const int8_t MIN_LOGIN_LENGTH = 6;
const int8_t MAX_LOGIN_LENGTH = 18;

class QWidget;
class MessengerWidget;
class PetClient;

enum class WindowState : int8_t {
	Start = 0,
	SignIn = 1,
	SignUp = 2,
	Messeging = 3,
	Confirmation = 4
	//etc
};

enum class LoginStatus : int8_t {
	Ok = 0,
	Short = 1,
	Long = 2,
	Taken = 3,
	Invalid = 4,
	Empty = 5
	//etc
};

enum class PasswordStatus : int8_t {
	Ok = 0,
	Short = 1,
	Long = 2,
	NumOnly = 3,
	Easy = 4,
	Empty = 5,
	Invalid = 6
	//etc
};

enum class EmailStatus : int8_t {
	Ok = 0,
	Invalid = 1,
	Taken = 2,
	Empty = 3
	//etc
};

class PetClientWindow : public QMainWindow {
	
	Q_OBJECT
	
	QWidget * m_startFrame;
	QWidget * m_signInUpFrame;
	QWidget * m_confirmationFrame;
	QWidget * m_messagingFrame;
	
	MessengerWidget * m_messenger;
	PetClient * m_petClient;
	
	WindowState m_state;
	
	Ui::PetClientWindow *ui;
	
public:
	
	explicit PetClientWindow(QWidget *parent = nullptr);
	~PetClientWindow();
	
private:
	//TODO: to realize more strict validation
	//1) login has to consist from one word and password too
	//2) need to realize checking for password complexity
	//3) check for number of symbols
	
	//dummy
	///
	/// \brief checkLogin - checking that login is free, valid, etc
	/// \param login - login str
	/// \param mess - output message (if login is valid, message is empty)
	/// \return status code (see LoginStatus enum)
	///
	LoginStatus checkLogin(const QString & login, QString & mess);
	
	///
	/// \brief checkPassword - checking that passwrod is  valid (length, complexity, etc)
	/// \param pass - password str
	/// \param mess - output message (if pass is valid, message is empty)
	/// \return status code (see PasswordStatus enum)
	///
	PasswordStatus checkPassword(const QString & pass, QString & mess);
	
	///
	/// \brief checkEmail - checking that email is valid and free
	/// \param email - email str
	/// \param mess - output message (if email is valid, message is empty)
	/// \return status code (see EmailStatus enum)
	///
	EmailStatus checkEmail(const QString & email, QString & mess);
	
	//help functions
	bool checkLoginIsFree(const QString & login) const;
	bool checkEmailIsFree(const QString & email) const;
	bool checkForWrongSymbols(const QString & string) const;
	
	///
	/// \brief checkPassComplexity
	/// \param pass - password string
	/// \return true if password is correct
	///
	bool checkPassComplexity(const QString & pass) const;
	
	//SLOTS
	void onPressSignIn();
	void onPressSignUp();
	void onPressSignInUp();
	void onPressConfirmation();
	
};

#endif // PETCLIENTWINDOW_H
