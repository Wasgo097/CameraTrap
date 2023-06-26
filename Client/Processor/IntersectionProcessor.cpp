#include "IntersectionProcessor.h"
void IntersectionProcessor::Process()
{
	std::vector<cv::Rect> mergedRects;
	for (const cv::Rect& rect : _result)
	{
		bool merged = false;
		for (cv::Rect& mergedRect : mergedRects)
		{
			if (rect.x < mergedRect.x + mergedRect.width &&
				rect.x + rect.width > mergedRect.x &&
				rect.y < mergedRect.y + mergedRect.height &&
				rect.y + rect.height > mergedRect.y)
			{
				mergedRect |= rect;
				merged = true;
				break;
			}
		}
		if (!merged)
			mergedRects.push_back(rect);
	}
	_result = std::move(mergedRects);
}

std::vector<cv::Rect> IntersectionProcessor::GetResult() const
{
	return _result;
}

void IntersectionProcessor::SetRectToProcess(std::vector<cv::Rect>&& rectsToMerge)
{
	_result = std::move(rectsToMerge);
}
