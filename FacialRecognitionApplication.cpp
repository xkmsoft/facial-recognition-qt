//
// Created by chasank on 25/04/2020.
//

#include "FacialRecognitionApplication.h"

bool FacialRecognitionApplication::notify(QObject *object, QEvent *event) {
    try
    {
        return QApplication::notify(object, event);
    }
    catch (std::exception &exception)
    {
        std::cerr << "std::exception was caught: " << exception.what() << std::endl;
    }

    return false;
}
