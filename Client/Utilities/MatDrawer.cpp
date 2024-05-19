#include "MatDrawer.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
void MatDrawer::ShowMat(const cv::Mat& image, const std::string& windowName)
{
	if (!image.empty())
		cv::imshow(windowName, image);
}

void MatDrawer::DrawObjectsOnMat(cv::Mat& image, const Objects& objects)
{
	for (const auto& object : objects.GetObjects())
		cv::rectangle(image, object, cv::Scalar(.0, 255.0, .0));
}

void MatDrawer::ClearWindow()
{
	cv::destroyAllWindows();
}