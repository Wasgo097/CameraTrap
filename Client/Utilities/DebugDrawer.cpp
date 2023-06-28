#include "DebugDrawer.h"

void DebugDrawer::ShowMat(const cv::Mat& image, const std::string& winName)
{
	if (!image.empty())
		cv::imshow(winName, image);
}
void DebugDrawer::DrawObjectsAndShowMat(const cv::Mat& image, const Objects& objects, const std::string& winName)
{
	if (image.empty())
		return;
	_bufferForDrawing = image.clone();
	DrawObjects(objects);
	cv::imshow(winName, _bufferForDrawing);
}
void DebugDrawer::DrawObjects(const Objects& objects)
{
	for (const auto& object : objects.GetObjects())
		cv::rectangle(_bufferForDrawing, object, cv::Scalar(.0, 255.0, .0));
}
