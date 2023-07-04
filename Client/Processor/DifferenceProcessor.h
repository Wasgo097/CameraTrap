#pragma once
#include "Interfaces/IProcessor.h"
#include "Interfaces/IFrame.h"
#include "ProcessorStructs.h"
#include "Settings/DifferenceProcessorSettings.h"
class DifferenceProcessor :public IProcessor<DifferenceResult, std::shared_ptr<IFrame>>
{
public:
	DifferenceProcessor(DifferenceProcessorSettings settings);
	void SetInput(std::shared_ptr<IFrame> input) override;
	void Process() override;
	DifferenceResult GetResult()const override;
protected:
	DifferenceProcessorSettings _settings;
	std::shared_ptr<IFrame> _pCurrentImage;
	std::shared_ptr<IFrame> _pPreviousImage;
	cv::Mat _currentMat;
	cv::Mat _previousMat;
	cv::Mat _difference;
	cv::Mat _treshold;
};