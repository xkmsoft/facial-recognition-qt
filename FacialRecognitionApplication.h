//
// Created by chasank on 25/04/2020.
//

#ifndef OPEN_CV_HELLO_WORLD_FACIALRECOGNITIONAPPLICATION_H
#define OPEN_CV_HELLO_WORLD_FACIALRECOGNITIONAPPLICATION_H

#include <QApplication>
#include <QObject>
#include <iostream>

class FacialRecognitionApplication : public QApplication {

    Q_OBJECT

public:

    FacialRecognitionApplication(int &argc, char **argv) : QApplication(argc, argv) {}

    bool notify(QObject *object, QEvent *event) override;

signals:

public slots:

};


#endif //OPEN_CV_HELLO_WORLD_FACIALRECOGNITIONAPPLICATION_H
