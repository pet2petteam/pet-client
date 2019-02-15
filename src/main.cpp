#include "PetClientWindow.h"

#include <QApplication>

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	
	PetClientWindow window;
	window.show();
	
	return a.exec();
}
