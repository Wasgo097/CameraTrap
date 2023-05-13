#pragma once
#include <opencv2/core/mat.hpp>
#include <chrono>
class IFrame 
{
public:
	virtual ~IFrame() = default;
	virtual cv::Mat GetMat() = 0;
	virtual const cv::Mat& GetMatCRef()const = 0;
	virtual cv::Mat GetMatCopy()const = 0;
	virtual unsigned int GetNumber()const = 0;
	virtual std::chrono::time_point<std::chrono::high_resolution_clock> GetTime()const = 0;
};