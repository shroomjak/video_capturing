//OpenCV header to use VideoCapture class//
#include <opencv2/opencv.hpp>
#include "source.hpp"
#include "processing.hpp"
#include <iostream>
#include <chrono>

int main() {
   cv::Mat src, dst;   //Declaring a matrix to load the frames//

   cv::namedWindow("Video Player", cv::WINDOW_NORMAL);//Declaring the video to show the video//

   cv::VideoCapture cap(config::SOURCE);//Declaring an object to capture stream of frames from default camera

   if (!cap.isOpened()){ //This section prompt an error message if no video stream is found//
      std::cout << "No video stream detected\n";
      system("pause");
      return -1;
   }

   // configure capture properties
   cap.set(cv::CAP_PROP_FRAME_WIDTH, config::WIDTH);
   cap.set(cv::CAP_PROP_FRAME_HEIGHT, config::HEIGHT);
   cap.set(cv::CAP_PROP_FPS, config::FPS);

   //double fps = cap.get(cv::CAP_PROP_FPS);
   //int delay = (fps > 0) ? (1000 / fps) : 1;

   int frame_count = 0;
   double current_fps = 0.0;

   auto start_time = std::chrono::steady_clock::now();

   while(1){ //Taking an everlasting loop to show the video//
      cap.read(src);
      if (src.empty()){ //Breaking the loop if no video frame is detected//
         break;
      }
      frame_count++;
      auto current_time = std::chrono::steady_clock::now();
      std::chrono::duration<double> elapsed_time = current_time - start_time;

      if (elapsed_time.count() >= 1.0) {
         current_fps = frame_count / elapsed_time.count();
         std::cout << "Current FPS: " << current_fps << std::endl;

         frame_count = 0;
         start_time = current_time;
      }
      

      cv::Mat kernel = cv::Mat::ones(10, 10, CV_32F); //Defining a smoothing kernel//
      processing::linear_filter(src, dst, kernel);
      //std::cout << src << std::endl << dst << std::endl;

      std::string fps_text = "FPS: " + std::to_string(current_fps).substr(0, 4); 
      cv::putText(dst, fps_text, cv::Point(30, 50), 
                  cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

      cv::imshow("Video Player", dst);//Showing the video//
      char c = (char)cv::waitKey(1);
      if (c == 'q'){ //If q is entered break the loop//
         break;
      }
   }
   cap.release();//Releasing the buffer memory//
   cv::destroyAllWindows();//Destroying all the windows opened by the program//
   return 0;
}