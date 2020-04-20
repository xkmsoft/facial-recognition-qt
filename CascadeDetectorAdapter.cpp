//
// Created by chasank on 19/04/2020.
//

#include "CascadeDetectorAdapter.h"

CascadeDetectorAdapter::CascadeDetectorAdapter(const cv::Ptr<cv::CascadeClassifier>& detector, int detectionFlag): IDetector(), Detector(detector)
{
    CV_Assert(detector);
    this->flags = detectionFlag;
}

void CascadeDetectorAdapter::detect(const cv::Mat &Image, std::vector<cv::Rect> &objects)
{
    Detector->detectMultiScale(Image, objects, this->scaleFactor, this->minNeighbours, this->flags,this->minObjSize, this->maxObjSize);
}
