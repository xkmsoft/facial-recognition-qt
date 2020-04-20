//
// Created by chasank on 18/04/2020.
//

#include "CentralWidget.h"
#include <QLabel>
#include <QLineEdit>


CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)  {

    this->entranceCameraGroupBox = new QGroupBox(this);
    this->entranceCameraGroupBox->setTitle("Stream Input");
    this->entranceCameraGroupBox->setFlat(true);

    this->entranceCameraLayout = new QGridLayout(this);
    this->entranceCameraLayout->addWidget(new QLabel("Stream URL:", this), 0, 0);

    this->entranceCameraURL = new QLineEdit(this);
    this->entranceCameraURL->setText("http://103.199.161.254/Content/bbcworld/Live/Channel(BBCworld)/index.m3u8");
    this->entranceCameraLayout->addWidget(this->entranceCameraURL, 1, 0);

    this->entranceCameraWidget = new CameraWidget(this);
    this->entranceCameraWidget->setFixedHeight(480);
    this->entranceCameraWidget->setFixedWidth(640);
    this->entranceCameraLayout->addWidget(this->entranceCameraWidget, 2, 0);

    this->entranceCameraStartButton = new QPushButton("Start Streaming", this);
    this->entranceCameraLayout->addWidget(this->entranceCameraStartButton, 3, 0);

    this->entranceLog = new QTextEdit(this);
    this->entranceLog->setFixedHeight(50);
    this->entranceCameraLayout->addWidget(this->entranceLog, 4, 0);
    this->entranceCameraGroupBox->setLayout(this->entranceCameraLayout);

    this->mainLayout = new QGridLayout(this);
    this->mainLayout->addWidget(this->entranceCameraGroupBox, 0, 0);
}

CameraWidget *CentralWidget::getEntranceCameraWidget() const {
    return this->entranceCameraWidget;
}

QPushButton *CentralWidget::getEntranceCameraStartButton() const {
    return entranceCameraStartButton;
}

const QMetaObject &CentralWidget::getStaticMetaObject() {
    return staticMetaObject;
}

QGroupBox *CentralWidget::getEntranceCameraGroupBox() const {
    return entranceCameraGroupBox;
}

QGridLayout *CentralWidget::getEntranceCameraLayout() const {
    return entranceCameraLayout;
}

QLineEdit *CentralWidget::getEntranceCameraUrl() const {
    return entranceCameraURL;
}

QTextEdit *CentralWidget::getEntranceLog() const {
    return entranceLog;
}

QGridLayout *CentralWidget::getMainLayout() const {
    return mainLayout;
}
