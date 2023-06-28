#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "Objects.h"
class DebugDrawer
{
public:
	void ShowMat(const cv::Mat& image, const std::string& winName);
	void DrawObjectsAndShowMat(const cv::Mat& image, const Objects& objects, const std::string& winName);
protected:
	void DrawObjects(const Objects& objects);
	cv::Mat _bufferForDrawing;
};

