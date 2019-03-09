#ifndef MESSAGELABEL_H
#define MESSAGELABEL_H

#include <QWidget>

namespace Ui {
class MessageLabel;
}

class QLabel;

namespace PetGUI {

class MessageLabel : public QWidget {
	
	Q_OBJECT
	
	QLabel * m_contentLabel;
	QLabel * m_loginLabel;
	QLabel * m_timeLabel;
	
public:
	
	explicit MessageLabel(QWidget *parent = nullptr);
	~MessageLabel();
	
	void setNickname(const QString & nickname);
	void setContent(const QString & content);
	void setTime(const QTime & time);
	
private:
	
	Ui::MessageLabel *ui;
	
};

}

#endif // MESSAGELABEL_H
