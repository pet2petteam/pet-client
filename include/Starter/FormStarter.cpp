#include "FormStarter.h"
#include <QApplication>

#include "Forms/PetClientWindow.h"

namespace PetGUI::Starter {

int start(int argc, char **argv) {
	QApplication a(argc, argv);
	
	PetClientWindow window;
	window.show();
	
	return a.exec();
}

}
