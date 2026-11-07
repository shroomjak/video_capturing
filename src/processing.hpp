#pragma once

namespace processing {
    void linear_filter(const cv::Mat & src, cv::Mat & dst, const cv::Mat & kernel) {
        cv::Mat_<float> norm_kernel;
        if (cv::sum(kernel)[0] > 0.0) {
            cv::normalize(kernel, norm_kernel, 1.0f, 0, cv::NORM_L1, CV_32F);
        } else {
            kernel.convertTo(norm_kernel, CV_32F);
        }
        std::cout << kernel << norm_kernel << std::endl;
        cv::filter2D(src, dst, -1, norm_kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT); //Applying the filter to the video frame//
        return;
    }
}