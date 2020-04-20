//
// Created by chasank on 19/04/2020.
//

#include "FacialRecognitionThread.h"
#include "CascadeDetectorAdapter.h"

#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>
#include <QtGui/QImage>


FacialRecognitionThread::FacialRecognitionThread(QObject *parent) : QThread(parent)
{

    std::cout << "Constructor of FacialRecognitionThread" << std::endl;

    this->streamURL = "";

    this->borderColor = cv::Scalar (0, 255, 0);

    this->borderSize = 2;

    this->scaleFactor = 1.5f;

    this->minNeighbours = 6;

    this->minSize = cv::Size(30, 30);

    this->maxSize = cv::Size (300, 300);

    this->detectionFlag = cv::CASCADE_SCALE_IMAGE;

    this->wasCancelled = false;

}

void FacialRecognitionThread::begin(const std::string &url) {
    std::cout << "begin of FacialRecognitionThread" << std::endl;
    std::cout << "URL: " << url << std::endl;
    this->streamURL = url;
    this->wasCancelled = false;
    this->start();
}

void FacialRecognitionThread::cancel() {
    this->wasCancelled = true;
}

void FacialRecognitionThread::run() {

    // QThread::run();

    int apiID = cv::CAP_ANY;
    cv::VideoCapture VideoStream(this->streamURL, apiID);
    std::string backendName = VideoStream.getBackendName();
    double providedFPS = VideoStream.get(cv::CAP_PROP_FPS);
    double frameWidth = VideoStream.get(cv::CAP_PROP_FRAME_WIDTH);
    double frameHeight = VideoStream.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "Backend Name: " << backendName << std::endl;
    std::cout << "Provided FPS: " << providedFPS << std::endl;
    std::cout << "Frame Width: " << frameWidth << std::endl;
    std::cout << "Frame Height: " << frameHeight << std::endl;

    if (!VideoStream.isOpened())
    {
        std::cout << "Error: Cannot open video stream from camera" << std::endl;
        return;
    }

    std::string cascadeFrontalFilename = cv::samples::findFile("lbpcascades/lbpcascade_frontalface.xml");
    cv::Ptr<cv::CascadeClassifier> cascade = cv::makePtr<cv::CascadeClassifier>(cascadeFrontalFilename);
    cv::Ptr<cv::DetectionBasedTracker::IDetector> MainDetector = cv::makePtr<CascadeDetectorAdapter>(cascade, this->detectionFlag);
    if ( cascade->empty() )
    {
        std::cout << "Error: Can not load " << cascadeFrontalFilename.c_str() << std::endl;
        return;
    }

    cascade = cv::makePtr<cv::CascadeClassifier>(cascadeFrontalFilename);
    cv::Ptr<cv::DetectionBasedTracker::IDetector> TrackingDetector = cv::makePtr<CascadeDetectorAdapter>(cascade, this->detectionFlag);

    TrackingDetector->setScaleFactor(this->scaleFactor);
    TrackingDetector->setMinNeighbours(this->minNeighbours);
    TrackingDetector->setMinObjectSize(this->minSize);
    TrackingDetector->setMaxObjectSize(this->maxSize);

    if ( cascade->empty() )
    {
        std::cout << "Error: Cannon load " << cascadeFrontalFilename.c_str() << std::endl;
        return;
    }

    cv::DetectionBasedTracker::Parameters params;
    cv::DetectionBasedTracker Detector(MainDetector, TrackingDetector, params);

    if (!Detector.run())
    {
        std::cout << "Error: Detector initialization failed" << std::endl;
    }

    cv::Mat ReferenceFrame;
    cv::Mat GrayFrame;
    std::vector<cv::Rect> Faces;

    std::cout << "VideoStream opened: " << VideoStream.isOpened() << std::endl;
    std::cout << "Was cancelled: " << this->wasCancelled << std::endl;

    int frames = 0;

    while (VideoStream.isOpened() && !this->wasCancelled)
    {
        frames = frames + 1;
        VideoStream >> ReferenceFrame;
        std::cout << "Frames taken: " << frames << std::endl;

        cv::cvtColor(ReferenceFrame, GrayFrame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(GrayFrame, GrayFrame);

        Detector.process(GrayFrame);
        Detector.getObjects(Faces);

        std::cout << "Number of detected faces: " << Faces.size() << std::endl;

        for (auto & Face : Faces)
        {
            cv::rectangle(ReferenceFrame, Face, this->borderColor, this->borderSize);
        }

        QImage imgIn= QImage((uchar*) ReferenceFrame.data, ReferenceFrame.cols, ReferenceFrame.rows, ReferenceFrame.step, QImage::Format_RGB888);
        imgIn = imgIn.rgbSwapped();

        emit frameUpdated(imgIn);

    }

    Detector.stop();
    VideoStream.release();
    emit frameUpdated(QImage());
}

FacialRecognitionThread::~FacialRecognitionThread() {
    if (this->isRunning()){
        this->cancel();
    }

}






