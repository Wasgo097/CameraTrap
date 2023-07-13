#include "MatDrawer.h"

void MatDrawer::ShowMat(const cv::Mat& image, const std::string& winName)
{
	if (!image.empty())
		cv::imshow(winName, image);
}

void MatDrawer::DrawObjectsOnMat(cv::Mat& image, const Objects& objects)
{
	for (const auto& object : objects.GetObjects())
		cv::rectangle(image, object, cv::Scalar(.0, 255.0, .0));
}
