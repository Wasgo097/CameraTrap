#pragma once
#include "Interfaces/IFrame.h"
class FrameBase : public IFrame 
{
public:
	FrameBase(cv::Mat mat, unsigned number);
	cv::Mat GetMat() override;
	const cv::Mat& GetMatCRef()const override;
	cv::Mat GetMatCopy()const override;
	unsigned int GetNumber()const override;
	const std::chrono::system_clock::time_point GetTime()const override;
protected:
	cv::Mat _mat;
	unsigned int _number{ 0u };
	const std::chrono::system_clock::time_point _timePoint;
};