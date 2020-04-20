#include "opencv2/opencv.hpp"
#include <qapplication.h>
#include <qpushbutton.h>
#include "MainWindow.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    return QApplication::exec();
    /*
    VideoCapture cap(0); // open the default camera
    cout << "Provided FPS: " << cap.get(CAP_PROP_FPS) << endl;

    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("Camera",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        // cvtColor(frame, edges, COLOR_BGR2GRAY);
        // GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        // Canny(edges, edges, 0, 30, 3);
        imshow("Camera", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
    */
}
