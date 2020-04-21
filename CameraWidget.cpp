//
// Created by chasank on 18/04/2020.
//

#include <QtGui/QPainter>
#include <iostream>
#include "CameraWidget.h"

CameraWidget::CameraWidget(QWidget *parent) : QWidget(parent) {
    this->image = QImage();
}

void CameraWidget::updateFrame(const QImage &frame) {
    this->image = frame.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
    this->update();
}

void CameraWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    QPoint point(0, 0);
    painter.drawImage(point, this->image);
    this->image = QImage();
}
