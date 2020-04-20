//
// Created by chasank on 18/04/2020.
//

#ifndef OPEN_CV_HELLO_WORLD_MAINWINDOW_H
#define OPEN_CV_HELLO_WORLD_MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "FacialRecognitionThread.h"
#include "CentralWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

    void initUI();

public slots:

    void updateFrame(const QImage &frame);

    void handleStream();

private:
    CentralWidget *centralWidget;

    FacialRecognitionThread *facialRecognitionThread;

};


#endif //OPEN_CV_HELLO_WORLD_MAINWINDOW_H
