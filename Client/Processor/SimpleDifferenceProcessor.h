#pragma once
#include "Interfaces/IProcessor.h"
#include "Interfaces/IFrame.h"
#include "ProcessorStructs.h"
#include "Settings/SimpleDifferenceProcessorSettings.h"
class SimpleDifferenceProcessor :public IProcessor<DifferenceResult, std::shared_ptr<IFrame>>
{
public:
	SimpleDifferenceProcessor(SimpleDifferenceProcessorSettings settings);
	void SetInput(std::shared_ptr<IFrame> input) override;
	DifferenceResult Process() override;
	void Notify(std::shared_ptr<IFrame> param) override;
protected:
	SimpleDifferenceProcessorSettings _settings;
	std::shared_ptr<IFrame> _pCurrentImage;
	std::shared_ptr<IFrame> _pPreviousImage;
	cv::Mat _currentMat;
	cv::Mat _previousMat;
	cv::Mat _difference;
	cv::Mat _treshold;



};