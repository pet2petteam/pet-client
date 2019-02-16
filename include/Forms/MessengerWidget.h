#ifndef MESSENGERWIDGET_H
#define MESSENGERWIDGET_H

#include <QWidget>

class QVBoxLayout;

namespace Ui {
class MessengerWidget;
}

class MessengerWidget : public QWidget {
	
	Q_OBJECT
	
	Ui::MessengerWidget *ui;
	QWidget * m_messageAreaCentralWidget;
	QVBoxLayout * m_messageAreaCentralWidgetLayout;
	
public:
	
	explicit MessengerWidget(QWidget *parent = nullptr);
	~MessengerWidget();
	
	void appentReceivedMessage(const QString & messageText);
	
private:
	
private slots:
	
	void sendMessageHandler();
	
signals:
	
	void onMessageSend(const QString & messageText);
	
};

#endif // MESSENGERWIDGET_H
