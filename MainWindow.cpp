//
// Created by chasank on 18/04/2020.
//

#include "MainWindow.h"
#include "CentralWidget.h"
#include <FacialRecognitionThread.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    this->centralWidget = new CentralWidget(this);
    this->setCentralWidget(this->centralWidget);

    this->facialRecognitionThread = new FacialRecognitionThread(this);
    connect(this->facialRecognitionThread, SIGNAL(frameUpdated(const QImage &)), this, SLOT(updateFrame(const QImage &)));
    connect(this->centralWidget->getEntranceCameraStartButton(), SIGNAL(clicked()), this, SLOT(handleStream()));

    this->initUI();
}

MainWindow::~MainWindow() {
    delete this->centralWidget;
    delete this->facialRecognitionThread;
}

void MainWindow::initUI() {
    this->setWindowTitle("Facial Recognition");
}

void MainWindow::updateFrame(const QImage &frame) {
    CameraWidget *cameraWidget = this->centralWidget->getEntranceCameraWidget();
    cameraWidget->updateFrame(frame);
}

void MainWindow::handleStream() {
    if (!this->facialRecognitionThread->isRunning())
    {
        this->centralWidget->getEntranceCameraStartButton()->setText("Stop Streaming");
        std::string url = this->centralWidget->getEntranceCameraUrl()->text().toStdString();
        this->facialRecognitionThread->begin(url);
    }
    else
    {
        this->centralWidget->getEntranceCameraStartButton()->setText("Start Streaming");
        this->facialRecognitionThread->cancel();
    }
}
