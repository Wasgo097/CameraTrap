#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "Utilities/Objects.h"
class DebugDrawer
{
public:
	int ShowMat(const cv::Mat& image, const std::string& winName, int delay = 1);
	int DrawObjectsAndShowMat(const cv::Mat& image, const Objects& objects, const std::string& winName, int delay = 1);
protected:
	void DrawObjects(const Objects& objects);
	cv::Mat staticBuffer;
};

