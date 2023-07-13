#pragma once
#include "Objects.h"
#include <opencv2/opencv.hpp>
#include <string>
class MatDrawer
{
public:
	static void ShowMat(const cv::Mat& image, const std::string& winName);
	static void DrawObjectsOnMat(cv::Mat& image, const Objects& objects);
};

