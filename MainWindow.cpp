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
    connect(this->facialRecognitionThread, &FacialRecognitionThread::frameUpdated, this, &MainWindow::updateFrame);
    connect(this->facialRecognitionThread, &FacialRecognitionThread::averageFPSUpdated, this, &MainWindow::updateAverageFPS);
    connect(this->centralWidget->getEntranceCameraStartButton(), &QAbstractButton::clicked, this, &MainWindow::handleStream);

    this->initUI();
    this->createActions();
    this->createMenus();
}

void MainWindow::initUI() {
    this->setWindowTitle("Facial Recognition");
    this->createStatusBar();
}

void MainWindow::createStatusBar() {
    this->statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createMenus() {
    this->fileMenu = this->menuBar()->addMenu(tr("&File"));
    this->fileMenu->addAction(this->openFileAction);
    this->fileMenu->addAction(this->quitAction);

    this->aboutMenu = this->menuBar()->addMenu(tr("&Help"));
    this->aboutMenu->addAction(this->aboutAction);
    this->aboutMenu->addAction(this->aboutQtAction);
}

void MainWindow::createActions() {

    this->openFileAction = new QAction(tr("&Open File"), this);
    this->openFileAction->setShortcuts(QKeySequence::Open);
    this->openFileAction->setStatusTip(tr("Open an existing file"));
    connect(this->openFileAction, &QAction::triggered, this, &MainWindow::openFile);

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
    delete this->openFileAction;
    delete this->quitAction;
    delete this->aboutAction;
    delete this->aboutQtAction;
}

void MainWindow::updateFrame(const QImage &frame) {
    this->centralWidget->getEntranceCameraWidget()->updateFrame(frame);
}

void MainWindow::updateAverageFPS(const double &fps) {
    this->statusBar()->showMessage(QString("Average FPS: %1").arg((int) fps));
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

void MainWindow::openFile() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList selectedFiles;
    if (dialog.exec()){
        selectedFiles = dialog.selectedFiles();
        QString file = selectedFiles.first();
        if (this->facialRecognitionThread->isRunning()){
            // Facial recognition Thread already running, cancel the current process and wait till thread finishes.
            this->facialRecognitionThread->cancel();
            this->facialRecognitionThread->wait(5000);

        }
        this->centralWidget->getEntranceCameraUrl()->setText(file);
        this->centralWidget->getEntranceCameraStartButton()->animateClick(100);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (this->facialRecognitionThread->isRunning()){
        this->facialRecognitionThread->cancel();
        this->facialRecognitionThread->wait(5000);
    }
    QWidget::closeEvent(event);
}
