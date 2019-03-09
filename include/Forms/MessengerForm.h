#ifndef MESSENGERWIDGET_H
#define MESSENGERWIDGET_H

#include <QWidget>

class QVBoxLayout;

namespace Ui {
class MessengerForm;
}

class MessengerForm : public QWidget {
	
	Q_OBJECT
	
	Ui::MessengerForm *ui;
	QWidget * m_messageAreaCentralWidget;
	QVBoxLayout * m_messageAreaCentralWidgetLayout;
	
public:
	
	explicit MessengerForm(QWidget *parent = nullptr);
	~MessengerForm();
	
	void appendReceivedMessage(const QString & messageText);
	
private:
	
private slots:
	
	void sendMessageHandler();
	
signals:
	
	void onMessageSend(const QString & messageText);
	
};

#endif // MESSENGERWIDGET_H
