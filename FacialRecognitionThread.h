//
// Created by chasank on 19/04/2020.
//

#ifndef OPEN_CV_HELLO_WORLD_FACIALRECOGNITIONTHREAD_H
#define OPEN_CV_HELLO_WORLD_FACIALRECOGNITIONTHREAD_H

#include <QThread>
#include <QtGui/QColor>
#include <QtCore/QSize>
#include "opencv2/opencv.hpp"

class FacialRecognitionThread : public QThread {

    Q_OBJECT

public:

    explicit FacialRecognitionThread(QObject *parent = nullptr);

    void begin(const std::string &url);

    void cancel();

    ~FacialRecognitionThread();

signals:

    void frameUpdated(const QImage &frame);

    void averageFPSUpdated(const double &fps);

protected:
    void run() override;

private:

    std::string  streamURL;

    cv::Scalar borderColor;

    int borderSize;

    float scaleFactor;

    int minNeighbours;

    cv::Size minSize;

    cv::Size maxSize;

    int detectionFlag;

    bool wasCancelled;
};


#endif //OPEN_CV_HELLO_WORLD_FACIALRECOGNITIONTHREAD_H
