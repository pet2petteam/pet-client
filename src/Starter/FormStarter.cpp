#include "Starter/FormStarter.h"
#include "PetMainWindow.h"

#include <QApplication>

namespace PetGUI::Starter {

int start(int argc, char **argv) {
	QApplication a(argc, argv);
	
	PetMainWindow window;
	window.show();
	
	return a.exec();
}

}
