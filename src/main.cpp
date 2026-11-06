//#include <opencv2/opencv.hpp>//OpenCV header to use VideoCapture class//
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "source.hpp"
#include <iostream>

int main() {
   cv::Mat myImage;   //Declaring a matrix to load the frames//

   cv::namedWindow("Video Player", cv::WINDOW_NORMAL);//Declaring the video to show the video//

   cv::VideoCapture cap(config::SOURCE);//Declaring an object to capture stream of frames from default camera

   if (!cap.isOpened()){ //This section prompt an error message if no video stream is found//
      std::cout << "No video stream detected\n";
      system("pause");
      return -1;
   }

   cap.set(cv::CAP_PROP_FRAME_WIDTH, config::WIDTH);
   cap.set(cv::CAP_PROP_FRAME_HEIGHT, config::HEIGHT);

   double fps = cap.get(cv::CAP_PROP_FPS);
   int delay = (fps > 0) ? (1000 / fps) : 1;

   while(1){ //Taking an everlasting loop to show the video//
      cap >> myImage;
      if (myImage.empty()){ //Breaking the loop if no video frame is detected//
         break;
      }
      cv::imshow("Video Player", myImage);//Showing the video//
      char c = (char)cv::waitKey(delay);
      if (c == 'q'){ //If q is entered break the loop//
         break;
      }
   }
   cap.release();//Releasing the buffer memory//
   return 0;
}