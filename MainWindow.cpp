//
// Created by chasank on 18/04/2020.
//

#include <QtWidgets>
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
    this->createActions();
    this->createMenus();
}

void MainWindow::initUI() {
    this->setWindowTitle("Facial Recognition");
}


void MainWindow::createMenus() {
    this->fileMenu = this->menuBar()->addMenu(tr("&File"));
    this->fileMenu->addAction(this->quitAction);

    this->aboutMenu = this->menuBar()->addMenu(tr("&Help"));
    this->aboutMenu->addAction(this->aboutAction);
    this->aboutMenu->addAction(this->aboutQtAction);
}

void MainWindow::createActions() {

    this->quitAction = new QAction(tr("E&xit"), this);
    this->quitAction->setShortcuts(QKeySequence::Quit);
    this->quitAction->setStatusTip(tr("Exit the application"));
    connect(quitAction, &QAction::triggered, this, &MainWindow::quit);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::aboutQt);
}


MainWindow::~MainWindow() {
    delete this->centralWidget;
    delete this->facialRecognitionThread;
    delete this->fileMenu;
    delete this->aboutMenu;
    delete this->quitAction;
    delete this->aboutAction;
    delete this->aboutQtAction;
}

void MainWindow::updateFrame(const QImage &frame) {
    this->centralWidget->getEntranceCameraWidget()->updateFrame(frame);
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

void MainWindow::about() {
    QMessageBox::about(this, tr("About Facial Recognition"),
                       tr("The <b>Facial Recognition Application</b> detect faces "
                          "on streamed videos either video camera or any stream url"));
}

void MainWindow::quit() {
    this->close();
}

void MainWindow::aboutQt() {

}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (this->facialRecognitionThread->isRunning()){
        this->facialRecognitionThread->cancel();
        this->facialRecognitionThread->wait();
    }
    QWidget::closeEvent(event);
}
