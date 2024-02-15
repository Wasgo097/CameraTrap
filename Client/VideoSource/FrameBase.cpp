#include "FrameBase.h"
FrameBase::FrameBase(cv::Mat mat, unsigned number) :_mat{ mat }, _number{ number }, _timePoint{ std::chrono::system_clock::now() } {}
const cv::Mat& FrameBase::GetMatCRef() const
{
	return _mat;
}
cv::Mat FrameBase::GetMatCopy() const
{
	return _mat.clone();
}
unsigned int FrameBase::GetNumber()const 
{
	return _number;
}
const std::chrono::system_clock::time_point FrameBase::GetTime()const
{
	return _timePoint;
}