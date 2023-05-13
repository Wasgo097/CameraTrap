#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
class Objects
{
public:
	Objects(size_t initBufferSize, size_t maxBufferSize);
	Objects() = default;
	bool PushNewObject(cv::Rect newObject);
	void ClearAllObjects();
	const std::vector<cv::Rect>& GetObjects()const;
protected:
	size_t _maxObjects{ 0 };
	std::vector<cv::Rect> _objects;
};