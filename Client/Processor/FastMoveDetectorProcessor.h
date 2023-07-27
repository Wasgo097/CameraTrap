#pragma once
#include "Interfaces/IProcessor.h"
#include "ProcessorStructs.h"
class FastMoveDetectorProcessor :public IProcessor <MoveDetectionResult, DifferenceResult>
{
public:
	FastMoveDetectorProcessor();
	void SetInput(DifferenceResult input) override;
	MoveDetectionResult Process() override;
	void Notify(DifferenceResult param) override;
protected:
	std::vector<cv::Point> _whitePixels;
	MoveDetectionResult _result;
	cv::Mat _differenceInput;
};