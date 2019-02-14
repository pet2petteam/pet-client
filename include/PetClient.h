#ifndef PETCLIENT_H
#define PETCLIENT_H

#include <QObject>

class QUdpSocket;
class QTcpServer;
class QByteArray;
class QHostAddress;

class PetClient : public QObject {
	
	Q_OBJECT
	
	QUdpSocket * m_senderSocket;
	QTcpServer * m_listener;
	
	unsigned short m_block;
	
public:
	
	explicit PetClient(QObject *parent = nullptr);
	virtual ~PetClient() override;
	
	void sendMessage(const QByteArray & mess) const;
	
private:
	
	void connectedHandle();
	
};

#endif // PETCLIENT_H
