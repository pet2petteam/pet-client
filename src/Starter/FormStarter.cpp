#include "Starter/FormStarter.h"
#include "Forms/PetClientWindow.h"

#include <QApplication>

namespace PetGUI::Starter {

int start(int argc, char **argv) {
	QApplication a(argc, argv);
	
	PetClientWindow window;
	window.show();
	
	return a.exec();
}

}
