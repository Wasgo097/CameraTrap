#include "DebugDrawer.h"

int DebugDrawer::ShowMat(const cv::Mat& image, const std::string& winName, int delay)
{
	if (not image.empty())
		cv::imshow(winName, image);
	return cv::waitKey(delay);
}
int DebugDrawer::DrawObjectsAndShowMat(const cv::Mat& image, const Objects& objects, const std::string& winName, int delay)
{
	if (image.empty())
		return cv::waitKey(delay);
	staticBuffer = image.clone();
	DrawObjects(objects);
	cv::imshow(winName, staticBuffer);
	return cv::waitKey(delay);
}
void DebugDrawer::DrawObjects(const Objects& objects)
{
	for (const auto& object : objects.GetObjects())
		cv::rectangle(staticBuffer, object, cv::Scalar(.0, 255.0, .0));
}
