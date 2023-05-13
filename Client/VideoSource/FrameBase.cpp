#include "FrameBase.h"
FrameBase::FrameBase(cv::Mat mat, unsigned number) :_mat{ mat }, _number{ number }, _timePoint{ std::chrono::high_resolution_clock::now() } {}
cv::Mat FrameBase::GetMat() 
{
	return _mat;
}
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
std::chrono::time_point<std::chrono::high_resolution_clock> FrameBase::GetTime()const 
{
	return _timePoint;
}