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
	
	m_nextDataBlock = 0;
	
	connect(m_listener, &QTcpServer::newConnection, this, &PetClient::connectedHandle);
}

PetClient::~PetClient() {
	m_listener->close();
	m_senderSocket->close();
	
	delete m_listener;
	delete m_senderSocket;
}

bool PetClient::sendMessage(const QByteArray & mess) const {
	return m_senderSocket->writeDatagram(mess, QHostAddress::LocalHost, 7777) != -1;
}

void PetClient::connectedHandle() {
	QTcpSocket * clientSock = m_listener->nextPendingConnection();
	qDebug() << clientSock->peerAddress().toString() + " has been connected";
	
	connect(clientSock, &QTcpSocket::disconnected, this, &PetClient::disconnectedHandle);
	connect(clientSock, &QTcpSocket::readyRead, this, &PetClient::readData);
}

void PetClient::disconnectedHandle() {
	QTcpSocket * senderSocket = static_cast<QTcpSocket*>(sender());
	if (!senderSocket) {
		qDebug() << __FUNCTION__ << "Error: Socket is nullptr";
		return;
	}
	emit onDisconnect(senderSocket->peerAddress(),
	                  senderSocket->peerPort(),
	                  senderSocket->peerName());
	senderSocket->close();
	senderSocket->deleteLater();
}

void PetClient::readData() {
	QTcpSocket * senderSocket = static_cast<QTcpSocket*>(sender());
	if (!senderSocket) {
		qDebug() << __FUNCTION__ << "Error: Socket is nullptr";
		return;
	}
	
	QByteArray message;
	QString utfStr;
	char * dataBuffer = new char[BUFFER_SIZE];
	memset(dataBuffer, 0, BUFFER_SIZE);
	while(true) {
		senderSocket->read(dataBuffer, BUFFER_SIZE);
		if (m_nextDataBlock == 0) {
			if (senderSocket->bytesAvailable() == 0) {
				message.append(dataBuffer);
				break;
			}
			m_nextDataBlock = senderSocket->bytesAvailable();
		}
		message.append(dataBuffer);
		m_nextDataBlock = 0;
		if (senderSocket->bytesAvailable() == 0) break;
	}
	delete [] dataBuffer;
	emit onMessageReceived(message);
}

