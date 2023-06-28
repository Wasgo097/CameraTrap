#pragma once
#include "Interfaces/IProcessor.h"
#include <vector>
#include <opencv2/core/core.hpp>
class IntersectionProcessor :public IProcessor<std::vector<cv::Rect>>
{
public:
	void SetRectToProcess(std::vector<cv::Rect>&& rectsToMerge);
	void Process() override;
	std::vector<cv::Rect> GetResult() const override;
protected:
	std::vector<cv::Rect> _result;
};

