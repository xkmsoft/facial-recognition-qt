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

#include <chrono>


FacialRecognitionThread::FacialRecognitionThread(QObject *parent) : QThread(parent)
{

    std::cout << "Constructor of FacialRecognitionThread" << std::endl;

    this->streamURL = "";

    this->borderColor = cv::Scalar (0, 255, 0);

    this->borderSize = 2;

    this->scaleFactor = 1.1f;

    this->minNeighbours = 6;

    this->minSize = cv::Size(10, 10);

    this->maxSize = cv::Size (500, 500);

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
    //cv::VideoCapture VideoStream(this->streamURL, apiID);
    cv::VideoCapture VideoStream(0, apiID);
    //cv::VideoCapture VideoStream("/media/psf/Home/Documents/Rose/P1200715.MOV", apiID);
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
    cv::Mat RGBReferenceFrame;
    cv::Mat GrayFrame;
    std::vector<cv::Rect> Faces;

    std::cout << "VideoStream opened: " << VideoStream.isOpened() << std::endl;
    std::cout << "Was cancelled: " << this->wasCancelled << std::endl;

    double frames = 0;
    auto begin = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    while (VideoStream.isOpened() && !this->wasCancelled)
    {
        frames = frames + 1;
        VideoStream >> ReferenceFrame;

        cv::cvtColor(ReferenceFrame, GrayFrame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(GrayFrame, GrayFrame);

        Detector.process(GrayFrame);
        Detector.getObjects(Faces);

        for (auto & Face : Faces)
        {
            cv::rectangle(ReferenceFrame, Face, this->borderColor, this->borderSize);
        }

        // Color format from BGR to RGB
        cv::cvtColor(ReferenceFrame, RGBReferenceFrame, cv::COLOR_BGR2RGB);
        // Mirror Flipping
        cv::flip(RGBReferenceFrame, RGBReferenceFrame, 1);

        QImage frame = QImage((uchar*) RGBReferenceFrame.data, RGBReferenceFrame.cols, RGBReferenceFrame.rows, RGBReferenceFrame.step, QImage::Format_RGB888);
        emit frameUpdated(frame);

        auto current = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        double averageFPS = frames / static_cast<double >(current - begin);

        std::cout << "Average FPS: " << averageFPS << std::endl;
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






