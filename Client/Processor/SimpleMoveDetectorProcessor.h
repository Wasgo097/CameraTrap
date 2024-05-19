#pragma once
#include "Interfaces/IProcessor.h"
#include "ProcessorStructs.h"
#include "Settings/SimpleMoveDetectorProcessorSettings.h"
class SimpleMoveDetectorProcessor :public IProcessor <MoveDetectionResult, DifferenceResult>
{
public:
	SimpleMoveDetectorProcessor(SimpleMoveDetectorProcessorSettings settings);
	void SetInput(DifferenceResult input) override;
	MoveDetectionResult Process() override;
	void Notify(DifferenceResult param) override;
protected:
	void ClearInternalBuffers();

	SimpleMoveDetectorProcessorSettings _settings;
	MoveDetectionResult _result;
	std::vector<std::vector<cv::Point>> _contours;
	std::vector<cv::Rect> _tempObjects;
	cv::Mat _differenceInput;
};

