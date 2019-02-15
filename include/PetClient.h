#ifndef PETCLIENT_H
#define PETCLIENT_H

#include <QObject>
#include <QHostAddress>

class QUdpSocket;
class QTcpServer;
class QByteArray;

const int BUFFER_SIZE = 512;

class PetClient : public QObject {
	
	Q_OBJECT
	
	QUdpSocket * m_senderSocket;
	QTcpServer * m_listener;
	
	long long int m_nextDataBlock;
	
public:
	
	explicit PetClient(QObject *parent = nullptr);
	virtual ~PetClient() override;
	
	bool sendMessage(const QByteArray & mess) const;
	
private:
	
	void connectedHandle();
	void disconnectedHandle();
	void readData();
	
signals:
	
	///
	/// \brief onMessageReceived
	/// \arg output message	(out)
	///
	void onMessageReceived(QByteArray);
	
	///
	/// \brief onDisconnect
	/// \arg peer address	(out)
	/// \arg peer port		(out)
	/// \arg peer name		(out)
	///
	void onDisconnect(QHostAddress, unsigned short, QString);
	
};

#endif // PETCLIENT_H
