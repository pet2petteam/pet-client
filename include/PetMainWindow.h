#ifndef PETCLIENTWINDOW_H
#define PETCLIENTWINDOW_H

#include <QMainWindow>
#include <stdint.h>
#include <map>

namespace Ui {
	class PetMainWindow;
}

class QWidget;
class QVBoxLayout;

namespace PetGUI {

enum class FormType : uint8_t {
	Init = 0,
	SignIn = 1,
	SignUp = 2,
	Messenger = 3
};

//------------------------------WARNING: "How to add new form" manual-------------------------------//
//1.--------------Create a form's class (Inherited from QWidget)------------------------------------//
//2.--------------Add the type of new form into the FormType enum-----------------------------------//
//3.--------------Create form initialization function-----------------------------------------------//
//4.--------------Add form object into m_form map---------------------------------------------------//
//5.--------------You need to write form signal handlers--------------------------------------------//
//6.--------------Use a connect() function to connect signals of your form with handlers------------//
//7.--------------If you want to show your form, use the setCurrentForm(YourFormType) method--------//
//--------------------------------------------------------------------------------------------------//

class PetMainWindow : public QMainWindow {
	
	Q_OBJECT
	
	///
	/// \brief m_forms - this map contains form object
	///
	std::map<FormType, QWidget *> m_forms;
	
	///
	/// \brief m_centralWidget - central widget of this window
	///
	QWidget * m_centralWidget;
	
	///
	/// \brief m_centralLayout - central widget's layout
	///
	QVBoxLayout * m_centralLayout;
	
	///
	/// \brief m_currentType - type of current form
	///
	FormType m_currentType;
	
	Ui::PetMainWindow *ui;
	
public:
	
	explicit PetMainWindow(QWidget *parent = nullptr);
	~PetMainWindow();
	
private:
	
	///
	/// \brief init - this method initialize main window
	///
	void init();
	
	///
	/// \brief the methods below are needed for forms initialization
	///
	void initInitForm();
	void initSignInForm();
	void initSignUpForm();
	void initMessengerForm();
	
	///
	/// \brief destroy - this method destroys all forms
	///
	void destroy();
	
	///
	/// \brief setCurrentForm - this method hides prevForm and shows currentForm
	/// \param type - form type (see FormType enum)
	///
	void setCurrentForm(FormType type);
	
};

}

#endif // PETCLIENTWINDOW_H
