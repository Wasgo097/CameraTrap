#pragma once
#include <opencv2/core/mat.hpp>
#include <chrono>
class IFrame 
{
public:
	virtual ~IFrame() = default;
	virtual const cv::Mat& GetMatCRef()const = 0;
	virtual cv::Mat GetMatCopy()const = 0;
	virtual unsigned int GetNumber()const = 0;
	virtual const std::chrono::system_clock::time_point GetTime()const = 0;
};