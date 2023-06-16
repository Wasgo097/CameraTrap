#pragma once
#include "Interfaces/IProcessor.h"
#include "Utilities/Objects.h"
#include "Settings/MoveDetectorProcessorSettings.h"
class MoveDetectorProcessor :public IProcessor <Objects>
{
public:
	MoveDetectorProcessor(MoveDetectorProcessorSettings settings);
	void SetNewDifferenceMat(const cv::Mat& differenceMat);
	// Inherited via IProcessor
	void Process() override;
	Objects GetResult() const override;
protected:
	void ClearInternalBuffers();
	void ManageTempObjects();
    std::vector<cv::Rect> MergeIntersectedRects(const std::vector<cv::Rect>& rects);
	bool _enableProcess{ false };
	cv::Mat _differenceMatBuffer;
	Objects _objects;
	std::vector<std::vector<cv::Point>> _contours;
	std::vector<cv::Rect> _tempObjects;
	MoveDetectorProcessorSettings _settings;
};

