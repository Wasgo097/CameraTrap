#pragma once
#include "Interfaces/IProcessor.h"
#include "Utilities/Objects.h"
#include "Settings/MoveDetectorProcessorSettings.h"
class IntersectionProcessor;
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
	bool _enableProcess{ false };
	std::shared_ptr<IntersectionProcessor> _intersectionProcessor;
	cv::Mat _differenceMatBuffer;
	Objects _result;
	std::vector<std::vector<cv::Point>> _contours;
	std::vector<cv::Rect> _tempObjects;
	MoveDetectorProcessorSettings _settings;
};

