#include <QCoreApplication>
#include <QTime>

#include "PetClient.h"

int main(int argc, char **argv) {
	QCoreApplication a(argc, argv);
	
	PetClient * client = new PetClient(&a);
	
	QByteArray message;
	message.append(QTime::currentTime().toString().toUtf8());
	message.append("PetToPetTeam ");
	
	//Test Message Sending
	client->sendMessage(message);
	return a.exec();
}
