#pragma once
#include "Interfaces/IProcessor.h"
#include "ProcessorStructs.h"
#include "Settings/MoveDetectorProcessorSettings.h"
class MoveDetectorProcessor :public IProcessor <MoveDetectionResult, DifferenceResult>
{
public:
	MoveDetectorProcessor(MoveDetectorProcessorSettings settings);
	void SetInput(DifferenceResult input) override;
	MoveDetectionResult Process() override;
	void Notify(DifferenceResult param) override;
protected:
	void ClearInternalBuffers();
	void ManageTempObjects();

	MoveDetectorProcessorSettings _settings;
	DifferenceResult _input;
	MoveDetectionResult _result;
	std::vector<std::vector<cv::Point>> _contours;
	std::vector<cv::Rect> _tempObjects;
};

