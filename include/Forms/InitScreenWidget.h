#ifndef INITSCREENWIDGET_H
#define INITSCREENWIDGET_H

#include <QWidget>

namespace Ui {
	class InitScreenWidget;
}

class QPushButton;

namespace PetGUI {

class InitScreenWidget : public QWidget {
	
	Q_OBJECT
	
	Ui::InitScreenWidget *ui;
	
	QPushButton * m_loginButton;
	QPushButton * m_registrationButton;
	
public:
	
	explicit InitScreenWidget(QWidget *parent = nullptr);
	~InitScreenWidget();
	
signals:
	
	void onLoginPressed();
	void onRegistrationPressed();
	
private:
	
	void onLoginPressedHandler();
	void onRegistrationPressedHandler();
	
};

}

#endif // INITSCREENWIDGET_H
