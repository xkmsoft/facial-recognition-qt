#include <FacialRecognitionApplication.h>
#include "MainWindow.h"

int main(int argc, char** argv)
{
    FacialRecognitionApplication facialRecognitionApplication(argc, argv);
    MainWindow window;
    window.show();

    return FacialRecognitionApplication::exec();
}
