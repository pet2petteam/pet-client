#ifndef INITSCREENWIDGET_H
#define INITSCREENWIDGET_H

#include <QWidget>

namespace Ui {
	class InitScreenForm;
}

class QPushButton;

namespace PetGUI {

class InitScreenForm : public QWidget {
	
	Q_OBJECT
	
	Ui::InitScreenForm *ui;
	
	QPushButton * m_loginButton;
	QPushButton * m_registrationButton;
	
public:
	
	explicit InitScreenForm(QWidget *parent = nullptr);
	~InitScreenForm();
	
signals:
	
	void onSignInPressed();
	void onSignUpPressed();
	
private:
	
	void onPressSignInHandler();
	void onPressSignUpHandler();
	
};

}

#endif // INITSCREENWIDGET_H
