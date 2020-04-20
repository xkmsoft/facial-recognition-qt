//
// Created by chasank on 18/04/2020.
//

#ifndef OPEN_CV_HELLO_WORLD_CAMERAWIDGET_H
#define OPEN_CV_HELLO_WORLD_CAMERAWIDGET_H

#include <QWidget>

class CameraWidget: public QWidget  {
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;

public:

    explicit CameraWidget(QWidget *parent = nullptr);

    void updateFrame(const QImage &frame);

private:
    QImage image;
};


#endif //OPEN_CV_HELLO_WORLD_CAMERAWIDGET_H
