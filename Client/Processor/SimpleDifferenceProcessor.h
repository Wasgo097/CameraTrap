#pragma once
#include "Interfaces/IProcessor.h"
#include "ProcessorStructs.h"
#include "Settings/SimpleDifferenceProcessorSettings.h"
class SimpleDifferenceProcessor :public IProcessor<DifferenceResult, LowBrightnessCompensationResult>
{
public:
	SimpleDifferenceProcessor(SimpleDifferenceProcessorSettings settings);
	void SetInput(LowBrightnessCompensationResult input) override;
	DifferenceResult Process() override;
	void Notify(LowBrightnessCompensationResult param) override;
protected:
	SimpleDifferenceProcessorSettings _settings;
	LowBrightnessCompensationResult _input;
	DifferenceResult _result;
	cv::Mat _currentMat;
	cv::Mat _currentMatWithBlur;
	cv::Mat _previousMat;
	cv::Mat _previousMatWithBlur;
	cv::Mat _difference;
};