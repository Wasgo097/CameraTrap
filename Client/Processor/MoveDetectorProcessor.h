#pragma once
#include "Interfaces/IProcessor.h"
#include "ProcessorStructs.h"
#include "Settings/MoveDetectorProcessorSettings.h"
class MoveDetectorProcessor :public IProcessor <MoveDetectionResult, DifferenceResult>
{
public:
	MoveDetectorProcessor(MoveDetectorProcessorSettings settings);
	void SetInput(DifferenceResult differenceMat) override;
	MoveDetectionResult Process() override;
	void Notify(DifferenceResult param) override;
protected:
	void ClearInternalBuffers();
	void ManageTempObjects();

	MoveDetectorProcessorSettings _settings;
	cv::Mat _differenceMatBuffer;
	MoveDetectionResult _result;
	std::vector<std::vector<cv::Point>> _contours;
	std::vector<cv::Rect> _tempObjects;
};

