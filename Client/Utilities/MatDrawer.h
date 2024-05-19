#pragma once
#include "Objects.h"
#include <opencv2/core/mat.hpp>
#include <string>
class MatDrawer
{
public:
	static void ShowMat(const cv::Mat& image, const std::string& windowName);
	static void DrawObjectsOnMat(cv::Mat& inOutImage, const Objects& objects);
	static void ClearWindow();
};