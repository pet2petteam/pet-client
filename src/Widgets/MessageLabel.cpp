#include "Widgets/MessageLabel.h"
#include "ui_MessageLabel.h"

#include <QTime>

namespace PetGUI {

MessageLabel::MessageLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageLabel) {
	ui->setupUi(this);
	
	m_contentLabel = ui->ContentLabel;
	m_loginLabel = ui->LoginLabel;
	m_timeLabel = ui->TimeLabel;
	
}

MessageLabel::~MessageLabel() { delete ui; }

void MessageLabel::setNickname(const QString & nickname) {
	m_loginLabel->setText(nickname);
}
void MessageLabel::setContent(const QString & content) {
	m_contentLabel->setText(content);
	while(m_contentLabel->hasScaledContents())
		setSizeIncrement(0, 5);
}
void MessageLabel::setTime(const QTime & time) {
	m_timeLabel->setText(time.toString(Qt::DateFormat::TextDate));
}

}
