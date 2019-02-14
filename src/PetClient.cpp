#include "PetClient.h"

#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>

#include <QNetworkDatagram>
#include <QByteArray>
#include <QDebug>

PetClient::PetClient(QObject *parent) : QObject(parent) {
	m_senderSocket= new QUdpSocket(this);
	m_senderSocket->bind(QHostAddress::LocalHost, 7778);
	
	m_listener = new QTcpServer(this);
	m_listener->listen(QHostAddress::Any, 7767);
	
	m_block = 0;
	
	connect(m_listener, &QTcpServer::newConnection, this, &PetClient::connectedHandle);
}

PetClient::~PetClient() {
	m_listener->close();
	m_senderSocket->close();
	
	delete m_listener;
	delete m_senderSocket;
}

void PetClient::sendMessage(const QByteArray & mess) const {
	
	QNetworkDatagram datagram(mess, QHostAddress::LocalHost, 7777);
	
	if (m_senderSocket->writeDatagram(datagram) == -1)
		qDebug() << "can't send message";
	
}

void PetClient::connectedHandle() {
	QTcpSocket * clientSock = m_listener->nextPendingConnection();
	qDebug() << clientSock->peerAddress().toString() + " has been connected";
	
	//TODO: replace lambda to class method
	connect(clientSock, &QTcpSocket::disconnected, this, [clientSock](){
		qDebug() << clientSock->peerAddress().toString() + " disconnected";
		clientSock->close();
	});
	
	//TODO: replace lambda to class method
	connect(clientSock, &QTcpSocket::readyRead, this, [this]() {
		QTcpSocket * client = static_cast<QTcpSocket*>(sender());
		if (!client) {
			qDebug() << "what the fuck is going on ???";
			return;
		}
		
		QByteArray mess;
		char * buff = new char[512];
		while(true) {
			memset(buff, 0, 512);
			client->read(buff, 512);
			if (m_block == 0) {
				if (client->bytesAvailable() < sizeof(m_block)) {
					mess.append(buff);
					break;
				}
				m_block = client->bytesAvailable();
			}
			if (client->bytesAvailable() < m_block) break;
			mess.append(buff);
			m_block = 0;
		}
		qDebug() << mess;
		delete [] buff;
	});
}

