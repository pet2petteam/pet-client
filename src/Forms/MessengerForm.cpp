#include "Forms/MessengerForm.h"
#include "ui_MessengerForm.h"

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>

MessengerForm::MessengerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessengerForm) {
	ui->setupUi(this);
	
	m_messageAreaCentralWidget = new QWidget(ui->messageArea);
	ui->messageArea->setWidget(m_messageAreaCentralWidget);
	ui->messageArea->setWidgetResizable(true);
	
	m_messageAreaCentralWidgetLayout = new QVBoxLayout(m_messageAreaCentralWidget);
	m_messageAreaCentralWidgetLayout->setAlignment(Qt::AlignmentFlag::AlignBottom);
	m_messageAreaCentralWidgetLayout->setMargin(2);
	m_messageAreaCentralWidget->setLayout(m_messageAreaCentralWidgetLayout);
	
	connect(ui->sendMessageButton, &QPushButton::pressed, this, &MessengerForm::sendMessageHandler);
}

MessengerForm::~MessengerForm() {
	delete ui;
}

void MessengerForm::appendReceivedMessage(const QString & messageText) {
	if (messageText.isEmpty()) return;
	
	QSpacerItem * spacer = new QSpacerItem(200,0);
	QLabel * messLabel = new QLabel(messageText);
	messLabel->setScaledContents(true);
	messLabel->setMinimumWidth(150);
	messLabel->setMaximumWidth(200);
	messLabel->setObjectName("messLabel");
	messLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
	
	QHBoxLayout * messLayout = new QHBoxLayout(this);
	messLayout->addSpacerItem(spacer);
	messLayout->addWidget(messLabel);
	messLayout->setMargin(2);
	
	QWidget * messWidget = new QWidget(ui->messageArea);
	messWidget->objectName();
	messWidget->setLayout(messLayout);
	messWidget->setMinimumHeight(50);
	messWidget->setMaximumHeight(200);
	
	QString styleMessLabel = "#" + messLabel->objectName() + " {\n"
													"border: 1px solid gray;\n"
													"border-radius: 10px;\n"
													"background-color: gray;\n"
													"color: white;\n"
													"}";
	
	messLabel->setStyleSheet(styleMessLabel);
	m_messageAreaCentralWidgetLayout->addWidget(messWidget);
}

void MessengerForm::sendMessageHandler() {
	QString text = ui->textEdit->toPlainText();
	if (text.isEmpty()) return;
	
	QSpacerItem * spacer = new QSpacerItem(200, 0);
	QLabel * messLabel = new QLabel(text);
	messLabel->setScaledContents(true);
	messLabel->setWordWrap(true);
	messLabel->setMinimumWidth(150);
	messLabel->setMaximumWidth(200);
	messLabel->setObjectName("messLabel");
	messLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
	
	QHBoxLayout * messLayout = new QHBoxLayout(this);
	messLayout->addWidget(messLabel);
	messLayout->addSpacerItem(spacer);
	messLayout->setMargin(2);
	
	QWidget * messWidget = new QWidget(ui->messageArea);
	messWidget->objectName();
	messWidget->setLayout(messLayout);
	messWidget->setMinimumHeight(50);
	messWidget->setMaximumHeight(200);
	
	QString styleMessLabel = "#" + messLabel->objectName() + " {\n"
													"border: 1px solid gray;\n"
													"border-radius: 10px;\n"
													"background-color: blue;\n"
													"color: white;\n"
													"}";
	
	messLabel->setStyleSheet(styleMessLabel);
	
	m_messageAreaCentralWidgetLayout->addWidget(messWidget);
	
	ui->textEdit->clear();
	emit onMessageSend(text);
}
