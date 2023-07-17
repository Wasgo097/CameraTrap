#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
class Objects
{
public:
	Objects(size_t initBufferSize = 0, size_t maxBufferSize = 0);
	bool PushNewObject(cv::Rect newObject);
	void ClearAllObjects();
	const std::vector<cv::Rect>& GetObjects()const;
protected:
	size_t _MAXOBJECTS{ 0 };
	std::vector<cv::Rect> _objects;
};