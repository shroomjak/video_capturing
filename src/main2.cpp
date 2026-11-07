#include <iostream>
#include <opencv2/opencv.hpp>

int main(void){
    cv::Mat src;
    cv::namedWindow("video", cv::WINDOW_NORMAL);
    cv::VideoCapture capture("/dev/video0");

    if (!capture.isOpened()) {
        std::cout << "no video\n";
        return -1;
    }

    while(1){
        capture.read(src);

        if (src.empty()) {
            continue;
        }
    
        cv::putText(src, "hello, world!", cv::Point(0, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 2.0, cv::Scalar(255, 255, 255), 6);

        cv::imshow("video", src);
        char c = (char)cv::waitKey(1);
        if (c == 'q'){
            break;
        }
    }
    capture.release();
    cv::destroyAllWindows();

    return 0;
}