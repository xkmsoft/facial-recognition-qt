//
// Created by chasank on 19/04/2020.
//

#ifndef OPEN_CV_HELLO_WORLD_CASCADEDETECTORADAPTER_H
#define OPEN_CV_HELLO_WORLD_CASCADEDETECTORADAPTER_H

#include "opencv2/opencv.hpp"
#include <opencv2/objdetect.hpp>


class CascadeDetectorAdapter: public cv::DetectionBasedTracker::IDetector {

public:
    CascadeDetectorAdapter(const cv::Ptr<cv::CascadeClassifier> &detector, int detectionFlag);

    void detect(const cv::Mat &Image, std::vector<cv::Rect> &objects) CV_OVERRIDE;

    virtual ~CascadeDetectorAdapter() CV_OVERRIDE {}


private:
    CascadeDetectorAdapter();

    cv::Ptr<cv::CascadeClassifier> Detector;

    int flags;
};


#endif //OPEN_CV_HELLO_WORLD_CASCADEDETECTORADAPTER_H
